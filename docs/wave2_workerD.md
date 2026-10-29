# Wave 2 worker D notes (2026-10-20)

Targets: sub_08004F18 (88B), sub_08004F80 (108B), sub_08006DD8 (88B).
Baseroom SHA-1 verified 72309736f3820470c6f372d6a05ad1f16bc5a946 before any byte trust.
Scratch: /tmp/wave2_D/. Ground truth: fn1_gt.bin (88B @0x4F18), fn2_gt.bin (108B @0x4F80), fn3_gt.bin (88B @0x6DD8).

## Fn1 = sub_08004F18 — proposed name: EntryMgr_Teardown

Behavior: base = (u8*)0x02003670. Calls sub_08004208(base+44), (base+0x264),
(base+0x49C); clears byte at 0x02005028; then if ((*(base+0x11AE) & 0xF8)==8)
calls the empty stub at 0x4F7C else calls 0x4F70 (which just bl's the empty
stub sub_080057FC). Both branch targets are effectively no-ops — looks like
vestigial hook slots. 88 callers, always paired with Fn2 (0x4F80) from the
same callers → teardown/setup pair for the 3-entry manager at 0x02003670.

Layout note: 88B span = body(58B) + pad(2B) + pool(16B: 02003670, 0000049C,
02005028, 000011AE) + tail(12B: beq-landing + epilogue). The bl targets
0x4F70/0x4F7C (helperA/helperB, only called from here) sit AFTER the span.

## Fn2 = sub_08004F80 — proposed name: EntryMgr_Setup

Behavior: base=(u8*)0x02003670, hp=*(u32*)0x020066F0. Calls sub_0800D568(*hp)
then sub_0800D59C(*hp) (D568 = linked-list teardown, 40 callers); sets
*(base+0x11AE) |= 2; if ((flag & 0xF8)==8) sub_080050E0(base) else
sub_08004FEC(base); then sub_0800419C(base+0x49C), (base+44), (base+0x264);
(*(u32*)base)++. Twin/variant of Fn1 confirmed: same base, same offsets
(44/0x264/0x49C/0x11AE), same flag check — Fn1 releases via 0x4208-family,
Fn2 re-inits via 0x419C-family and bumps the generation counter at [base].
108B span = code(46B) + pad + pool(02003670, 020066F0, 000011AE) + code(42B)
+ pad + pool(0000049C).

## Fn3 = sub_08006DD8 — proposed name: GatedDispatch_6E6C

Behavior: if (*(u8*)(0x02004830+0x265) != 0) return 0; else return
(u8)sub_08006E6C(0x02004830, p, (s16)(u16)a, (s16)(u16)b, (s8)(u8)c, (u8)d).
Flag-gated forwarder with u16->s16 / u8->s8 conversions; last two args go
on the stack (sub sp,#8). 88B span = code(66B) + pad(2B) + pool(02004830,
00000265) + tail(10B: return-0 block + epilogue). Called 77x mostly from
sub_080285C4 (table-driven dispatcher). Callee 0x6E6C also called from
0x6E30 and 0x7A2C.

## Attempts log

### Fn1 (0x08004F18) — MATCHED, 88/88 bytes, old_agbcc
Final C: /tmp/wave2_D/fn1.c (section .text.fn1). Verify:
`./mk.sh fn1 .text.fn1 0x08004F18 88 fn1_gt.bin sub_08004208=0x08004208 sub_080057FC=0x080057FC` with USE_OLD=1.
New idioms: (1) the two tiny callees take the base pointer as an ignored
arg — reproduces `adds r0, r4, #0` before each bl; (2) reusing one `u8 *p`
local for the 0x02005028 store AND the `base+0x11AE` computation forces the
ROM's `ldr r0`/`adds r1, r4, r0` register allocation (a fresh temp gives
`ldr r1`/`adds r0, r4, r1`); (3) `if ((...) != 8) HelperA(); else HelperB();`
emits `beq` to the out-of-line HelperB block after the pool, matching ROM
branch layout; (4) old_agbcc required: main agbcc schedules `ldrb` before
`movs r0, #248` (4-byte diff), old_agbcc emits ROM's `movs`-before-`ldrb`
— scheduler divergence between the two compiler variants, evidence = the
4-byte diff disappearing under old_agbcc with zero other changes.
Bonus: helper bytes 0x4F70–0x4F7E reproduce exactly (HelperA 10B, pad,
HelperB 2B); only the final section-end pad differs (GAS emits c046/nop,
ROM has 0000) — outside all target spans.

