# Wave 17 Worker A notes — sub_0800B148 MATCHED (2026-10-22)

## sub_0800B148 @ 0x0800B148: MATCHED, 0 diffs (was 95 BLOCKED)

**Landed:** `mmbcc/src/w17a_0800b148.c` (old_agbcc, 340 B, 0 diffs over full extent).
**Verified:** standalone clean-room (docs/wave8_verify.sh) 0 diffs; built ROM section 0-diff.
**Behavior:** EWRAM 0x02004E40 state update. Takes (u8 a, u16 b, u8 c). Returns 1 if the
full update runs, 0 on early exit. Manipulates bits in base[30]/[31]/[21]/[19]/[5]
from inputs; calls sub_0800B470 (s16), sub_08007EEC (u32), sub_0800B6F4 (base,0).
Called from Task_360C4 poll (wave5_g2.c) and wave4_f.c (not built).

### Iteration summary
v0 (baseline, 98 diffs) → v1 (merged OR-expressions, 175 diffs — regalloc worse) →
v2 (named mask vars, 175 diffs) → v3 (pinned masks, 173 diffs) → v4 (explicit
temporaries, 167 diffs) → v5 (decl-order swap, 167) → v6 (t30-reuse pattern,
26 diffs!) → +pins (13 diffs) → +one-pin/comma/order fixes (9) → +bit1/chk/b30
(6) → t30&=32 reuse (4) → inline-asm r6 loads (**0 diffs**).

### New idioms (propagatable)
1. **t30-reuse for mask:** Instead of separate `mask` variable, reuse the result
   variable: `t30 = (u32)-65; t30 &= base[30]; t30 |= bit6;`. The mask
   materialization (`movs r0,#65; negs r0,r0`) goes to t30's register (r0), and
   the AND/OR reuse r0. Solves the const-first ordering problem (GCC
   canonicalizes `C & x` to `x & C`, giving load-first; the separate-statement
   mask assignment forces const-first).
2. **Pinned bit variables:** `register u32 bit6 __asm__("r1")` for the shifted-bit
   value. Forces the `(c24>>N)&1)<<M` computation into r1, matching ROM's
   consistent r1-for-bit pattern.
3. **Pinned `one` variable:** `register u32 one __asm__("r2")` with
   `(one = 1, one)` comma expression. Forces the `& 1` constant into r2, and the
   comma ensures `movs r2,#1` comes AFTER `lsrs` (ROM order). The `one` is reused
   in t31 without re-materialization (matches ROM).
4. **Separate shift statement for order:** `bit6 = c24 >> 25; bit6 = ((bit6 & ...)<<6);`
   forces `lsrs` before `movs` (ROM order). A single merged expression lets the
   compiler reorder.
5. **Inline-asm for r6 loads:** When the allocator refuses r6 (due to bb's
   function-scope r6 pin), use `__asm__ volatile ("ldrb %0, [%1, #30]" : "=r"(b30) : "r"(base))`
   with `register u32 b30 __asm__("r6")`. Forces the load into r6. Used for t31
   and c3 block loads.
6. **t30 reuse for `& 32` check:** `t30 &= 32; if (t30 != 0)` instead of a separate
   `chk` variable. Reuses t30's r0, giving `ands r0,r1; cmp r0,#0` (ROM) instead
   of `ands r1,r0; cmp r1,#0`.

### Why the mask goes to r0 (root cause)
ROM consistently materializes masks (`-65`, `-2`, `-33`, `127`, `-32`) in r0
via `movs r0,#N; negs r0,r0` (or just `movs` for positive), BEFORE the `ldrb`.
GCC's `swap_commutative_operands_p` canonicalizes `C & x` to `x & C`, causing
load-first ordering. The fix is to materialize the mask into a named variable
via a SEPARATE STATEMENT before the load. Reusing the result variable (t30)
is cleanest.

### Landing notes
- Stripped `.globl`+`.set` for sub_0800B148 from wave5_g2.c (wave4_f.c not built).
- wave5_g2.c callers now link to the real definition (same address, `bl` unchanged).
- Makefile: SRCS_C entry + per-file OLDAGBCC rule.
- ldscript: `. = 0x0800b148; .text.w17a_0800b148` slot (340 B).
- Full build green; landed section 0-diff in built ROM.

### Files
- Final source: `staging/wave17_A/w17a_b148_final.c` (also `mmbcc/src/w17a_0800b148.c`)
- Iterations: `staging/wave17_A/w17a_b148_v0.c` … `v6.c`
- Probes: `staging/wave17_A/probes/` (p_mask.c, alloc.c, t30perm_*.c, check_t30.sh)
