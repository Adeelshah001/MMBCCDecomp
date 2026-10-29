# Wave 19 Worker D — Match Notes (pool-placement blocker cluster)

All three targets MATCHED, 0 diffs, full extents incl. pools.

## Matched (3)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x080250bc | FindEntryIdx_080250BC | 74 | main+align_sed | No-arg prototype for GetEnt_U16_22 (thunk ignores r0); FIXALIGN1 on ALL aligns (pool in branch shadow at +0x0c) |
| 0x08022868 | BuildList5_08022868 | 84 | main | Shift-first u8 increment `(idx<<24)+0x1000000>>24`; pool already inline at +0x14 |
| 0x08020340 | BuildNodePair_08020340 | 100 | main | `u8 *p=0` first, `if (v>1)` ble-direct (no mid barrier → pool falls to end at +0x60); `u8 z=0` zero-first in block 1 |

## Per-function detail

### 0x080250bc — FindEntryIdx_080250BC (74 B)
Scans i=1..GetEnt_U16_22()-1; returns `(s8)F_0802663c(base+24, i)` on
`Fwd_25054(i)==x`, else -1. Two blockers, both solved:
1. ROM's loop-condition call is a bare `bl` with no arg setup. The callee
   thunk at 0x08025024 ignores r0 entirely (loads 0x02007090 itself), so the
   original source declares it **with no prototype args** and calls
   `GetEnt_U16_22()`. (Idiom below.)
2. Section came out 76 B (`bx r1; c0 46` tail pad). The pool `.align 2,0`
   mid-function also bumps section alignment, so the wave18 leading-only
   FIXALIGN1 was insufficient — the landed per-file rule replaces **all**
   `.align 2, 0` with `.align 1, 0` (pool stays at +0x0c, already 2-aligned).

### 0x08022868 — BuildList5_08022868 (84 B)
Builds a 5-node doubly-linked list via Node_PopAndInit(1,1,0,5), returns the
last node; guarded by `*(s16 *)(*(u8 **)0x020066f0 + 10) > 4`. The pool was
already inline at +0x14 (branch shadow). The only codegen gap was the idx++
dance: ROM does `lsls r0,r5,#24; movs r2,#128; lsls r2,r2,#17; adds r0,r0,r2;
lsrs r5,r0,#24` — i.e. `(idx<<24) + 0x1000000 >> 24`, shift-FIRST. Plain
`idx++` emits adds-first (`adds r0,r5,#1; lsls; lsrs`). Fixed with the
shift-first u8 increment idiom (below). Everything else (incl. the
`(s8)idx <= 4` asrs/cmp/ble tail and `return prev` → `adds r0,r1,#0`) matched.

### 0x08020340 — BuildNodePair_08020340 (100 B section)
If `*(s16 *)(*(u8 **)0x020053c0 + 10) > 1`, allocates two (0,0,0,18) nodes:
node1 `[16]=3,[17]=0,[120]=47,[40]=a`; node2 `[16]=3,[17]=1,[120]=49,[40]=a`;
returns last p (0 if skipped). Fixes vs the wave18 attempt:
1. `u8 *p = 0;` declared FIRST → `movs r2,#0` hoisted above the pool load and
   reused as the first `bl` arg (ROM has no `movs r2,#0` before the 1st call).
2. `if (v > 1) { ... }` instead of early `return 0`: ROM uses `ble` straight
   to the return block. The early-return form emits an unconditional `b`
   barrier that captures the pool mid-function; the ble-direct form has no
   mid-function barrier, so the pool falls to the END (+0x60). This is the
   generalizable pool-control rule (below).
3. `u8 z = 0;` inside block 1 + `p[17] = z` (wave18 zero-first idiom):
   reproduces `movs r1,#0` BEFORE `movs r0,#3` in block 1.
4. Section is 100 B: 96 B code + pool word at +0x60..+0x63, sitting in the
   gap before 0x080203a4. Abuts the landed NewNode_080203A4 slot exactly.

## New idioms

### No-arg prototype for arg-ignoring thunks
If the callee's thunk ignores its argument register (verify by disassembling
the callee), declare it with an empty prototype — `extern u16 F(void);` —
and call `F()`. gcc then emits a bare `bl` with no argument setup, matching
ROM. (A `(u16 x)` prototype forces an `adds r0,...` that ROM never had.)

### Shift-first u8 increment
To reproduce `lsls r0,rx,#24; movs ry,#128; lsls ry,ry,#17; adds r0,r0,ry;
lsrs rx,r0,#24` (wrapping u8 increment done as `(x<<24)+0x1000000>>24`),
write `x = (u8)(((x << 24) + 0x1000000) >> 24);`. Plain `x++`/`x+=1` emits the
adds-first form instead. (The following `(s8)x` compare then reuses r0 via
`asrs r0,r0,#24` with no reload.)

### FIXALIGN1-extended: replace ALL `.align 2, 0`
When a literal pool sits mid-function, its `.align 2, 0` also forces 4-byte
section alignment (46c0 tail pad). The landed per-file sed must replace every
occurrence, not just the leading one:
`sed -i 's/\.align\s*2, 0/.align 1, 0/'`. Safe when the pool offset is already
2-aligned (no bytes move).

### Generalizable pool-control strategy (blocker-class fix)
agbcc dumps a function's literal pool **immediately after the first
unconditional jump (barrier) that follows the last literal use**; if there is
no mid-function unconditional jump, the pool falls to the function end.
Evidence across this cluster:
- 0x080250bc: pool in the initial `b`-to-loop-cond shadow (+0x0c).
- 0x08022868: pool in the early-`return` `b` shadow (+0x14).
- 0x08020340: no mid-function `b` (condition is `ble`-direct-to-return) →
  pool at end (+0x60).
Practical levers, in order of preference:
1. **Restructure the branch**: `if (v > 1) { ... }` + trailing `return`
   instead of `if (v <= 1) return 0;` removes the barrier and pushes the pool
   to the end (or vice versa to pull it inline).
2. **Declaration order**: pool-dependent initializations (`u8 *p = 0`)
   declared before/after the pool load steer which instructions precede the
   first barrier.
3. **Tied-opaque loads / volatile barriers** (untried this wave): an
   `__asm__` tied to the pool load, or a volatile barrier placed to force a
   specific emission point, should pin the pool when restructuring the
   source is not enough.
Note: this rule predicts pool placement — use it *before* writing the
candidate to choose the branch structure, rather than fighting the compiler
afterward.