### Fn2 (0x08004F80) — MATCHED, 108/108 bytes, old_agbcc
Final C: /tmp/wave2_D/fn2.c (section .text.fn2). Verify:
`USE_OLD=1 ./mk.sh fn2 .text.fn2 0x08004F80 108 fn2_gt.bin sub_0800D568=0x0800D568 sub_0800D59C=0x0800D59C sub_080050E0=0x080050E0 sub_08004FEC=0x08004FEC sub_0800419C=0x0800419C`.
Twin of Fn1 confirmed (same base 0x02003670, same offsets, same flag idiom).
old_agbcc required for the whole TU: main agbcc misallocates the flag-pointer
(p in r2 vs ROM r1), emits `ldrb` before `movs r0,#2`, and uses r1 (not r2)
for the 0x264=153*4 materialization. old_agbcc reproduces all of it byte-exact
with the natural C — strong evidence the original TU was built with the
old_agbcc variant. Pool order (02003670, 020066F0, 000011AE) + (0000049C)
falls out of use order. `*p |= 2` with the shared `u8 *p` local reproduces
`ldrb r2,[r1] / orrs / strb` + reuse of r0 for the `& 0xF8` check (no reload).

### Fn3 (0x08006DD8) — MATCHED, 88/88 bytes, main agbcc
Final C: /tmp/wave2_D/fn3.c (section .text.fn3). Verify:
`./mk.sh fn3 .text.fn3 0x08006DD8 88 fn3_gt.bin sub_08006E6C=0x08006E6C`
(main agbcc — no old_agbcc needed for this TU).
Behavior: flag-gated forwarder. `u16 x=(u16)a; u16 y=(u16)b; u8 z=(u8)c;
u8 w=(u8)d;` locals reproduce the hoisted zero-extends (r1, r4, r5, r6);
`u8 *base=(u8*)0x02004830` → r7; arg0 spills to ip (r12) since r4-r7 are
taken; `if (*(base+0x265)) return 0;` reproduces the pool-pair
(02004830, 00000265) + `adds r0,r7,r2` (no folding — base is a register);
call args `(s16)x, (s16)y` → r2/r3 via asrs, `(s8)z` → str [sp,#0],
`w` → str [sp,#4] (sub sp,#8 frame); return `(u8)` → lsls/lsrs #24.
New idiom: 2-byte zero tail pad via `static const u8 sPad[2]` in the same
section — GAS ends a non-4-aligned code section with its nop fill (c046)
but the ROM has 0000 (original: `.align 2, 0` before the next function).
The pad bytes are inside the 88B span, so the section must carry them.
Pool (02004830, 00000265) sits mid-function before the out-of-line
`return 0` block — falls out naturally from the early-return shape.

## Final sources

### /tmp/wave2_D/fn1.c (old_agbcc, section .text.fn1, 88B @ 0x08004F18)
typedef unsigned char u8;
typedef unsigned int u32;

void sub_08004208(u8 *p);
void sub_080057FC(void);

static void HelperA(u8 *base);
static void HelperB(u8 *base);

__attribute__((section(".text.fn1")))
void EntryMgr_Teardown(void)
{
    u8 *base = (u8 *)0x02003670;
    u8 *p;
    sub_08004208(base + 44);
    sub_08004208(base + 0x264);
    sub_08004208(base + 0x49C);
    p = (u8 *)0x02005028;
    *p = 0;
    p = base + 0x11AE;
    if ((*p & 0xF8) != 8)
        HelperA(base);
    else
        HelperB(base);
}

__attribute__((section(".text.fn1")))
static void HelperA(u8 *base)
{
    (void)base;
    sub_080057FC();
}

__attribute__((section(".text.fn1")))
static void HelperB(u8 *base)
{
    (void)base;
}

### /tmp/wave2_D/fn2.c (old_agbcc, section .text.fn2, 108B @ 0x08004F80)
typedef unsigned char u8;
typedef unsigned int u32;

void sub_0800D568(u32 v);
void sub_0800D59C(u32 v);
void sub_080050E0(u8 *base);
void sub_08004FEC(u8 *base);
void sub_0800419C(u8 *p);

__attribute__((section(".text.fn2")))
void EntryMgr_Setup(void)
{
    u8 *base = (u8 *)0x02003670;
    u32 *hp = (u32 *)0x020066F0;
    u8 *p;
    sub_0800D568(*hp);
    sub_0800D59C(*hp);
    p = base + 0x11AE;
    *p |= 2;
    if ((*p & 0xF8) != 8)
        sub_08004FEC(base);
    else
        sub_080050E0(base);
    sub_0800419C(base + 0x49C);
    sub_0800419C(base + 44);
    sub_0800419C(base + 0x264);
    *(u32 *)base += 1;
}

### /tmp/wave2_D/fn3.c (agbcc, section .text.fn3, 88B @ 0x08006DD8)
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

u8 sub_08006E6C(u8 *base, void *p, s16 x, s16 y, s8 z, u8 w);

__attribute__((section(".text.fn3")))
u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d)
{
    u16 x = (u16)a;
    u16 y = (u16)b;
    u8 z = (u8)c;
    u8 w = (u8)d;
    u8 *base = (u8 *)0x02004830;
    if (*(base + 0x265) != 0)
        return 0;
    return (u8)sub_08006E6C(base, p, (s16)x, (s16)y, (s8)z, w);
}

/* 2-byte zero pad: ROM has 0000 here; GAS would otherwise end the section
   with its default nop fill (c046). */
__attribute__((section(".text.fn3")))
static const u8 sFn3Pad[2] = { 0, 0 };
