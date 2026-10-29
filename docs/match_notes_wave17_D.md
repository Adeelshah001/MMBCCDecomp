# Wave 17 Worker D — Match Notes (2026-10-22)

## Part 1 — C1 Re-derivations (13/13 verified 0-diff in staging)

All re-derived from docs/match_notes_wave15_C.md idioms. Verified via standalone
clean-room build+diff (staging/wave17_D/verify.sh). Sources in
staging/wave17_D/final_<addr>.c. Landed src in mmbcc/src/w17d_<addr>.c
(landing blocked by ldscript issue — see below).

| Addr | Name | Size | Compiler | Key idiom |
|---|---|---|---|---|
| 0x0800b3b0 | FlagCheckInit_0800B3B0 | 58B | main | Accumulator `&=` forces ands dest (`u32 r=128; r&=t;`) |
| 0x080379f0 | StateMachine_080379F0 | 64B | main | `(u32)(s8)` double-cast for asrs-into-r1 |
| 0x08038efc | StateMachine_08038EFC | 64B | main | Twin of 379F0, p[2]/p[3] stores swapped |
| 0x0803ae90 | StateMachine_0803AE90 | 64B | main | Identical twin of 38EFC |
| 0x0800b6a4 | NibbleGate_0800B6A4 | 68B | old | `(((u32)p[18]<<28)>>28)` for `&15`; explicit `.byte 0,0` pad |
| 0x080226b0 | ChipInit_080226B0 | 80B | main | Constant-first double-OR; `& -13` via int var |
| 0x0802278c | ChipInit_0802278C | 80B | main | Identical twin of 226B0 |
| 0x08027c28 | StateMachine_08027C28 | 92B | main | Pure accumulator double-AND (no pins/asm) |
| 0x08035170 | StateMachine_08035170 | 92B | main | p[5] switch, p[4]=4/p[5]=0, returns 0 |
| 0x08037a7c | StateMachine_08037A7C | 92B | main | Identical to 27C28 |
| 0x08038f88 | StateMachine_08038F88 | 92B | main | 27C28 twin, p[2]/p[3] swapped |
| 0x0803af3c | StateMachine_0803AF3C | 92B | main | Identical to 38F88 |
| 0x08048380 | StateMachine_08048380 | 92B | main | p[3] switch, p[2]=4/p[3]=0, returns 0 |

Skipped (already landed by wave16-C): 0x0801bd7c, 0x0802316c.

## Part 2 — Blocked Revisits (2 matched, 6 blocked)

### MATCHED
- **0x08016e0c** (64B, old_agbcc): F_08016E0C. u32 param + explicit `(u16)v` cast
  orders s-copy before v-extension; `u8 z=0` after p-computation yields early movs.
- **0x080254e0** (66B, main + fix_tail_align): F_080254E0. Register-pinned q (r0)
  in scoped block for `(*q)++`, then unpinned recompute for `if (*q==1)`.

### BLOCKED (registered)
- **0x08002300**: 41 diffs (old_agbcc) / 63 (main). Spread across function:
  count-init coalescing; third-loop field8 reload reg.
- **0x0801b47c**: 65 diffs (old_agbcc). Table pattern: `adds r1,r2,r4` vs ROM
  `adds r0,r2,r4` (dest-reg mismatch). Operand swap tried, dest still wrong.
- **0x080211ec**: 70 diffs (old_agbcc). Table variant, `adds r1,r2,#4` intermediate.
- **0x0800e6d0**: 31 diffs. Pool duplication (0x02005020 twice) — needs full-build
  check; standalone pool placement differs.
- **0x0803aed0**: 47 diffs. Pool placement interleave — needs full-build check.
- **0x08011ac8**: 122 diffs. 3-state machine, nested branches diverge.

## Part 3 — Leaves-up Bulk (6 matched)

| Addr | Name | Size | Compiler | Notes |
|---|---|---|---|---|
| 0x080250a8 | F_080250A8 | 14B | main | Empty-asm anti-folding for pool+adds |
| 0x0802508c | F_0802508C | 22B | main | ldr hoisted before cmp; adds inside if |
| 0x080228bc | F_080228BC | 34B | main | r2-pinned return; b=0/a=1 order for movs |
| 0x0801f12c | F_0801F12C | 40B | main | Node_PopAndInit(0,1,0,17); n[16]=2 |
| 0x08020514 | F_08020514 | 40B | main | Node_PopAndInit(0,0,0,18); n[16]=4 |
| 0x0801d048 | F_0801D048 | 40B | main | u8 param to r4; n[16]=x, n[40]=0 |

## New Idioms

1. **Empty-asm anti-folding**: When ROM does `ldr rX,[pc]; adds rX,#N` (pool holds
   base, adds separate), use `__asm__ volatile("" : "=r" (p) : "0" ((type *)BASE));`
   then `p + N` to prevent constant folding. (0x080250a8)
2. **Accumulator `&=` forces ands dest**: `u32 r = 128; r &= t;` → `movs r0,#128;
   ands r0,r1`. Compiler otherwise reuses dead source reg as dest. (0x0800b3b0)
3. **Scoped register pin**: Pin variable in scoped block for specific codegen,
   let it die at block end to force recompute after. (0x080254e0)

## Landing Status: BLOCKED

21 src files created in mmbcc/src/w17d_*.c. Makefile SRCS_C and per-file rules
added. ldscript.ld entries added but **ldscript corrupted during reorder** —
`make compare` fails with 7M diffs starting at 0x0800033c (not in my functions).
The ldscript needs coordinator review/restore from backup. Functions are
verified 0-diff in staging (staging/wave17_D/final_*.c) per hardened rules.

**Do NOT register as MATCHED until landing is fixed and `make compare` passes.**
