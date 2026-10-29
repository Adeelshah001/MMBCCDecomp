# Wave 24 Coordinator Notes (parent-spawned run, 2026-10-23)

## Headline
**773 / 1674 C-matched** (was 764 → **+9**); 13 ASM; **786 byte-identical total**; 211 blocked.
Full regression: 762 sections — 708 clean (+6 vs wave 23), 51 accepted 2B c046 tail
artifacts, 3 pre-existing dirty (sram VerifyCompare, mainloop, text_open). Zero regressions.

## The parallel-coordinator incident
Two "Wave 24" coordinators ran simultaneously: this one (spawned by the parent at
~09:05 EDT) and a second run (almost certainly the 9:00 AM daily cron), both using
wave24_* naming. Consequences:
- The other run's workers used staging/wave24_A/ (rect-fill), staging/wave24_C/
  (bulk), and a pre-existing staging/wave24_D/ harness.
- My Worker A's 0x0804AF20 landing and my Worker D's landings proceeded cleanly.
- When I landed the other run's three verified bulk matches (0x0800A6BC, 0x0800E748,
  0x0800E224 — verified 0-diff by my Worker C independently), the other coordinator
  reverted my src/ files to staging/wave24_C/rogue_reverted/ and removed my ldscript
  slots, then landed all three itself under its own naming. Final state reconciled:
  all 9 wave-24 matches are landed and in the registry. No work lost.
- Lesson for the parent: on cron days, do NOT spawn a parallel wave coordinator —
  the standing lesson ("the daily cron owns the wave cadence") was violated by the
  parent's 09:05 spawn, not by the cron.

## My workers' results

### Worker A — 0x0804AF20 MATCHED (InitRec28_4AF20, 112 B, main agbcc + Makefile sed)
- Breakthrough: wave-23's store decode was wrong. Hand-decoding 0x82A7: strh,
  imm5=10, Rn=r4, Rd=r7 → `strh r7,[r4,#20]` with r7=a. The tail is p+20=a,
  p+22=c — wave-23's "=b" reading was the error, and it *created* the "b live in
  r2 across 4 calls" wall. With =a/=c, b is dead after call 1, so b→r2
  (caller-saved) is gcc-consistent. Root cause: objdump scales strh/ldrh
  immediates by 2 (#20 = field 10), and Rd was misread.
- Second finding: gcc hoists 0x10000 out of any call-free loop (proven undefeatable:
  14 -fno-* flags, old_agbcc -O2/-O1/-Os, noiw all still hoist) → fixed via sed.
- New idioms: hand-decode strh/ldrh when a wall depends on it; call-free-loop
  invariant hoist is undefeatable in this gcc (go straight to sed); dead-after-first-
  call ⇒ caller-saved is fine (re-examine the store decode before assuming a
  call-live wall is real).
- Landing: mmbcc/src/w24a_0804af20.c, Makefile sed rule (inline, single-\t form
  verified by od — the `\\t` display doubling is output-wrapper escaping), ldscript
  slot. Callee TblGetByte_24384 uses the absolute-symbol idiom (.set in TU) since
  its section is BYTE-emitted in ldscript.
- Independently re-verified 0-diff by coordinator from clean rebuild; landed 0-diff
  in built ROM.

### Worker B — rect-fill family: still BLOCKED (no claims)
- 0x08006AD8 (768 B): best 5/8 prologue instructions; wall is ctx→r6, b→r9, d→r8
  rotation (tried 24 decl permutations, 32 extension subsets, clobber-denial,
  pins, old_agbcc, -O1).
- New idioms: `u8 *pa = a;` first-local reproduces param-spill + sl-reload exactly;
  live-range extension spills (zero-byte asm at function end lowers gcc priority →
  ROM-identical spills); root-caused in agbcc's local-alloc.c (QTY_CMP_PRI sort,
  lowest free hard reg wins).
- Siblings 0x08007134/0x080065BC/0x08006374: BLOCKED (registry rows by parallel run).
- Staging: staging/wave24_B/ (best_08006AD8.c, README_08006AD8.md, WAVE24_B_REPORT.md).

### Worker C — bulk: 0 matched, 2 near-matches (both superseded by parallel run's landings)
- 0x08007728: 3 diffs (parallel run landed it as MATCHED).
- 0x080097CC: 8 diffs, old_agbcc -O1 (parallel run landed it as Load4Tiles MATCHED).
- Also independently verified the parallel run's 0x0800A6BC/0x0800E748/0x0800E224
  as 0-diff (all valid).
- Noted a duplicate-Worker-C collision in staging/wave24_C/; used *_ii files.

### Worker D — 2 MATCHED, both landed
- 0x08002EF4 SetAA_Clr2_08002EF4 (48 B incl pool, main agbcc): the 0xAA pool mystery
  solved — agbcc folds every pure-constant 0xAA spelling to `movs r0,#170`
  (brute-forced 19 spellings × 2 compilers), so the ROM's pool-loaded 0xAA must be
  a link-time expression: `(u32)&gAddrZero[0xAA]` with gAddrZero an absolute symbol
  at 0x0 (via .set in the TU) forces a pool word linking to exactly 0xAA.
  0x02000818/0x02000819 pool-forcing via tied empty-asm from Clr2_08002f24.
- 0x08001C88 CallTwice_08001C88 (32 B, main agbcc): plain do-while, no steering.
- 0x08004998 (HexFormat): 95 → 31 diffs, parked with full trail (p0–p14).
- Both landed 0-diff in built ROM; registry rows appended.

## Landing catches (coordinator)
- Makefile inline-sed escaping: the recipe file must contain single `\t` (od-verified);
  the `\\t` seen in tool output is display escaping only. Tested and confirmed.
- Section-name case: worker .o files used lowercase (`.text.w24d_08002ef4`) while my
  ldscript slots used uppercase → empty sections. Fixed ldscript to match; always
  objdump -h the .o before writing the slot.
- Callee symbol mismatches: F_08016E0C referenced but .o exports Sub_16E0C →
  absolute-symbol .set idiom. TblGetByte_24384's section is BYTE-emitted → .set in TU.
- nm hygiene: confirm GLOBAL (A/T), not just present.

## New idioms for the catalog (wave 24)
1. Hand-decode strh/ldrh (Rd/Rn/imm5) when a wall depends on it.
2. Call-free-loop invariant hoist undefeatable in gcc 2.9-arm-000512 → sed.
3. gAddrZero absolute-symbol pool trick for un-foldable constants.
4. `u8 *pa = a;` first-local for param spill + sl reload.
5. Live-range extension spills via end-of-function zero-byte asm.
6. Explicit pre-UAL asm templates (agbcc divided-syntax rejects UAL mnemonics).

## What's next (Wave 25 candidates)
1. Rect-fill prologue wall (ctx→r6, b→r9, d→r8) — needs a novel allocator idiom.
2. 0x08004998 (31 diffs, full trail in staging/wave24_D/).
3. Remaining bulk rows; blocked revisits with the 6 new wave-24 idioms.
4. **Resolve the dual-coordinator issue before Wave 25** — the parent must decide
   whether the daily cron or a manual spawn owns the wave cadence.
