# Wave 19 Worker C — Match Notes (twin pairs)

## Matched (4)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x0800fff4 | Setup_0800FFF4 | 136 | old_agbcc | Pinned-r2 barrier idiom (new). Twin of 0x0801009c. |
| 0x0801009c | Setup_0801009C | 136 | old_agbcc | Same source, Ewram5160_Init_10508(2). |
| 0x08017620 | ChipInit_08017620 | 78 | main+FIXALIGN1 | ChipInit family shape (sibling-matched). Node_PopAndInit(0,1,b,2). |
| 0x08017d00 | ChipInit_08017D00 | 78 | main+FIXALIGN1 | Twin: Node_PopAndInit(0,1,b,5). |

All 4 verified 0-diff: recompile → link at true ROM address → objcopy
extract → cmp vs baserom, full extents including pools; .o/.elf/.bin/ROM
extract all non-empty; exact byte counts (136/136, 78/78).

## Pair 1: scheduler twins (0x0800fff4 / 0x0801009c)

Behavior: flag byte at 0x02005160; if nonzero return 0; else
Ewram5160_Init_10508(1|2), Zero_0801052C(), then two 32-byte records at
0x02004ca0: p[29]=a|b|c (then d|e|f), p[30]=0, p[31]|=1.

Blocker was: ROM `movs r2,#1` BEFORE `ldrb r0,[r1,#31]`; both agbcc
variants' schedulers hoist the load into the delay slot (ldrb; movs; orrs).

Solution path (evidence in staging/wave19_C/c1..c5_0800fff4.c):
1. `u8 one=1` + empty volatile asm barrier on `one` before the load pins the
   order (c1: movs stayed above ldrb) but gcc chose r3 and emitted u8
   re-extension copies (adds/lsls/lsrs).
2. Scoped `register u32 one __asm__("r2")` + barrier: order AND register
   right, but u8 `t` forced lsls/lsrs re-extends after each orrs (c2).
3. `u32 t`: extends gone, but allocator swapped p->r0/t->r1 (c3/c4, 20 diffs
   all in register-field bits).
4. Also pin `register u8 *p __asm__("r1")` in the same scope (c5): 0 diffs.

The scope must be narrow (opened after the arg-extension prologue) so the
prologue can still use r1/r2 as scratch. `t` stays live as u32 across both
halves; the second half reuses r2=1 with no rematerialization (matches ROM).
The `__asm__ volatile("" : "+r" (t))` barriers (prior wave idiom) keep the
two `orrs r0,r2` per half from folding.

Twin transfer: 0x0801009c = identical source with `Ewram5160_Init_10508(2)`
(movs r0,#2) and its own section/name; 0 diffs first try.

## Pair 2: alloc-rotation twins (0x08017620 / 0x08017d00)

Blocker was: ROM a->r7, c->r5, d->r6; the wave-18 attempt's source
(u8* p, literal 0s, (s16) casts) gave a->r5, c->r6, d->r7.

Key find: already-matched 78 B siblings ChipInit_0801AB94 (0,1,b,7),
ChipInit_08017A44 (0,1,b,4), ChipInit_0801BBB4 (0,1,b,9) in
mmbcc/src/w17c_chipinit.c use plain C and produce the ROM allocation.
ROM-byte-diff of sibling 0x0801ab94 vs target 0x08017620: only the
`movs r3,#imm` (7 vs 2) and the PC-relative `bl` encodings differ.

So the "rotation" was an artifact of the source shape, not a real
allocation puzzle: copying the sibling shape verbatim —
`u32 *n`, `u8 *q` + `u32 z = 0` inside the `if` block, `(s32)(s16)` casts,
`*(u32 *)(q + 44) = (u32)e` — with only the Node_PopAndInit 4th arg changed
(2 / 5) gives 0 diffs first try on both twins. The explicit
`register __asm__` pinning attempted in wave 18 (u8/u16 pins) actively
harmed codegen (gcc loaded the 5th arg into the pinned r7).

Lesson: before pinning, diff the target against matched same-size family
members — a sibling's proven source shape transfers.

## New idioms

### Pinned-constant + empty-asm scheduling barrier (old_agbcc)
To force a constant materialization (`movs r2,#1`) to stay ABOVE a
subsequent load that the scheduler wants to hoist:
```c
{
    register u32 one __asm__("r2");   /* narrow scope: prologue keeps r1/r2 scratch */
    one = 1;
    __asm__ volatile("" : "+r" (one)); /* scheduling barrier: movs cannot cross down */
    t = p[31] | one;                   /* ldrb cannot cross up */
    ...
}
```
Pin the constant's register explicitly (u32, not u8/u16 — narrower types
invite re-extension copies), keep the scope narrow so earlier code still
uses the register as scratch, and widen companion temps (u32 t) to avoid
extension insns. Companion pin (`register u8 *p __asm__("r1")`) can restore
an allocation the extra live variable perturbs.

### Sibling-shape transfer for "alloc rotation" blockers
When natural allocation rotates registers vs ROM, check matched
same-size/same-family functions first (here: w17c_chipinit.c ChipInit
siblings). A verbatim shape copy with only call-arg immediates changed
beat every pinning attempt.

## Verification notes / pitfalls hit

- Isolated link of `extern`-only landed files: `--defsym` makes the linker
  emit Thumb->ARM `bl` veneers (+20 B). Use a stub .s with
  `.thumb_func`+`.set` at the true addresses instead (staging/wave19_C/final/stubs.s);
  mirrors the real build's Thumb symbols. Do NOT land the stub.
- NEVER put `*/` inside a block comment (here: `u8*/literal-0` silently
  terminated the comment and turned the tail into code). Also avoid
  non-ASCII (em-dash) in comments — the system cpp + agbcc pipeline
  mis-tracks lines.
- FIXALIGN1 sed must use the `\s*` form (`s/\.align\s*2, 0/.align 1, 0/`);
  the literal-tab form silently never matches (wave-18 lesson, re-verified:
  sections came out exact 0x4e).
- 78 B functions: with FIXALIGN1 the sections are exact-size (0x4e), so the
  following unlanded bytes (0x0801766e/0x08017d4e) keep their existing
  BYTE() coverage — no overlap hazard.
