# Wave 26-C Match Notes (Worker C: blocked revisit + bulk leaves-up)

## Summary
- **MATCHED (2):** 0x0801bf10 (ChipState_Advance_0801BF10, 164 B), 0x08042c04 (EntryState_08042C04, 172 B). Both verified via hardened protocol (clean-room recompile, link at true address, objcopy, dd with file-offset skip, cmp -l zero diffs, non-empty asserts at every step).
- **BLOCKED (7):** 0x0801f254, 0x08003fc8, 0x0801fcd0, 0x080482d8, 0x0804b514, 0x0801c56c (triaged), 0x0803643c (revisit, not re-attempted).
- **Not attempted (19):** triaged as complex (jump tables, high regs, sibling-allocation walls). Listed at end.

All staging in `staging/wave26_C/v_<addr>/f.c`. Section names `.text.w26c_<addr>`.

---

## MATCHED

### 0x0801bf10: ChipState_Advance_0801BF10 (164 B, 0 diffs, old_agbcc)
State-machine dispatch on `s[13]` for chip initialization.
- **case 0:** if `(u8)(s[119]-3) <= 1`, loads `t = ((u8*)0x08226884)[s[17]]`, calls `ChipInit_080178A8(t, (s[35]&15), 0x3C00, 0, *(s+44))` (5th param on stack → `sub sp,#4`), then `SetBit16(*(s+44), 3)`, `ChipSlot_IncUse(s, 1)`, `s[13]++`.
- **case 1:** if `GetField17_U8(*(s+44)) > 5`, `ChipSlot_IncUse(s, 2)`, `s[13]++`.
- **case 2:** if `(u8)(s[119]-3) <= 1`, `MaxAssign_17(*(s+44), 7)`, return 1.
- Returns 0 otherwise. Cases 0/1 share the `ChipSlot_IncUse; s[13]++` tail via `b`.
- **Decisive idioms:** (1) `(s[35] & 15)` must be written as `((u32)s[35] << 28) >> 28` to get ROM's `lsls r1,#28; lsrs r1,#28` (plain `& 15` gives `movs`+`ands`). (2) No `ret` variable — direct `return 0/1` avoids extra `push {r5}`. (3) `0x3C00` as `(0xF0 << 6)` gives `movs r2,#240; lsls r2,#6`.
- True extent 164 B (no trailing pool; pool at 0x801bf6c inline).

### 0x08042c04: EntryState_08042C04 (172 B, 0 diffs, old_agbcc)
Switch on `s[5]` managing entry-manager states.
- **case 0:** `Set_08004E24(0)`, `s[5]++`, fall through.
- **case 1:** `EntryMgr_Teardown()`; if `(Cmp_08004E0C(3) << 24) != 0`, mask `*(0x020031e0)` by `0xEDFF` then `0xDBFF` (two separate `&=` statements — single expression `(v & 0xEDFF) & 0xDBFF` folds to one `& 0xC9FF`), `s[5]++`; `EntryMgr_Setup()`.
- **case 2:** `PalModeSet_4DFC(*(0x02004f80+2))`, `s[5]++`, fall through.
- **case 3:** `EntryMgr_Teardown()`; `r = (Cmp_08004E0C(0) << 24) >> 24` (the shift form is REQUIRED to get `asrs` — plain `(s8)` cast gives `lsrs` in this agbcc); if `r == 0`, copy `s[4]`→`s[7]` then set `s[4]` to 3 (if old `s[7]==1`) or 1, zero `s[5]`/`s[6]` via `(u8)r`; `EntryMgr_Setup()`.
- **Decisive idioms:** (1) `(x << 24) >> 24` for signed narrowing (`asrs`), not `(s8)` cast. (2) Split `&=` statements to defeat constant folding and force two pool loads.
- True extent 172 B (pools at 0x8042c58/5c/60/94 inline).

---

## BLOCKED

