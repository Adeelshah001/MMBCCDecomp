# Wave 11 Worker D — Match Notes

**TAG=D — compiler-version forensics + blocked revisits**
**Date:** 2026-10-21
**Result: 1 MATCHED (sub_0803FACC), 6 blocked revisits documented**

---

## Part 1: sub_0803FACC Third-Compiler-Vintage Investigation

### Verdict: MATCHED — not a different-vintage function

The Wave-10 "likely compiled with a different compiler version" conclusion was
premature. All three reported codegen mismatches were solvable with
`old_agbcc`, once the true constant was identified. The function is landed in
`mmbcc/src/wave11_D_old.c` (section `.text.w11d_0803facc`, 76 B incl. trailing
pool), built via the standard Makefile `old_agbcc` rule, and the linked ROM
region `0x0803FACC[76]` is byte-identical to the baserom (verified by
`make mmbcc.gba` + region `cmp`).

### Correction 1: the constant is 0x2030, not 0x3020

The W10-L attempt used `0x3020`. The ROM pool bytes at `0x0803FB04` are
`30 20 00 00` = `0x00002030`. With the wrong constant, `old_agbcc`'s combiner
rewrote `0x3020` as `subs r0, #16` (0x3030−16) — reported as mismatch (3).
With the correct `0x2030` (0x3030−0x2030 = 0x1000, not an 8-bit immediate),
`old_agbcc` emits a literal pool `ldr` exactly like the ROM. **Mismatch (3)
was an artifact of the wrong constant, not a compiler difference.**

True accepted set: `{0x1030, 0x3030, 0x2030, 0x4030} ∪ [0x30, 0x36]`.

### Confirmed ROM disassembly (76 B @ 0x0803FACC, incl. pool word @ 0x0803FB14)

```
lsls r0, r0, #16        ; u16 arg normalize
lsrs r1, r0, #16        ; r1 = a
adds r2, r1, #0         ; r2 = b-copy of a   (mismatch 1 site)
movs r3, #0             ; r3 = ret
ldr r0, =0x1030
cmp r1, r0 / beq -> ret1
cmp r1, r0 / bgt -> big
cmp r1, #0x36 / bgt -> ret0
cmp r1, #0x30 / blt -> ret0   (mismatch 2 site)
b -> ret1
big: ldr r0, =0x3030
cmp r1, r0 / beq -> ret1
cmp r1, r0 / bgt -> huge
ldr r0, =0x2030                  (mismatch 3 site)
cmp r1, r0 / beq -> ret1
b -> ret0
huge: ldr r0, =0x4030
cmp r2, r0              ; uses the b-copy
bne -> ret0
ret1: movs r3, #1
ret0: adds r0, r3, #0
bx lr
.word 0x4030            ; trailing pool @ 0x0803FB14
```

Note: the func-list "72B" extent omits the trailing pool word; the true
codegen extent is 76 B (0x0803FACC–0x0803FB17). The ldscript slot places the
76-byte section; no other slot overlaps (nearest above is 0x0803FCC4).

### Per-attempt results

| # | Source variant | old_agbcc -O2 | Result |
|---|---|---|---|
| A | W10-L goto tree, 0x3020→0x2030 fixed, `-mthumb-interwork` | DIFF | 3 diffs: push{lr}/pop{pc} vs bx lr; b-copy elim + ret in r2; cmp #47/ble vs cmp #48/blt |
| A2 | Same, no interwork flag | DIFF | agbcc still push{lr}; old_agbcc bx lr. Remaining: b-copy elim, #47/ble fold |
| B | A2 + `asm("" : "+r"(b))` right after `int b = a` + `int lo = 0x30; if (a < lo)` | DIFF (2 halfwords) | b-copy KEPT, `cmp r1,#0x30; blt` EMITTED — but a→r2, b→r1 (register swap) |
| C | B with barrier moved to just before `huge:` (`if (b != 0x4030)`) | **IDENTICAL (76 B)** | a→r1, b→r2, all compares/pools/branches match |
| H | C with `int b = chip` (copy from arg, not from a) | DIFF | allocation swap again (a→r2) |
| — | C source, old_agbcc -Os | **IDENTICAL (76 B)** | -Os also matches |
| — | C source, old_agbcc -O1 | DIFF | different allocation (early cmps use r2) |
| — | C source, old_agbcc -O0 | DIFF | 180 B stack frame |
| — | C source, main agbcc -O2 (incl. -mno-thumb-interwork) | DIFF | agbcc ALWAYS emits push{lr}/pop{pc} here → excluded |

### Mismatch-by-mismatch resolution

