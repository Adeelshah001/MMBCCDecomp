# Wave 24 Worker B notes (2026-10-23)

Worker B: rows 6-37 of wave24_layer.tsv excluding row 14 (0x080065BC, worker A's rect-fill).
31 functions assigned. Result: 3 MATCHED, 2 BLOCKED, 26 PENDING (not attempted, time).

Staging: `staging/wave24_B/` (harness `w24b.sh`, `dis.sh`, `addrs_sizes.txt` with wave22-corrected extents).
Final C files: `staging/wave24_B/w24b_<addr>.c`. Patch scripts: `w24b_<addr>_patch.sh`.

## Matched (3)

### 0x080097cc — Load4Tiles (148 B), main agbcc + sed
Copies 4 tiles (32 B each) from ROM tables to VRAM 0x06010000+off.
Args: (u8 a, u16 b, u16 c, u8 d, u8 e). off = ((u16)c + (e<<5) + d) << 5.
base = T1[a] (u32 table at 0x081720b4); row = T2[a] (u32* table at 0x081720cc);
ent = row[b]; src_k = base + ((u16*)ent)[k]<<5; dst = 0x06010000/0x06010020/0x06010400/0x06010420 + off.
Calls Memcpy16(src, dst, 32) x4.

**New idiom — extern array forces pool-load-before-index:** writing the table
as `*(u32 *)((a << 2) + 0x081720b4)` makes agbcc emit `lsrs r0,#22` BEFORE the
`ldr r2,[pc]` pool load (constant folding + canonicalization). Declaring
`extern u32 gTileBaseTbl[];` + `gTileBaseTbl[a]` forces a genuine symbol-address
pool load FIRST, then the shift — matching ROM's `ldr; lsrs; adds; ldr` order.
Also fixed the r5/r6 allocation (base->r6, ent->r5).

**Sed patch** (w24b_080097cc_patch.sh, verified reproduces 0-diff .s): the four
`ldrh` temps for f[0..3] need r1/r2/r1/r5 (not r0); copy4's tail needs
`adds r0,r6,r0` (not `adds r6,r6,r0`), pool into r1, and deletion of the
redundant `adds r0,r6,#0`. GAS recalculates pool offsets after the 2-byte deletion.

Stubs for harness: Memcpy16=0x08000759, gTileBaseTbl=0x081720b4, gTileIdxTbl=0x081720cc.
Deliverable C uses `extern u32 gTileBaseTbl[]; extern u32 *gTileIdxTbl[];` —
coordinator must define these (or equivalent) at 0x081720b4/0x081720cc on landing.

### 0x08026184 — InitBufs_26184 (132 B), main agbcc + sed
Fills two buffers via Fill_0802520C, stores u16/u8 fields, appends 1..127.
Args: (u8 *a1, u16 *a2).
- Fill((Buf*)(a1+8), *(u8**)a1 + 0xE00, 0x82)
- Fill((Buf*)(a1+16), *(u8**)a1 + 0xE82, 0x82)
- Append((Buf*)(a1+16), 0)
- ((u16*)*(a1+4))[7..10] = a2[0..3]; [11] = 0x8000; [24]=[25]=1 (u8)
- do { Append((Buf*)(a1+8), (u8)i); t=((u32)i<<16)+0x10000; i=t>>16; } while ((s16)(t>>16) <= 127)

**Idioms:** `*(u8 *volatile *)(a1+4)` forces fresh `ldr r1,[r6,#4]` before each
store (defeats CSE — ROM reloads the pointer 7 times); explicit u16 increment
`t = ((u32)i << 16) + 0x10000; i = t >> 16;` (w22c).

**Sed patch** (w24b_08026184_patch.sh): the `0x8000` store materialized as
`movs r2,#128; lsls r2,#8; adds r0,r2,#0`; patch to `movs r0,#128; lsls r0,#8`
(direct) and delete the mov. The 2-byte shrinkage is absorbed by the `.align`
pool pad — total stays 132.

### 0x08007728 — F_08007728 (84 B incl pool), main agbcc, no sed
EWRAM byte checks/sets at 0x02004830+620..622; conditional NodeInit_08022FB0.
Args: (u8 a, u8 b, u8 c).
```c
s8 v = (s8)g_02004830[620];
if (v == -1 && (s8)a != v) NodeInit_08022FB0((s8)a);
g_02004830[620] = a; g_02004830[621] = b; g_02004830[off622] = c;
```
**Idioms:** extern array `extern u8 g_02004830[]` prevents the compiler folding
`0x02004830+620` into a single pool word (ROM keeps base and offset separate:
`ldr r0,[pc]` then `adds r0,r0,r1` with r1=620 via `movs/lsls`); `u32 off622 = 622`
forces 622 into the pool (ROM pools it; the compiler would otherwise do 621+1).
True extent 84 B (74 code + 2 pad + 8 pool); corrected in addrs_sizes.txt.

## Blocked (2)

### 0x080263a4 — Validate_263A4 (138 B): 50 diffs (best, p4, old_agbcc)
Validation returning 0/1. Checks p[1]-1<=198, TblGet11(p[1])&4==0, loop i=1..9
(q=p+1; q[i]<=199, TblGet11(q[i])&4==0), p[11]/p[12]<=199, p[13]<=2, then a
3-way on p[13] (0: p[0]==50; 1: 50<=p[0]<=55; 2: 50<=p[0]<=146).
**Blocker:** in the loop, ROM does `adds r0,r6,r4` (address in r0),
`ldrb r1,[r0]` (value for cmp), `ldrb r0,[r0]` (reload for call). Both agbcc
variants do `adds r1,r6,r4` (address in r1), `ldrb r0,[r1]`. Also branch-target
layout differs (fail/success label placement). Tried: natural C, q delayed,
explicit addr temp, old_agbcc. The address-register choice resists steering.
Staging: `w24b_080263a4_p4.c` (best).

### 0x080103E0 — F_080103E0 (114 B): 22 diffs (best, p4 + sed)
Args (u8 a, u8 *b, u8 *c, u8 *d). Checks *g_02005160==0, (b[35]&15)==1 selects
q=g+8 vs g+28; if q[16]&1 → Clr_08010478(b[35]&15), return 0; if q[16]&2 → return 0;
calls NewNode_080236B0(a, q, b, sp->[c,d]); if null return 0; q[16]|=1; return 1.
**Blockers:** (1) `ands` operand order (`ands r2,r0` vs ROM `ands r0,r2`) — fixed
via sed. (2) ROM emits the literal pool (0x02005160) MID-function at 0x801043c,
with the Clr_08010478 call block AFTER the pool; agbcc puts the pool at the end.
This block-layout difference resists C-level steering. Staging: `w24b_080103e0_p4.c`
+ sed for ands (22 diffs remain, mostly layout).

## Pending (26, not attempted)
Time-boxed out. Notes on triage:
- ShiftPair_Copy_800C wrapper family (0x0803f844, 0x08046810, 0x08045914, 0x0804a1f0, 0x0803ad48, 0x08041890): 216-228 B, likely siblings — match one, transfer shape.
- 0x080224e4 / 0x08021b3c: Memcpy16 callers, complex branchy with muls, high regs — siblings of each other.
- 0x08016e84 / 0x08016efc / 0x08010e00 / 0x0800909c: high registers (r8/r9/sl), 5-6 args — complex.
- 0x080460c0 (200 B, 9 callees), 0x08024a30 (268 B, 7 callees), 0x080176ac (462 B, 9 callees): large multi-call.
- 0x08002a1c (CpuSet), 0x080046b0 (CpuFastSet): use high regs, non-trivial control flow.
- Remainder: 0x0800d1e0, 0x0801d598, 0x0800571c, 0x080291ec, 0x0803ac4c, 0x080096bc, 0x08006fe8, 0x08034f2c, 0x08007840.

## Registry
- No duplicates: all 31 addresses grep-clean against docs/match_status.tsv before work.
- 0x080065bc skipped per task (worker A rect-fill family).

## New idioms for catalog
1. **Extern-array pool ordering** (0x080097cc, 0x08007728): for ROM data tables
   accessed as `base + (idx<<k)`, declare `extern T gTbl[]` and use `gTbl[idx]`.
   A casted absolute address `*(T*)((idx<<k) + 0x08XXXXXX)` gets constant-folded
   (shift emitted before pool load); the extern symbol forces a true address
   pool-load before the index computation. Also prevents offset folding
   (`0x02004830+620` → single pool word).
2. **Volatile reloads defeat CSE** (0x08026184): `*(u8 *volatile *)(p + off)` forces
   a fresh pointer load before each store when ROM reloads instead of keeping
   the pointer in a register.
3. **Pool a small constant via u32 var** (0x08007728): `u32 off = 622;` forces a
   pool word where the compiler would otherwise synthesize via adds.
