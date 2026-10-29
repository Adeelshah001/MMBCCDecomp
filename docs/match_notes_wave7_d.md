# Wave 7 D — Match Notes (worker, 2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc` at `-O2 -mthumb-interwork`, exact project build rule.
Verification: hardened protocol (link at ROM address, objcopy --only-section,
byte-diff vs baserom, assert non-empty at every step, full extent incl. pools).
Scratch: `/tmp/wave7_d/` (`wv.sh` harness, `f*.c` probes,
`*_MATCHED.c` = staged formulations).

Result: **5 UNBLOCKED, 2 still blocked**.

## UNBLOCKED (5)

### 1. sub_080031B8 @ 0x080031b8 — UNBLOCKED (0 diffs, main agbcc)

**Formulation** (`/tmp/wave7_d/StructInit_031B8_080031B8_MATCHED.c`):
- **Prologue**: `push {r4,r5,r6,lr}; mov r6,r8; push {r6}` — r8 used for a2.
  Pinned `register u32 va1 __asm__("r6") = a1;` and `register u32 va2
  __asm__("r8") = a2;` force the allocation. s left plain (compiler puts
  it in r4 naturally).
- **The 2-byte blocker** (`mov r1,r8` vs `mov r0,r8`): solved via explicit
  pinned asm:
  ```c
  register u32 t __asm__("r1");
  __asm__("mov %0,%1" : "=r"(t) : "r"(va2));  // emits mov r1,r8
  *(u32 *)(s + 12) = t;
  ```
  The `"=r"` with pinned r1 forces the dest; the `"r"(va2)` uses r8.
- **m pinned to r2**: `register u32 m __asm__("r2");` prevents the allocator
  from spilling m to r9 (which happened with plain u32).
- **z pinned to r5**: `register u32 z __asm__("r5");` prevents r9 usage.
- **k3f block**: `register int k3f __asm__("r3"); k3f = -0x3f;` gives
  `movs r3,#63; negs r3,r3`. Then `t = k3f` (pinned r0) gives
  `adds r0,r3,#0`. The double-AND (`ands r0,r1` then `ands r0,r3` after
  the m|=3) reproduced via two separate `__asm__("and...")` blocks.
- **Pool**: 0x08003725 and 0xFFFFFE00 via `ldr=` asm, placed correctly by GAS.

### 2. sub_0800322C @ 0x0800322c — UNBLOCKED (0 diffs, main agbcc)

**Formulation** (`/tmp/wave7_d/StructInit_0322C_0800322C_MATCHED.c`):
- **True size**: 100B code + 8B pool = 108B total (0x0800322c to 0x08003298).
  The prior worker's 120B claim was wrong (included extra bytes).
- **z in r3**: `register u32 z __asm__("r3");` with `__asm__("movs %0,#0" :
  "=r"(z))`.
- **k3f in r0**: direct `k3f = -0x3f` with pinned r0 gives `movs r0,#63;
  negs r0,r0`. Single AND (no double-AND like 031B8).
- **0x100**: `v100 = (0x80 << 1)` gives `movs r0,#128; lsls r0,r0,#1`.
- **m |= 3**: via opaque asm OR to force `orrs r2,r0` dest:
  ```c
  __asm__("movs %0,#3" : "=l"(c3));
  __asm__("orr %0,%1" : "+r"(m) : "r"(c3));
  ```
- **Pool**: 0x080039a5 and 0xFFFFFE00.

### 3. ObjInit_TypeA @ 0x08017F8C — UNBLOCKED (0 diffs, old_agbcc)

**Formulation** (`/tmp/wave7_d/ObjInit_TypeA_08017F8C_MATCHED.c`):
- **Compiler**: old_agbcc (for idx calc `movs r1,#3` before `ldrb` ordering,
  and mask block scheduling).
- **Dual branches**: `if (s[16] == 2)` with idx calc DUPLICATED in both
  branches (not shared). Each branch has its own `ldr` pools.
