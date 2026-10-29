# Wave 14 Worker A (TAG=A) — Task_3AFFC Path: sub_0800B148 + Task_3AFFC Retry — Match Notes

Worker: Wave 14 specialist (TAG=A). Date: 2026-10-22.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}`; `arm-none-eabi` 2.42 (present).
Harness: `staging/wave14_A/mk.sh` (adapted from wave13_C; hardened assertions,
file offset = addr − 0x08000000, full extent incl pools, `cmp -l`).
Staging: `~/workspace/mmbcc-decomp/staging/wave14_A/` (27 B148 versions + 1 3AFFC retry; NEVER delete).
Results: `docs/wave14_A_results.tsv`.

**Result: BOTH BLOCKED.**
- **sub_0800B148 @ 0x0800B148: BLOCKED.** Best: 213 diffs (v25, 364/340 B, old_agbcc)
  with 82-byte exact prefix (bytes 0–42). 27 versions iterated. Final saved version
  (w14a_0800b148_FINAL.c) has 230 diffs due to memcheck restructuring.
- **Task_3AFFC @ 0x0803AFFC: BLOCKED.** Retry: 363 diffs (928/928 B, old_agbcc),
  unchanged from wave11_C v18. BEE0 signature corrected to `(u32,u32)` (was
  `(u16,u8)`); no diff change. 3 landed callees do not unblock modes (separate
  functions; 3AFFC bytes independent).

## sub_0800B148: New Idioms Discovered (Wave 14)

### 1. Widened-temp `& -N` → `movs`+`negs` (CRITICAL, 5 sites)
**Probe result:** `u32 t = p[30]; t &= -65; p[30] = t | 1;` yields
`movs r1,#65; negs r1,r1; ldrb r2,[r0,#30]; ands r1,r2` (old_agbcc).
**Rule:** The `& -N` must be a separate `&=` statement on a widened (u32/int)
temporary. If `& -N` appears directly in the store expression
(`p[30] = (p[30] & -65) | 1`), combine narrows to `& 191` (`movs r1,#191`).
**Applies to:** -2 (0x800B188), -65 (0x800B1E6), -32 (0x800B20E), -16 (0x800B22A),
-33 (0x800B242). All 5 sites in B148 use this idiom.

### 2. Pinned b4→r1 forces `ands r0,r1` (site2 blocker SOLVED)
**Probe result:** With `register u8 b4 __asm__("r1")`, `(b4 & 128)` yields
`movs r0,#128; ands r0,r1` (result in r0, r1 preserved). Without pin,
`ands r1,r0` (in-place, r1 clobbered).
**Mechanism:** The pinned register cannot be reused as AND destination;
compiler materializes constant in fresh r0.
**Applies to:** Site1 (`mask & b4` → `adds r0,r2,#0; ands r0,r1`) and
Site2 (`b4 & 128` → `movs r0,#128; ands r0,r1`). Both now exact in v25.

### 3. `sh` temp forces shift-before-copy ordering (v21 site SOLVED)
**Problem:** `v21t = base[21]; v21 = v21t; if ((((u32)v21t<<28)>>28) != aa)`
gave `adds r4,r1` BEFORE shifts (wrong order).
**Solution:** Introduce `u32 sh = ((u32)v21t << 28) >> 28;` temp, then
`v21 = v21t; if (sh != aa)`. Forces: `ldrb r1; lsls r0,r1,#28; lsrs r0,r0,#28;
adds r4,r1,#0; cmp r0,ip` (exact ROM order).
**Also:** Declaring `aa` as `u32` (not `u8`) pinned to ip avoids the
zero-extend (`lsls r0,r7,#24; lsrs r0,r0,#24`) before `cmp r0,ip`.

### 4. Explicit asm for c1/t19/base[5] block (0x38–0x4A EXACT)
**ROM sequence:**
```
38: movs r2,#1; mov r1,r8; ands r1,r2     (c1 = c & 1)
3e: movs r0,#2; negs r0,r0; ldrb r3,[r5,#19]; ands r0,r3; orrs r0,r1;
48: strb r0,[r5,#19]                       (base[19] = (base[19] & -2) | c1)
4a: strb r2,[r5,#5]                        (base[5] = 1, reuses r2=1)
```
**C cannot achieve this:** Compiler won't use r2 for the constant 1 (mask
occupies r2, even though dead in this path). Explicit divided-syntax asm
(`and`/`neg`/`orr` without S, 3 operands) forces exact bytes.
**Note:** `ands r1,r2` in asm template fails ("not supported in Thumb16");
must use `and r1, r1, r2` (divided syntax).

### 5. b16 pinned r3 for hoisted `lsls` (3 sites)
**ROM:** `lsls r3,r6,#16` appears at 0x4E, 0x76, and (as `adds r3,r0,#0` copy)
at 0x82. All feed join's `asrs r0,r3,#16`.
**Solution:** `register s32 b16 __asm__("r3")`; assign `b16 = ((s32)bb) << 16`
in each path. At join: `sub_0800B470((s16)(b16 >> 16))` → `asrs r0,r3,#16`.
(s32, not u32, gives arithmetic shift.)
**0x76 site:** Requires asm `lsl %0,%1,#16` placed between `cmp #2`/`beq` and
`cmp #4`/`bne` — C cannot schedule it there.

