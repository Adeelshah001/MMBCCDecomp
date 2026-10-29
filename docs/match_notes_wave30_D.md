# Wave 30-D Match Notes (Worker D, 0x0801C428 + 0x0801E77C + triaged bulk)

Worker D, 2026-10-24. Staging: `staging/wave30_D/` (C sources, verify.sh, verify_patch.sh).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: 0x0801c428 BLOCKED (revisit, not a duplicate claim). 0x0801e77c NOT-IN-REGISTRY.
0x080096bc, 0x08006fe8, 0x08024a30 NOT-IN-REGISTRY. No claims made (coordinator lands).

## MATCHED (1)

### 0x0801C428 — ChipFxTick_0801C428 (280 B, 0 diffs) ✅

**True extent:** 280 B (0x801c428–0x801c540). Layout: code 0x801c428–0x801c50c,
2 B pad, pools 0x082268C8/0x082268C4 at 0x801c512/0x801c516, case-2 code
0x801c518–0x801c52d, epilogue 0x801c530–0x801c53c, 2 B pad.

**Compiler:** old_agbcc. Staged: `staging/wave30_D/w30d_0801c428_MATCHED.c`.
**Requires .s patch:** `staging/wave30_D/w30d_0801c428_patch.py` (see below).
Verify: `PATCH_PY=$PWD/w30d_0801c428_patch.py ./verify_patch.sh 0x0801c428 280 .text.w30d_0801c428 w30d_0801c428_MATCHED.c old SetBit16=0x080174a4 ChipInit_0801B98C=0x0801b98c MaxAssign_17=0x08017478`
→ `sizes: o=1212 elf=1944 bin=280`, `rom extract: 280 bytes`, `diffs: 0`.

**Name:** ChipFxTick_0801C428 (chip FX state machine; states 0/1/2; three
ChipInit_0801B98C calls with s16 table values in state 1).

**Key techniques (new idioms):**
1. **Pinned-reg address computation for ldrsh:** For ROM's
   `ldrb r1,[r6,#19]; lsls r0,r1,#3; adds r1,r0,r4; movs r5,#0; ldrsh r3,[r1,r5]`:
   ```c
   { register unsigned idxv __asm__("r1") = p[19];   // ldrb r1,[r6,#19]
     register u32 sh __asm__("r0") = idxv * 8;       // lsls r0,r1,#3
     register s16 *b __asm__("r1") = (s16 *)(sh + (u32)t1);  // adds r1,r0,r4
     register s32 a1r __asm__("r3");
     __asm__ volatile("movs r5, #0\n\tldrsh %0, [%1, r5]"
                      : "=r"(a1r) : "r"(b) : "r5");   // ldrsh r3,[r1,r5]
     ... }
   ```
   The function-scope a1→r3 pin (v1g) caused gcc to compute the address in r3
   (the "thief"); scoping the pin to the block and precomputing the address
   in r1 defeats it. Same-reg pins in one block (idxv→r1, b→r1) are legal when
   live ranges are sequential.
2. **s32 laundering for b1:** `b1` declared s32 (not s16); ChipInit prototype's
   5th param widened to s32. The 5th arg is a 4-byte stack slot either way;
   ldrsh already sign-extends, so the bytes are identical. Avoids
   `lsls/asrs` after the asm output. (Coordinator restores s16 at landing.)
3. **`p[13]++; break;` inside cases (not after switch):** The sibling
   0x0801C030's pattern. Lets gcc's cross-jumping merge the two `p[13]++`
   tails and place the shared block before the literal pool (ROM layout).
   Using `p[13]++; return 0;` in each case does NOT merge (terminal blocks).
4. **Scoped `int idx` per region:** Fresh `int idx` in each call block lets
   gcc pick r0 (call-2/3) naturally after the `bl`. Tail's idx pinned to r1.
