# Wave 32-D Match Notes (Worker D)

Worker D, 2026-10-24. Staging: `staging/wave32_D/` (C sources, verify.sh, didiff.sh).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: all targets NOT-IN-REGISTRY (verified 2026-10-24).
No claims made (coordinator lands per DO-NOT-LAND rule).

## Targets (caller-count desc, size asc)

| Address | Size | Callers | Status |
|---------|------|---------|--------|
| 0x08008b08 | 176 | 2 | ❌ BLOCKED (172/176 B, ~154 diffs) |
| 0x0800695c | 246 | 2 | ⏸️ not attempted (complex nested loops) |
| 0x08007678 | 166 | 1 | ⏸️ not attempted (w31-blocked) |
| 0x0800cd5c | 138 | 0 | ❌ BLOCKED (136/138 B, 2 bytes short) |
| 0x080221cc | 172 | 0 | ❌ BLOCKED (196/172 B, not close) |

**Result: 0/5 MATCHED.** All staged as BLOCKED with precise diffs.

## BLOCKED Details

### 0x08008b08 — DrawChipRects_08008B08 (172/176 B)
Best: `staging/wave32_D/w32d_08008b08_v12.c` (main agbcc).
12-iteration loop calling RectFill_7134(0x02004848, x, y, z, w).
- x = *(u16*)(p+4+2*i), y = tbl0[2*i+24*kind]+(s8)p[0], z = tbl1[2*i+24*kind]+(s8)p[1]
- w = (mask&1)?0:16, mask >>= 1 each iteration
- Flag check `*(u8*)(0x02004830+0x265)` each iteration, early return if set

**Key techniques developed:**
- In-place shift idiom: `u16 *xp = (u16 *)(p + 4); x = xp[i]; k = (i << 1) + kind * 24;`
  triggers `lsls rX,rX,#16; asrs rY,rX,#15` (2-insn) vs 3-insn version. FRAGILE —
  lost when full body added.
- Opaque barrier `__asm__ volatile("" : "+r"(base))` defeats `0x02004830+0x265`
  → `0x02004A95` fold AND prevents hoisting (stays in-loop).
- ldrsb via hardcoded `mov r4, %1` in template with r4 clobber:
  `__asm__ volatile("mov r4, %1\n\tmovs %0,#0\n\tldrsb %0,[r4,%0]" : "=&r"(sb0) : "r"(p) : "r4");`
  (compiler won't pick lo reg automatically when p in hi reg).
- 0x10000 increment idiom confirmed: `movs rX,#128; lsls rX,#9; adds r0,rY,rX;
  lsrs rZ,r0,#16; asrs r0,r0,#16; cmp r0,#11` for s16 loop counter.

**Walls:**
- Prologue order: ROM `lsls r1,#24; lsrs r1,#24; mov sl,r1` then mask; mine
  interleaves due to kind pin scheduling.
- kind pin to sl (`register u8 kind __asm__("sl")`) gets kind in sl but breaks
  in-place shift and prologue order.
- Register allocation: i in r2 vs r3, flag in r0/r4 vs r6, y in r5 vs r2.

### 0x0800cd5c — StateMachine_0800CD5C (136/138 B)
Best: `staging/wave32_D/w32d_0800cd5c_v2.c` (main agbcc).
State machine on s[1]: case 0 (init), case 1 (NodeInitSwitch), case 2 (compare
s[0] vs s[7], update masks), default return 1.

**Key techniques:**
- Opaque barrier on v defeats `0xedff & 0xdbff` → `0xc9ff` fold:
  `v &= 0xedff; __asm__ volatile("" : "+r"(v)); v &= 0xdbff;`
  Generates two separate pool loads with ANDs in between (matches ROM).
- Branch inversion: `if (a != b) {...} else {ret=0}` gives ROM's `beq` (else-code
  as fall-through) vs `bne`.

**Wall (2 bytes):** Instruction scheduling in case 2:
- ROM: `movs r0,#0` BEFORE strbs, `ldr r2,[pc]` (0x020031e0) AFTER strbs
- Mine: `ldr r2` before strbs, `movs r0,#0` after first two strbs
- Tried: explicit `int zero = 0`, direct address (no p var), no a/b locals.
  Compiler still schedules differently.

### 0x080221cc — ChipInit_080221CC (196/172 B)
Best: `staging/wave32_D/w32d_080221cc_v4.c` (main agbcc).
Straight-line chip init: clears s+108, sets bits in s+10, calls ChipSlot_Setup,
ChipSlot_IncUse, does table lookups, calls BlendCopy_080224E4.

**Walls:**
- Compiler optimizes `2 | b | 1` to `|= 3`; ROM does two separate orrs.
  Two statements help but increase size.
- `& -13` folds to `& 0xF3` (movs #243); ROM does `movs #13; negs`.
- Too many locals cause extra push (r6) and spills. 24 bytes over.

## New Idioms Discovered

1. **Opaque barrier defeats constant fold + hoist:** `__asm__ volatile("" : "+r"(var))`
   makes var opaque, preventing `0x02004830+0x265` → `0x02004A95` fold and keeping
   the load inside the loop (volatile prevents LICM hoist).
2. **Hardcoded lo-reg move for ldrsb:** When base is in hi reg (r9), compiler uses
   it directly (invalid for ldrsb). Template `"mov r4, %1\n\t..."` with `"r4"`
   clobber forces the move. (No pin needed — pins are function-wide!)
3. **In-place shift trigger:** `u16 *xp = (u16 *)(p + 4); x = xp[i]; k = (i << 1) + ...`
   gives 2-insn `lsls; asrs #15`. Using `2*i` or `((u16*)p)[2+i]` gives 3-insn.
   FRAGILE — sensitive to surrounding code.
4. **Branch direction:** `if (a != b) {big} else {small}` puts big code as
   fall-through with `beq` to small; inverted from naive expectation.

## For Coordinator

- **Staging:** All in `staging/wave32_D/`. Best versions:
  - `w32d_08008b08_v12.c` (172/176 B)
  - `w32d_0800cd5c_v2.c` (136/138 B) — CLOSEST, 2 bytes short
  - `w32d_080221cc_v4.c` (196/172 B)
- **Registry:** All NOT-IN-REGISTRY. Append BLOCKED rows with diff counts if
  desired, or leave for next wave.
- **Names:** DrawChipRects_08008B08, StateMachine_0800CD5C, ChipInit_080221CC.
- **Not attempted:** 0x0800695c (246B nested loops), 0x08007678 (166B w31-blocked).
- **Recommendation:** 0x0800cd5c is closest (2 bytes). The scheduling wall might
  yield to a different formulation. 0x08008b08 needs the in-place shift + prologue
  order solved together.

## Progress Bar

Wave 32-D: 0/5 layer targets matched (0%). Overall: 819 / 1674 C-matched (+0).
