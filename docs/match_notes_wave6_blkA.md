# Wave 6 Blocked-Revisit A — Match Notes (worker, 2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc` at `-O2 -mthumb-interwork`, exact project build rule.
Verification: per-function link at ROM address with `.thumb_func`+`.set`
absolute symbols (fixes the minimal-harness `bl` veneer quirk),
`objcopy -O binary --only-section=.text`, byte-diff vs baserom.
Scratch: `/tmp/wave6_blkA/` (`wv.py` harness, `f*.c` probes,
`*_MATCHED.c` / `*_BLOCKED_*.c` = staged formulations).

Result: **4 UNBLOCKED, 2 near-miss (2-byte), 9 still blocked**.

## UNBLOCKED (4)

### 1. sub_08017D50 @ 0x08017D50 — UNBLOCKED (0 diffs, old_agbcc)

**Formulation** (`/tmp/wave6_blkA/ObjInit_17D50_08017D50_MATCHED.c`):
- **Idx calc** (the family key): 
  ```c
  register u32 idx __asm__("r1");
  register int c __asm__("r0");
  u32 b;
  __asm__("movs %0,#3" : "=r" (idx));
  b = *tab;
  __asm__("and %0,%1" : "+r" (idx) : "r" (b));
  __asm__("movs %0,%1" : "=r" (c) : "r" (idx));
  if (c > 3)
      __asm__("movs %0,#3" : "=r" (idx));
  ```
  Gives ROM's `movs r1,#3; ldrb r0,[r0]; ands r1,r0; adds r0,r1,#0;
  cmp r0,#3; ble; movs r1,#3`. The `"=r"`/`"+r"` with pinned regs forces
  the dest registers; the opaque `movs` copy defeats CSE.
- **Mask block**: late `mask = -13` assignment (textually AFTER
  `sh = idx << 2`) defeats old_agbcc's scheduler hoist; emits ROM order
  `adds; adds; lsls; movs; negs; ldrb; ands; orrs; strb`.
- **Split-adds** for `p = s; p += 0x45;` and `p -= 0x23`.
- **Shift-materialized** `(0x80 << 3)` for 0x400.
- **Pool via `ldr=`**: `__asm__("ldr %0,=0x...")` forces pool loads for
  constants the compiler would otherwise materialize.

**Unlocks**: the idx pattern (`movs r1,#3` before `ldrb`, `ands r1,r0`
dest) appears in all 15 ObjInit-family functions. This formulation cracks
it.

### 2. sub_08003154 @ 0x08003154 — UNBLOCKED (0 diffs, agbcc)

**Formulation** (`/tmp/wave6_blkA/StructInit_03154_08003154_MATCHED.c`):
- **Anti-fold strategy**: The ROM's compiler does NOT do value-tracking
  folds, but agbcc does. Defeat folds by making OR-constants opaque:
  ```c
  __asm__("movs %0,#16" : "=l"(c16));  // c16 unknown to compiler
  m |= c16;                            // orrs r2,r0, no fold possible
  int k2 = -0x0d;                      // fresh movs r0,#13; negs r0,r0
  ```
  Keep the fold where ROM wants it: `int k4 = k3 - 0x3b;` → `subs r0,#0x3b`.
- **Critical correction**: The `ldr r1,[pc,#80]` loads `0x0800330d`
  (a ROM pointer), NOT `0x800`! The compiler's `movs+lsls` for 0x800 was
  a red herring. Use `ldr=` asm or ensure the true constant is used.
- **Register pinning**: `register int k1 __asm__("r2")`, `register int k3
  __asm__("r0")`, etc., to force ROM's allocation.
- **Late assignment**: `k1 = -0x21` AFTER the call (not at declaration)
  to avoid callee-saved spill.

### 3. sub_0800322C @ 0x0800322C — UNBLOCKED (0 diffs, agbcc)

Adaptation of 03154: fresh `-0x3f` (not folded from `-4`), `0x100` via
`(0x80 << 1)`, `m |= 3` via opaque asm OR to force `orrs r2,r0` dest.
Pointer `0x080039a5`.

### 4. sub_08003298 @ 0x08003298 — UNBLOCKED (0 diffs, agbcc)

Adaptation: fresh `-0x3f` via opaque `movs`+negate (`k3f = -k3f` after
opaque `movs`), `m &= -4` (pinned r0), `m |= 1` via asm OR.
Pointer `0x08003cb9`.

## NEAR-MISS (2-byte diffs)

### sub_080031B8 @ 0x080031B8 — BLOCKED (2 bytes)

