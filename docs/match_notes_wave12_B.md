# Wave 12 Worker B — Allocation-Forcing Investigation

**Date:** 2026-10-21
**Target:** the r1/r2/r3 allocator-difference cluster (B3/B4/B5/B6/B7)
**Result: 4 MATCHED (B4, B5, B6, B7), 1 BLOCKED (B3)**

---

## Verdict: YES, there is a shared trick — pinned COPY registers

The systematic difference is **not** a different compiler vintage. All five
functions were matched (or nearly matched) with `old_agbcc` using one shared
idiom:

> **Pin the COPY to its ROM register with `register ... __asm__("rN")`.**
> This occupies the register from the top of the function, which forces the
> allocator to place the PRIMARY variable in-place (reusing the argument
> register) or in the remaining free register — exactly the ROM's allocation.

Why it works: our compiler's allocator prefers to put a fresh `lsls`/`lsrs`
extension result into the next free low register (r1/r2/r3), while the ROM's
vintage reuses the argument register in-place and puts the copy in the fresh
register. By pinning the copy, the "fresh" register is already taken, so the
primary is forced in-place. The pin also blocks copy propagation (the copy
cannot be eliminated when its destination is pinned).

This is a genuine shared trick, not per-function work: B4, B6, and B7 all
fell to it directly. B5 used pinning plus a volatile keep. B3 gets the right
allocation from it but is blocked by scheduler ordering (see below).

### Supporting idioms (used alongside the pin)

- **Dummy live-range use:** `asm("" : : "r" (x));` after the last real use
  keeps `x` live, preventing the allocator from reusing its register as a
  scratch temp (B6: kept `off` in r3 so the `p+off` temp went to r2;
  B7: kept `p`/`t` live so the join accumulator went to r0, not r2/r3).
- **Volatile dead-init keep:** `asm volatile("" : "+r" (z));` retains a
  `movs r2, #0` that is otherwise dead (B5).
- **`.align 1` section fix:** GAS pads a section to its 4-byte alignment with
  `mov r8, r8`; changing the compiler-emitted `.align 2, 0` to `.align 1, 0`
  in the `.s` yields the exact ROM byte count for 30-B (B5) and 50-B (B7)
  sections. The linked ROM places the section at its absolute address anyway,
  so the alignment change is safe (GAS warns about PC-relative loads; the
  placed address is 4-aligned so loads are safe).

---

## Per-function results

### B4 @0x08011DB0 — MATCHED (32/32 B)

ROM wants: `lsrs r0, r0, #16` (in-place) + `adds r1, r0, #0` (copy), compares
on r0, `ldr r0, [r0, #8]` fusion for `p += 8`.

Decisive source (`staging/wave12_B/b4_v22.c`):
```c
u8 TblByte_11DB0(u16 idx)
{
    u16 a = idx;
    register u16 c __asm__("r1") = a;   /* pin the COPY */
    u8 *p; u8 *base;
    if (a > 7) goto ret0;
    if (a != 0) goto main;
ret0:
    return 0;
main:
    p = gEwram02005260;
    p += 8;
    base = *(u8 **)p;
    return base[c];
}
```
Pinning `c`→r1 forces `a`'s extension in-place into r0. The `p += 8` fuses to
`ldr r0, [r0, #8]` only with the `extern` (absolute `.set`) symbol — a literal
`0x02005260` constant-folds the +8 into the pool. The pool word is a
`R_ARM_ABS32` reloc to `gEwram02005260` (= 0x02005260); patched to the literal
for the byte-compare (linker resolves it identically).

Key negative result: the Wave-11 "late empty-asm copy barrier"
(`asm("" : "+r"(b))` at the use site, which saved sub_0803FACC) does NOT work
here — the barrier is deleted or the copy is still propagated. RTL dumps
show identical pseudo structure between working and failing variants; the
difference is purely the register allocator's choice, which the pin controls
deterministically.

### B5 @0x0804D7A0 — MATCHED (30/30 B)

ROM: `adds r1, r0, #0; movs r2, #0; movs r0, #0; ...` — the `movs r2, #0` is a
dead init that must be kept.

Decisive source (`staging/wave12_B/b5_v8.c`):
```c
void FlagClear_4D7A0(u8 *s)
{
    register u8 *p __asm__("r1") = s;
    register u8 z __asm__("r2") = 0;
    register u8 w __asm__("r0");
    asm volatile("" : "+r" (z));   /* keep the dead init */
    p[26] = 0;
    p[22] = 0;
    if (p[24] != 0) goto else_;
    w = 12;
    goto join;
else_:
    w = 3;
join:
    p[0] |= w;
}
```
Codegen is byte-identical for 30 B; only the GAS 4→32 B section padding
(`mov r8, r8`) needed the `.align 1` fix. (The Wave-11 note's "28/30" claim
was inaccurate — no saved variant achieved it; v8 is the true best at 30/30
modulo padding.)

### B6 @0x0802518C — MATCHED (44/44 B)

ROM: `ldr r3, =0x13A4`, three `ldrh`/`strh` pairs with `off` in r3 and the
`p+off` temp in r2, then a second pool `0x13AA` for the last copy.

Decisive source (`staging/wave12_B/b6_v7.c`):
```c
void Copy4_2518C(u8 *p, u16 *q)
{
    register u32 off __asm__("r3") = 0x13A4;
    q[0] = *(u16 *)(p + off);
    off += 2;
    q[1] = *(u16 *)(p + off);
    off += 2;
    q[2] = *(u16 *)(p + off);
    q[3] = *(u16 *)(p + 0x13AA);
    asm("" : : "r" (off));   /* keep off live: temp forced to r2 */
}
```
Without the trailing dummy use, the compiler reuses r3 for the third `p+off`
temp (`adds r3, r0, r3`, clobbering `off`) since `off` is otherwise dead. The
dummy use is the decisive piece. Both pools are literals; the 44-B extent
includes 2 pad bytes + 8 pool bytes.

