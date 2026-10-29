# Wave 25-B Worker Notes (near-miss closers)

Worker B, 2026-10-23. Staging: `staging/wave25_B/` (C sources, `w25b.sh`
harness adapted from w24d.sh, `fix_08004998.py`, `fix_080259a4.py`,
`addrs_sizes.txt`). Results: `docs/wave25_B_results.tsv`. Baserom SHA-1
verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

All four targets were BLOCKED in `docs/match_status.tsv` at session start
(checked 2026-10-23; none had flipped to MATCHED).

## MATCHED (2)

### 0x08004998 — HexFormat_08004998 (108 B true extent): 0 diffs
Hex-formats u32 p into a 16-byte stack buffer, calls DrawText_048B4.

**Catch-22 broken.** The w24d catch-22 (denying r7 for the pool prevents
c→r7) is resolved by COMBINING the r7 pin with the clobber-reservation:
- `register u32 c7 __asm__("r7") = c;` forces c→r7. The pin does NOT
  miscompile here (proves the w22d "never pin r7" rule is
  context-dependent, consistent with w24d's 0x080259A4 finding).
- `__asm__ volatile("" : "+r"(d16) : : "r7")` at the pool load denies r7
  for the pool pseudo → pool goes to r1 (ROM-correct).
- gcc honors both: the pinned c stays in r7, the pool avoids r7.

**Prologue shift sequence.** ROM does:
`lsls r3,r3,#16; lsrs r0,r3,#16; lsls r2,r0,#16; adds r0,r2,#0; asrs r0,r0,#16`.
Reproduced via a pinned-COPY chain with opaque barriers to defeat combiner
fusion:
- `d16a = (u32)d << 16; __asm__("" : "+r"(d16a));` → `lsls r3,r3,#16`
- `register u32 de __asm__("r0") = d16a >> 16;` → `lsrs r0,r3,#16`
- `register u32 d16 __asm__("r2") = de << 16;` → `lsls r2,r0,#16`
- `register u32 d16c __asm__("r0") = d16; __asm__("" : "+r"(d16c));` →
  `adds r0,r2,#0`, then `sd = (s32)d16c >> 16` → `asrs r0,r0,#16`.

**Loop scheduling fixup** (`fix_08004998.py`, Makefile sed-rule equivalent
per w23a/w24d precedent): gcc schedules q/ch before bufaddr; ROM does
bufaddr first (`mov r0,sp; adds r3,r0,r2`). The fixup reorders the 7 insns
(pure reorder + r7→r0 rename for the sp temp). Semantically identical.

**True extent 108 B** (not 102): 102 code + 4 pool at 0x8004A00; next
function at 0x8004A04. `addrs_sizes.txt` corrected.

**Callee prototype:** uses real signature `(u8*,u32,u32)` from
`src/wave13_D_old.c`; a u16 prototype would emit a spurious zero-extend
at the call. (u16 pins are NOT honored — tested, 84 diffs.)

Staging: `staging/wave25_B/w25b_08004998.c`, `fix_08004998.py`.
Verified via hardened protocol: 108/108 bytes, `cmp -l` 0 diffs,
disassembly eyeballed, pool `00 00 ff ff` verified as raw LE bytes.

### 0x08026740 — Task_Clock_08026740 (116 B true extent): 0 diffs
Clock task with nested rollover branches and a function-table dispatch.

**Control-flow correction:** ROM's `beq` at 0x8026790 skips the `S[18]=0`
when `S[19]==99`. The w24d C had `S[18]=0` outside the if (wrong).
Fixed: `if (S[19] != 99) { S[19]++; S[18] = 0; }`.

**Dispatch via pins:** `register u32 *tbl __asm__("r0")`,
`register u32 idx __asm__("r2")`, `register u32 idx4 __asm__("r1")`,
`register u32 *fnaddr __asm__("r1")`, plus `__asm__ volatile("" ::: "memory")`
reproduces ROM's:
`ldr r0,=0x0822D8EC; ldrb r2,[r4,#0]; lsls r1,r2,#2; adds r1,r1,r0;`
`ldr r1,[r1,#0]; adds r0,r4,#0; bl _call_via_r1`.
The `idx4 + (u32)tbl` order (not `tbl + idx4`) gives `adds r1,r1,r0`.

**ldrh:** `register u32 hrs __asm__("r2") = *(u16 *)(S+18)` gives
`ldrh r2,[r4,#18]` (ROM) vs `ldrh r0` (unpinned).

**True extent 116 B** (not 112): 112 code + 4 pool at 0x80267B0; next
function at 0x80267B4.

Staging: `staging/wave25_B/w25b_08026740.c`.
Verified: 116/116 bytes, 0 diffs.

## BLOCKED (2)

### 0x080259A4 — Tbl_SwapAndUpdate_080259A4 (98 B): 25 diffs (best, was 76)
Swaps `*(p+20+b*4)` / `*(p+20+c*4)`, then conditional StoreIdx2_25638 calls.

**Progress:** Pinned temps `b4→r2` (`b7<<2`) and `p20→r1` (`p+20`) achieve
ROM's exact swap sequence:
`lsls r2,r7,#2; adds r1,r5,#0; adds r1,#20; adds r3,r1,r2; ldr r4,[r3,#0];`
`mov r0,r8; lsls r6,r0,#2; adds r1,r1,r6; ldr r0,[r1,#0]; str r0,[r3,#0];`
`str r4,[r1,#0]; adds r2,r2,r5; adds r2,#20`.
Pins b7→r7, c8→r8, c4→r6, t→r4 give correct callee-saved allocation.

**BLOCKED on:**
1. **r7 not saved in prologue** (gcc bug): `register u32 b7 __asm__("r7")`
   does NOT cause gcc to emit `push {r4,r5,r6,r7,lr}`; it emits
   `push {r4,r5,r6,lr}`. ROM saves r7. The pin achieves the allocation
   but not the save/restore. (In 0x08004998 the r7 pin DID trigger the
   save — the bug is context-dependent.)
2. **Prologue extend order:** ROM: `lsls r1; lsrs r7,r1` (b) then
   `lsls r2; lsrs r2; mov r8` (c). gcc interleaves: `lsls r1; lsls r2;
   lsrs r7,r1; lsrs r2`.
3. **u8 extract from pinned reg is buggy:** `(u8)b7` generates
   `mov r0,sp; lsl r2,r0,#24` (wrong!) instead of `lsl r2,r7,#24`.
   Inline asm (`lsl %0,%1,#24; lsr %0,%0,#24`) works but disrupts the
   call-argument ordering (asm scheduled before `adds r1,r0,#0`).
4. **Call setup ordering:** ROM: `adds r1,r0,#0` then lsl/lsr; gcc+asm:
   lsl/lsr then `adds r1,r0,#0`.

A `.s` fixup (`fix_080259a4.py`) was attempted for the prologue/epilogue
and ordering, but it destabilized the branch alignment (50 diffs). The
C-only 25-diff version is staged as the best candidate.

Staging best: `staging/wave25_B/w25b_080259a4.c` (25 diffs).

### 0x0800E440 — ChipState_F_0800E440 (118 B): 83 diffs (best, was 87)
ChipState machine with switch dispatch.

**Progress:** `register u8 *S __asm__("r4")` pins S to r4, preventing gcc
from folding `S+37` to an absolute pool load (0x02005155). Now generates
ROM's `adds r0,r4,#0; adds r0,#37; ldrb r0,[r0,#0]`. Switch keeps
`push {r4,lr}`.

**BLOCKED on:**
1. **Ternary:** `(S[37]!=0)?5:3` — gcc uses r1 (`movs r1,#3` before cmp;
   `adds r0,r1,#0` after), ROM uses r0 directly
   (`cmp r0,#0; beq; movs r0,#5; b; movs r0,#3`). Tried ternary and
   if/else; gcc insists on r1. The `ldrb r0` for S[37] occupies r0,
   forcing the result to r1.
2. **80+ diffs** across the body from register allocation and branch
   layout differences. The function needs a more fundamental restructuring
   or a different compiler version.

Staging best: `staging/wave25_B/w25b_0800e440.c` (83 diffs).

## Idioms / observations for the catalog
1. **r7 pin + clobber-reservation breaks the catch-22** (0x08004998): when
   a pin forces the wanted reg AND a clobber denies it for a different
   pseudo, gcc honors both. The "never pin r7" rule is context-dependent.
2. **Pinned-COPY chain with barriers defeats fusion** (0x08004998): to
   reproduce a multi-insn shift sequence, pin each intermediate to its
   ROM register and separate with opaque `"+r"` barriers.
3. **True extents:** 0x08004998 is 108 B (not 102); 0x08026740 is 116 B
   (not 112). Always verify pool inclusion via disassembly.
4. **Control-flow from branch targets** (0x08026740): the `beq` target
   revealed `S[18]=0` is inside the `if (S[19]!=99)`, not after it.
   Always verify branch targets against the C structure.
5. **u8 extract from explicit reg var is buggy** (0x080259a4): `(u8)` cast
   of a `register ... __asm__("rN")` variable generates `mov r0,sp`
   garbage. Use inline asm or avoid the pattern.
6. **Local reg var does not guarantee save/restore** (0x080259a4): pinning
   to a callee-saved reg achieves the allocation but gcc may omit the
   push/pop. Verify the prologue/epilogue, not just the body.
7. **S pinned to r4 prevents absolute folding** (0x0800E440): when gcc
   folds `base+const` to a pool load, pinning the base to a register
   forces the adds sequence.

## Tooling
- `staging/wave25_B/w25b.sh`: hardened harness (from w24d.sh).
- `staging/wave25_B/fix_08004998.py`: verified loop-reorder fixup.
- `staging/wave25_B/fix_080259a4.py`: attempted (not working reliably).
- `staging/wave25_B/addrs_sizes.txt`: corrected sizes (08004998: 108,
  08026740: 116).
- `staging/wave25_B/rom_*.bin`: ROM extracts for reference.
- `staging/wave25_B/build/`: build artifacts (kept, not deleted).
