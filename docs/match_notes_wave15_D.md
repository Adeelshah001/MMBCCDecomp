# Wave 15 Worker D (TAG=D) — Blocked Revisits — Match Notes

Worker: Wave 15-D. Date: 2026-10-22.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/{agbcc,old_agbcc}`; `arm-none-eabi` 2.42.
Harness: `/tmp/wave15_D/mk.sh` (adapted from wave14_C; hardened assertions,
file offset = addr − 0x08000000, full extent incl pools, `cmp -l`).
Staging: `/tmp/wave15_D/` (NEVER delete; C sources kept for re-verification).
Results: `docs/wave15_D_results.tsv`.

**Result: 3 MATCHED, 9 BLOCKED (parked with precise diffs).**
Unattempted (budget): 0x080052A0 (calls LEAVE_ALONE 0x0804DD08, 39 diffs),
0x0800CC24 (70 diffs), 0x0803618C (10 diffs, base-in-r5 loop).

All MATCHED claims verified per hardened protocol: non-empty .o/.elf/.bin
asserted, `cmp -l` 0 diffs over full extent including pools, disassembly eyeballed.

## MATCHED

### 0x08000DC0 — Task_ActivateSlot (68 B, main agbcc, 0 diffs)
Task-slot activation. `p = 0x030005C0 + 0x1E08 + (*(u32*)(0x030005C0+0x1E50)*24)`;
if `v != 0`: `*(u16*)(p+2) = v`, `*p = 4`, then `ContextSwitch(p+4, p+8, *(u32*)0x02000800)`.
Callee: `ContextSwitch` (0x08000300, ASM in crt0.s) — extern with `.set` in staging.
Decisive idioms:
1. Split `t = ((t<<1)+t) << 3` into `t = (t<<1)+t; t <<= 3;` — forces in-place
   `lsls r0,r0,#3` (was `lsl r1,r0,#3`).
2. Split load/compute: `register u32 t1 __asm__("r1")` for the `ldr` only,
   plain `u32 t` for the arithmetic — gives `ldr r1,[r0]` then compute in r0.
   (Pinning t itself to r1 kept the whole computation in r1 — too strong.)
3. **If-scope correction:** the `beq` skips the *entire* block (strh + strb +
   call), not just the strh. The `*p = 4` and the call are inside `if (v != 0)`.
Staged: `/tmp/wave15_D/w15d_08000dc0_final.c` (uses real callee name).

### 0x08024818 — TblStride_24818 (48 B, main agbcc, 0 diffs)
`u8 TblStride_24818(u16 idx)`: `p = *(u8**)(0x02007090+20)`; `k = *(p+432)`;
return `(u8)GetStride4Byte20(p + k*144, idx)`.
**Size correction:** TSV said 46 B; actual is 48 B (42 code + 2 pad + 4 pool).
Callee: `GetStride4Byte20` (0x080258C0, MATCHED) — extern with `.set` in staging.
Decisive idiom: pin the intermediate sum `register u8 *q __asm__("r3") = p + (216<<1)`.
This forces the 216 constant into r2 (`movs r2,#216; lsls r2,#1`) and the sum
into r3 (`adds r3,r0,r2`), matching ROM. (Pinning the constant itself was ignored.)
Kept wave14_B's `register u8 k __asm__("r4")` for the `ldrb r4` + `push {r4,lr}`.
Staged: `/tmp/wave15_D/w15d_08024818_v2.c`.

### 0x08011170 — Tbl_ClearEntries (68 B, main agbcc, 0 diffs)
`n = (s16)GetRomTableEntry_082240B8(a)`; if `n <= 0` return;
`for (i=0; (s16)i < n; ) { TblFindClear_02C74(TableByte_16FAC(a,(u8)i)); <incr> }`.
Callees (all MATCHED): `GetRomTableEntry_082240B8`, `TableByte_16FAC`, `TblFindClear_02C74`.
Decisive idiom: explicit widened u16 increment —
```c
u32 t = (u32)i << 16;
t += 0x80 << 9;
i = (u16)(t >> 16);
```
The `(0x80<<9)` (wave14_C idiom 8) defeats folding to 0x10000, giving
`movs r1,#0x80; lsls r1,#9`. The u32 temp forces the `(i<<16)+0x10000` form
instead of the compiler's `add r0,r4,#1`.
Staged: `/tmp/wave15_D/w15d_08011170_final.c`.

