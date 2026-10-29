# Wave 24 Worker C (ii) — Match Notes

**IMPORTANT:** This is from a SECOND process also assigned as "Worker C".
There is an active collision: another process is writing to
`staging/wave24_C/` (f_*.c files) and `docs/wave24_C_results.tsv`.
That process has 3 verified MATCHED (0x0800A6BC, 0x0800E748, 0x0800E224,
all independently re-verified 0-diff by this worker).
This file documents THIS worker's separate near-matches.
Results: `docs/wave24_C_ii_results.tsv` (separate file, do not merge blindly).

## Parked / Blocked (with staging)

### 0x08007728 — F_08007728 (84 B incl pool), 3 diffs, main agbcc
EWRAM 0x02004830 byte-field init. `void F_08007728(u8 a, u8 b, u8 c)`:
if `*(s8 *)(0x02004830 + 620) == -1 && (s8)a != -1`, call
NodeInit_08022FB0 (0x08022FB0, MATCHED). Then
`*(u8 *)(0x02004830+620) = a; *(u8 *)(0x02004830+621) = b;`
`*(u8 *)(0x02004830+622) = c`.

Key idioms:
- `(155 << 2)` MUST NOT fold into the base pointer. Used
  `__asm__ volatile("" : "=r"(off) : "0"(155 << 2))` to make the offset
  opaque, forcing `movs rX,#155; lsls rX,#2` at runtime.
- Base `0x02004830` reloaded via pool ldr each section (not kept in reg).
  For the second half, pinned base to r0
  (`register u8 *b2 __asm__("r0")`) to get ROM's `adds r1,r0,r2` shape
  and keep base live in r0 across the a/b/c stores.
- `off += 1` gives ROM's `adds r2,#1` for the b store.
- 622 forced via opaque asm to get pool `ldr r1,[pc]` (not folded
  `0x02004A9E`).

Remaining 3 diffs at file offsets 0x11/0x12/0x14 (first `if` block):
mine `movs r2,#155; lsls r2,r2,#2; adds r0,r2,r0`
vs ROM `movs r1,#155; lsls r1,r1,#2; adds r0,r0,r1`.
The offset temp lands in r2 instead of r1. Second half of function is
0-diff. Fixable with a 3-byte sed (r2->r1 rename in those 3 insns) per
the 02CB0 precedent (Makefile AGBCC+sed rule).
Staging: `staging/wave24_C/best_08007728_3diff.c`.

### 0x080097CC — LoadTiles4_VRAM (148 B incl pool), 8 diffs, old_agbcc -O1
4-tile VRAM loader via Memcpy16 (0x08000758, MATCHED).
`void LoadTiles4_VRAM(u8 a, u16 b, u16 c, u8 d, u8 e)`:
- `dst = ((c&0xFFFF) + ((e&0xFF)<<5) + (d&0xFF)) << 5` (r4)
- `t1 = *(u32 *)(0x081720B4 + (a&0xFF)*4)` (r6, pinned)
- `p = *(u16 **)(*(u32 *)(0x081720CC + (a&0xFF)*4) + (b&0xFFFF)*4)` (r5)
- 4x `Memcpy16(t1 + (v[i]<<5), dst + pool[i], 32)` where
  pools = 0x06010000, 0x06010020, 0x06010400, 0x06010420 (VRAM addrs),
  v[i] = p[i] as u16 temps.

Key idioms:
- old_agbcc (not main) for the ldrh dest allocation: v0->r1, v1->r2,
  v2->r1 (reuse), v3->r5 (dying-p coalesce). Main agbcc puts all in r0.
- `t1` pinned to r6 (`register u32 t1 __asm__("r6")`); p naturally to r5.
- `((b&0xFFFF)<<2) + t2` operand order for `adds r1,r1,r0` (not r0).
- 4th call uses `dst += 0x06010420` for ROM's in-place
  `ldr r1; adds r4,r4,r1; adds r1,r4,#0`.
- Explicit `u16 v0..v3` temps (not direct `p[i]`) for the ldrh pattern.
- `-O1` (or `-Os`) for the 4th-call ordering (src before dst+=);
  `-O2` does dst+= first.

Remaining 8 diffs:
- 0x20-0x25 (6B): pool-load hoist. ROM: `ldr r2,[pc]; lsrs r0,#22;
  adds r2,r0,r2`. Mine: `lsrs r0,#22; ldr r5,[pc]; adds r2,r0,r5`.
  The `tbl1` two-statement split did NOT hoist the ldr. An
  `__asm__` barrier forces the hoist but breaks the top shift fusion
  (`lsls #24; lsrs #24` + `lsls #2` instead of `lsls #24` + `lsrs #22`).
- 0x69/0x6b (2B): 4th-call pool in r5 (`ldr r5; adds r4,r4,r5`)
  vs ROM r1 (`ldr r1; adds r4,r4,r1`). Deep allocator preference;
  the barrier version got r1 but broke the top.
Staging: `staging/wave24_C/best_080097cc_8diff.c`.

## Verification of other Worker C's claims
Independently re-verified with the hardened harness (verify.sh):
- 0x0800A6BC (Ewram4830_StateReset): 152 B, 0 diffs. VALID.
- 0x0800E748 (ChipState_Tick): 128 B, 0 diffs. VALID.
- 0x0800E224 (ChipList_Setup): 168 B, 0 diffs. VALID.
None were in `docs/match_status.tsv` at check time (unlanded).

## Collision note
Another process is actively working as "Worker C" in `staging/wave24_C/`
(f_*.c, _try/) and `docs/wave24_C_results.tsv`. This worker used `g_*`
and `c_*`/`best_*` prefixes and a separate results file to avoid
clobbering. The coordinator should deduplicate: the two workers may
have attempted overlapping functions. This worker did NOT attempt
0x0800A6BC, 0x0800E748, 0x0800E224, 0x0800E2CC (other worker's).
