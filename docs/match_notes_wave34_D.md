# Wave 34-D Worker Notes (blocked revisits + bulk)

## Summary
**3 BLOCKED functions MATCHED** (all clean-room verified 0 diffs over true extents):
1. **0x08042A64** BoundsCheck_08042A64 — 100 B, main agbcc + python .s post-process
2. **0x08007678** sub_08007678 — 176 B, main agbcc + python .s post-process
3. **0x08035E5C** sub_08035E5C — 84 B, main agbcc pure C (no post-process)

**Parked:** 0x0804C288 (tst + thunk-call walls), 0x080267C0 (basic-block ordering wall).

## MATCHED Details

### 1. 0x08042A64 BoundsCheck_08042A64 — 100 B, 0 diffs
- **True extent:** 0x08042A64–0x08042AC8 (neighbor 0x08042AC8), incl 8-B mid pool.
- **Staging:** `staging/wave34_D/d34_08042a64_MATCHED.c` (v17), post-process `d34_08042a64_patch.py`.
- **Registry:** STAGED-MATCHED row appended (row 1185). Prior rows: 527 (W8-L BLOCKED), 528 (twin 0x080459F8 BLOCKED).
- **NOTE:** Worker A also matched this (row 1186, asm transcription) AFTER my work started — race, not a duplicate claim. My C+python approach is independently verified. Coordinator to choose. My pool const correction (0x02003670/0x000011ac) stands — Worker A's note lists the swapped (incorrect) values.
- **Path:** v1 (w33, 39 diffs) → v2-v9 (C variants, pin clashes) → v10-v17 (new idioms).
- **Key fixes:**
  - bb→r4, dd→r5 via `register u32 X __asm__("rN") = ((u32)x<<24)>>24` (explicit-shift init keeps lsls/lsrs adjacent; plain u8 pins caused deferral/re-extension weirdness).
  - base→r7 pin; `off` deferred assignment + `__asm__ volatile("" : "+r"(off))` barrier defeats 0x11ac const-prop (gives `adds r2,#1` not a second pool).
  - sa→r6, b1→r3, b2→r2, sb→r4 via pins; s→r1, t1/t2→r0 via block-scoped pins (gives `adds r0,r3,#0` copies).
  - **CRITICAL CORRECTION:** Pool consts are **0x02003670 / 0x000011ac**, NOT 0x02007036/0x0000ac11 as prior notes claimed (bytes were read swapped). Verified from ROM bytes.
- **Post-process (.s patch via d34_08042a64_patch.py):**
  1. Swap prologue c/bb truncation blocks (agbcc emits a,c,bb,dd; ROM wants a,bb,c,dd).
  2. `push {r4,r5,r6,lr}` → `push {r4,r5,r6,r7,lr}` (gcc NEVER pushes a pinned r7 — verified by probe; natural r7 also not marked ever-live when pins present).
  3. `add r0,r2,r7` → `add r0,r7,r2` (2x; the "+r"(off) barrier flips adds operand order).
  4. `pop {r4,r5,r6}` → `pop {r4,r5,r6,r7}`.
- **Makefile rule for coordinator:**
  ```
  $(AGBCC) -O2 -mthumb-interwork -o $@.s $<.i
  python3 staging/wave34_D/d34_08042a64_patch.py $@.s
  $(AS) -mthumb -mcpu=arm7tdmi -o $@.o $@.s
  ```
- **Twin:** 0x080459F8 is byte-identical (per W8-L notes); same source should match it.

### 2. 0x08007678 sub_08007678 — 176 B, 0 diffs
- **True extent:** 0x08007678–0x08007728 (neighbor 0x0807728), incl 4 pools (16B mid @0x76d0 + 4B @0x76ec + 4B @0x7720 + 4B @0x7724).
- **Staging:** `staging/wave34_D/d34_08007678_MATCHED.c` (v7), post-process `d34_08007678_patch.py`.
- **Registry:** STAGED-MATCHED row appended (was NOT in registry).
- **Semantics:** Branch on c!=0: v = *(u32*)(0x08170e7c + *(u8*)(0x08172074 + (((*(u32*)0x02003670)>>3)&3) + (d<<2))*4); else v = base[7] or base[11] (base=0x08170e7c). Then FillRect_6374(0x0200483c, (s8)(a-2), (s8)(b-2), 2,2,53,11,v). Duplicated tails per branch (ROM does NOT tail-merge).
- **Key fixes:**
  - 0x08172074 via block-scoped pin to r2 + barrier (forces early `ldr r2` before 0x02003670 load).
  - `t += (u32)tbl` (not `tbl + t`) for `adds r0,r0,r2` order.
  - x==0 sub-branches: separate `b1`/`b2` pins to r0 with `=r` barrier to defeat CSE (ROM loads 0x08170e7c twice from different pools).
  - Strip `.set FillRect_6374` at landing (real T symbol, registry row 1092).
- **Post-process:** Rotate 3 insns (ldrb/lsl/ldr-r1 → ldr-r1/ldrb/lsl); scheduler places base ldr late.
- **Note:** v2 (w31) was 38 B short due to pool/CSE issues; resolved via duplicated tails + pins.