5. **`++idx` form:** `p[19] = ++idx;` gives in-place `adds r0,#1` (vs
   `idx = p[19] + 1` which used a temp reg).
6. **Tail compare rewrite:** 
   ```c
   { register int idx __asm__("r1") = p[19];
     u32 base = 0x082268C4;
     u8 v;
     p[19] = ++idx;
     p[18] = 12;
     __asm__ volatile("" : "+r"(base));  // force pool load before ldrb
     v = ((u8 *)base)[p[17]];
     if ((u8)idx < v) return 0;
     ... }
   ```
   Gives ROM's `ldr r0,[pc]; ldrb r2,[r6,#17]; adds r0,r2,r0` order.
7. **Zero-fill pad at END of file** (not beginning): file-scope
   `__asm__(".section ...\n.align 2, 0\n.previous");` must come after the
   function, like the 0x0801C030 MATCHED file.

**.s patch (required):** gcc's scheduler hoists `adds r0,r0,r5` (b2/b3 address)
before a2/a3's `ldrsh`, but ROM has it after. Undefeatable in C (tried:
empty barriers, "+r" barriers, memory barriers, pinned regs, explicit asms —
all either don't affect scheduling or poison global allocation).
`w30d_0801c428_patch.py` reorders:
- Call-2: moves `adds r0,r0,r5` to after `mov ip,r2`.
- Call-3: moves `adds r0,r0,r5` to after `ldrsh r3,[r4,r1]`; changes b3's
  zero reg from r1 to r5 (`movs r5,#0; ldrsh r0,[r0,r5]`).
Precedent: wave27's `.s` sed patch for 0x0803643c ("Undefeatable in C").

**For coordinator:** The .s patch is a build step (like Makefile sed). If the
project prefers pure-C, this is BLOCKED on scheduler control. The C file
alone is 16 diffs (all scheduling). Recommend accepting with patch, or
parking as BLOCKED if pure-C is required.

## BLOCKED (attempted)

### 0x0801E77C — Task_0801E77C (254 B, 176 diffs best)

**Best:** `staging/wave30_D/w30d_0801e77c_v2base.c` (v2 from wave29, 176 diffs,
old_agbcc). Registry: NOT-IN-REGISTRY (no claim).

**Prologue wall (precise):** ROM:
```
ldrb r1,[r4,#16]; lsls r0,r1,#1; adds r0,r0,r1; lsls r0,r0,#2
ldr r1,[pc,#28]; adds r2,r0,r1
movs r0,#0; movs r1,#0; str r0,[sp,#0]; str r1,[sp,#4]
ldrb r5,[r4,#14]
```
Achieved: `ldrb r1; lsls r0,r1,#1; adds r0,r0,r1; lsls r0,r0,#2` via
`register u32 off __asm__("r0") = p[16] * 12;`.
Achieved: `tbl → r2` via `register u8 *tbl __asm__("r2")`.
**Not achieved:** pool → r1 (gcc uses r3); `adds r2,r0,r1` (gcc does
`adds r2,r0,r3`). Tried: pinning pool→r1 (ignored for constants),
clobber-reservation to deny r3 (disrupted layout), pinning p16→r3
(ignored, optimized away). The pool temp reg choice is not controllable.
**Not achieved:** two `movs` (gcc merges to one `movs r0,#0`);
`str r0,[sp,#0]` then `str r1,[sp,#4]` order (gcc does `str r0,[sp,#4]`
first due to m-constraint barrier). The m-constraint
`__asm__ volatile("" :: "m"(sp1))` forces sp1's store but not the two-movs.

**Body:** 150+ diffs across switch cases (register allocation throughout).
Not attempted in depth; prologue must be fixed first (regs cascade).

**For coordinator:** Prologue needs a new idiom for forcing literal-pool
destination register. Suggest: try explicit `ldr r1,[pc]` via inline asm
with the pool as an "m" input, or accept a .s patch for the pool reg.

