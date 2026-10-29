# Wave 27-C Worker Notes (BlendCopy twins + bulk)

## Summary
- **Attempted:** 3 functions (twins, 0x0801c030, 0x0801b0dc). All BLOCKED with precise walls documented.
- **Not attempted:** 9 bulk functions (triaged by complexity/time).
- **Key new idiom:** Single mask→r9 pin solves the BlendCopy high-reg rotation (v11).

## 0x080224e4 / 0x08021b3c — BlendCopy (206 B, BLOCKED, 104 diffs best)

15-bit color blender. Twins are identical except the `bl Memcpy16` encoding.

### Progress
The high-register rotation wall (w26d: gcc srcA→r9/srcB→r8/mask→ip vs ROM r8/ip/r9) is **SOLVED**.

**Decisive idiom:** Pin ONLY `mask` to r9 (`register int mask __asm__("r9") = 31;`).
With mask taking r9, gcc's remaining high-reg allocation gives srcA→r8, srcB→ip —
exactly ROM's assignment. Theory: gcc's high-reg preference order is r9 > r8 > ip;
denying r9 to the highest-priority quantity (mask) shifts the others down by one.

This is a new variant of the pin idiom: **instead of pinning the variables you want
placed, pin the variable that's stealing the wrong register.** Less perturbation
than pinning all three (v7-v10 with 3-4 pins gave 133-173 diffs; single pin gives 104).

Prologue with the pin matches ROM byte-for-byte except 2 bytes:
- `mov r8, r1; mov ip, r2` ✓
- `lsls r3,r3,#24; lsrs r6,r3,#24` ✓ (blend zero-extend via split `bsh`/`bl`)
- `lsls r0,r0,#24; lsrs r0,r0,#19` ✓
- `ldr r1,[pc,#12]` ✓
- `adds r1, r0, r1` vs ROM `adds r0, r0, r1` ✗ (2 bytes)
- `str r1, [sp,#0]` vs ROM `str r0, [sp,#0]` ✗
- Branch structure (`cmp r6,#0; bne; mov r0,r8; b; ...; cmp r6,#14; bls; mov r0,ip`) ✓
- `movs r0,#31; mov r9,r0` ✓, `movs r1,#15; mov sl,r1` ✓
- Loop tail `movs r2,#1; negs r2,r2; add sl,r2; mov r4,sl; cmp r4,#0; bge` ✓ (only temp reg differs: r4 vs ROM r3)

### Remaining wall (104 diff bytes)
Systematic low-register allocator difference in the loop body:
1. **r3↔r4 swap:** ROM: av→r4, mask-copy→r3, b1→r3. Mine: av→r3, mask-copy→r1, b1→r4.
   The mask copy goes to r1 (mine) vs r3 (ROM) because av occupies r3 in mine.
   When bv's `ldrh r1` kills the mask copy (r1), mine rematerializes to r4; ROM's
   mask copy (r3) survives and is reused for b0's `ands r2, r3`.
2. **Loop-top copy:** `mov r7, ip` vs ROM `mov r2, ip`; `ldrh r3, [r7]` vs `ldrh r4, [r2]`.
3. **Mask init temp:** `movs r2, #31` vs ROM `movs r0, #31`.
4. **c0 finalize placement:** ROM does `lsrs r2,r2,#24` immediately after `lsls r2,r2,#24`;
   mine defers it to the pack region (formulation `s0=(x)<<24; ... (s0>>24)`).
   Tried `(u32)(u8)` cast — gcc restructured to 164 B (worse).
5. **Prologue adds dest:** `adds r1, r0, r1` vs `adds r0, r0, r1` (tried `d += const`, pinned COPY — no effect).

### Tried
- v6 (w26d draft5): 40 diffs (high-reg rotation only)
- v7-v10 (3-4 pins + structural): 133-173 diffs (pins perturb low-reg alloc)
- **v11 (single mask pin): 104 diffs** ← best
- v12 (clobber r3 at av birth): 104 diffs (no effect)
- v13 (av pinned r4): worse (structure broke)
- v14 (`(u32)(u8)` c0): 164 B (restructured, worse)
- v15 (u32 mask/i): 104 diffs (no effect)
- old_agbcc on v6/v11: 104-108 diffs
- -O1: 169 diffs, -Os: 167 diffs

### Staged
`staging/wave27_C/w27c_080224e4_v11.c` (best, 104 diffs), plus v6-v10, v12-v15.

## 0x0801c030 — ChipState_0801C030 (214 B, BLOCKED, 60 diffs best)

Chip state dispatch on s[13] (cases 0,1,2), sibling of matched 0x0801bf10.

### Progress
- Prologue matches ROM: `push {r4,r5,lr}; sub sp,#8; adds r5,r0,#0; ldrb r4,[r5,#13]`
  (achieved via `register u8 *sp __asm__("r5")` pin; vv unpinned goes to r4).
- Branch tree matches: `cmp r4,#1; beq; cmp r4,#1; bgt; cmp r4,#0; beq; b; cmp r4,#2; beq; b`.
- Case 0 matches (SetBit16, ChipSlot_IncUse, s[18]=3, s[19]=v).
- Case 2 matches (MaxAssign_17, return 1).

