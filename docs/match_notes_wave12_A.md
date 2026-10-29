# Wave 12 Worker A (TAG=A) — Task_3AFFC Callees — Match Notes

Worker: Wave 12 specialist (TAG=A). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}`; `arm-none-eabi` 2.42 (present).
Harness: `staging/wave12_A/mk.sh` (adapted from wave10_T; hardened non-empty
assertions, file offset = addr − 0x08000000, full extent incl pools, `cmp -l`).
Staging: `~/workspace/mmbcc-decomp/staging/wave12_A/` (NEVER delete).
Results: `docs/wave12_A_results.tsv`.

**Result: 0 MATCHED, 4 BLOCKED.** All four targets have precise blockers
documented below. The most valuable finding is the BEE0 prologue breakthrough
(byte-exact via widened params); the remaining blockers look like systematic
compiler-version differences (register allocation preferences, a `|0x80`
neg-fold our compilers do that the ROM's compiler did not).

## Target 1: sub_0800BEE0 @ 0x0800BEE0 (100 B) — BLOCKED

Best: v11 (47 diffs, 96 B) / v12 (56 diffs, 100 B, **prologue byte-exact**).

### Prologue breakthrough (v9/v10/v12)

With `(u16 a, u8 b)` params, both agbcc and old_agbcc emit b's `lsl r1,#24`
BEFORE a's `lsl r0,#16` whenever a shifted copy (`a32 = (u32)a << 16`) exists,
and shift a back too early otherwise. Fix: declare params as `(u32 a, u32 b)`
(logical types `(u16,u8)` in comment) and truncate explicitly in statement order:

```c
void sub_0800BEE0(u32 a, u32 b)   /* logical: (u16 a, u8 b) */
{
    register u32 a32 __asm__("r0");          /* optional; unpinned also works */
    register u8 b3 __asm__("r3");
    register u8 b5 __asm__("r5");
    register u16 aa __asm__("r4");
    register u8 *base __asm__("r2");
    register u16 v __asm__("r6");
    register u32 vs __asm__("r1");
    u32 a32n;
    ...
    a32n = a << 16;                          /* lsl r0,r0,#16 */
    b3 = (u8)((b << 24) >> 24);              /* lsl r1,#24; lsr r3,r1,#24 */
    b5 = b3;                                 /* add r5,r3,#0 */
    base = (u8 *)0x02004F40;                 /* ldr r2,[pc] */
    aa = (u16)(a32n >> 16);                  /* lsr r4,r0,#16 */
    v = *(u16 *)(base + 20);                 /* ldrh r6,[r2,#20] */
    vs = (u32)v << 16;                       /* lsl r1,r6,#16 (vs pinned r1) */
    if (vs == a32n)                          /* cmp r1,r0; beq */
        return;
```

This reproduces ROM bytes 0–17 exactly, including `push {r4,r5,r6,lr}` and the
shifted compare. Notes:
- `(u8)((b << 24) >> 24)` is required: plain `(u8)b` on a u32 param collapses
  to `add r3,r1,#0` (no truncation!) in old_agbcc.
- Pinning `vs` to r1 forces `lsl r1,r6,#16` (unpinnned gives in-place `lsl r6,r6`).
- `a32` need not be pinned; a natural `u32` keeps `lsl r0` first as long as it is
  the first statement. Pinning r0 also works but is unnecessary.

### Body blockers

1. **`|128` neg-fold (fatal).** ROM: `mov r0,#3; ldrb r1,[r2,#9]; and r0,r1;
   mov r1,#128; orr r0,r1; strb r0,[r2,#9]`. Our compilers turn
   `(base[9] & 3) | 128` into `| -128` (valid under u8 store truncation:
   `(x|0x80)&0xFF == (x|0xFFFFFF80)&0xFF`), emitting
   `mov r3,#128; neg r3; add r1,r3; orr`. Workaround that defeats it in isolation:
   `int o = 128; ... base[9] = t | o;` gives `mov r2,#128; orr` — but in full
   function context the compiler outsmarts it (`sub r0,r0,#10` to derive -7 from
   3, etc.). This looks like a genuine compiler-version difference: the ROM's
   compiler did not have this fold.