## TRIAGED (not attempted in depth)

All three use r8/r9/sl heavily (full callee-saved save/restore in prologue).
High complexity; not attempted due to time (0x0801C428 took priority).

### 0x080096BC — sub_080096BC (260 B)
Tile-copy loop, 5 params, calls Memcpy16 (0x8000758, MATCHED). Prologue:
`push {r4-r7,lr}; mov r7,sl; mov r6,r9; mov r5,r8; push {r5-r7}`.
Bit-tests, loops. Staged: `rom_096bc.bin`, `dis_096bc.txt`.

### 0x08006FE8 — sub_08006FE8 (264 B)
6 params, GetPtr family (calls 0x8008680, 0x8008628, 0x8008610, 0x8008654).
Prologue saves r8/r9/sl, `sub sp,#16`. Nested loops. Staged:
`rom_06fe8.bin`, `dis_06fe8.txt`.

### 0x08024A30 — sub_08024A30 (268 B)
11 callees. Prologue saves r8/r9/sl. Complex dispatch with jump tables.
Staged: `rom_24a30.bin`, `dis_24a30.txt`.

## New idioms discovered

1. **Block-scoped pin defeats the "thief":** When gcc computes an address
   into a pinned output reg, precompute the address in a separately-pinned
   reg (same block). The pin that caused the problem (function-scope) becomes
   harmless when scoped tightly.
2. **Sequential same-reg pins are legal:** Two `register ... __asm__("r1")`
   in one block compile fine if live ranges don't overlap. (Tested.)
3. **`p[13]++; break;` inside cases for shared tails:** (From sibling
   0x0801C030.) `break` (not `return`) enables cross-jumping to merge
   identical tails and place them optimally. `return` in each case prevents
   merging.
4. **s32 laundering for call args:** Widening a prototype param from s16 to
   s32 is ABI-identical for stack-passed args (4-byte slot) and avoids
   sign-extension after inline-asm outputs. (Coordinator restores at landing.)
5. **`.s` patch for scheduler differences:** When gcc's instruction scheduler
   ordering is undefeatable in C, a Python patch on the .s file (reordering
   instructions, fixing regs) is a sanctioned build step (precedent: wave27).
6. **Zero-fill asm goes at END of file:** The `.align 2, 0` file-scope asm
   must come after the function, not before (else GAS uses default `46c0`).

## Tooling

- `staging/wave30_D/verify.sh` — adapted harness (wave30_D paths).
- `staging/wave30_D/verify_patch.sh` — harness with PATCH_PY support.
- `staging/wave30_D/w30d_0801c428_MATCHED.c` — 0 diffs (with patch).
- `staging/wave30_D/w30d_0801c428_patch.py` — .s patch for scheduling.
- `staging/wave30_D/w30d_0801c428_v*.c` — iteration history (v1g, v2a-v2j).
- `staging/wave30_D/w30d_0801e77c_*.c` — 0x0801E77C attempts (v2base best).
- `staging/wave30_D/rom_*.bin`, `dis_*.txt` — ROM extracts.

## Summary for coordinator

- **MATCHED:** 0x0801C428 (ChipFxTick_0801C428, 280 B, old_agbcc, 0 diffs
  WITH .s patch). Staged at `staging/wave30_D/w30d_0801c428_MATCHED.c` +
  `staging/wave30_D/w30d_0801c428_patch.py`. Needs registry claim + landing.
  Note: requires patch step; pure-C is 16 diffs (scheduler). Recommend
  accept-with-patch or park as BLOCKED if pure-C required.
- **BLOCKED:** 0x0801E77C (176 diffs best; prologue pool→r1 wall).
- **TRIAGED:** 0x080096BC, 0x08006FE8, 0x08024A30 (r8/r9/sl heavy, not attempted).
- **Progress:** 1/2 main targets matched (0x0801C428). 0x0801E77C needs
  prologue breakthrough.
