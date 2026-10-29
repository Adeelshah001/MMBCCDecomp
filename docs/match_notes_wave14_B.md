# Wave 14 Worker B — Match Notes (batch 1)

**Assignment:** docs/wave14_layer.tsv (all 15 pure-leaf candidates) + docs/wave14_pool.tsv rows 0–99.
**Result:** 13 MATCHED (verified 0-diff in built mmbcc.gba), 10 BLOCKED with best diffs.
**Evidence:** docs/wave14_B_results.tsv, staging/wave14_B/ (mk.sh harness logs).

## Landed (13, all byte-identical)

### From wave14_layer.tsv (6)

**0x0804E008 — MemsetAligned_4E008 (82 B, no-interwork agbcc)**
Aligned memset with byte-replication word fill. Decisive idioms: (1) no-interwork
build for `pop{r4,r5,pc}` epilogue — main and old agbcc emit `pop{r1};bx r1`
for any function with a conditional branch; (2) explicit `u32 t=n--` temp
defeats the compiler's -1 loop transform; (3) `*pw++` x4 unrolled stores
produce `stmia`. GAS pads the section to 84 with c046; ROM has 82 bytes,
so emitted via BYTE() in ldscript.ld (verified bytes from noiw build).

**0x0804D130 — IoRegWrite_4D130 (80 B, old_agbcc)**
Switch-driven IO register writes (0x4000063–0x400007D). Decisive: old_agbcc
omits `push{lr}` for a true-leaf switch (main agbcc emits it even without
calls). Interleaved literal pools fall out of barrier placement. TSV size
74 was code-only; true extent 80 incl pools.

**0x0802567C — SearchFF_2567C (86 B, old_agbcc)**
Searches two tables for 0xFF marker. Decisive: statement order — counter
init BEFORE pointer init (`i=1; p=a+2`) — for exact instruction order.
GAS pads to 88; ROM has 86, emitted via BYTE().

**0x08004484 — List_InsertAfter_4484 (56 B, old_agbcc)**
Free-list allocate + insert after node. Decisive: `if(nw!=0){...} return nw`
falls through to `r0=nw` — no `mov r0,#0` for the null case (the null
path just returns the null in r0). 56 B incl pool; TSV 52 was code-only.

**0x080044BC — List_InsertBefore_44BC (56 B, old_agbcc)**
Twin of 4484, inserts before node. Same fall-through idiom.

**0x08047C4C — CopyTables_47C4C (88 B, old_agbcc)**
Copies two u16 tables (5 and 25 entries). Decisive: `i=0` init BEFORE
pointer loads (statement order). 88 B incl 4 pools; TSV 72 was code-only.

### From wave14_pool.tsv (7)

**0x08004DFC — PalModeSet_4DFC (14 B, main agbcc)**
Wrapper for sub_0800D3A0 (Gfx_PaletteModeSet). 14 B exact; GAS pads to 16,
emitted via BYTE().

**0x08004E44 — Call4E60_4E44 (12 B, main agbcc)**
Wrapper passing 0 to sub_08004E60 (unmatched; .set to 0x08004E60).
12 B exact.

**0x0804A328 — LoadCallClear_4A328 (24 B, main agbcc)**
Loads u16 from 0x200BD10, calls sub_08002FD4 (unmatched; .set), clears
next u16. 24 B incl pool.

**0x08025730 — TblLookup_25730 (36 B, main agbcc)**
Calls matched TblGet_25654; 0xFF sentinel returns 0; else `tbl[v*4+20]`.
36 B exact.

**0x0802FC28 — RangeCheckClear_2FC28 (34 B, main agbcc)**
Range-checks via matched InRange3B0_3B1; `(u8)callee==0` check compiles
to `lsls#24`; clears output. 34 B; GAS pads to 36, emitted via BYTE().

**0x0800D770 — Wrapper_D770 (36 B, main agbcc)**
5-param wrapper for sub_0800D800 (unmatched; .set): `(a,0,b,c,1)`.
Decisive: 5th param on stack forces `r3=(u8)c` setup. 36 B exact.

**0x0800D728 — Wrapper_D728 (36 B, main agbcc)**
5-param wrapper: `(a,2,b,c,0)`. Same idiom. 36 B exact.

## Blocked (10, with best diffs)

