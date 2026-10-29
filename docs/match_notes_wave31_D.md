# Wave 31-D Match Notes (Worker D, bulk leaves-up)

Worker D, 2026-10-24. Staging: `staging/wave31_D/` (C sources, verify.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: all 10 matched targets NOT-IN-REGISTRY (verified 2026-10-24).
No claims made (coordinator lands per DO-NOT-LAND rule).

## Recomputed leaves-up layer (Wave 31)

Generated via `docs/gen_wave31_layer.py` (adapted from wave26 script):
- 17 candidates, UNMATCHED/INTERIOR with all callees MATCHED/ASM/INTERIOR.
- Excluded: leave-alones (Vec2_CopyMirrored, Sram_VerifyCompare, MainLoop, ChipSlot_Tick, B3),
  L1 dispatchers, and Worker-B trio (0x080096BC/0x08006FE8/0x08024A30).
- Sorted by caller count (desc), then size (asc).

| Address | Size | Callers | Callees | Status |
|---------|------|---------|---------|--------|
| 0x080062b4 | 90 | 10 | 0x08006374 | ✅ MATCHED |
| 0x080070f0 | 58 | 9 | 0x08007134 | ✅ MATCHED |
| 0x080073d4 | 62 | 6 | 0x08007134 | ✅ MATCHED |
| 0x08007378 | 78 | 2 | 0x08006ad8 | ✅ MATCHED |
| 0x080363ec | 78 | 2 | 0x080217a8, 0x0803643c | ✅ MATCHED |
| 0x08006318 | 82 | 2 | 0x08006374 | ✅ MATCHED |
| 0x080249b8 | 118 | 2 | 0x080258d8, 0x080259a4 | ❌ BLOCKED (16 diffs) |
| 0x08008b08 | 176 | 2 | 0x08007134 | ⏸️ not attempted (complex) |
| 0x0800695c | 246 | 2 | 0x08006ad8 | ⏸️ not attempted (complex) |
| 0x08006aa0 | 52 | 1 | 0x08006ad8 | ✅ MATCHED |
| 0x0803639c | 54 | 1 | 0x0803643c | ✅ MATCHED |
| 0x08007678 | 166 | 1 | 0x08006374 | ❌ BLOCKED (pool/allocation) |
| 0x08036338 | 60 | 0 | 0x0803643c | ✅ MATCHED |
| 0x08006518 | 86 | 0 | 0x080065bc | ✅ MATCHED |
| 0x0800cd5c | 138 | 0 | 0x0800520c, 0x0800d1e0 | ❌ BLOCKED (pool folding) |
| 0x080221cc | 172 | 0 | 0x0800d6e0, 0x0800d9ec, 0x080224e4 | ⏸️ not attempted (complex) |
| 0x0801e77c | 254 | 0 | 6 callees | ⏸️ not attempted (176 diffs in w29/w30) |

**Result: 10/17 MATCHED.**

## MATCHED (10)

All verified via clean-room: cpp → agbcc/old_agbcc -O2 -mthumb-interwork → as →
ld at true ROM address (custom .ld) → objcopy → cmp vs baserom extract.
Non-empty assertions at every step. 0 diffs, full extents.

### 1. 0x080363EC — ChangedBitsInit_080363EC (78 B, 0 diffs, old_agbcc) ✅
Staged: `staging/wave31_D/w31d_080363ec_MATCHED.c`
Verify: `./verify.sh 0x080363ec 78 .text.w31d_080363ec w31d_080363ec_MATCHED.c old`
→ `sizes: o=972 elf=1680 bin=80`, `diffs: 0`.

**Behavior:** If `p[3] != p[2]`, for each newly-set bit `i` in `(p[2]^p[3])&p[2]`
(bits 0-6), calls `NodeInit_080217A8(i)`; then `p[3]=p[2]` and calls
`WalkBits_0803643C((s8)p[1], 0, 0)`.

**Key techniques:**
- do-while with `i = (u16)(j+1)` gives ROM's two-var loop shape
  (`lsls r0,r2,#16; asrs r4,r0,#16` at top, `adds r0,r4,#1; ...; lsrs r2` at bottom).
- Inline asm for `ldrsb` (agbcc never emits it): `movs r0,#1; ldrsb %0,[%1,r0]`
  with `=r` output pinned to r0 (s32 to avoid re-extension).
- The `beq` skips the entire if-body including the WalkBits tail (tail is INSIDE the if).

### 2. 0x080070F0 — CondRectFill_080070F0 (58 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_080070f0_MATCHED.c`
**Behavior:** If `*(u8 *)(0x02004830+0x265)` set, return; else
`RectFill_7134(base, x, (s16)y, (s16)z, w)`. Matched first try.

### 3. 0x080073D4 — CondRectFill_080073D4 (62 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_080073d4_MATCHED.c`
**Behavior:** Flag check, then `RectFill_7134(base, (x<<2)|y, (s16)z, (s16)w, 2)`.
Callee param1 declared `int` to avoid u16 truncation code. Matched first try.

### 4. 0x08007378 — CondTilemapRectFill_08007378 (78 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_08007378_MATCHED.c`
**Behavior:** Flag check; if `mode != 0`, `t = ((u32 *)0x08171ee0)[mode-1]`;
then `TilemapRectFill_6AD8(base, t, (s16)x, (s16)y, 2, z)`.
**Key techniques:**
- Pin `t` to r1 to get `movs r1,#0` before flag check and correct allocation.
- Opaque `+r` barrier on tbl base defeats `-4` pool folding; explicit `int m = mode-1`
  gives ROM's `subs r0,r4,#1` (not `lsls; adds; subs #4`).
- Separate `t = 0;` statement (not initializer) forces `movs r1,#0` before base load.

### 5. 0x080062B4 — CondRectFill_080062B4 (90 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_080062b4_MATCHED.c`
**Behavior:** Flag check (base in ip, w in r8); then
`FillRect_6374(base, (s8)x, (s8)y, w, h, a, b, c)`. Matched first try.
(10 callers — highest value.)

### 6. 0x08006518 — CondRectFill_08006518 (86 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_08006518_MATCHED.c`
**Behavior:** Same as 0x062b4 but calls `FillRect_65BC` (7 params, no 8th).
Matched first try.

### 7. 0x08006AA0 — TilemapFill_08006AA0 (52 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_08006aa0_MATCHED.c`
**Behavior:** No flag check; `TilemapRectFill_6AD8(0x0200483c, t, (s16)x, (s16)y, (s8)z, w)`.
Params: `(u32 t, int x, int y, int z, u8 w)`; callee param5 declared s8 for sign-extension.
Matched first try.

### 8. 0x08006318 — CondRectFill_08006318 (82 B, 0 diffs, main agbcc) ✅
Staged: `staging/wave31_D/w31d_08006318_MATCHED.c`
**Behavior:** Flag check; then `FillRect_6374(base+12, (s8)x, (s8)y, w, h, a, b, c)`.
**Key technique:** Pin `base` to r1 defeats gcc's folding of `base[0x265]` to
absolute `0x02004A95` pool load; gives ROM's `ldr r1; ldr r2; adds r0,r1,r2` sequence.

### 9. 0x0803639C — CondBitSet_0803639C (54 B, 0 diffs, old_agbcc) ✅
Staged: `staging/wave31_D/w31d_0803639c_MATCHED.c`
**Behavior:** If `(x&1)`, `p[4] = 2|p[4]`; else `p[1] = WalkBits_0803643C((s8)p[1], x, 1)`;
return `(s8)p[1]` (as int to avoid re-extension).
**Key techniques:**
- Pin constant `2` to r0 gives ROM's `movs r0,#2; ldrb r1,[r4,#4]; orrs r0,r1` order.
- `ldrsb` via inline asm; int return avoids sign-extension bytes.

### 10. 0x08036338 — ClearBitWalk_08036338 (60 B, 0 diffs, old_agbcc) ✅
Staged: `staging/wave31_D/w31d_08036338_MATCHED.c`
**Behavior:** If bit `x` of `p[2]` set, clear it (`p[2] ^= 1<<x`),
`p[1] = WalkBits_0803643C((s8)p[1], 0, 0)`, return 1; else return 0.
**Key techniques:**
- Pin `x` to r2 matches ROM's `adds r2,r0,#0`.
- Named `u8 b2 = p[2]` local keeps it live in r1 (vs reload).
- Swap if/else so bit-set path is fall-through (`beq` to else).
- WalkBits declared `(int,int,int)` to avoid s8 re-extension after ldrsb.

## BLOCKED (3, with precise diffs)

### 0x080249B8 — 16 diffs (r1↔r2 regalloc wall)
Best: `staging/wave31_D/w31d_080249b8_v3.c` (old_agbcc, pin base→r0).
Structure, branches, and calls all match. The q-computation
`base + base[432]*144` allocates 432-constant to r2 and temps swapped vs ROM's
r1. Tried: natural, `q+=`, named v, pin base→r0, pin 432→r1, main vs old.
The pin helps (17→16) but the r1↔r2 swap persists. May need .s patch or
different expression shape.

### 0x08007678 — BLOCKED (pool/allocation, ~38 B short)
`staging/wave31_D/w31d_08007678_v2.c`. v pinned to r4 works, table lookup
matches, but ctx (0x0200483c) gets hoisted by CSE (ROM loads it in each branch
via separate pools), and `0x08170e7c+28/+44` folding needs opaque base.
Complex; parked.

### 0x0800CD5C — BLOCKED (pool folding, 2 B short)
`staging/wave31_D/w31d_0800cd5c_v1.c`. State machine structure matches.
Wall: gcc folds `0xedff & 0xdbff` → `0xc9ff` single pool; barrier defeats it
but layout shifts 2 B. Also case2 `movs r0,#0` ordering vs stores.
Parked.

## New idioms discovered

1. **do-while two-var loop:** `do { j=(s16)i; ...; i=(u16)(j+1); } while ((s16)i<=6);`
   reproduces ROM's u16-shadow + s16-use loop shape exactly.
2. **ldrsb via pinned s32:** `register s32 v __asm__("r0"); __asm__ volatile("movs r0,#1\n\tldrsb %0,[%1,r0]" : "=r"(v) : "r"(p));`
   deterministic; declare callee params widened (int) to avoid re-extension.
3. **Pin base to defeat absolute fold:** `register u8 *base __asm__("r1") = (u8 *)0x02004830;`
   prevents `base[0x265]` → `0x02004A95` pool fold.
4. **Pin constant for order:** `register int t __asm__("r0") = 2;` forces
   `movs r0,#2` before `ldrb r1,[...]` in OR sequence.
5. **Separate `t = 0;` statement** (vs initializer) forces early `movs` before pool loads.
6. **Opaque tbl + explicit `int m = mode-1`** defeats `-4` pool folding, gives
   ROM's `subs; lsls; adds` (not `lsls; adds; subs #4`).
7. **Tail-inside-if:** the `beq` at function top skips the WalkBits tail —
   re-read disassembly; tail was inside the if, not after.

## For coordinator

- **Landing:** 10 staged files in `staging/wave31_D/*_MATCHED.c`. Strip `.set` for
  real build symbols at landing: FillRect_6374, RectFill_7134, TilemapRectFill_6AD8,
  FillRect_65BC (all real T), NodeInit_080217A8 (real T), WalkBits_0803643C (real T),
  CheckPair_258D8 (real T), Tbl_SwapAndUpdate_080259A4 (real T),
  BitCtl_520C (real T), NodeInitSwitch_0800D1E0 (real T).
  Keep `.set` for unmatched (none in these files).
- **Registry:** 10 NOT-IN-REGISTRY, ready for MATCHED claims (wave 31).
- **Names:** ChangedBitsInit_080363EC, CondRectFill_080070F0, CondRectFill_080073D4,
  CondTilemapRectFill_08007378, CondRectFill_080062B4, CondRectFill_08006518,
  TilemapFill_08006AA0, CondRectFill_08006318, CondBitSet_0803639C,
  ClearBitWalk_08036338.
- **Next:** 0x080249b8 (r1↔r2 wall), 0x08007678, 0x0800cd5c (parked);
  0x08008b08/0x0800695c/0x080221cc (complex, untried); 0x0801e77c (176 diffs w30).

## Progress bar

Wave 31-D: 10/17 layer targets matched (59%). Overall: 807 → **817 / 1674** C-matched
(+10); 830 byte-identical total (+10).