## BLOCKED (parked)

### 0x0800B448 (36 B) — NEW IDIOM, allocator resists
**New finding:** an empty-asm barrier `__asm__ volatile("" : "+r"(t))` after
`t += 0x24` defeats the pool fold (pool stays 0x02004E40, `adds r3,#36` emitted
separately) AND forces the shift-split (`lsls#24` at def, pool `ldr` between,
`lsrs#20` late). This solves the two blockers wave14_C listed.
**Residual:** the barrier forces the allocator to put t in r0 and bb in r3;
ROM has t in r3, bb in r0 (plus ROM needs no `adds r0,r3,#0` before the call).
13 variants tried (pin t/bb, two barriers, split copy/shift, -O1/-Os, multi-var
barrier, early-clobber). Pure allocator resistance. Best: `/tmp/wave15_D/w15d_0800b448_v4.c`.

### 0x08024878 (46 B) — second-vintage, parked
Confirmed the signature: `adds r2,r1,#0; lsls r2,r2,#24; lsrs r2,r2,#24` on the
2nd param which is never used. Per wave14_C idiom 5, parked without retry.

### 0x080260D4 (56 B) — loop LICM resists
ROM hoists `movs r0,#0; lsls r4,r0,#16; asrs r4,r4,#16` once before the loop;
our compiler puts `lsls r4,r0,#16; asrs r4,r4,#16` at the loop top.
Tried: pin r4 (worse: `mov r4,#0`), init-at-decl, explicit s16 copy, inline asm
extend, int/s16 split counters, while-loop. The dead `lsrs r0,r4,#16` IS
reproduced (wave14_C's version); only the hoist resists. Wave14_C best stands.

### 0x08040364 / 0x080437D4 (56 B twins) — indexed ldrsb resists
ROM: `movs r4,#0; ldrsb r4,[r1,r4]`. A variable index gives `ldrsb r0,[r1,r0]`
(right insn, wrong reg, no r4 save). Pin + inline asm
`ldrsb %0,[%1,%0]` gives `ldrsb r4,[r1,r4]` exactly, but the surrounding
allocation (base in r3 vs r1, v1/v2/v3 order, extra extends) diverges.
7 variants. Parked; 0x080437D4 not attempted separately (same blocker, different
pool 0x08232D84 / callee 0x080459F8).

### 0x08006124 / 0x08006578 (64 B twins) — 6-arg wrapper, version diff
Dead `ldr r0,[pc,#32]` (0x0200483C, never used) + stack-arg codegen 12 B over
(76 B vs 64 B). Likely compiler version difference in stack-arg handling.
Parked; 0x08006578 not attempted separately.

### 0x08043630 (62 B) — near-miss, 2-byte allocator diff
Barrier defeats the 3-pool fold; u32 temp avoids the u8 return extend; base
assigned after calls gets r1. Best (v7): everything matches except
`movs r0,#0; strb r0,[r1]` vs ROM `movs r3,#0; strb r3,[r1]` (r3 is free in ROM
because the 0 is materialized while r0 still holds x; our compiler materializes
late). Pinning zero to r3 conflicts with the 0x26A pool load. Parked.

### 0x080052DC (68 B) — 6-pool fold resists
ROM keeps 0x02003670/0x02003230/0x11B0-0x11B3 as 6 separate pools; our compiler
folds. Barrier prevents folding but forces base into r8 (120 B vs 68 B).
Pinning to r6/r5 doesn't help. Parked.

## Files
- `/tmp/wave15_D/mk.sh` — harness
- `/tmp/wave15_D/dis.sh` — disassembly helper
- `/tmp/wave15_D/w15d_*.c` — all C variants (DO NOT DELETE)
- `docs/wave15_D_results.tsv` — results
- `docs/match_notes_wave15_D.md` — this file

## Progress Bar (this worker's 15 assigned)
██████░░░░░░░░░░░░░░░░░░░░░░░░░░ 3/15 matched (20%)