### Remaining wall (60 diffs, in case 1)
1. **ldrsh index:** ROM: `movs r6, #0; ldrsh r3, [r3, r6]` (twice). Mine uses r4 as index
   (or ldrh). The `z` variable won't go to r6. Tried pinning z→r6 (ignored).
   Root cause: passing s16 d/e to u16 params causes gcc to use ldrh; declaring
   extern with s16 params fixes ldrsh but index reg is wrong.
2. **s[19] reuse:** ROM reuses r4 (vv's reg) for s[19] via `ldrb r4, [r5, #19]`.
   Achieved by reassigning `vv = sp[19]` in case 1.
3. **Pool order:** ROM: `adds r0, r4, r0` (pool in r0). Mine: `adds r0, r0, r1` (pool in r1).

### Tried
- v1 (if/else): wrong structure
- v2 (switch): 114 diffs, 216 B
- v3 (pins): 152 diffs
- **v4 (sp pin only, vv unpinned): 60 diffs, 216 B** ← best
- v5-v8 (ldrsh attempts): 208-212 B, wrong index reg

### Staged
`staging/wave27_C/w27c_0801c030_v4.c` (best, 60 diffs), plus v1-v3, v5-v8.

## 0x0801b0dc — ChipSetup_0801B0DC (208 B, BLOCKED, 16 diffs best)

Chip setup dispatch on s[17] (cases 0,1,2) with common tail doing table lookup.

### Progress
- Switch cases 0-2 match ROM (ChipSlot_Setup/Wrapper_D770/ChipSlot_IncUse calls,
  struct field stores).
- **old_agbcc is decisive:** 16 diffs (vs 25 with main agbcc on same C).
- Tail mostly matches; 16 diff bytes in the clamp/shift region.

### Remaining wall (16 diffs)
1. **Clamp:** ROM: `movs r1, #3` BEFORE `ldrb r0, [r0]`; `ands r1, r0`; `adds r0, r1, #0`;
   `cmp r0, #3; ble; movs r1, #3`. Mine: `ldrb` first, `movs r2, #3`, no `adds` copy,
   `cmp r2, #3; bls`. The `adds r0, r1, #0` copy resists all formulations tried.
2. **Shift:** ROM: `lsls r1, r1, #2`. Mine: `lsls r0, r1, #26; lsrs r1, r0, #24`
   (u8 `t <<= 2` needs zero-extend; int t perturbs earlier allocation).
3. **p69 reg:** ROM: r2. Mine: r3.

### Tried
- v1: 51 diffs, 216 B
- v2 (negs idiom): 49 diffs, 220 B
- v3 (reordered): 25 diffs, 220 B (main agbcc)
- **v3 + old_agbcc: 16 diffs, 220 B** ← best
- v4-v9 (int t, inline shift, pins, int cast): 44-49 diffs (worse)

### Staged
`staging/wave27_C/w27c_0801b0dc_v3.c` (best with old_agbcc, 16 diffs), plus v1-v2, v4-v9.

## Idioms discovered
1. **Pin-the-thief (v11 BlendCopy):** To fix a high-reg rotation, pin ONLY the variable
   that's occupying the wrong register, not the variables you want placed. The thief
   taking r9 forces the others into the correct homes (r8, ip) via gcc's preference
   order (r9 > r8 > ip). Less perturbative than pinning all.
2. **old_agbcc for tail allocation (0x0801b0dc):** old_agbcc's scheduler/allocator
   gives 16 diffs vs 25 for main agbcc on identical C. Always try old_agbcc on
   near-misses, even when main agbcc is close.
3. **s16 extern params force ldrsh:** Declaring an extern function with s16 params
   (instead of u16) forces `ldrsh` loads for s16 locals passed to it. Same calling
   convention; coordinator should restore u16 signature at landing.
4. **Reuse switch var for later loads (0x0801c030):** Reassigning `vv = sp[19]` in
   case 1 reuses r4 (vv's dead register) for the new value, matching ROM's
   `ldrb r4, [r5, #19]`.

## Tooling issues
- **binutils PATH outage (3x):** `/usr/bin/arm-none-eabi-*` disappeared mid-session
  three times. Reinstalled via `sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb`.
  This is a recurring environment issue; consider adding to TOOLS.md.
- **/tmp wipe:** Staging files in /tmp were lost (as warned in brief). Used
  `staging/wave27_C/` for all work per protocol.

## Not attempted (triaged)
- 0x08002d6e0 (192 B): Jump-table switch, 5 complex cases.
- 0x0802375c (198 B), 0x0802298c (220 B): 0x0801f254 sibling family, known v/c wall.
- 0x08002a1c (210 B): Contains ldrsb (needs inline asm).
- 0x080046b0 (238 B): Complex gfx, CpuFastSet, high-reg pressure.
- 0x08003ac4c (238 B): Multiple branches.
- 0x0801e77c (254 B): Switch on p[14], stack args.
- 0x080096bc (260 B): Tile-copy loop, 5 params.
- 0x08006fe8 (264 B): 6 params, GetPtr family.
- 0x08024a30 (268 B): 11 callees.