1. **b-copy `adds r2, r1, #0` eliminated / ret in r2 not r3.** Defeated with an
   empty read/write asm barrier on `b` placed at its single use site
   (`huge:`). The barrier blocks copy propagation, so the `b = a` copy
   materializes as `adds r2, r1, #0` at the top; with `b` occupying r2, the
   return accumulator naturally goes to r3. Barrier placement matters: early
   placement (right after `int b = a`) swaps allocation (a→r2); late placement
   (at use) gives the ROM allocation. No code emitted by the barrier.
2. **`cmp r1, #0x30; blt` vs `cmp r1, #0x2F; ble`.** The fold `a < 0x30` →
   `a <= 0x2F` happens in the C frontend at ALL -O levels (verified at -O0:
   still `cmp #47`), so no -O flag defeats it. Defeated by declaring
   `int lo = 0x30;` and writing `if (a < lo)`: the frontend sees a
   non-constant comparison (no fold); RTL constant propagation substitutes
   30 after the tree fold, and the backend emits `cmp r1, #0x30; blt`. The
   variable disappears entirely (no stack/register traffic at -O2/-Os).
   (`a > 0x36` is NOT folded by these compilers — `cmp #54; bgt` matches
   as-is.)
3. **Pool `ldr` for 0x2030 vs `subs r0, #16`.** Resolved by Correction 1:
   with the true constant, old_agbcc emits the pool load.

### Landed source (mmbcc/src/wave11_D_old.c)

```c
u8 IsSpecialChip_3FACC(u16 chip)
{
    int a = chip;
    int b = a;
    int lo = 0x30;
    u8 r = 0;
    if (a == 0x1030) goto yes;
    if (a > 0x1030) goto big;
    if (a > 0x36) goto no;
    if (a < lo) goto no;
    goto yes;
big:
    if (a == 0x3030) goto yes;
    if (a > 0x3030) goto huge;
    if (a == 0x2030) goto yes;
    goto no;
huge:
    asm("" : "+r" (b));   /* keep the b-copy alive in r2 */
    if (b != 0x4030) goto no;
yes:
    r = 1;
no:
    return r;
}
```

Needs `old_agbcc` (main agbcc cannot emit the `bx lr` epilogue for this
shape). Makefile rule + ldscript slot added; `make mmbcc.gba` green;
region diff clean. Full-ROM `compare` still fails (partial build — expected).

### New idioms discovered

- **Late empty-asm copy barrier:** `asm("" : "+r" (b));` at the variable's
  single late use keeps an otherwise copy-propagated `adds` at the top of the
  function. Placement affects allocation: late placement preserved ROM
  register assignment where early placement swapped it.
- **Variable-constant anti-fold:** `int lo = 0x30; ... if (a < lo)` defeats
  the frontend `x < C` → `x <= C-1` fold while still emitting an immediate
  compare (constant propagates in RTL after the tree fold). Generalizes the
  "split-adds anti-folding" family to comparisons.
- **Pool-word verification first:** when a combiner rewrites a constant
  (`subs r0, #16` ⟸ 0x3030−16), check the ROM pool bytes before concluding
  a compiler difference — the attempt's constant may be wrong.
- **True extent includes trailing pool:** func-list sizes can omit the
  trailing literal pool word; always verify `ldr` targets land inside the
  compared extent (here 76 B, not 72 B).

---

## Part 2: Blocked-revisit log

All revisits use `staging/wave11_D/retry.sh` (old_agbcc -O2
-mthumb-interwork, disassembly diff). None of the six landed; precise
residual diffs recorded in `docs/wave11_D_results.tsv`.

### B2. sub_08004398 (80 B) — LICM, likely different-vintage
ROM keeps stride re-extension (`lsls`/`asrs`) and the `0xFFFF0000` pool load
INSIDE the fixed-point countdown loop; old_agbcc hoists both at -O1 and -O2.
No source formulation defeats LICM without changing emitted code; -O0 is
unusable (stack frame). **Recommendation:** keep BLOCKED; revisit only if a
third compiler vintage (e.g. gcc 2.7.2, weaker LICM) becomes available.

### B3. sub_080244B0 (76 B) — r4 + b-copy
Pinning `tbl` to r4 reproduces `push {r4,lr}` and the r4 table base
(first 3 instructions match), but the `u16 b = a` copy (`adds r3, r2, #0`)
is eliminated; adding the empty-asm barrier keeps a copy but as
`adds r2, r3, #0` after the `c` normalize with `a` in r3 — an r2/r3 role
swap. **Residual:** single allocation swap. Needs an idiom to force
`a`→r2 / `b`→r3 with the copy at the top.