### B7 @0x0802D8F4 — MATCHED (50/50 B)

ROM: `p` in r2, `168*2` materialized as `movs r3, #0xA8; lsls r3, #1`, pool
`393` (0x189) loaded via `ldr r3, [pc, #8]` whose pool word sits disguised as
dead code (`lsls r1, r1, #6; lsls r0, r0, #0`) after the unconditional branch.

Decisive source (`staging/wave12_B/b7_v9.c`):
```c
u32 TblPtr_2D8F4(u8 *s)
{
    register u8 *p __asm__("r2") = s;
    register u32 t __asm__("r3");
    register u32 idx4 __asm__("r1");
    u32 idx;
    u32 ret;
    if ((p[24] & 2) == 0) {
        t = 393;
        idx = p[t];
        idx4 = idx * 4;
        t -= 29;
    } else {
        idx = p[392];
        idx4 = idx * 4;
        t = 168 * 2;
    }
    ret = *(u32 *)(p + t + idx4);
    asm("" : : "r" (p), "r" (t));   /* keep p/t live: join accumulates in r0 */
    return ret;
}
```
Three pins were needed: `p`→r2 (the copy), `t`→r3 (base/off), `idx4`→r1 (the
shifted index — without the pin the compiler does `lsls r0, r0, #2` in-place).
Pinning `t`→r3 also defeats the combiner's `392-56` rewrite of `168*2`
(the sub needs the 392 in the same register). The dummy uses force the final
`p+t+idx4` accumulation into r0 instead of clobbering r2/r3. The 393 pool is
emitted by the compiler as `.word 393` right after the `b` — byte-identical
to ROM's disguised dead code. `.align 1` fix for the 50-B section.

### B3 @0x080244B0 — BLOCKED (80-B extent)

Best attempt: `staging/wave12_B/b3_v23.c` (also see b3_v17–v22 series).
The pinned-copy trick DOES deliver the right allocation (`a`→r2, `b`→r3 via
`register u16 b __asm__("r3")` + `u32 a` with barrier giving the single
`lsrs r0, r2, #12`). Residual blockers are scheduler-level, not allocation:

1. **Instruction order:** ROM does `adds r3, r2, #0` (b-copy) BEFORE the
   `lsls/lsrs r1` (c-normalize); our scheduler does the two extensions first
   and the copy after. No source formulation (declaration order, separate
   assignment, volatile/input-only asm barriers, nested blocks) reorders them
   — the scheduler groups the extensions. 4-byte position diff.
2. **`ands` register swap:** `0xFFF & a` / `0xFFF & b` in the two branches —
   the compiler substitutes the copy and emits `ands r0, r3` / `ands r0, r2`
   where ROM has `ands r0, r2` / `ands r0, r3`.
3. **Temp register:** the `idx*20` address temp goes to r4 (clobbering `tbl`)
   vs ROM's r1.
4. **Pool sharing:** the two `0xFFF` loads don't share one trailing pool word.

B3 likely needs either a scheduler-constraint idiom we haven't found, or it
is a genuine second-vintage function (like B2's LICM). Recommend revisiting
only with a new idea; the 4 matched functions prove the cluster's shared
trick.

---

## What was learned (idiom catalog additions)

1. **Pinned copy register** (new, shared): `register T x __asm__("rN") = ...;`
   on the COPY forces the primary in-place. Defeats the systematic r1/r2/r3
   allocator difference across B4/B6/B7 (and the allocation half of B3).
   Prefer pinning the copy over pinning the primary — pinning the primary
   perturbs neighbors (B7: `adds r1, r0, #0; adds r2, r1, #0`).
2. **Dummy live-range use** (new): `asm("" : : "r" (x));` after the last real
   use keeps `x` allocated, forcing temps into other registers (B6, B7).
   Emits no code.
3. **Late barrier ≠ early barrier ≠ pin:** the 3FACC late-barrier idiom is
   NOT universal — it failed on B4 (barrier deleted/propagated through).
   The pin is strictly stronger and more predictable.
4. **`.align 1` section fix** (new): for sub-4-byte-multiple function
   extents, GAS pads the section with `mov r8, r8`; flipping the
   compiler-emitted `.align 2, 0` to `.align 1, 0` in the `.s` gives the
   exact ROM size (B5: 30 B, B7: 50 B). Safe: ldscript places the section at
   an absolute 4-aligned address.
5. **Pool-in-dead-code:** the compiler naturally emits a literal pool after
   an unconditional branch (B7's 393) — byte-identical to ROM's disguised
   pool. No special handling needed.
6. **Negative:** `u16` barrier-protected shift `a >> 12` becomes
   `lsl r0, r2, #4; lsr r0, r0, #16` (two shifts); making the variable `u32`
   recovers the single `lsr r0, r2, #12` (B3).

## Staging
All attempt sources (b3_v3–v23, b4_v4–v22, b5_*, b6_v6–v7, b7_v3–v9),
`retry12.sh` harness, `thumb1.py` decoder, and RTL dumps under
`~/workspace/mmbcc-decomp/staging/wave12_B/` (never delete).
Matched sources: `b4_v22.c`, `b5_v8.c`, `b6_v7.c`, `b7_v9.c`.
Results: `docs/wave12_B_results.tsv`.
