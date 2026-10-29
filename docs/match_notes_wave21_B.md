# Wave 21 Worker B — Match Notes

## Matched (2)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x08010308 | Sub_08010308 | 90 | main + FIXALIGN1 (all) | Setup twin of 0x0801029C family; sibling-shape from w20d_0801029c.c (p->r4/z->r5 pins); Ewram5160_Init_10508(5); mid-function pool +0x48 (4-aligned by construction) |
| 0x08042ae4 | Sub_08042AE4 | 124 (120+4 pool) | main | Struct init with large offsets (18088/18092/18096/18098/18099); EwGet16_18()>7?1:0 at [18099]; F_080248AC(0), EntryMgr_Teardown(), EntryMgr_Setup(); trailing pool (18099 not CSE'd across branches) included in section extent |

Both coordinator-verified 0-diff in full build. Registry appended.

## New Idioms

### Sibling-shape transfer defeats allocator mismatch (0x08010308)
Natural codegen allocated a->r7/b->r8/d->r6/c->r9/base->r5/f->r4 (96 B,
67 diffs). Transferring the exact structure from matched twin w20d_0801029c.c
(pinned `register u8 *p __asm__("r4")`, `register u8 z __asm__("r5")`,
`q1=p+66`, `q3` pinned ->r0) produced 0 diffs immediately. When a twin
exists, copy its shape BEFORE trying pinning variations.

### FIXALIGN1-all for mid-function pools (0x08010308)
The `0,/` (first-only) sed left the pool's `.align 2,0` intact, keeping
section alignment at 4 and causing a 2-byte trailing pad (92 vs 90 B).
Replacing ALL occurrences (`s/\.align\s*2, 0/.align 1, 0/g`) drops section
alignment to 2; pool stays 4-aligned by construction (offset 0x48).
Assembler warning "section does not have enough alignment" is harmless
(ldscript places section at 4-aligned address). Use -all variant when the
mid-function pool is 4-aligned by construction.

### Trailing pool is part of the section extent (0x08042ae4)
The 18099 pool for the else-branch sits at +0x78 (offset 120), 4 bytes past
the 120-byte "code size". The full 124-byte extent (code + pool) is 0-diff
against the ROM. The next ldscript address (0x08042EC0) is far enough that
no overlap occurs. When a trailing pool exists, the section extent INCLUDES
it; verify against the ROM bytes, not just the nominal size.

## Blocked / Parked

### 0x080259a4 (98 B) — BLOCKED: register allocation
Swap function with conditional StoreIdx2_25638 calls. ROM allocates
a->r5, b->r7, c->r8 (callee-saved), b*4->r2, c*4->r6, recomputing addresses
from kept scaled offsets. Natural codegen (main and old_agbcc) produces
72 B with b->r3, c->r6 (65-68 diffs). The 26-byte gap comes from r8 save/
restore, callee-saved b/c, and address recomputation. Pinning r7 is
forbidden (miscompile idiom). The C shape driving b->r7/c->r8 naturally
was not found in 3 attempts.

### 0x08004998 (102 B) — BLOCKED: instruction order + allocation
Hex-print to stack buffer with DrawText_048B4 call. ROM: c->r7, pool loaded
AFTER null-terminator store, `adds r0,r2,#0` before `asrs` for (s16)d,
reuses d<<16 (r2) for t computation. Attempts produce 100 B (78-80 diffs)
with c->r6, pool loaded early, direct `asrs`. The redundant `adds` and the
r7 allocation resisted 3 attempts.

### 0x08011e20 (112 B) — BLOCKED: out-of-bounds pools
Bit-manipulation on struct byte + double-deref table loads. Pools at
0x8011e90 (0x08223cc0) and 0x8011e94 (0x02005020) are 0/4 bytes past the
112-byte end. Requires special harness handling (cf. 0x08002cb0, wave20).

### 0x08026740 (112 B) — PARKED: complex state machine
Timer update (BCD-like counters at 0x020070f0+16..19, max 0x633b) + function
pointer dispatch via table at 0x0822d8ec indexed by *p, infinite loop.
Not attempted in depth; timer nested-condition logic is intricate.

### 0x08016e84 (114 B) / 0x08016efc (116 B) — BLOCKED: out-of-bounds pools
Twin 6-param setup functions (a+124/+128/+134 stores, F_08017458/
F_080174C4/F_08011F68 calls). Pool at 0x8016ef8 (0x08016e84) is 2 bytes past
end; pool at 0x8016f70 (0x08016efc) is at the boundary. Requires special
harness handling.

### 0x0800e440 (118 B) / 0x0800e748 (118 B) — BLOCKED: out-of-bounds pools
State-machine functions with mid-function pools (0x02005130) plus trailing
pools at 0x800e4b8/0x800e4bc (0x0800e440) and 0x800e7c0/0x800e7c4
(0x0800e748), 2-6 bytes past the 118-byte end. Requires special harness
handling.

### 0x080097cc (122 B) — BLOCKED: out-of-bounds pools
Complex address math with 5 pools at 0x8009848-0x8009858, all 2+ bytes past
the 122-byte end. Requires special harness handling.

### 0x0802493c (124 B) — BLOCKED: register allocation
Array-swap with CheckPair_258D8/GetStride4Byte20/Clear20_Set21_FF/
F_080254E0 calls. ROM computes idx*144 in r1, forcing `adds r1,r3,#0` to
restore b before bl; natural codegen computes in r0, keeping b in r1
(91 diffs, 120 vs 124 B). Allocator resists explicit temporaries.

### 0x080263a4 (138 B) — BLOCKED: complex validation
Loop validation with TblGet11 calls. Natural codegen: 140 B, 109 diffs.
The s8/u8 loop-counter idiom and nested conditions did not match in 1 attempt.

### 0x08026184 (126 B) — BLOCKED: out-of-bounds pool
Loop copy function. Pool at 0x8026204 is 2 bytes past the 126-byte end.
Requires special harness handling.

## Already in Registry (skipped honestly)
- 0x08010ec4: MATCHED (F_08010EC4, src/w20d_08010ec4.c, wave 20-D). Not touched.
- 0x0804af20: BLOCKED (sub_0804AF20, src/w20d_0804af20.c, wave 20-D; 73 diffs:
  u16 increment idiom). Not touched.

## Unattempted (54 remaining)
0x08011e20 (blocked, see above), 0x08026740 (parked), 0x08016e84 (blocked),
0x08016efc (blocked), 0x0800e440 (blocked), 0x0800e748 (blocked),
0x080097cc (blocked), 0x0802493c (blocked), 0x08026184 (blocked),
0x080263a4 (blocked), 0x080259a4 (blocked), 0x08004998 (blocked),
0x0800a6bc, 0x0801e174, 0x0801f254, 0x08020b60, 0x08003fc8, 0x0801bf10,
0x0801fcd0, 0x080482d8, 0x08042c04, 0x080405d8, 0x080439d8, 0x080460c0,
0x0801c56c, 0x0800571c, 0x0802d6e0, 0x080291ec, 0x0800e2cc, 0x080224e4,
0x08021b3c, 0x0801b0dc, 0x08002a1c, 0x0801c030, 0x08045838, 0x0803f844,
0x08046810, 0x0804a1f0, 0x0802298c, 0x08045914, 0x0803ad48, 0x08041890,
0x080046b0, 0x0803ac4c, 0x080096bc, 0x08006fe8, 0x0801c428, 0x08049560,
0x0800ac8c, 0x080203e0, 0x08001f1c, 0x08002070, 0x0804d8a8, 0x08034f2c,
0x08007840, 0x0803aaa8, 0x080065bc, 0x08006374, 0x0803643c, 0x080176ac,
0x08025ec8, 0x08007134, 0x08009c7c, 0x080099fc, 0x0801e208, 0x08006ad8,
0x080471d8, 0x08046df8, 0x08008bc8.

Pool-boundary audit (script staging/wave21_B/check_pools.sh): the following
have all pools within bounds (best candidates for future work):
0x08002070, 0x08006374 (0 pools), 0x080065bc (0 pools), 0x08006ad8 (0 pools),
0x08006fe8 (0 pools), 0x08008bc8, 0x08009c7c, 0x080176ac, 0x0801bf10,
0x0801c030, 0x0801c428, 0x0801c56c, 0x0801e208, 0x080203e0, 0x08020b60,
0x08021b3c, 0x080224e4, 0x08025ec8, 0x080291ec (0 pools), 0x0802d6e0,
0x08034f2c (0 pools).