### 0x0801f254: Reset_0801F254 (164 B, ~6 insns + 8 B short, old_agbcc)
Struct reset + table-driven field update. Sibling of 0x0801fcd0/0x0802375c/0x0802298c.
- **What it does:** zeroes `*(s+108)`, sets `s[10] = (s[10]|2)&0xFE`, clamps `s[17]` to 39 (remainder to `s[121]`), computes `b = s[120] | ((s[35]&15) ? 0x100 : 0)`, calls `Wrapper_D728(s, b, s[121])`, table lookup via `0x081705b0`/`0x020031e4` to set `s[69]` bits, `s[34] = 16`, calls `F_20230(s, *(s+40), 0)`.
- **Blocker:** v/c register allocation. Natural C gives v→r2,c→r1; ROM has v→r1,c→r2. Clobber-reservation `__asm__ volatile("" : "+r"(v) : : "r2","r3")` forces v→r1,c→r2 and matches through the `s[120]`/`s[121]` stores, BUT the `s+121` address then allocates to r3 (ROM: r1), cascading to w→r1 (ROM: r3) and missing the `adds r2,r1,#0` copy before `cmp`. Tried: declaration reorder, u32 pins (ignored), explicit temp for the `adds r0,r1,#0` copy (works but doesn't fix v→r1), `u8 *q` variable (worse, uses ip), denying r3 via clobber on address var (uses ip).
- **Best:** `staging/wave26_C/v_0801f254/f_best.c` (v-clobber version, 156 B vs 164 B ROM).
- **True extent:** 164 B (0x801f254–0x801f2f8; pools `0x081705b0`, `0x020031e4`).

### 0x08003fc8: Setup_08003FC8 (176 B, 154 diffs, old_agbcc)
Bitfield struct setup with high-register pressure.
- **What it does:** `SetU32_4(s, 0x08004079)`, manipulates `s[13]`/`s[17]` bitfields with `-33`/`-13` masks, zeroes `s[18]`/`s[19]`/`s[12]`, stores param `b` to `*(s+8)`, derives fields from param `c` (`(c>>2)<<6`, `(c&3)<<6`), masks `*(s+16)` with `0x3FF`/`0xFFFFFC00` using param `d`, masks `*(s+14)` with `0xFFFFFE00`.
- **Blocker:** high-reg allocator wall. ROM uses r8=(u8)c, r9=0, sl=b, r5=c, r6=d (all callee-saved, live across `bl SetU32_4`). Natural C spills the `(u8)c` copy to stack and puts the zero in r8 (swapped vs ROM). Also: ROM uses `negs` for -33/-13 (source likely wrote negative constants, not `~32`/`~12`).
- **True extent:** 176 B (pools `0x08004079`, `0x3FF`, `0xFFFFFC00`, `0xFFFFFE00` at 0x804068–0x804078).

### 0x0801fcd0: Reset_0801FCD0 (188 B, 142 diffs, old_agbcc)
Sibling of 0x0801f254 with extra table lookups.
- **What it does:** same reset pattern (`*(s+108)=0`, `s[10]|=3`), calls `Wrapper_D728(s, (s[35]&15)?0x3a18:0x3918, 0)` (pool-chosen arg), `ChipSlot_IncUse(s, 0)`, same `0x081705b0`/`0x020031e4` table lookup, `s[34]=31`, then `*(s+96) = tbl[((p5[35]&15)<<3)] - *(p5+80)` and `*(s+100) = tbl[4+((p5[35]&15)<<3)] - *(p5+84)` where `p5 = *(s+40)`, `tbl = 0x08226e48`, `s[18]=0`, `SelBlob_Ret(0x6f)`.
- **Blocker:** same v/c allocation wall as 0x0801f254, plus the `0x3a18`/`0x3918` pool args get unwanted `lsls`/`lsrs` narrowing when cast to u16 (absolute-symbol trick forces pool but not the width).
- **True extent:** 188 B (5 pools at 0x801fd78–0x801fd8c).

### 0x080482d8: F_080482D8 (168 B, 73 diffs, old_agbcc)
State machine with indirect dispatch via `_call_via_r1`.
- **What it does:** switch on `s[3]` (0: `Call4E60_4E44()` + `PalModeSet_4DFC(*(0x02004f80+2))` + `s[3]++` fallthrough; 1: indirect call `fn = ((u32*)0x08234328)[*r5]` where `r5 = s+0x46a4`, then dispatch on `u8 ret`: 2/5/6 set `s[2]=4,s[3]=0` with `*r5=4`/`*r5=ret`/`*(s+0x46b7)=ret` and `*(s+0x46a5)=0`, else `s[2]=3,s[3]=0`).
- **Blocker:** agbcc emits an extra `adds r1,r2,#0` after `bl _call_via_r1` (copies ret to r1) not in ROM. Tried: direct function-pointer call, inlined call, `tblbase` variable (fixes `ldr` order but not the copy), explicit inline-asm `bl` (worse, breaks r0=s setup). The copy persists across all variants.
- **Note:** `*r5 = ret` (not constant) for the ret==5 case; `*(s+0x46b7) = ret` for ret==6. Two separate pool entries for `0x46a5` (same value, must not CSE).

### 0x0804b514: F_0804B514 (182 B, 95 diffs, old_agbcc)
Jump-table switch (`mov pc,r0`) on `s[3]`, cases 0–4.
- **Blocker:** jump table generates correctly, but the 5 case bodies diverge (95 diffs, 6 B long). Cases involve `Cmp_08004E0C`, `NewNode_0802030C`, `F_08002FD4`, bit ops on `s[10]`, `*(s+6)` countdown. Needs per-case body work.
- **Jump table:** base pointer at 0x804b528 → entries at 0x804b52c (5 addresses).

### 0x0801c56c: F_0801C56C (186 B, not attempted)
Switch on `s[13]` with `ldrsh` (sign-extending halfword loads at 0x801c5bc, 0x801c5c4). Per w25d, agbcc NEVER emits ldrsh/ldrsh from C — requires inline-asm transcription (wave7 precedent). Triaged as needing asm-staging; not attempted in this wave.

### 0x0803643c: WalkBits_0803643C (444 B, 60 diffs — revisit, not re-attempted)
- Per docs/match_notes_wave25_D.md: 3 hoisted `0x10000` constants (`movs r1,#128; lsls r1,#9`) inside loops are undefeatable in this gcc (14 `-fno-*` flags tried, all compilers) — needs Makefile-style `.s` sed. Register allocation also diverges (gcc r5/r7/r9 vs ROM r6/r8/ip/r9). The w25d v3 C source is in `staging/wave25_D/w25d_0803643c_v3.c`. As a worker I stage only; the `.s` sed on a 444 B function with allocator divergence is coordinator-level work. Left for coordinator.

---

## Triaged (not attempted)
Quick scans show these are complex (jump tables, high regs, sibling-allocation walls, or large):
- 0x0802d6e0 (192 B): jump-table switch, calls Cmp_08004E0C/Set_08004E24.
- 0x0802375c (198 B): sibling of 0x0801f254 (same reset pattern), calls ChipSlot_Setup/ChipSlot_IncUse.
- 0x0801b0dc (208 B), 0x0801c030 (214 B): not scanned in detail.
- 0x0802298c (220 B): sibling of 0x0801f254 (same `*(s+108)=0`, `s[10]|=3` pattern).
- 0x0801e77c (254 B): struct-array indexing + switch, 6 callees.
- 0x0801c428 (278 B), 0x08049560 (278 B): not scanned.
- 0x0800ac8c (294 B), 0x080203e0 (306 B): high regs (r8/r9/sl).
- 0x08001f1c (334 B), 0x08002070 (340 B): switch state machines, Sram callees.
- 0x0804d8a8 (344 B): jump table (`mov pc,r0`), `_call_via_r2`.
- 0x08027400 (358 B): 14 callees.
- 0x0803aaa8 (412 B), 0x0804b124 (492 B): not scanned.
- 0x0801e208 (706 B): not scanned.
- 0x0800f4f8 (1188 B), 0x0800ef40 (1464 B): large, not scanned.

## Lessons
1. **`(x << 24) >> 24` for `asrs`:** plain `(s8)` cast gives `lsrs` in this agbcc; the explicit shift form is required for arithmetic shift narrowing (0x08042c04).
2. **Split `&=` to defeat folding:** `(v & 0xEDFF) & 0xDBFF` folds to `& 0xC9FF`; separate statements force two pool loads (0x08042c04).
3. **Shift-mask for `& 15`:** `(s[35] & 15)` gives `movs`+`ands`; `((u32)s[35] << 28) >> 28` gives ROM's `lsls`/`lsrs` (0x0801bf10).
4. **No `ret` variable:** a return-value local adds `push {r5}`; direct returns avoid it (0x0801bf10).
5. **Clobber-reservation for v→r1:** `__asm__ volatile("" : "+r"(v) : : "r2","r3")` forces v→r1,c→r2, but downstream allocation (s+121 address →r3 vs r1) remains stubborn (0x0801f254).
6. **True extents:** layer TSV sizes exclude pools; always verify against next-function start (0x0801f254: 164 not 154; 0x08003fc8: 176 not 160).
