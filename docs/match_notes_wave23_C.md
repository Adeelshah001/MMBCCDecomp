# Wave 23 Worker C notes — blocked revisits (2026-10-23)

## Matched (0 landed; 1 solved but DUPLICATE)

### 0x08002E80 — SOLVED but DUPLICATE (do not land)
Reached **0 diffs** (84 B, main agbcc) via p21:
`staging/wave23_C/w23c_08002e80_p21.c.DUPLICATE_W23A`.
- **New idiom — hard-reg pin BOTH sides of `|` to control expand order:**
  `register u32 d32 __asm__("r0")` for the disp load and
  `register u32 pp0v __asm__("r4")` for the pp0 load. With both sides as
  hard-reg assignments, gcc expands LHS-first (vs RHS-first when only the
  RHS is a hard-reg assign), giving ROM's `ldrh r0` / `ldrh r4` order.
- **New idiom — `addr` split for pool/mov interleaving:** the pool `ldr r2`
  must come between `mov r0,sp` and `ldrh r0`. Achieved via
  `(addr = (u16*)&disp, p = (u32*)0x02003230, d32 = *(volatile u16*)addr)`
  — the separate `addr` assignment emits `mov r0,sp`, the comma sequences
  the pool next, then the load. The allocator coalesces `addr` into r0.
- **DUPLICATE:** Worker A already MATCHED and landed 0x08002E80 in Wave 23
  (`src/w23a_08002e80.c`, old_agbcc, registry row 1002). My p21 is an
  independent main-agbcc solution but must NOT be landed. Staging kept as
  `.DUPLICATE_W23A` for the record.

## Blocked revisits (refined, with staging)

### 0x08002CB0 — sub_08002CB0 (112 B): 17 diffs (was 31)
Best: `staging/wave23_C/w23c_08002cb0_p10.c` (17 diffs, 112 B correct size).
Progress:
- **Mask-as-u32-temp idiom:** `u32 tmp = 0xFFF8; tmp &= *p;` gives ROM's
  `ldr r0,[pc]` (mask→r0) + `ldrh r1,[r2]` (v→r1) + `ands r0,r1` prologue.
  (The mask must be the AND target in r0, not the v.)
- **Pin + opaque asm for r4/r3:** `register u32 z3 __asm__("r3") = 0` (with
  assignment placed after the AND) gives ROM's `movs r3,#0` position and
  delayed `str r3,[sp]`. `register u32 x4 __asm__("r4") = 0x1300` with
  `__asm__ volatile("" : "+r"(x4))` defeats constant propagation and gives
  `movs r4,#152; lsls r4,#5`.
- **Resists:** the `adds r1,r4,#0` copy (2 bytes, load-bearing for the 112 B
  size + alignment pad). Forcing the copy via a second pinned var
  (`y1`→r1) + opaque asm perturbs the whole function (p→r5, tmp→r2,
  `push {r4,r5,lr}`). The `adds` appears to be a gcc reload quirk that
  resists clean C expression.
- p10 has the copy but is perturbed (17 diffs). Clean p9 (no copy) is at
  80 diffs / 108 bytes.

### 0x0804AF20 — sub_0804AF20 (112 B): 32 diffs (was 68)
Best: `staging/wave23_C/w23c_0804af20_p9.c` (32 diffs).
Progress:
- **Pin d to r8 (u32) WORKS:** `register u32 d8 __asm__("r8") = d;` with
  opaque `"+r"` asm gives ROM's `mov r8,rX` and cascades a→r7, c→r6
  correctly! (68→38 diffs). The r8 save/restore prologue
  (`mov r7,r8; push {r7}` / `pop {r3}; mov r8,r3`) falls out naturally.
- **Pin b to r2:** `register u32 b2 __asm__("r2") = b;` keeps b in r2
  (38→32 diffs) but SPLITS the zero-extension (`lsl r2,#16` early,
  `lsr r2,#16` late vs ROM's adjacent pair).
- **Resists:** (1) b's split extension; (2) loop 0/0x10000 register swap
  (ROM: 0→r3, 0x10000→r5; mine: 0→r5, 0x10000→r3). The explicit u16-increment
  idiom (`t=((u32)i<<16)+0x10000; i=t>>16`) is in place and correct.

### 0x080259A4 — F_080259A4 (98 B): 69 diffs (no progress)
Best: `staging/wave23_C/w23c_080259a4_p2.c` (w22d base, 69 diffs, 76 B vs
ROM 98 B). Attempted pinning c to r8 (`w23c_080259a4_p3.c`) — worsened to
79 diffs / 96 B. The 22-byte size gap suggests a structural mismatch beyond
allocation (ROM uses 5 callee-saved regs r4-r8; mine uses 4). Needs fresh
analysis.

### 0x08004998, 0x08026740, 0x0800E440 — not attempted
Time prioritized to the closer targets above. Staging bases preserved at
`staging/wave22_D/w22d_08004998.c`, `w22d_08026740.c`, `w22d_0800E440.c`.

## New idioms for catalog

1. **Hard-reg pin both sides of `|`** (0x08002E80): when only the RHS is a
   hard-reg assignment, gcc expands RHS-first; pinning both sides restores
   LHS-first expansion. Controls `ldrh` order for OR sequences.
2. **`addr` split for pool/mov interleaving** (0x08002E80): separate the
   address computation (`addr = &x`) from the load to interleave a pool
   `ldr` between `mov rX,sp` and the load. Allocator coalesces `addr`.
3. **Mask-as-u32-temp** (0x08002CB0): to get `ands r0,r1` with mask in r0,
   hold the mask in a u32 temp (`u32 tmp = MASK; tmp &= *p;`) rather than
   `v &= MASK` (which puts v in r0).
4. **Pin d to r8 cascades** (0x0804AF20): pinning the stack-arg d to r8 via
   u32 pin + opaque asm not only fixes d but cascades a→r7, c→r6 correctly.
   High-reg u32 pins ARE honored (r8 works; r7 still avoid per w20).
5. **Opaque `"+r"` defeats constant propagation** (0x08002CB0): 
   `__asm__ volatile("" : "+r"(x))` keeps a pinned constant in its register
   instead of being propagated. (But can perturb allocation if overused.)

## Registry
- No MATCHED rows appended (0x08002E80 was a duplicate; others still blocked).
- No BLOCKED rows appended (all targets already have BLOCKED rows; p10/p9
  are refinements documented here).

## Workdirs
- Staging: `staging/wave23_C/` (scripts `w23c.sh`, `w23c_dis.sh` copied
  from wave22_C and adapted).
- Added to `staging/wave23_C/addrs_sizes.txt`: 0x080259a4 (98),
  0x08004998 (102), 0x08026740 (112), 0x0800e440 (118).
- Never deleted staging; duplicate p21 kept as `.DUPLICATE_W23A`.
