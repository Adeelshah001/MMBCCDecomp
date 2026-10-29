# Wave 2 — Worker C notes (2026-10-20)

Worker: Phase-3 Wave-2 (caller-count order). Baserom SHA-1
`72309736f3820470c6f372d6a05ad1f16bc5a946` verified before any byte trust.
Toolchain: `~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/agbcc` (main),
`.../old_agbcc` (fallback). Exact rule per task brief (cpp → agbcc →
arm-none-eabi-as -mthumb -mcpu=arm7tdmi).

Scratch: `/tmp/wave2_C/` (all .c/.s/.o/.bin attempts).

## MATCHED (2/3)

### 1. Text_SelectBlobIdx @ 0x0804A378 — MATCHED (18/18)

**Bytes:** `b500 0400 0c00 f7b8 fe5d 0400 1400 bc02 4708` (18 B, 9 insns).

**Disassembly:**
```
push {lr}
lsls r0, r0, #16; lsrs r0, r0, #16   ; (u16)arg
bl 0x0800303C
lsls r0, r0, #16; asrs r0, r0, #16   ; (s16)result
pop {r1}; bx r1
```

**Behavior:** Forwards its u16 arg to `sub_0800303C` (which calls
`Text_SelectBlob(idx)` and returns the index), sign-extends the result.
Sampled callers (4/194: `0x0800EFF0`, `0x0800F5A2`, `0x0800F67A`,
`0x08011642`) ignore the return value — called for the blob-select side
effect. The `pop {r1}; bx r1` epilogue is agbcc's normal output for this
shape (cf. matched `Sram_Read`'s `pop {r0}; bx r0`).

**C** (`/tmp/wave2_C/text_selidx.c`, section `.text.text_selidx`):
```c
typedef unsigned short u16;
typedef signed short s16;
s16 sub_0800303C(u16 idx);

__attribute__((section(".text.text_selidx")))
s16 Text_SelectBlobIdx(u16 idx)
{
    return sub_0800303C(idx);
}
```

**Compiler:** main `agbcc`, `-O2 -mthumb-interwork`. First-try match —
the generated `.s` is instruction-identical to the ROM disassembly.

**Verification:**
- `arm-none-eabi-objcopy -O binary -j .text.text_selidx text_selidx.o
  text_selidx.bin` → first 18 bytes byte-identical to baserom at
  `0x4A378` (0 diffs).
- `bl` is a relocation in the `.o`; test-linked against a stub at
  `0x0800303C` → linked bytes `f7b8 fe5d` match ROM (target
  `0x0800303C`).
- **Landing note for coordinator:** GAS pads the section to 20 bytes
  (`.align 2`); the 2 trailing bytes are `c0 46` (nop) vs ROM `00 00`
  at `0x4A38A–0x4A38B`. The 18 function bytes are clean; the pad bytes
  sit in the gap before the (currently unlisted) function at
  `0x0804A38C`. `__attribute__((aligned(2)))` is rejected by this
  agbcc ("alignment may not be specified"), so the padding cannot be
  suppressed from C.

**Name rationale:** Text-blob selection wrapper returning the (signed)
index; mirrors the existing `Text_SelectBlob` naming.

---

### 2. Gfx_BlitRequest @ 0x08006A54 — MATCHED (76/76)

**Bytes:** 68 B code (`0x6A54–0x6A97`) + 8 B pool (`0x6A98–0x6A9F` =
`02004830 00000265`).

**Disassembly (key parts):**
```
push {r4-r7,lr}; sub sp,#8; mov ip,r0
ldr r0,[sp,#28]                       ; e (5th arg)
lsls r1,r1,#16; lsrs r1,r1,#16        ; b: u16
lsls r2,r2,#16; lsrs r4,r2,#16        ; c: u16 -> r4
lsls r3,r3,#24; lsrs r5,r3,#24        ; d: u8 -> r5
lsls r0,r0,#24; lsrs r6,r0,#24        ; e: u8 -> r6
ldr r7,[pc,#40]   ; =0x02004830 (ctx)
ldr r2,[pc,#44]   ; =0x265 (off)
adds r0,r7,r2; ldrb r0,[r0]; cmp r0,#0
bne skip                              ; if (*(u8*)(ctx+0x265)) return
lsls r2,r1,#16; asrs r2,r2,#16        ; (s16)b
lsls r3,r4,#16; asrs r3,r3,#16        ; (s16)c
lsls r0,r5,#24; asrs r0,r0,#24        ; (s8)d
str r0,[sp,#0]; str r6,[sp,#4]
adds r0,r7,#0         ; r0 = ctx
mov r1,ip             ; r1 = a
bl 0x08006AD8
skip: add sp,#8; pop {r4-r7}; pop {r0}; bx r0
```

**Behavior:** Guarded forwarder. If flag byte at `0x02004830+0x265`
(`=0x02004A95`) is nonzero, returns immediately; else calls
`sub_08006AD8(ctx, a, (s16)b, (s16)c, (s8)d, (u8)e)`. The s16/s16 pair
smells like X/Y coordinates; `a` (u32) is likely a src pointer. The
callee `sub_08006AD8` is also called by `Tilemap_DecodeBlit`
(`sub_0800695C`), suggesting a graphics/blit request path. Sampled
caller (`0x08026AC2`) passes small int args (1,1,8,…).

**C** (`/tmp/wave2_C/sub_08006A54.c`, section `.text.sub_08006A54`):
```c
typedef unsigned char u8; typedef signed char s8;
typedef unsigned short u16; typedef signed short s16;
typedef unsigned int u32;

__asm__(
    ".globl gReqCtx\n.set gReqCtx, 0x02004830\n"
);
extern u8 gReqCtx[];

void sub_08006AD8(u32 ctx, u32 a, s16 b, s16 c, s8 d, u8 e);

__attribute__((section(".text.sub_08006A54")))
void sub_08006A54(u32 a, u16 b, u16 c, u8 d, u8 e)
{
    u8 *ctx = gReqCtx;

    if (*(ctx + 0x265) != 0)
        return;
    sub_08006AD8((u32)ctx, a, b, c, d, e);
}
```

**Idiom used:** extern-absolute-symbol (from `match_notes_text.md`) for
the context pointer — keeps the two literal loads (`ldr r7`, `ldr r2`)
separate and in ROM order. A folded `0x02004830 + 0x265` would emit a
single pool entry; the split is required.

**Compiler:** main `agbcc`, `-O2 -mthumb-interwork`. First-try match —
instruction-identical including register allocation (`ip` for `a`,
`r7` for ctx across the branch) and pool order.

**Verification:**
- `.bin` (76 B) vs baserom at `0x6A54`: 0 diffs (bl bytes masked;
  they are a relocation).
- Test-linked against a stub at `0x08006AD8` → linked `bl` bytes
  `00f0 24f8` match ROM exactly.
- Section is exactly 76 B (multiple of 4); no padding issue.

**Name rationale:** Guarded graphics/blit request forwarder. Tentative —
semantics inferred from arg shapes (s16 x/y) and the shared callee with
`Tilemap_DecodeBlit`. Coordinator may rename.

---

## BLOCKED (1/3)

### 3. sub_0802D7A0 @ 0x0802D7A0 — BLOCKED

**Bounds:** 334 B code (`0x2D7A0–0x2D8ED`) + 4 B pool (`0x2D8F0` =
`0x000001B3` = 435). 159 `bl` callers. Leaf (no calls).

**Semantics (fully reverse-engineered, high confidence):**
```c
// 10 params: (u8 *work, u8 a1, u8 a2, u8 a3, u8 a4,
//             u16 a5, u16 a6, u16 a7, u8 a8, u8 a9)
if ((work[6] & 2) != 0 && (u8)(a8 - 106) > 3)
    return;                       // guard: skip entry if flag set and
                                  // a8 not in [106,109]
idx = work[5];                    // entry index (count)
e = work + idx*16 + 420;          // 16-byte entry base
e[0] = (e[0] & ~2)  | ((a1 & 1) << 1);
e[0] = (e[0] & 3)   | (a2 << 2);          // bits: b0 keep, b1=a1&1, b2-7=a2
e[4] = (e[4] & ~2)  | ((a3 & 1) << 1);
e[4] = (e[4] & 3)   | (a4 << 2);
e[4] |= 1;                                // net b0=1, b1=a3&1, b2-7=a4
*(u16*)(e+8)  = a5;   // +428
*(u16*)(e+10) = a6;   // +430
*(u16*)(e+12) = a7;   // +432
e[14] = a8;           // +434
e[15] = a9;           // +435 (via literal pool 0x1B3)
work[5]++;            // bump count
```
This is an "append 16-byte entry to a table" utility (likely
sprite/object/task attributes). The address `work+idx*16+420` is
recomputed before every store (work[5] reloaded via `ldrb` 10×); the
base offsets 420/424 are materialized as `(210<<1)`/`(212<<1)` etc. via
`movs`+`lsls`, while 435 comes from the literal pool. The constant 420
is CSE-kept in r4 across its two uses (likewise 424).

**Prologue (register homes):** `r7`=work, `r6`=(u8)a1, `ip`=(u8)a3,
`sl`=(u16)a7, `r8`=(u8)a8, `r9`=(u8)a9; `a2,a4`→`[sp,#0,#4]`,
`a5,a6`→`[sp,#8,#12]` (u16). Frame is `sub sp,#24` (8-byte aligned).

**Key compiler finding (new idiom):** The 24-byte frame is produced by
`old_agbcc` but NOT by main `agbcc` (which gives `sub sp,#20`). The
extra 4 bytes are dead stack (`[sp,#16]`, `[sp,#20]` never accessed) —
`old_agbcc` keeps the frame 8-byte aligned (32+24=56), main `agbcc`
does not (32+20=52). **This function was compiled with `old_agbcc`
(or equivalent).** All matching attempts below use `old_agbcc`.

**Blocking diff (precise):** The `& ~2` bit-clear. ROM does a full
32-bit `and` with `-3`, materialized as `movs r3,#3; negs r3,r3;
adds r0,r3,#0`, and CSE-keeps `-3` in r3 across both `~2` RMWs (second
use at `0x2D85C` is `ands r3,r5` with no rematerialization). Both
`agbcc` and `old_agbcc` narrow `x & ~2` to `x & 253` (`movs rN,#253`)
when the result feeds a `u8` store — a sound optimization the ROM's
build did not apply. Workarounds tried:
- `u32`/`int` temporaries for the mask (`int m = ~2;`, `u32 w = e[0];
  w = (w & ~2) | ...`) — avoids narrowing but the compiler then
  materializes `-3` via `sub r2,r2,#4` (reusing the `r2=1` register)
  instead of the ROM's fresh-register `movs r3,#3; negs`, and/or
  orders the `(a1&1)<<1` computation differently.
- Unsigned mask `0xFFFFFFFD` — still narrowed to 253.
- `&=`/`|=` compound form — generates shorter in-place RMW code,
  diverges structurally.
- Swapped `|` operand order, `u8 bit` temporaries, late mask
  assignment — all produce `sub`-based or early-hoisted
  materialization, never the ROM's exact 10-insn RMW sequence with
  its register choices (`r5=1`, `r6=a1&1`, `r2=(a1&1)<<1`,
  `r3→r0=-3`, `r6=e[0]` reload).

**Variants tried (~17):** plain recompute-everything; `u8 *e` local;
`u8 idx` + `u8 *e` locals; `u32`/`int` mask temporaries (early, late,
per-RMW, shared); unsigned mask; compound-assign form; swapped operand
order; `u8 bit` extraction first. Best (plain form, old_agbcc):
prologue (110 B incl. guard) byte-identical; body diverges from the
first RMW onward (213+ diff bytes). The pool word `0x1B3` is emitted
correctly in all variants.

**Status:** BLOCKED on the `~2`-without-narrowing + exact register
allocation. Functionally understood; needs either a new idiom for
suppressing the narrowing or acceptance as asm. Best scratch:
`/tmp/wave2_C/sub_0802D7A0.c` (+ variants `b`–`g`).

**Name proposal:** `Obj_AddEntry` (appends a 16-byte attribute entry;
tentative).

---

## New idioms / findings

1. **`old_agbcc` vs `agbcc` frame alignment:** `old_agbcc` rounds the
   local frame to keep the stack 8-byte aligned (`sub sp,#24` here);
   main `agbcc` does not (`sub sp,#20`). When a target's frame size
   mismatches by 4 with dead stack slots, try `old_agbcc` before
   inventing phantom locals. (This also retro-explains why
   `Text_SelectBlob` needed `old_agbcc` — register allocation — but
   frame size is a cheaper diagnostic.)
2. **`pop {r1}; bx r1` is ordinary agbcc output** for tiny forwarding
   functions (not hand-asm): `s16 f(u16 x) { return g(x); }` reproduces
   it exactly, first try.
3. **Narrowing hazard:** both compilers rewrite `u8var & ~2` to
   `& 253` when feeding a byte store. The ROM has two functions so far
   (`sub_0802D7A0` twice) using full `-3`; no clean C idiom found yet
   to suppress the narrowing while keeping ROM instruction order.
4. **Extern-absolute-symbol works for split base+offset literal loads**
   (reused from text notes): `*(ctx + 0x265)` with `ctx` from a `.set`
   symbol emits the two `ldr`s in source order.

## Verification commands (all run)

```bash
ROM=~/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba
AGBCC=~/workspace/mmbcc-decomp/mmbcc/tools/agbcc/bin/agbcc
# per function, e.g.:
cpp -I ~/workspace/mmbcc-decomp/mmbcc/include text_selidx.c -o text_selidx.i
$AGBCC -O2 -mthumb-interwork -Wimplicit -Wparentheses -o text_selidx.s text_selidx.i
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o text_selidx.o text_selidx.s
arm-none-eabi-objcopy -O binary -j .text.text_selidx text_selidx.o text_selidx.bin
python3 -c "compare text_selidx.bin vs ROM[0x4A378:0x4A378+18]"
# bl resolution verified by test-linking against stubs at the true
# targets (0x0800303C, 0x08006AD8) and comparing linked bytes.
```

## Files for coordinator landing

- `/tmp/wave2_C/text_selidx.c` → `Text_SelectBlobIdx` @ `0x0804A378`,
  section `.text.text_selidx`, compiler `agbcc`. MATCHED.
- `/tmp/wave2_C/sub_08006A54.c` → `Gfx_BlitRequest` @ `0x08006A54`,
  section `.text.sub_08006A54`, compiler `agbcc`. MATCHED.
- `sub_0802D7A0` — no landable C; see BLOCKED analysis above.
