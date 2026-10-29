# Wave 13 Worker A — B3 @ 0x080244B0 (80-B extent)

**Date:** 2026-10-22
**Target:** B3, last holdout of the r1/r2/r3 allocator-difference cluster
**Result: BLOCKED** — 76/80 bytes match; residual is a 4-instruction prologue
ordering issue robust against 20 source variants.

Best attempt: `staging/wave13_A/b3_best_v42.c` (copy of `b3_v42.c`).

---

## Status: what matches in v42

Byte-identical except for 8 bytes (4 instructions) at 0x080244B4–0x080244BA.

| Area | ROM | v42 | Status |
|---|---|---|---|
| `push {r4,lr}` | `b510` | `b510` | ✅ |
| `lsls r0,r0,#16` | `0400` | `0400` | ✅ |
| prologue order (4 insns) | `lsrs r2 / adds r3 / lsls r1 / lsrs r1` | `lsls r1 / lsrs r1 / lsrs r2 / adds r3` | ❌ **only diff** |
| `lsrs r0,r2,#12; cmp r0,#3` | `0b10 2803` | `0b10 2803` | ✅ |
| branches, `beq`/`b` | — | — | ✅ |
| `ldr r4,[pc,#24]` (tbl) | `4c06` | `4c06` | ✅ |
| `movs r0,#1; ands r0,r1; cmp r0,#0` | `2001 4008 2800` | same | ✅ |
| `ands r0,r2` (0xFFF & a branch) | `4010` | `4010` | ✅ |
| `ands r0,r3` (0xFFF & b branch) | `4018` | `4018` | ✅ |
| `idx*20` in r1, `adds r1,r1,r4` | `0081 1809 0089 1909` | same | ✅ |
| `ldrb r0,[r1,#15]` / `[r1,#14]` | `7bc8`/`7b88` | same | ✅ |
| pools: `082298F0`, two `00000FFF` | — | — | ✅ |
| epilogue `pop {r4}; pop {r1}; bx r1` | — | — | ✅ |

v42 source (the important parts):
```c
u8 TblLookup_244B0(u16 p0, u8 p1)
{
    u32 a = p0;
    u16 b = a;
    u8 c = p1;
    u8 *tbl;
    register u32 idx __asm__("r0");
    asm("" : "+r" (a));   /* keeps single `lsrs r0,r2,#12`, blocks a>>12 combine */
    if ((a >> 12) != 3)
        return 0;
    tbl = rom082298F0;
    if ((c & 1) == 0) {
        idx = 0xFFF & b;          /* note: b here, a in else — matches ROM */
        return tbl[idx * 20 + 14];
    } else {
        idx = 0xFFF & a;
        return tbl[idx * 20 + 15];
    }
}
```

Key findings that resolved the other three blockers:
1. **`ands` swap — FIXED.** ROM uses `b` (r3) in the `(c&1)==0` branch and `a`
   (r2) in the else branch. Writing the source operands to match
   (`0xFFF & b` / `+14` in first branch, `0xFFF & a` / `+15` in second)
   emits the right registers. (v17 already had this layout.)
2. **Temp register — FIXED without pins.** With no pin on `b`, the natural
   allocation puts `tbl` in r4 and the `idx*20` address temp in r1
   (`adds r1,r1,r4`), matching ROM. The idx→r0 pin is still needed for the
   `ldr r0`/`ands r0` dest.
3. **Pool sharing — already fine.** Both 0xFFF loads get their own pool word;
   layout matches.

**Major surprise:** B3 does NOT need the pinned-copy trick for allocation.
The plain (unpinned) `u32 a = p0; u16 b = a;` naturally yields a→r2,
`adds r3,r2,#0`. The pin was actively harmful (it defers b's init RTL past
c's init, perturbing the scheduler). Only `idx` needs its r0 pin.

---

## The residual blocker: prologue instruction order

ROM (0x080244B2–0x080244BB):
```
lsls r0, r0, #16
lsrs r2, r0, #16
adds r3, r2, #0
lsls r1, r1, #24
lsrs r1, r1, #24
```
v42 emits:
```
lsls r0, r0, #16
lsls r1, r1, #24
lsrs r1, r1, #24
lsrs r2, r0, #16
adds r3, r2, #0
```
8 bytes differ (two independent pairs swapped). Everything downstream of
0x080244BC is byte-identical.

### Root-cause analysis (from RTL dumps + scheduler source)

The repo ships agbcc's GCC source at `tools/agbcc/gcc_arm/`, so the
scheduler's exact decision procedure was read, not guessed
(`sched.c: rank_for_schedule`):

1. Among ready insns, highest `INSN_PRIORITY` wins.
2. On priority ties, with a `last_scheduled_insn`, insns are classed:
   class 1 = data-dependent on last scheduled, class 2 = anti/output,
   class 3 = independent (or dependence cost == 1). **Highest class wins —
   i.e. independent insns are preferred.**