2. **Body register allocation.** ROM uses r0 as the accumulator
   (`mov r0,#7; neg r0; ldrb r6; and r0,r6`) with the loaded value in r1/r6.
   Ours uses r1 as accumulator with mask in r3. Mask-first int temps
   (`int m = -7; int v = base[10]; base[10] = v & m;`) give the right
   mask-before-load ORDER and the `mov+neg` idiom, but not ROM's registers.

3. **Crossjump shape.** ROM's if-branch `base[10] &= -7` ends with `b` to the
   shared final `strb r0,[r2,#10]`, skipping the else's `mov r1,#4; orr r0,r1`.
   Achievable when if/else share temp structure (v10/v12 did this), but it
   interacts with (2).

Staging: `w12a_0800bee0_v1.c` … `v14.c`; best prologue in v12, best diff in v11.

## Target 2: sub_080241F8 @ 0x080241F8 (176 B) — BLOCKED

Best: v3/v7 (49 diffs, 176/176 B, main agbcc; old_agbcc 53 diffs).

### Control-flow correction

W10 notes had case 2 wrong. ROM:
```
ands r1,r0(=a,0xFFF); cmp r1; bne -> 26554-call
  (==0): p-call; b join
  (!=0): ldr r0,=0x020070A8; bl 0x08026554; join
join: lsls r0,#24; lsrs r0,#24; epilogue
```
So case 2 is if/else-return, NOT if-then-fallthrough:
```c
case 2:
    if ((aa & 0xFFF) == 0) {
        p = *(u8 **)0x020070A4;
        return (u8)GetByte1_25A08(p + p[432] * 144);
    }
    return (u8)GetByte1_26554((void *)0x020070A8, aa & 0xFFF);
```
The 26554 call passes `aa & 0xFFF` in r1 **via CSE**: r1 already holds it from
the `ands`, so the compiler emits just `ldr r0; bl`. Declaring the callee as
`(void*, u32)` avoids a spurious s16 conversion (`asr r1,r1,#16`); the real
callee signature is `(void*, s16)` (GetByte1_26554, MATCHED in wave11_B).

### Prologue blocker (fatal)

ROM:
```
push {lr}
lsls r0, r0, #16
lsrs r0, r0, #16      ; in-place
cmp r0, #0
beq default
lsrs r1, r0, #12     ; r1 = a>>12
cmp r1, #2; ...
```
Ours (all variants):
```
lsl r0, r0, #16
lsr r2, r0, #16      ; cross-register (r2 or r1, never r0)
cmp r2, #0
...
lsr r0, r0, #28      ; fused shift instead of lsr r1,r0,#12
```
Tried: natural `(u16 a)`, `u16 aa = a`, pinned `register u16 aa __asm__("r0")`
(worse: 152 diffs, extra moves), self-assignment `a = (u16)a`, `(u32 a)` with
`a <<= 16; a >>= 16` (goes to r2), computing the switch value first. The
compiler always allocates the truncated u16 to r2/r1 and fuses `>>12` into
`>>28`. This is a register-allocation preference difference; the in-place
truncation is what a less smart scheduler would emit. The misallocation
cascades into case-body registers (p in r2 vs r0, etc.).

Also note: `(u8)` casts on the `GetByte1_25A08` returns are required — the ROM
truncates at the join (`lsls/lsrs #24`) even though the callee returns u8.

Staging: `w12a_080241f8_v1.c` … `v7.c`.

## Target 3: sub_08024384 @ 0x08024384 (174 B) — BLOCKED

