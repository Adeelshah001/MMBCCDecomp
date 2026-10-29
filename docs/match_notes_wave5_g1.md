# Wave 5 Batch POOL-G1 — Match Notes (worker, 2026-10-20)

Worker: matching-C, batch POOL-G1 (17 functions, 120–499 B, all bl-callees already matched).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place, never copied).
Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc`.
Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i && agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i && arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link `.o` section at ROM address via ld script, `objcopy -O binary --only-section`, byte-diff vs baserom.
Scratch: `/tmp/wave5_g1/` (`f207ec.c`, `f22ebc.c`, etc.; `matched_080207ec.*`, `matched_08022ebc.*` are the verified sources).

Result: **2 MATCHED, 15 BLOCKED** (11 not attempted due to time; 4 attempted with specific blockers).

## MATCHED

### ObjInit_207EC @ 0x080207ec (132 B total: 126 code + 2 pad + 4 pool) — MATCHED
**Compiler:** old_agbcc. **0 diffs** across all 132 bytes (verified via full-section binary compare).

Semantics: Object initializer (ObjInit family). 
- `r5 = *(s+40)` (linked struct)
- `*(s+108) = 0`
- `s[10] = 2 | s[10] | 1` (double-OR)
- `ChipSlot_Setup(s, 0x411a, 0)`
- `ChipSlot_IncUse(s, s[0x78])`
- `idx = ((r5[0x45] >> 2) & 3)`, clamped to 3
- `s[0x45] = (s[0x45] & -13) | (idx << 2)`
- `s[0x22] = r5[0x22]`
- `*(s+0x60) = (s[17] & 2) ? 0x15400 : 0xFFFF9C00`
- `*(s+0x64) = 0`

**Winning formulation:**
```c
u8 *r5 = *(u8 **)(s + 40);
u8 t;
*(u32 *)(s + 108) = 0;
t = 2;
t |= s[10];
s[10] = t | 1;  // NOTE: two-statement split forces movs r0,#2 BEFORE ldrb
ChipSlot_Setup(s, 0x411a, 0);
ChipSlot_IncUse(s, s[0x78]);
{
    u32 idx = ((u32)r5[0x45] << 28) >> 30;
    int mask = -13;
    u8 *p = s;
    u32 sh;
    register int c __asm__("r1");
    __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));  // opaque copy to r1
    if (c > 3)  // signed! gives ble not bls
        idx = 3;
    p += 0x45;
    sh = idx << 2;
    *p = (*p & mask) | sh;
}
```

**New idioms:**
1. **Double-OR constant-first:** `t = 2; t |= s[10]; s[10] = t | 1;` produces ROM's `movs r0,#2; ldrb r1; orrs r0,r1; movs r1,#1; orrs r0,r1; strb`. The single-expression `s[10] = 2 | s[10] | 1` gives `ldrb` before `movs` (wrong order).
2. **Opaque register copy via asm:** When the ROM has `adds r1,r0,#0` (copy) before a compare, and the compiler CSEs it away, use `register int c __asm__("r1"); __asm__ ("movs %0,%1" : "=r"(c) : "r"(idx));` to force the copy. The `=r`/`r` constraints with the pinned register variable guarantee r1. The asm must be opaque (non-volatile is fine) so the compiler can't CSE.
3. **Signed clamp:** `if (c > 3)` with `c` as `int` gives `ble` (signed); with `u32` gives `bls` (unsigned). ROM uses `ble` here.
4. **old_agbcc for mask block:** The `s[0x45] = (s[0x45] & mask) | (idx<<2)` with `int mask=-13` needs old_agbcc to get p→r2, sh→r1, byte→r3 (main agbcc gives p→r3, sh→r2, byte→r1).
5. **Declarations before if:** If `int mask; u8 *p; u32 sh;` are declared AFTER `if (idx>3)`, agbcc miscompiles (drops the store as dead code!). Must declare before the if. (agcc optimizer quirk)

### ObjInit_22EBC @ 0x08022ebc (140 B total: 126 code + 2 pad + 12 pool) — MATCHED
**Compiler:** old_agbcc. **0 diffs** across all 140 bytes.