- **Split pools**: old_agbcc/GAS naturally splits the literal pools —
  branch 1's pool (0x081705B0, 0x020031E4, 0xFFFFE100) placed at 0x08017FF8
  (after branch 1's `b`), branch 2's pool (0x081705B0, 0x020031E4,
  0x00000706, 0xFFFFEB00) at 0x08018054 (end). 0 diffs confirms the split.
- **Mask block**: `idx <<= 2` in-place (not separate `sh` variable) gives
  `lsls r1,r1,#2`. Then `mask = -13` gives `movs r0,#13; negs r0,r0`.
- **Zero stores**: `u32 zero = 0;` declared after `p -= 0x23`, used for the
  four `str r1,[r4,#N]` stores. The `movs r1,#0` is scheduled before
  `movs r0,#17` (compiler hoist).
- **Vec2_AddMirrored**: called with direct literals `(s, 0x3300, -0x1F00)`
  and `(s, 0x2C00, -0x1500)`. The negative consts go to pool via compiler.
  Declared as `(u8*, int, int)` to avoid u16 truncation codegen.

### 4. ObjInit_TypeB @ 0x0801DCC0 — UNBLOCKED (0 diffs, old_agbcc)

**Formulation** (`/tmp/wave7_d/ObjInit_TypeB_0801DCC0_MATCHED.c`):
- **Double-OR**: 
  ```c
  u32 v; v = 2; v |= s[0xA]; v |= 1; s[0xA] = v;
  ```
  gives `movs r0,#2; ldrb r1; orrs r0,r1; movs r1,#1; orrs r0,r1; strb`
  (exact ROM).
- **s[0x41] mask block**: The combiner was putting mask in r3 (with
  `adds r0,r3,#0` copy). Fixed by pinning `register int m41 __asm__("r0");`
  giving `movs r0,#13; negs r0,r0` directly. The `*p = (*p & m41) | 4`
  pattern works.
- **Idx calc**: uses `gRom_081705B0[1]` (ldrh from [r0,#2], not [r0,#0]).
- **s[0x45] mask block**: standard `*p = (*p & mask) | idx` with `idx <<= 2`
  in-place.

### 5. ObjInit_205B8 @ 0x080205B8 — UNBLOCKED (0 diffs, old_agbcc)

**Formulation** (`/tmp/wave7_d/ObjInit_205B8_080205B8_MATCHED.c`):
- **Double-OR const**: The `1` was going to r5 (with `push {r4,r5,lr}`)
  instead of r1. Fixed via pinned asm:
  ```c
  register u32 c1 __asm__("r1");
  __asm__("movs %0,#1" : "=r"(c1));
  v |= c1;
  ```
  This "persists across compilers" per the task — the pinning is required.
- **Mask block (swapped!)**: Unlike TypeA, here `sh` is in r0 and mask in r1:
  ```
  lsls r0,r1,#2   ; sh in r0
  movs r1,#13; negs r1,r1  ; mask in r1
  ldrb r3,[r2,#0]; ands r1,r3; orrs r1,r0; strb r1,[r2,#0]
  ```
  Achieved via `register u32 sh __asm__("r0"); register int m __asm__("r1");`.
- **Pad**: Explicit `static const u16 pad_080205b8 = 0;` in the section to
  get `00 00` instead of linker's `c0 46`.
- **Branch**: `if (s[0x11] & 1)` with different `*(u32*)(s+0x54)` values
  (0x8C00 vs 0x2000).

## STILL BLOCKED (2)

### Obj_AddEntry @ 0x0802D7A0 — BLOCKED (260 diffs best)

**Best** (`/tmp/wave7_d/f2d7a0_v1.c`, main agbcc): 336B vs 340B, 260 diffs.

**Prologue issue**: The 10-param prologue has specific register allocation:
- ROM: a4→[sp,#4], a5→[sp,#8], a6→[sp,#12], a7→sl, a8→r8, a9→r9
- Mine: a4→[sp,#4], a5→[sp,#8], a6→sl, a7→r6, a8→r8, a9→r9

The compiler assigns sl to a6 (used in Block F) instead of a7 (used in
Block G). The `mov sl,r5` (a6→sl) happens instead of ROM's `ldr r6,[sp,#68];
mov sl,r6` (a7→sl). Pinning a7/a8/a9 to sl/r8/r9 breaks the stack layout
(sub sp,#20 vs #24).

**Mask narrowing**: The `& ~2` (`& -3`) in blocks A-D needs 32-bit AND, not
narrowed `& 253`. The `(mask & e[0])` pattern with `int mask=-3` should work,
but the full function wasn't integrated successfully due to the prologue.

**What was tried**: Plain C with per-block `u8 *e`; pinned sl/r8/r9 (breaks
stack); main vs old_agbcc (old worse). The mask idiom from wave5 (`int mask
+ inline asm and`) is proven in isolation but needs the correct prologue.

### ObjInit_1D3C0 @ 0x0801d3c0 — BLOCKED (137 diffs best)

**Best** (`/tmp/wave7_d/f1d3c0_v2.c`, old_agbcc): 160B vs 164B, 137 diffs.

**Issues**:
1. **v11 register**: ROM does `ldrb r1,[r4,#17]` (r1), but compiler puts it
   in r0. The `str r1,[r4,#108]` reuses r1 (which holds 0). Pinning v11 to r1
   via `register` didn't work; needs inline asm ldrb.
2. **Pool placement**: Two pools (0x501 at 0x801d400 for if-branch,
   0x501 at 0x801d460 for else-branch). The compiler merges or misplaces.
3. **Mask blocks**: Else branch has `s[0x41] = (s[0x41] & -13) | 4` followed
   by `s[0x45] &= -13` with mask in r2 (copied to r0 for first). The two-
   pointer formulation confuses the allocator (uses ip).
4. **Scheduler**: The `movs r1,#0` in else branch is hoisted before the
   `ldrb r2,[r4,#10]` (for the later `str r1,[r0,#28]`). The task notes
   "scheduler reorders str before strb" — the source order vs ROM order
   needs careful matching.

**What was tried**: v1 (plain), v2 (pinned v11), v3 (simplified). The if-branch
`s[0xA] |= 1` with ldrb to r2 (not r1) is tricky because r1 holds v11.

## New idioms

1. **Pinned `mov r1,r8`**: `register u32 t __asm__("r1"); __asm__("mov %0,%1"
   : "=r"(t) : "r"(va2));` forces `mov r1,r8` for hi-reg to specific lo-reg.
   Use when the compiler picks the wrong lo-reg for a hi-reg move.

2. **Pin m to prevent r9 spill**: When the allocator spills a variable to r9
   (hi reg), pin it to its ROM register (e.g., `register u32 m __asm__("r2");`).

3. **Separate mask variables per block**: If ROM materializes `-13` fresh in
   each block (not CSE'd), use separate `int m1, m2;` variables, not a shared
   `mask`.

4. **Pin double-OR const**: The `1` in `v |= 1` may go to r5 instead of r1.
   Pin via `register u32 c1 __asm__("r1"); __asm__("movs %0,#1" : "=r"(c1));`.

5. **In-place `idx <<= 2`**: Instead of `sh = idx << 2` (which may allocate
   sh to a different reg), do `idx <<= 2` in-place to get `lsls r1,r1,#2`.

6. **Explicit pad**: `static const u16 pad = 0;` in the section to avoid
   linker's `c0 46` padding.

## Files for coordinator

- `/tmp/wave7_d/StructInit_031B8_080031B8_MATCHED.c` — 0 diffs (main agbcc)
- `/tmp/wave7_d/StructInit_0322C_0800322C_MATCHED.c` — 0 diffs (main agbcc)
- `/tmp/wave7_d/ObjInit_TypeA_08017F8C_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave7_d/ObjInit_TypeB_0801DCC0_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave7_d/ObjInit_205B8_080205B8_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave7_d/f2d7a0_v1.c` — Obj_AddEntry best (BLOCKED)
- `/tmp/wave7_d/f1d3c0_v2.c` — ObjInit_1D3C0 best (BLOCKED)
- `docs/wave7_d_results.tsv` — summary table
- `docs/match_notes_wave7_d.md` — this file

**Landing notes**:
- The 5 MATCHED use inline asm and `register __asm__` pinning; keep in
  separate sections/files.
- The `.thumb_func`+`.set` footer is harness-only; in the full build,
  callees are real symbols.
- TypeA, TypeB, 205B8 need old_agbcc Makefile overrides.
- 031B8, 0322C use main agbcc.
- 205B8 needs the explicit `pad_080205b8` u16 (or the linker will pad with
  c0 46 in the full build too — check).