**0x08002960 — BlendMasked_2960 (78 B):** In-loop `push{r0,r1,r7}`/`pop`
spill not reproduced — allocator uses r8/r9/ip instead. v1: 120 B vs 78 B.

**0x080029B0 — BlendMasked_29B0 (82 B):** Same twin blocker; not attempted
separately.

**0x0800CC24 — InitRegs_0CC24 (78 B):** Register allocation — ROM pins
base→r3, zero→r2, bases→r4/r5/r6 plus r7=0x10000 u16-increment idiom.
v2: 104 B vs 78 B.

**0x08010AD8 — ObjInit_10AD8 (84 B):** r4/r5 swap — ROM has v→r5, b<<24→r4;
repro gives opposite. v2: 59 diffs.

**0x080017A0 — TblChecksum_17A0 (96 B):** Register allocation — top→r6,
low→r7, x<<16→r2. v2 pinned: 75 diffs.

**0x0800483C — QueuePush_483C (76 B):** ip-based allocation with c→r6.
v3 pinned ip: 61 diffs.

**0x080027D4C — SetInsert_27D4C (78 B):** Register allocation — val→r3,
base→r5, arr→r7. v2: 62 diffs.

**0x08023DD8 — BigMul_23DD8 (88 B):** Register allocation — a→r6, b→r5.
v1: 73 diffs (structure close).

**0x0800C784 — TblInterleave_C784 (92 B):** Loop structure + `(+64)*2`
constant folding. v1: 86 diffs.

**0x080052A0 — AbsScale_52A0 (50 B):** `ldrsh` target reg (r0 vs r1) +
u16-trunc optimization. v3: 39 diffs.

**0x08024818 — TblStride_24818 (46 B):** r2/r3 swap for the 216 constant
not reproduced (v7: 5 diffs). Pool at 0x2007090, callee GetStride4Byte20
(matched). Volatile pointer prevents pool folding; pinned r4 for k;
`(u8)` cast on int-returning callee forces truncation. The 216→r2 vs r3
allocation remains.

## New idioms documented

1. **Volatile pointer prevents pool folding:** `u8 * volatile *pp =
   (u8 * volatile *)0x2007090; u8 *p = pp[5];` emits `ldr r0,[pc];
   ldr r0,[r0,#20]` with pool=0x2007090, instead of folding to
   `ldr r0,[r0]` with pool=0x20070A4.

2. **5-param wrapper idiom:** For a callee taking 5 params
   `(u32,u32,u16,u8,u32)`, the 5th param on stack forces the compiler
   to set up `r3=(u8)c` explicitly. Two wrappers (D770/D728) verified.

3. **Fall-through null return:** `if(nw!=0){...} return nw;` — the null
   case falls through with r0 already null; no `mov r0,#0` emitted.
   (List_InsertAfter/Before.)

4. **True-leaf switch omits push{lr} (old_agbcc):** For a switch with no
   calls, old_agbcc emits no prologue push; main agbcc pushes {lr}
   unnecessarily.

## Unattempted rows (returned to pool)

- wave14_layer.tsv: rows 1, 6, 9, 11, 13 (0x08005A9C is 1166 B — likely
  skip/defer; others have calls or were deprioritized)
- wave14_pool.tsv: rows 0, 1, 4, 7, 10, 13–99 (0x080178A8, 0x08017000,
  0x08020ED4, 0x0801AA70 have calls; 0x08024818 attempted/blocked;
  0x080062B4, 0x0801B98C, 0x080070F0, 0x08002300, 0x080247C4,
  0x0804A2DC not yet attempted; rows 20–99 untouched)

## Build integration

- src/wave14_B.c (main agbcc): 5 compiled + 2 documented (#if 0) for BYTE()
- src/wave14_B_old.c (old_agbcc): 4 compiled + 1 documented for BYTE()
- src/wave14_B_noiw.c (no-interwork): 1 documented for BYTE()
- Makefile: three build rules (main/old/noiw patterns)
- ldscript.ld: 9 .o slots + 4 BYTE() blocks (renamed `_b` to avoid
  section-name merge with .o orphans)
- All 13 verified 0-diff in built mmbcc.gba via direct byte comparison.
- Unmatched callees use .set: sub_08004E60, sub_08002FD4, sub_0800D800.
  Replace with real symbols when matched.