Semantics: Object initializer, table-driven variant.
- `*(s+108) = 0`
- `s[10] = 2 | s[10] | 1` (double-OR)
- `ChipSlot_Setup(s, *(u16*)(0x08227174 + s[17]*6), 0)` — table lookup for arg1
- `ChipSlot_IncUse(s, s[17])`
- `idx = (*(u8*)((((*(u16*)0x081705b0)>>4)<<1) + 0x020031e4)) & 3`, clamped to 3
- `s[0x45] = (s[0x45] & -13) | (idx<<2)` (mask in r1)
- `s[0x22] = 31`
- `s[0x41] = (s[0x41] & -13) | 4` (reuses mask in r1!)
- `s[18] = 4`

**Key differences from 0x080207ec:**
- The `s[17]*6` is `(s[17]*2 + s[17])*2` → `tbl[s[17]*3]` with `u16 *tbl`
- The mask (-13) is computed in r1 (not r0) and reused for both s[0x45] and s[0x41]
- The idx clamp uses `adds r0,r2,#0` (r2→r0 copy) not r1
- `s[18] = 4` needs a fresh `movs r0,#4` (not CSEd from the earlier `| 4`); use `{ u8 v = 4; s[18] = v; }` to force it

**New idioms:**
6. **Table index as `tbl[i*3]`:** `*(u16*)(tbl + s[17]*6)` written as `tbl[s[17]*3]` with `u16 *tbl` gives the ROM's `lsls r0,r2,#1; adds r0,r0,r2; lsls r0,r0,#1` sequence.
7. **Mask reuse:** Declaring `int mask;` at function scope (no initializer), assigning `mask = -13;` right before first use, keeps it in r1 across both the s[0x45] and s[0x41] updates. Initializer at declaration hoists the computation to function top (wrong).
8. **Pool load scheduling:** `u16 *tbl = gRom_...;` declared in a block AFTER the double-OR (not at function top) gives ROM's pool-load-after-double-OR scheduling.

## BLOCKED (attempted)

### ObjInit_1D3C0 @ 0x0801d3c0 (160 B) — BLOCKED (scheduler)
If/else on `s[17]==0`. Branch1: `s[10]|=1; *(s+108)=0; s[10]|=2; ChipSlot_Setup(s,0x501,0); ChipSlot_IncUse(s,8); s[0x45]&=-13`. Branch2: `s[10]|=1; *(s+0x6c)=0; s[10]|=2; ChipSlot_Setup(s,0x501,0); ChipSlot_IncUse(s,0); s[0x41]=(s[0x41]&-13)|4; s[0x45]&=-13`. Tail: `s[18]=s[19]=0; s[10]|=1`.

**Blocker:** The scheduler reorders `str r1,[r4,#108]` BEFORE the `strb r0,[r4,#10]` for the `s[10]|=1` + `*(s+108)=0` sequence. A `__asm__ volatile("" ::: "memory")` barrier fixes the if-branch, but the else-branch still merges the two `s[10]` ORs and mis-schedules. 81 diffs remain, including a branch-offset mismatch (else branch 8 bytes short).

The `*(s+0x6c)=0` needs the two-step `adds r0,#80; str r1,[r0,#28]` (not folded `str [r4,#108]`); use `u8 *p=s; p+=0x50; *(u32*)(p+28)=0;`.

### ObjInit_205B8 @ 0x080205b8 (166 B) — BLOCKED (register allocator)
Similar to matched ones, but the double-OR constant `1` goes to r5 (`mov r5,#1`, `push {r4,r5,lr}`) instead of ROM's r1 (`movs r1,#1`, `push {r4,lr}`). 

**Blocker:** The register allocator prefers r5 for the `1` in `s[10] = t | 1` when r5 is free. In the matched 0x080207ec, r5 was used for the `*(s+40)` pointer, forcing r1. Here r5 is free. Tried: agbcc, old_agbcc, no-interwork (all use r5); block-scoped vs function-scoped `t`; `u8 one=1` temp; `__asm__ ::: "r5"` clobber; dummy r5 usage. None force r1. 108 diffs (prologue mismatch shifts everything).

This is likely a fundamental allocator preference; may need a different compiler version or a new idiom.

## BLOCKED (not attempted)

The following were not attempted due to time constraints. Brief analysis from disassembly:

- **0x08001f1c** (334 B): Complex switch on `s[3]` (modes 0-3), calls `0x0804dc94` (save driver). Uses stack frame (`sub sp,#16`). Likely a save/load state machine.
- **0x08002070** (340 B): Complex switch on `s[3]`, calls `0x0804db5c` (save driver). Similar to 0x08001f1c.
- **0x08002300** (330 B): Takes 2 args (u8 *s, int a?). Has `muls`, calls `0x0804db24/2c/34`. Save-driver related.
- **0x08002a1c** (210 B): Uses r8/r9/sl (high registers), complex. Calls `0x0804db28`.
- **0x08003fc8** (160 B): 4 args, calls `0x08003130` (SetU32_4). Uses sl/r9/r8.
- **0x080046b0** (238 B): Uses r8/r9, calls `0x0804db24`. Complex.
- **0x0801b47c** (146 B): ObjInit variant using `Vec2_AddMirrored` (0x0800dd4c). s in r6 (not r4). Table at 0x0822672a. Complex table lookups with `ldrsh`.
- **0x08020b60** (158 B), **0x080211ec** (146 B), **0x08021594** (132 B), **0x0802184c** (144 B): Likely ObjInit variants similar to 0x080205b8 (may hit the r5 allocator quirk).
- **0x0802298c** (220 B): Larger ObjInit variant, `push {r4,r5,lr}` (uses r5 legitimately).
- **0x080263a4** (138 B): Calls `0x08026710`. Not analyzed.

## New idioms for the catalog

1. **Double-OR constant-first** (`t=2; t|=s[10]; s[10]=t|1;` → `movs r0,#2` before `ldrb`)
2. **Opaque register copy** (`register int c __asm__("r1"); __asm__("movs %0,%1":"=r"(c):"r"(idx));` forces `movs r1,r0`)
3. **Signed vs unsigned clamp** (`int` → `ble`, `u32` → `bls`)
4. **old_agbcc mask allocation** (p→r2, sh→r1, byte→r3 for the `& -13 | <<2` pattern)
5. **Declarations before if** (agcc drops stores if locals declared after conditional!)
6. **Table index `tbl[i*3]`** for `*6` byte offset with u16 table
7. **Late mask assignment** (`int mask; ... mask=-13;` not `int mask=-13;`)
8. **Memory barrier for store ordering** (`__asm__ volatile("" ::: "memory")` prevents str/strb reordering)

## Recomp-relevant discoveries

- **ObjInit family:** These are object initializers that set up game entities. Common pattern: `*(s+108)=0`, `s[10]` bitflags, `ChipSlot_Setup`/`ChipSlot_IncUse`, `s[0x45]` mode bits, `s[0x22]`/`s[0x41]` config. The `0x411a`, `0x401b`, `0x501`, `0x255` args to ChipSlot_Setup are likely object type IDs.
- **s[0x45] bit layout:** Bits 2-3 are an index (0-3) clamped, bits 0-1 and 4-7 preserved via `& -13` (0xFFFFFFF3).
- **s[10] bitflags:** Bit 0 (1), bit 1 (2), bit 4 (16) set in various combinations.
- **Table 0x08227174:** u16 table indexed by `s[17]*3` (6 bytes per entry), used for ChipSlot_Setup arg.
- **EWRAM 0x020031e4:** Used in idx computation `((*(0x081705b0)>>4)<<1) + 0x020031e4`, byte `& 3` gives index.
- **0xFFFF9C00:** Constant used for `*(s+0x60)` when `!(s[17]&2)`; `0x15400` when set. Likely a pointer or color value.

## ldscript lines (for coordinator)

```
. = 0x080207ec; .text.objinit_207ec : { build/wave5_g1_old.o (.text.f207ec); }
. = 0x08022ebc; .text.objinit_22ebc : { build/wave5_g1_old.o (.text.f22ebc); }
```

Both need old_agbcc. The `.set` for ChipSlot_Setup/ChipSlot_IncUse must be removed on integration (they're defined in src/chipslot.c). The `.set` for gRom_081705B0/gEwram_020031E4/gRom_08227174 should be kept (or moved to a shared header) — check for duplicates.

Trailing pads: 0x080207ec has 2-byte `0000` pad + 4-byte pool (section 132 B). 0x08022ebc has 2-byte `0000` pad + 12-byte pool (section 140 B). Pools are part of the section (not trailing GAS pad).