### 6. b16 variable breaks prologue (CAUTION)
**Finding:** Adding a function-scope `s32 b16` (even natural, unpinned)
changes prologue from `push {r4-r7,lr}` to `push {r4-r5,r6,lr}` (drops r7).
**Workaround:** Pin b16 to r3 (`register s32 b16 __asm__("r3")`); prologue
restored. Mechanism unclear (register pressure affecting save set).

## sub_0800B148: Residual Blockers (why 0 diffs not achieved)

### R1. Memcheck b16 copy (`adds r3,r0,#0` at 0x82)
**ROM:**
```
7c: lsls r0,r6,#16   (bfresh)
7e: ldrh r3,[r5,#6]
80: lsls r1,r3,#16   (m16)
82: adds r3,r0,#0    (b16 = bfresh)
84: cmp r1,r3
```
**Problem:** C cannot produce the `adds r3,r0,#0` copy. If `b16 = bfresh`
in C, compiler either omits the copy (uses r0 directly) or schedules
differently. The copy exists because b16 (pinned r3) must be set for join,
but the compare uses the fresh r0 value.
**Tried:** Natural C (wrong order/regs), bfresh pinned r0 (wrong scheduling),
full asm block (adds bytes for flag). **Resists.**

### R2. t21 `ands r0,r4` vs `ands r4,r0` (at join, 0xE4)
**ROM:** `movs r0,#16; negs r0,r0; ands r0,r4` (r0 = -16 & v21, r4 preserved).
**Ours:** `ands r4,r0` (in-place on pinned v21).
**Problem:** `t21 &= -16` where t21 aliases pinned v21 (r4) does in-place.
The widened-temp idiom (which works for natural vars) fails for pinned vars.
**Hypothesis:** Pinned register variables are treated as modifiable in-place
for `&=`; no C formulation found to force fresh-reg result while keeping
v21 pinned (needed for other sites).

### R3. Path A `orrs` destination (`orrs r0,r1` vs `orrs r1,r0`)
**ROM:** `orrs r0,r1` (r0 = (mask&v21) | (aa<<4)).
**Ours:** `orrs r1,r0`.
**Problem:** Compiler chooses r1 (first-computed (aa<<4)) as destination.
Minor 2-byte diff; resists C-level control.

### R4. Size (364–368 vs 340 B; +24–28 bytes)
Extra bytes from: asm blocks (c1/t19, tm lsls), `sh` temp, v21t pin,
b16 assignments. The ROM achieves the same semantics in fewer bytes via
tighter allocation that resists reproduction.

## sub_0800B148: Best Version Summary (v25, 213 diffs)

**Exact regions (82-byte prefix + blocks):**
- Bytes 0–42: prologue through site2 (`ands r0,r1` at both sites) ✓
- 0x38–0x50: c1/t19/base[19]/base[5]/v21/b16 block (via asm) ✓
- 0x52–0x5A: v21 load/shift/compare (`ldrb r1; lsls r0,r1; lsrs; adds r4,r1; cmp r0,ip`) ✓
- 0x70–0x7C: tm site (`ands r2,r4; adds r0,r2; cmp #2; beq; lsls r3,r6; cmp #4; bne`) ✓

**Blocked regions:** memcheck (R1), join t21 (R2), Path A orrs (R3).

## Task_3AFFC Retry

**Method:** Copied wave11_C v18 (363 diffs) to wave14_A; corrected BEE0
signature from `(u16,u8)` to `(u32,u32)` per landed `SyncObjFlagBits_BEE0`.
Rebuilt with old_agbcc.

**Result:** 363 diffs (unchanged). The signature fix did not affect codegen
at the BEE0 call site (arguments already in r0/r1; extension differences
optimized away).

**Conclusion:** The 3 landed callees (BEE0, 241F8, 24384) do not unblock
3AFFC modes. 3AFFC's blockers (per wave11_C notes) are:
- Mode 2/4 `lsls;ldr;lsrs` interleave (compiler fuses shifts)
- TailC sharing via goto disrupting modes 10–15
- Register allocation (g8 in r1 vs r2, per-mode ldr variation)
These are independent of callee signatures. B148 (blocked) is the 4th
callee; 3AFFC cannot match until B148 lands (call target must resolve).

## Files
- `staging/wave14_A/w14a_0800b148_FINAL.c` — best B148 (230 diffs; 213 achieved
  transiently in v25 before memcheck asm regression)
- `staging/wave14_A/w14a_3affc_v1.c` — 3AFFC retry (363 diffs)
- `staging/wave14_A/probeA.c` … `probeG.c` — idiom probes (widened-temp,
  pinned b4, u32 aa, sh temp)
- `staging/wave14_A/mk.sh` — harness

## What's Next for the 3AFFC Path
1. **B148:** The memcheck b16 copy (R1) and t21 in-place (R2) are the critical
   blockers. If solved, B148 may land, unlocking 3AFFC's 4th callee.
2. **3AFFC:** Even with B148 landed, the mode 2/4 interleave and TailC sharing
   need dedicated work (per wave11_C notes). The JT is inline and correct;
   modes 0–9 are 91% identical.
3. **Idioms to propagate:** Widened-temp `& -N`, pinned b4→r1, `sh` temp
   ordering, u32 aa to avoid extend, asm for r2-reuse blocks. These apply to
   other bitfield/state-machine functions in the 144 blocked.
