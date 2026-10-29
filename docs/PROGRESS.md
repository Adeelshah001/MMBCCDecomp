
## 2026-10-22 — Wave 12 worker A (3AFFC callees) done: 0 MATCHED, 4 BLOCKED
- sub_0800BEE0 (100B): prologue now byte-exact (widened (u32,u32) params + explicit shifts defeats prologue reorder); body blocked by neg-fold compiler difference ((base[9]&3)|128 → ours folds to |-128).
- sub_080241F8 (176B): 102→49 diffs; fixed case-2 control flow (if/else-return, r1 CSE); fatal: ROM in-place u16 truncation (lsl r0,#16; lsr r0,#16) vs ours cross-register (lsr r2,r0,#16).
- sub_08024384 (174B): twin, 46 diffs, same prologue blocker; confirmed bl GetU8_0/bl GetByte0_265B0, [r0,#0], default 50.
- sub_0800B148 (340B): 263 diffs, needs CFG-first reconstruction; CORRECTION: ROM calls 0x08007EEC (not 0x0800800C) + 0x0800B470 + 0x0800B6F4; s16-ness only at B470 call site ((u8,u16,u8)+cast fits better).
- New idioms: widened-param prologue control; mask-first int temps (int m=-7; int v=base[i]; base[i]=v&m).
- Task_3AFFC retry NOT dispatched — callees didn't land; remaining 3AFFC gaps are callee-independent.

## 2026-10-23 — Wave 22 worker C done: 2 MATCHED, 4 BLOCKED (refined)

Progress bar: 732 / 1674 C-matched (43.7%)

Matched (both full-build verified 0-diff, 8,388,608-byte ROM green):
- 0x08011A78 F_08011A78 (80 B: 78 code + 2 zero pad, main agbcc). Blocked revisit (w20-B parked 59 diffs, w21-D 49 diffs). q pinned r1 but later uses via p->f0 so ROM's `ldrb r1` kill + `ldr r1` reload fall out; eight (r6) init after *r2=z; explicit `.short 0x0000` pad via Makefile sed. Evidence: docs/match_notes_wave22_C.md.
- 0x08016D2C sub_08016D2C (128 B: 116 code + 12 pool, old_agbcc). Blocked revisit (w15-C2 26 diffs). Clobber-reservation denies r4+r0 (tbl pool->r1) and r4 (tab2 pool->r1); tied asm keeps int copy before clamp; `int m=-13` for movs+negs; pool 3 = 0x020031E4 from ROM bytes. Evidence: docs/match_notes_wave22_C.md.

Blocked revisits (refined diffs, registry updated append-only):
- 0x0804BDE0 ListWalk (48 B): tst wall CONFIRMED — 32 diffs, single root cause (`ands;cmp` vs `tst`; no tst precedent in any matched object; GCC thumb lacks the pattern). Attempt once per brief; stays blocked.
- 0x0804AF20 (112 B): 68 diffs (was 73). NEW IDIOM: explicit u16 increment `t=((u32)i<<16)+0x10000; i=t>>16` (from w16b_08025754.c) reproduces the `movs #128/lsls #9` materialization; r8 save/restore achieved. Resists: a/c/d register rotation.
- 0x08002CB0 (112 B): 31 diffs (was not attempted; pools inside extent, not outside). Resists: prologue scheduling + pool order.
- 0x08002E80 (84 B): 4 diffs (was 53). `&disp`-twice form + pp-in-OR + clobber for DISPCNT->r3. Resists: r1/r4 swap for store-addr vs pp0-load.
- 0x08010F34: already MATCHED by Wave 22-D (skipped per registry check).

New idioms: kill-and-reload via re-derivation; explicit u16 increment; tied-asm copy preservation; int mask variable for movs+negs; verify pools from bytes; `&var`-twice for double `mov rX,sp`. Full evidence: docs/match_notes_wave22_C.md. Staging: staging/wave22_C/ (harness w22c.sh with STUBS support).
