# Wave 10 Batch L — Match Notes

Worker L, 2026-10-21. 7 matched (all old_agbcc), 7 blocked.
Build: `mmbcc/src/wave10_L_old.c`, Makefile SRCS_C + per-file rule,
ldscript.ld slots `.text.w10l_*`. All 7 verified byte-identical by
extracting from built `mmbcc.gba` and diffing against baserom.

## Matched

### 1. S8TableLookup_0C248 @0x0800C248 (28B)
s8 table lookup via `gTbl_0817313C` (0x0817313C). Returns -1 if idx==-1
or idx<=59, else `(s8)table[idx]`.
- Goto-style (`if (x==-1) goto done; if (x<=59) goto done;`) preserves
  the redundant `idx==-1` check; `&&` form lets the compiler delete it.
- `(s8)` via `u8 b = table[x]; r = (s8)b;` produces `ldrb; lsls #24;
  asrs #24` (not `ldrsb`).
- `int x = idx;` before `int r = -1;` gets extension-first ordering
  and r in r0.
- Uses canonical `gTbl_0817313C` (defined in wave5_h1.c).

### 2. PairBonus_2D460 @0x0802D460 (40B)
Returns 6 if (y,x) in {(4,4),(3,1),(2,4)}, else 0.
- **Key:** if/else-if chain, NOT `||`. The `||` form makes old_agbcc
  use r4 (push/pop) and spill copies of x/y. The if/else-if form
  jump-threads the three `r = 6` assignments into the shared tail,
  matching ROM exactly.

### 3. Clamp_26720 @0x08026720 (32B)
`v>84 → 239; v>48 → (u8)(v+150); else → (u8)(w+200)` where `w = v`.
- Result-variable form (`u8 r; if... r=...; return r;`) fixes branch
  order; direct returns get reordered (`bhi` vs `bls`).
- The `w` copy (`adds r1, r0, #0`) is kept and used in the else branch.

### 4. EwramLookup_26D94 @0x08026D94 (26B)
EWRAM `gEwram020070F0` (0x020070F0). Returns -1 if `p[1]==0`, else
`(s8)p[2]`.
- Early-return form (`if (p[1]==0) return -1; return (s8)p[2];`)
  materializes `-1` only in the branch and keeps the pool embedded
  mid-function (after `b`, before `movs r0,#1`).
- Trailing 2-byte `nop` is section alignment; 26 code bytes identical.

### 5. TableByte_16FAC @0x08016FAC (34B)
ROM table at 0x082240B8, 8-byte entries (`{u8 *p; u8 _pad[4];}`).
Returns 0 if null entry, else `p[off]`.
- `if (p != 0) return p[off]; return 0;` gives `bne` (not `beq`).
- **Idiom:** explicit `u8 *tbl = g_082240b8_L;` forces `ldr r1,[pc]`
  BEFORE `lsrs r0,#21`; without it the compiler schedules `lsrs` first.
- Uses distinct symbol `g_082240b8_L` (global) to avoid conflict with
  wave7_g2_old.c's local `g_082240b8`.

### 6. Rank_49934 @0x08049934 (54B)
EWRAM u16 at `gEwram020070F0 + idx*12 + 50`. Returns 2 if 254, 3 if 255,
1 if 253, else 0.
- Goto decision-tree (`beq; bgt; beq`) matches ROM; if/else-if gives
  linear chain.
- **Idiom:** `int v = *(u16 *)(base + 50);` gives `ldrh` (unsigned load)
  + `bgt` (signed compare). `u16 v` gives `bhi`; `s16 v` gives `ldrsh`.
- `u8 *pool` declared BEFORE `u8 r` gets `ldr r2` before `movs r3,#0`.
- Trailing `nop` is alignment; 54 code bytes identical.

### 7. Xor_23CE4 @0x08023CE4 (44B)
XOR-folds 14 bytes: `dst[i] ^= src[((i*2)&7)]` for i=0..13.
- do-while with `u8 i` increment via `lsls/lsrs #24` matches exactly.
- `movs r5,#7` hoisted outside loop by compiler.

## Blocked (precise diffs)

### B1. sub_0803FACC @0x0803FACC (72B) — compiler mismatch
Decision tree returning 1 if u16 arg in {0x1030,0x3030,0x3020,0x4030}
or 0x30..0x36. Three independent codegen mismatches vs both compilers:
1. ROM keeps `adds r2, r1, #0` (b-copy) with result in r3; compilers
   eliminate the copy and put result in r2.
2. ROM: `cmp r1, #0x30; blt`. Both compilers fold `a < 0x30` →
   `cmp #0x2F; ble` (frontend, at -O1 and -O2).
3. ROM: literal pool load for 0x3020. old_agbcc does `subs r0, #16`
   (0x3030-16) via combiner.
Goto-tree source reproduces the branch layout but not these three.
Likely compiled with a different compiler version.

### B2. sub_08004398 @0x08004398 (80B) — LICM mismatch
Struct initializer with fixed-point countdown loop (`c += 0xFFFF0000`,
`while ((c>>16) > 0)`). ROM keeps `lsls/asrs` stride re-extension AND
`ldr r0, =0xFFFF0000` INSIDE the loop body. old_agbcc hoists both
(loop-invariant code motion). Cannot defeat via source.

### B3. sub_080244B0 @0x080244B0 (76B) — register allocation
Table lookup (20-byte structs at 0x082298F0, mask 0xFFF). ROM uses r4
(`push {r4,lr}`/`pop {r1}; bx r1`) for table base and keeps the
`u16 b = a` copy in r3. Compilers eliminate the copy and avoid r4.

### B4. sub_08011DB0 @0x08011DB0 (28B) — allocation + branch
EWRAM table byte. ROM compares r0 (not r1) and uses `bne` (not `beq`)
for the `idx==0` check. Compiler insists on r1 and `beq`. Also ran into
GAS `.set` forward-reference limitation: `.word sym+8` with trailing
`.set` assembles to `sym+0`; worked around with explicit `p += 8`
(which the combiner fuses into `ldr [r0,#8]`).

### B5. sub_0804D7A0 @0x0804D7A0 (30B) — allocation
Flag clear. ROM: `adds r1, r0, #0` (p in r1), `movs r2, #0` (v in r2).
Compilers insist on p in r2, v in r1.

### B6. sub_0802518C @0x0802518C (34B) — allocation
Struct copy (offsets 0x13A4/0x13AA). ROM: `ldr r3, =0x13A4` (off in r3).
Both compilers put off in r2.

### B7. sub_0802D8F4 @0x0802D8F4 (50B) — allocation + scheduling
Table pointer. ROM: p in r2, `bne` to then-branch, 336 as `168*2`
independent. Mine: p in r1, 336 as `392-56`, different instruction order.

## New idioms discovered
- **Explicit base-var for load ordering:** `u8 *tbl = SYM;` before use
  forces the pool `ldr` before a dependent `lsrs` (TableByte_16FAC).
- **`int v = *(u16 *)p;`:** unsigned load + signed compare (`ldrh`+`bgt`).
- **Goto decision-tree:** `if (v==C1) goto y1; if (v>C1) goto big; ...`
  reproduces the `beq/bgt/beq` tree that if/else-if linearizes (Rank_49934).
- **`.set` + constant forward ref:** `.word sym+8` with trailing `.set`
  does NOT evaluate the +8 in GAS 2.42; use separate `p += 8` (fused by
  combiner) or a distinct pre-offset symbol.
