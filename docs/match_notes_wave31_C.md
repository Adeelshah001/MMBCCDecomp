# Wave 31-C Match Notes (Worker C, 2026-10-24)

Worker C, targets: 0x0801E77C (primary), blocked revisits with Wave-29/30 idioms.
Staging: `staging/wave31_C/` (C sources, verify.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry checks: 0x0801e77c NOT-IN-REGISTRY; 0x08000ca8 IN-REGISTRY as BLOCKED
(revisit, wave 7); 0x0801e14c IN-REGISTRY as BLOCKED (revisit, wave 15);
0x080173d4 NOT-IN-REGISTRY; 0x0801787c NOT-IN-REGISTRY. No duplicate claims.

## MATCHED (5, staged, DO-NOT-LAND — coordinator lands)

### 0x0801E77C — ChipTask_0801E77C (254 B, 0 diffs, old_agbcc)

**Staged:** `staging/wave31_C/w31c_0801e77c_MATCHED.c`.
**Verification:** clean-room rebuild (exact old_agbcc -O2 -mthumb-interwork rule)
→ link at 0x0801E77C with custom .ld → objcopy → cmp vs baserom extract at
file offset 0x1e77c: **0 diffs over 254 B**, reproducible.

**Wall broken (176 → 0 diffs):** prologue pool→r1. gcc put the pool load in r6
and the sum in r3; ROM wants pool→r1, sum→r2. New idiom: **function-scope pin
for pool constants** — `register u32 base __asm__("r1") = (u32)&gAddrZero[0x20051c8];`
forces `ldr r1,[pc]` (pin NOT ignored for constants when the pin is a
function-scope/early declaration; the wave-30 "ignored" finding was for a
different context). Combined with `register u32 off __asm__("r0")` and
`register u8 *tbl __asm__("r2") = (u8 *)(off + base)`, the prologue is
byte-perfect including the pool dump at 0x801e7a8 (pool-barrier mechanism).

**Two-movs idiom:** `u32 sp[2] = {0, 0};` (init at declaration) emits ROM's
`movs r0,#0; movs r1,#0; str r0,[sp,#0]; str r1,[sp,#4]`. Separate assignment
statements (`sp[0]=0; sp[1]=0;`) get CSE-merged into one movs. (Isolated test
confirmed.)

**Case 1 idiom:** `int v = pp[0]; int nv = v - 1; pp[0] = nv; if ((s16)nv == 0)`
gives ROM's `subs r0,r2,#1; strh r0,[r1,#0]; lsls r0,r0,#16; cmp r0,#0`.
(`--v` modifies in place → wrong regs; `(s16)(v-1)==0` folds to `cmp r2,#1`.)

**Case 3 idioms:** block-scope pins `base→r1`, `idx→r3` (u32 pin for byte
load); `(idx << 2) + base` operand order gives `adds r0,r0,r1` (w29b idiom).

**Behavioral name:** ChipTask_0801E77C — chip task state machine (p[14]):
case 0 init (ChipSlot_IncUse(p,8), NewNode), case 1 countdown (SelBlob_Ret(110)
at zero), case 2 flag check (Cmp_08004E0C(3), mask 0x020031E0), case 3 table
setup (0x082243D8-based). Sibling of ChipState_0801C030/ChipFxTick_0801C428.

**Bl targets (all verified from ROM):** ChipSlot_IncUse=0x0800D9EC,
NewNode_0801D278=0x0801D278, SelBlob_Ret=0x0800303C, Set_08004E24=0x08004E24,
Cmp_08004E0C=0x08004E0C, Fwd_10BA0=0x08010BA0.

### 0x08000CA8 — Init_08000CA8 (44 B, 0 diffs, old_agbcc)

**Staged:** `staging/wave31_C/w31c_08000ca8_MATCHED.c`.
**Wall broken:** "ROM pool→r3, zero→r2; mine swapped" (wave 7). Function-scope
pins `register u32 *base __asm__("r3") = (u32 *)0x030023c8` and
`register u32 zero __asm__("r2") = 0` defeat the allocator swap. **Declaration
order controls emission order:** `p1 = base - 2` declared before `zero`
gives ROM's `adds/subs` before `movs r2,#0`.
**Loop idiom:** `do { *b = one; i--; b += 24; } while (i >= 0)` with
`u8 one = 1` gives ROM's `movs r1,#1; movs r0,#2` order and
`strb; subs; adds; cmp; bge` body order.

**Behavior:** Init — zeros `*(0x030023c0)` and `*(0x02000800)`, stores param at
`*(0x030023c4)`, sets 3 bytes at 0x030023c8/0xE0/0xF8 to 1.

### 0x0801E14C — SlotCopy_0801E14C (34 B, 0 diffs, old_agbcc)

**Staged:** `staging/wave31_C/w31c_0801e14c_MATCHED.c`.
**Wall broken (6 diffs):** pool-scheduling — ROM does `ldr r1,[pc]` BEFORE
`ldrb r2,[r4,#9]`; scheduler always did ldrb first. New idiom: **`&gAddrZero[const]`
form forces early pool-load scheduling.** `register u32 base __asm__("r1") =
(u32)&gAddrZero[0x82243d8]` gives `ldr r1,[pc]` first; the raw `(u32)0x082243d8`
form lets the scheduler defer the ldr (verified empirically — same pins,
different scheduling).

**Bl target:** ClearSlot_10F88=0x08010F88 (MATCHED).

### 0x080173D4 — TblSlotInit_080173D4 (36 B, 0 diffs, old_agbcc)

Sibling of SlotCopy_0801E14C (same pool-scheduling idiom; pins base→r2/idx→r3).
`push {lr}` only; `*(p+12)=1`; `p[10] &= 254` inline; bl F_173FC=0x080173FC
(MATCHED).
**Staged:** `staging/wave31_C/w31c_080173d4_MATCHED.c`.

### 0x0801787C — SlotClear_0801787C (38 B, 0 diffs, old_agbcc)

Sibling of SlotCopy_0801E14C. Prologue: `DecIfNonZero_18(*(u8 **)(p+44))`
then `*(u32 *)(p+44) = 0`; then the SlotCopy pattern (`*(p+12)=4`).
**Bl target:** DecIfNonZero_18=0x08017464 (MATCHED).
**Staged:** `staging/wave31_C/w31c_0801787c_MATCHED.c`.

## New idioms discovered

1. **Function-scope pin for pool constants:** `register u32 base __asm__("r1") =
   (u32)&gAddrZero[CONST];` forces the literal-pool load into the pinned
   register. The "pinning ignored for constants" finding is context-dependent —
   it works for early function-scope declarations.
2. **`&gAddrZero[const]` vs raw `(u32)const` scheduling:** the gAddrZero-address
   form forces the pool load to schedule early (before independent ldrb);
   the raw constant form lets the scheduler defer it. Use gAddrZero form when
   ROM has ldr-before-ldrb.
3. **Array-init two-movs:** `u32 sp[2] = {0, 0};` at declaration gives two
   `movs` + ordered stores; separate assignments merge via CSE.
4. **Declaration order = emission order** for pinned inits (0x08000CA8).
5. **int-temp for `--v`:** `int nv = v - 1;` defeats both in-place modification
   and the `(s16)(v-1)==0` → `cmp` fold.
6. **do-while with `u8 one` temp** for ROM's movs order + `strb/subs/adds` body.

## Triaged (not attempted in depth)

- **0x080096BC / 0x08006FE8 / 0x08024A30:** all high-complexity (r8/r9/sl-heavy,
  Duff's-device-style loops, 6+ params, 11 callees). 0x080096BC decoded as a
  partially-unrolled tile-copy loop; not attempted — risk outweighs the likely
  gain given the 5 matches above.
- **0x080170D4:** SlotCopy-family pattern but with extra trailing logic
  (orrs/movs/bl after the standard prologue); follow-up candidate.

## Tooling

- `staging/wave31_C/verify.sh` — verify harness (wave30_D adapted).
- `staging/wave31_C/w31c_*.c` — iteration history (v1-v17 for 0x0801e77c).
- `staging/wave31_C/*_MATCHED.c` — the 5 staged matches.
- `staging/wave31_C/rom_*.bin` — ROM extracts.

## Summary for coordinator

- **MATCHED (5, staged, DO-NOT-LAND):** 0x0801E77C (254 B), 0x08000CA8 (44 B),
  0x0801E14C (34 B), 0x080173D4 (36 B), 0x0801787C (38 B). All 0 diffs,
  old_agbcc, clean-room verified. Registry rows appended (append-only).
- **For landing:** 5 Makefile rules (old_agbcc) + 5 ldscript slots. Extern
  prototypes: ChipSlot_IncUse, NewNode_0801D278, SelBlob_Ret, Set_08004E24,
  Cmp_08004E0C, Fwd_10BA0, ClearSlot_10F88, F_173FC, DecIfNonZero_18 — all
  real build T symbols (nm-verify at landing). gAddrZero `.set` is TU-local
  per w24b convention.