Best: v1 (46 diffs, 176/174 B, main agbcc). Twin of 241F8; identical prologue
blocker. Differences vs 241F8 confirmed in ROM: `bl 0x08025A0C` (GetU8_0),
`bl 0x080265B0` (GetByte0_265B0, declared `(void*,u32)` for the caller),
`ldrb [r0,#0]` in cases 3/4 (vs `[r0,#1]`), `movs r0,#50` default (vs #200).
Staging: `w12a_08024384_v1.c`.

## Target 4: sub_0800B148 @ 0x0800B148 (340 B) — BLOCKED

Best: v1 (263 diffs, 268/340 B, old_agbcc). The 72-byte shortfall means the
control-flow structure is wrong, not just allocation.

Corrections to W10 notes from the ROM disassembly:
- Calls are `bl 0x0800B470`, `bl 0x08007EEC`, `bl 0x0800B6F4` — **not**
  0x0800800C. (0x08007EEC is unregistered; 0x0800B6F4 unregistered.)
- Prologue zero-extends b: `lsls r1,#16; lsrs r6,r1,#16`. The s16-ness appears
  only at the B470 call: `asrs r0,r3,#16` where r3 = b<<16 (hoisted).
  Signature `(u8,u16,u8)` + explicit `(s16)` cast at the call matches the
  prologue better than `(u8,s16,u8)`.
- Full control flow decoded (see staging notes): early `return 0` if
  `(base[4]&15)!=0`; `(base[4]&128)==0` branch sets base[19]/base[5] and joins;
  else-branch has the `(base[21]&15)` vs `a` decision tree with two sites
  writing `base[21]` in opposite operand order (`(15&v21)|(a<<4)` vs
  `(a<<4)|(15&v21)`); shared tail0 writes base[21]/+24/+30/+31 and returns 0;
  join block does the base[20]/base[30] bit shuffling, B470 call, conditional
  7EEC call, B6F4 call, clears base[9]/base[10], returns 1.
- Epilogue saves/restores r8,r9:
  `push {r4-r7,lr}; mov r7,r9; mov r6,r8; push {r6,r7}` … `pop {r3,r4};
  mov r8,r3; mov r9,r4; pop {r4-r7}; pop {r1}; bx r1`.
- Base pointer kept in two registers: r5 (early) and r9→r7 (late).

The v1 C (if/else + goto tail0/join) does not reproduce the ROM's block layout;
the compiler merges/reorders differently. This needs a ground-up reconstruction
with careful block-order control, likely multiple iterations.

Staging: `w12a_0800b148_v1.c`.

## New idioms / findings

- **Widened-param prologue control**: declaring `(u32,u32)` and shifting
  explicitly in statement order reproduces multi-param prologues byte-exactly
  when narrow params trigger prologue-reorder (BEE0). Caveat: `(u8)((b<<24)>>24)`
  needed — plain `(u8)b` on u32 collapses to a mov in old_agbcc.
- **`|0x80`-under-u8-store neg-fold**: our compilers rewrite `x | 128` (with
  u8 store) to `x | -128` via `mov+neg`; the ROM's compiler did not. Blocks
  BEE0 body. `int o = 128;` local defeats it in isolation but not in context.
- **Case-2 CSE call**: `GetByte1_26554(ctx, a&0xFFF)` needs no r1 setup — r1
  already holds `a&0xFFF` from the dominating `ands`.
- **Mask-first int temps** (`int m = -7; int v = base[i]; base[i] = v & m;`)
  reliably emit `mov #imm; neg; ldrb; and` in that order (BEE0 body).
- **B148 call-target correction**: 0x08007EEC, not 0x0800800C.

## What's still open

All four targets remain BLOCKED. Recommended next angles:
1. BEE0: the prologue is solved; the body needs a compiler that lacks the
   `|0x80` neg-fold, or a C shape that defeats it in full-function context.
   The `int o = 128` + shared-temp + mask-first combination (v14 direction)
   deserves 2–3 more iterations before declaring it a version difference.
2. 241F8/24384: the prologue in-place truncation (`lsr r0,r0,#16`) resists all
   tried shapes. A probe sweep over minimal `(u16 a)` functions with different
   body shapes may find the trigger; if none exists, it's a version difference.
3. B148: needs iterative block-layout reconstruction; consider transcribing the
   ROM to .s first to pin the exact CFG, then lifting to C.
4. 3AFFC itself remains blocked downstream of these four.