**Best** (`/tmp/wave6_blkA/StructInit_031B8_080031B8_BLOCKED_2B.c`):
- Prologue with r8 correct (`push {r4,r5,r6,lr}; mov r6,r8; push {r6}`).
- Integrated k-block with k in r3 correct.
- **Remaining**: `mov r0,r8; str r0,[r4,#12]` vs ROM's `mov r1,r8;
  str r1,[r4,#12]`. The a2 temp register (r0 vs r1) is a pure allocator
  preference; pinning, dummy uses, and old_agbcc all still choose r0.

### sub_08021E64 @ 0x08021E64 — BLOCKED (2 bytes)

**Best** (`/tmp/wave6_blkA/ObjInit_21E64_08021E64_BLOCKED_2B.c`):
- Uses 17D50 idx+mask patterns; fresh `movs r0,#0` for `s[0x22]=0` via
  opaque asm (defeats zero-CSE).
- **Remaining**: `adds r0,r0,r3` vs ROM's `adds r0,r0,r1` (table base
  0x020031e4 in r3 vs r1). The pinned `idx` (r1) causes the compiler to
  avoid r1 for the base.

## STILL BLOCKED

### sub_0800288C @ 0x0800288C — BLOCKED (15 diffs)

Arg-copy pinning (`register __asm__("r2"/"r3")`) gets the prologue but
causes `push {r4,lr}` (vs ROM's `push {lr}`) and misallocates the
`s[7]<<5` byte (r0 vs r1) and pool regs. The dual arg-copy + v-reload
pattern needs a different approach.

### Obj_AddEntry @ 0x0802D7A0 — BLOCKED (not integrated)

The wave5_blk mask idiom (`int mask=-3` + inline `and`) is proven in
isolation but the full 10-param, 332-byte function was not built.
Needs old_agbcc frame + full integration.

### ObjInit_TypeA @ 0x08017F8C / ObjInit_TypeB @ 0x0801DCC0 — BLOCKED

TypeB attempted: idx+mask patterns from 17D50 apply, but the `s[0x41]`
mask block scheduling and the `0x081705B0+2` pool/offset split need work.
TypeA not attempted.

### ObjInit_1D3C0 @ 0x0801D3C0 / ObjInit_205B8 @ 0x080205B8 — BLOCKED

Not attempted (time). See wave5_g1 notes for blockers.

### sub_080129F8 / sub_08025958 / sub_080281F0 — BLOCKED

Not attempted (time). See wave5_h1/h2 notes.

## New generalizable idioms

1. **Opaque OR-constants defeat value-fold**: `__asm__("movs %0,#16" :
   "=l"(c)); m |= c;` makes the constant unknown, preventing agbcc from
   folding a subsequent `-K` into `subs`/`adds`. Use when ROM has fresh
   `movs; negs` but the compiler folds.

2. **`.thumb_func` + `.set` fixes bl veneers**: In minimal harness,
   absolute symbols cause `bl` to route via `from_thumb` veneers. Append
   `__asm__(".thumb_func\n.set sym, 0x...")` to force direct `bl`.

3. **`ldr %0,=const` forces pool loads**: For constants the compiler
   would materialize via `movs+lsls` (e.g., 0x800), `__asm__("ldr
   %0,=0x800" : "=l"(v))` forces a literal pool load. GAS places the
   pool in first-use order.

4. **Verify pool values, don't assume**: The `ldr r1,[pc,#80]` in 03154
   loads `0x0800330d`, not `0x800`. Always check raw pool bytes.

5. **Late mask assignment defeats scheduler hoist**: Assign `mask = -13`
   textually AFTER the shift computation, not at block top, to get ROM's
   `lsls; movs; negs` order (not `movs; negs; lsls`).

6. **Pinned idx + opaque asm for `ands` dest**: The 17D50 idx pattern
   (`register u32 idx __asm__("r1")` + `__asm__("movs"/"and"/"movs")`)
   reliably produces `movs r1,#3; ldrb r0; ands r1,r0; movs r0,r1`.

## Files for coordinator

- `/tmp/wave6_blkA/ObjInit_17D50_08017D50_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave6_blkA/StructInit_03154_08003154_MATCHED.c` — 0 diffs (agbcc)
- `/tmp/wave6_blkA/StructInit_0322C_0800322C_MATCHED.c` — 0 diffs (agbcc)
- `/tmp/wave6_blkA/StructInit_03298_08003298_MATCHED.c` — 0 diffs (agbcc)
- `/tmp/wave6_blkA/StructInit_031B8_080031B8_BLOCKED_2B.c` — 2-byte diff
- `/tmp/wave6_blkA/ObjInit_21E64_08021E64_BLOCKED_2B.c` — 2-byte diff
- `docs/wave6_blkA_results.tsv` — summary table

**Landing notes**:
- The 4 MATCHED use inline asm and `register __asm__` pinning; keep in
  separate sections/files to avoid affecting other functions.
- The `.thumb_func`+`.set` footer is harness-only; in the full build,
  callees are real symbols so `bl` encodes correctly.
- 17D50 needs old_agbcc (mask block scheduling).