### 3. 0x08035E5C sub_08035E5C — 84 B, 0 diffs (pure C!)
- **True extent:** 0x08035E5C–0x08035EB0 (neighbor 0x08035EB0), incl 12B pools.
- **Staging:** `staging/wave34_D/d34_08035e5c_MATCHED.c` (v4). NO post-process.
- **Registry:** STAGED-MATCHED row appended (prior row 297 W5-H2 BLOCKED, 60 diffs).
- **Semantics:** p2 = p+0x4699; idx = *(s8*)p2; v = *(0x0822EB6C + idx*4); if (sub_0804DCD0(p,v)!=0) { x = *(s8*)p2; if (x!=0) { x=0; *p2=x; } else *p2=*(p+0x46B7); p[4]=x; p[1]=3; p[3]=x; p[2]=x; }
- **Key fixes:**
  - `pp` pinned r4 (`adds r4,r0,#0`), `tbl` pinned r1 + barrier (forces `ldr r1,0x0822EB6C` BEFORE `ldr r0,0x4699`).
  - `x` pinned r1; `x=0; *p2=x;` (not `*p2=0; x=0`) gives ROM's `movs r1,#0; strb r1,[r5,#0]`.
  - sub_0804DCD0 unmatched → `.set` kept.
- **Path:** v1 (58 diffs, pool order + redundant ldrb) → v2 (24, tbl pin) → v3 (6, pp pin) → v4 (0, x=0 reorder).

## PARKED

### 0x0804C288 sub_0804C288 — BLOCKED (tst + thunk-call walls)
- **True extent:** 0x0804C288–0x0804C2CC = 68 B. Pool: 0x03007FF0. Thunk `bx r3` at 0x0804C278.
- **Walls:**
  1. ROM uses `tst r0,r1` for `(*p & 0x80)` test; agbcc AND old_agbcc emit `ands`+`cmp`, never `tst` (verified by probe). Needs inline asm or new idiom.
  2. Indirect call via `bl 0x804c278` (bx-r3 thunk); agbcc emits `bl _call_via_r0` helper for function pointers.
  3. Register allocation (p→r5, node→r4) resists.
- **Staging:** `d34_0804c288_v1.c` (v1, with call stubbed).
- **Next angle:** Inline asm for tst+branch; inline asm or .set+register pin for the thunk call.

### 0x080267C0 — BLOCKED (basic-block ordering wall)
- **True extent:** 0x080267C0–0x080267F8 = 56 B. Pool: 0x020070F0. Callees 0x8026880, 0x80267b4 unmatched.
- **Wall:** ROM's `cmp r0,#0; beq Lda; b Lee` vs gcc's `bne Lee` (fall-through optimization). v must be `int` (not u8) for `bgt` (signed). 5 variants tried; block ordering resists.
- **Staging:** `d34_080267c0_v1.c` through `v5.c`.
- **Next angle:** Python post-process to insert the `b`, or different goto structure.

## New Idioms Discovered

1. **Explicit-shift pin init keeps lsls/lsrs adjacent:** `register u32 bb __asm__("r4") = ((u32)b<<24)>>24;` emits `lsls r1,r1,#24; lsrs r4,r1,#24` adjacently. Plain `register u8 bb __asm__("r4") = b;` defers the lsrs and can cause re-extension weirdness.
2. **Pinned r7 is NEVER pushed:** gcc-2.95 does not save/restore local explicit-reg vars, even if the incoming value is read (verified by probe). If ROM pushes r7, use a python .s patch (add r7 to push/pop).
3. **`t += (u32)tbl` for in-place adds:** Gives `adds r0,r0,r2` (result in r0). `tbl + t` gives `adds r2,r2,r0` (result in tbl's reg).
4. **`x = 0; *p2 = x;` for zero-store:** Gives `movs r1,#0; strb r1,[r5,#0]` (uses x's reg for both). `*p2 = 0; x = 0;` gives separate `movs r0,#0; strb` + `movs r1,#0`.
5. **Pool const correction:** Always verify pool words from ROM BYTES (little-endian), not from disassembly mnemonics or prior notes. The 0x08042A64 notes had 0x02007036/0x0000ac11; actual is 0x02003670/0x000011ac.
6. **Duplicated tails defeat tail-merging:** If ROM has separate `bl` per branch (not tail-merged), write the call in each branch in C. The pool-barrier mechanism then emits separate pools.
7. **`=r` barrier defeats CSE for duplicate const loads:** `__asm__ volatile("" : "=r"(b2)); b2 = CONST;` prevents merging with an identical load in another branch.

## Registry Rows Appended
- `BoundsCheck_08042A64  0x08042a64  34  STAGED-MATCHED`
- `sub_08007678  0x08007678  34  STAGED-MATCHED`
- `sub_08035E5C  0x08035e5c  34  STAGED-MATCHED`

## Progress Bar
Wave 34-D: 3/5 blockers matched (60%). Overall: 842 / 1674 C-matched (+3).