3. Final tie-break is `INSN_LUID` (original stream order).

In the prologue, after `lsls r0,r0,#16`, the ready set is
{`lsrs r2,r0,#16` (data-dep on the lsls), `lsls r1,r1,#24` (independent)}.
The independent c-extension wins the tie-break (class 3 > class 1 when the
ARM data-dependence cost exceeds 1), so it is scheduled before the
a-extension/b-copy. The b-copy's RTL also lives at a higher LUID than the
c-extension, so it loses LUID ties as well.

Additionally, the combiner and reload passes move the a-extension's
`lsrs r2,r0,#16` later (observed: insn deleted in `.combine` and recreated
just before the b-copy), because a's value is only needed later.

### What was tried (20 variants in staging/wave13_A/)

- **Opaque-asm ordering edges** (v24, v28, v29, v43): `asm("" : "=r"(c) :
  "r"(p1), "r"(b))` (tied and untied), `asm("" : "+r"(c) : "r"(b))`,
  `asm("" : "+r"(c) : "r"(b))` on v42. The compiler sees through the empty
  asm and hoists the c-extension onto p1 anyway; the "+r" variant splits the
  `lsls`/`lsrs` pair across the b-copy (one half lands right, the other
  doesn't) and flips the downstream `ands` to `ands r1,r0`.
- **Pinned c / pinned idx2** (v27, v34–v39): pinning `c`→r1 and/or `idx2`→r1.
  Fixes the address temp but the c-extension RTL is still generated in the
  prologue *before* the deferred b-copy store — pinning defers only the
  store to the hard reg, not the RHS computation.
- **Separate `b = a;` statement** (v30), **no inner block** (v31),
  **barrier before pins** (v40), **swapped declaration order** (v41):
  no change — the reorder is not a source-order artifact.
- **Dummy live-range / priority-bump asms** (v25, v26, v33): keep `tbl` in r4
  (works) but lengthening the b-copy's dependence chain cannot beat the c-
  extension: the chain end always ties with the c-extension and loses on LUID
  (c-ext has the lower LUID).
- **Manual 5-insn prologue asm** (v32): defeated — old_agbcc strips the
  space after commas in asm templates *and* requires no-`s` mnemonics
  (`lsl` not `lsls`) without `.syntax unified`; worse, the compiler emits its
  own p0/c zero-extends *before* the asm (for the `"+r"` operands) plus
  `mov r4,r8; push {r4}` spills from register pressure.
- **Both compilers, both flag sets**: main `agbcc` shows the identical
  reorder; `-fno-schedule-insns`, `-fno-combine` (alone and together) do NOT
  fix it — the move happens in reload/combine, not just the scheduler.
- **Plain unpinned version**: allocation is naturally correct (a→r2,
  b→r3!) but the order is still wrong and `a>>12` miscompiles to
  `lsrs r0,r0,#28` without the `"+r"(a)` barrier.

### Verdict

The 4-instruction prologue reorder (c-extension scheduled before the
a-extension/b-copy) is a robust codegen behavior of this agbcc vintage:
it survives pinning, declaration reordering, opaque-asm edges, dummy
live-ranges, both compilers, and disabling combine/schedule. No
source-level idiom found in 20 variants produces
`lsrs r2 / adds r3` before `lsls r1 / lsrs r1`.

This is consistent with the wave-12 hypothesis that B3 is a genuine
second-vintage function: its *allocation* matches old_agbcc's natural
output (no pins needed), but its *scheduler* ordered the prologue
differently than any source formulation achieves here. Recommend parking
B3 until a new idea (or a different compiler vintage) appears; v42 is staged
as the 76/80-byte best attempt.

---

## Staging

- `staging/wave13_A/b3_best_v42.c` — best attempt (76/80 B).
- `staging/wave13_A/b3_v24.c` … `b3_v43.c`, `b3_plain.c`, `b3_v41.c` —
  all variants tried (never delete).
- `staging/wave13_A/retry13.sh`, `thumb1.py` — harness (copied from wave12_B).
- `staging/wave13_A/t.i`, `t.s`, `rom.dis`, `mine.dis` — last run artifacts.

## Follow-ups for the coordinator

1. B3's *allocation* does not need the pinned-copy trick — consider
   re-examining whether B4/B6/B7's pins are load-bearing or whether a
   simpler formulation also works there (their pins may be masking the same
   scheduler behavior).
2. The `asm("" : "+r" (a));` barrier is what forces the single
   `lsrs r0,r2,#12` for `a>>12`; without it the compiler folds to
   `lsrs r0,r0,#28`. Keep it in any future B3 attempt.
3. If a second agbcc vintage surfaces, B3 is the prime candidate to retry.