### B4. sub_08011DB0 (28 B) — r0/r1 compare registers
Goto form yields the ROM branch shape (`bhi` / `bne`); using the existing
`extern u8 gEwram02005260[]` (defined in wave3_d.c — no new `.set`) plus
`p += 8` fuses to the ROM's `ldr r0, [r0, #8]`. Blocker: `idx` normalizes to
r1 (`lsrs r1, r0, #16`, copy eliminated); ROM has `lsrs r0, r0, #16` +
`adds r1, r0, #0` with compares on r0. Barrier on `idx` forces the copy but
swapped (`adds r0, r1, #0`). **Residual:** r0/r1 compare-register swap.

### B5. sub_0804D7A0 (30 B) — allocation + dead init + section padding
10 variants. Best: pin `p`→r1, split dead `v`/`w`, pin dead-init `z`→r2 and
`w`→r0 → 28/30 bytes byte-identical; only `movs r2, #0` (dead init)
missing. A volatile asm keeps the init but the assembler pads the 30-byte
section to 32 B with `mov r8, r8` (ROM has 2 zero bytes; next function at
0x0804D7C0). Section-alignment padding is the landing blocker. **Residual:**
2 bytes (dead-init keep + padding). Closest approach of the six.

### B6. sub_0802518C (34 B) — r2/r3 role swap
Decoder bug fixed en route (`0x8812` = `ldrh`, not `ldr` — format-12 vs
format-11 disambiguation). ROM: `off` in r3 via pool `ldr r3, =0x13A4`,
`ldrh`/`strh` accesses. Compilers put `off` in r2, temp in r3 across all
tried types (u16/u32/int), decl orders, named-temp, and pointer-arithmetic
forms. Pinning `off`→r3 forces `ldr r2, =0x13A4; adds r3, r2, #0` (extra
copy). **Residual:** pure r2/r3 role swap, resistant.

### B7. sub_0802D8F4 (50 B) — allocation + constant materialization
Forcing `off = 168 * 2` reproduces ROM's `movs r3, #0xA8; lsls r3, #1`
(vs combiner's `392-56`); 393 correctly comes from a pool `ldr`.
Blocker: `p` allocates to r1 (ROM: r2); pinning `p`→r2 backfires
(`adds r1, r0, #0; adds r2, r1, #0`, 56 B). **Residual:** r1/r2 swap.

### Script_StepState-adjacent blockers (0x0803Exxx)
Surveyed: Task_3E144 (whole-function allocation), sub_0803FBCC / sub_0803FE44
(188 B / 174 B, not attempted in depth), sub_0803F998 / sub_0803F920 (not
attempted in depth), sub_0803FB9C / sub_0803FC8C (mid-function pool in dead
code deleted by GCC). None presented a single-idiom gap; left for future
waves. (sub_0803FACC itself, the adjacent target, is now matched.)

---

## Recommendations

1. **Allocation-swap family (B3/B4/B5/B6/B7):** five blockers share one root
   cause — our compilers assign r1/r2/r3 roles differently than the ROM's
   vintage. A dedicated "allocation-forcing" investigation (e.g. dummy
   live-range injection, or finding which gcc 2.x sub-version matches the
   ROM's allocator) could unblock several at once. The pinned-register idiom
   works for single registers but perturbs neighbors.
2. **B2 (LICM):** needs a weaker-LICM vintage; do not burn more source-level
   attempts.
3. **B5 padding:** if a future idiom reproduces the 30 bytes, land it as a
   30-byte section — verify the assembler does not pad (needs
   2-byte-aligned section or explicit handling).
4. **Decoder:** `staging/wave11_D/thumb1.py` now correctly disambiguates
   Thumb format 11 (word/byte, `hw>>13 == 0b011`) from format 12 (halfword,
   `hw>>12 == 0b1000`); the old broad check misdecoded `ldrh`/`strh` as
   `ldr`/`str`. Recommend replacing ad-hoc decoders with this fixed one.
5. **Count update:** 429/1674 C-matched (was 428), 442 byte-identical total.

## Staging
All attempt sources, scripts, and disassembly diffs kept under
`~/workspace/mmbcc-decomp/staging/wave11_D/` (never delete).
Key files: `facc_c.c` (matched source), `facc_c.s`/`facc_c.bin`,
`try1.sh`/`tryfacc2.sh`/`retry.sh` harnesses, `thumb1.py` decoder,
`b5_v*.c`/`b6_v*.c`/`b7_v*.c`/`b4_v*.c`/`b3_v*.c` attempt series.
