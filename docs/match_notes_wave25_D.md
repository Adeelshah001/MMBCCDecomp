# Wave 25-D Notes (Bulk Leaves-Up)

## MATCHED

### 0x08045838: FlagPairDispatch_08045838 (220 B, old_agbcc, 0 diffs)
Two-stage s8-flag dispatch on `p[0x46B0]` / `p[0x46B1]`. Value 1 programs EWRAM
control structs (0x02004D48 / 0x02004D7C) and calls `ShiftPair_Copy_800C`;
value 3 clears bit 1 of the +44 byte. Stores back 2/0 via shared cross-jump store.

**True extent**: 220 B (0x08045838–0x08045914). Code 216 B + 4 B pool (0x02007C4D at
0x08045910). Note: layer TSV said 216 B; actual is 220 B.

**Idioms used**:
- `switch` (not if/else) for `beq`-style dispatch
- Inline asm `ldrsb` (this agbcc NEVER emits ldrsb from C, even for s8* — verified
  with minimal test; precedent: wave7_f_old.c)
- Register pins: `pp→r5`, `q→r4`, `t→r1` (first block), `x→r4` (second block, late declaration)
- Cross-jumping creates the shared `strb` store
- `int n = 2; n = -n;` for `movs/negs` materialization of -2
- `u8 *b = g_...; b += 44;` for `ldr; adds #44` ordering

**Critical catches**:
- Pool at 0x80458b8 is `0x000046B1`, NOT `0x0000B146` (byte-swap error in initial read)
- Second block base is `0x02004D7C`, NOT `0x02007C4D` (another byte-swap)
- Always verify pool values with `od`, not just objdump disassembly

**Callee**: `ShiftPair_Copy_800C` (0x0800800c) via harness stub; real name from registry.

## BLOCKED

### 0x0803643c: WalkBits_0803643C (444 B, 60 diffs)
Table-walk/bit-test function. Calls `SelBlob_Ret` (0x0800303C).
**True extent**: 444 B (0x0803643c–0x080365f8). Pools: 3× 0x0200BCE8, 2× 0x0822EED8.
**Blockers**:
- Register allocation diverges significantly (gcc uses r5/r7/r9, ROM uses r6/r8/ip/r9)
- Three instances of hoisted `0x10000` (`movs r1,#128; lsls r1,#9`) inside loops — per w24d, undefeatable in this gcc, needs Makefile sed
- Complex nested loops with bit manipulations
**Tried**: main/old_agbcc, explicit r4 shift form, split globals. Needs pinning work + sed.

### 0x080460c0: F_080460C0 (186 B, 174 diffs)
7-call dispatch (GetEnt_U16_14, Wrap_GetRomTableU16, TblGet_f00/f04/f08,
GatedDispatch×3, Gfx_BlitRequest). 
**Blockers**: Register allocation (r5/r7 swap, r4 vs r6 for struct ptr),
pool ordering. Needs significant allocator work.
**Pools**: 0xA946, 0x2308502E, 0x2308342E (verified).

### 0x08016e84: F_08016E84 (114 B, 49 diffs)
Calls IncU8_12, SetField120_U16Pair, SetBytes_08011F68.
**Blockers**: 
- Inline asm ldrsh works, but temp reg allocation (r0/r2/r3) diverges
- u16 param conversion adds `lsls/lsrs` — needs `int` param trick (ABI-compatible)
- Pool-first vs byte-first ordering
**Tried**: main/old_agbcc, pins (caused worse codegen), inline asm ldrsh.

### 0x08046df8 / 0x08016efc
Not attempted — 832B too large / sibling of 0x08016e84.

## Unattempted (returned to pool)
48 rows: 0x080224e4, 0x08021b3c, 0x08002a1c, 0x080046b0, 0x0803ac4c, 0x080096bc,
0x08006fe8, 0x08024a30, 0x08034f2c, 0x08007840, 0x080176ac, 0x08025ec8, 0x08009c7c,
0x080099fc, 0x080471d8, 0x08008bc8, 0x0801f254, 0x08003fc8, 0x0801bf10, 0x0801fcd0,
0x080482d8, 0x08042c04, 0x0804b514, 0x0801c56c, 0x0802d6e0, 0x0802375c, 0x0801b0dc,
0x0801c030, 0x0802298c, 0x0801e77c, 0x0801c428, 0x08049560, 0x0800ac8c, 0x080203e0,
0x08001f1c, 0x08002070, 0x0804d8a8, 0x08027400, 0x0803aaa8, 0x0804b124, 0x0801e208,
0x0800f4f8, 0x0800ef40, 0x08010e00, 0x0800d1e0, 0x0800909c, 0x0801d598, 0x0800571c,
0x080291ec.
All registry-checked CLEAR (not MATCHED/ASM/INTERIOR/BLOCKED).

## Lessons
1. **Verify pool values with `od`, not objdump**: I made TWO byte-swap errors
   (0xB146 vs 0x46B1, 0x02007C4D vs 0x02004D7C) from misreading disassembly.
2. **This agbcc never emits ldrsb/ldrsh from C**: Use inline asm (wave7 precedent).
3. **Switch > if/else** for `beq`-style dispatch.
4. **Late declaration** of pinned variables controls instruction ordering.
5. **Cross-jumping** can create shared stores from direct stores in each case.
