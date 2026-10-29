# Wave 28-B Match Notes (Worker B: near-miss closers)

## Summary
- **MATCHED (1):** 0x0801b0dc (ChipSetup_0801B0DC, 220 B true extent, 0 diffs, old_agbcc)
- **BLOCKED (2):** 0x0803643c (structural size mismatch), 0x0801c428 (register allocation wall)

All staging in `staging/wave28_B/`. Section names `.text.w28b_<addr>`.
Registry checked: 0x0801b0dc NOT-IN-REGISTRY as MATCHED (only BLOCKED rows); no duplicate.

---

## MATCHED

### 0x0801b0dc: ChipSetup_0801B0DC (220 B true extent, 0 diffs, old_agbcc)

Chip setup dispatch on s[17] (cases 0,1,2) with common tail doing table lookup,
clamp, and bitfield update.

**True extent:** 220 B (0x0801b0dc–0x0801b1b7). Code 208 B + pools:
0x081705b0 @ 0x0801b1b0, 0x020031e4 @ 0x0801b1b4 (trailing); 0x00000847 @
0x0801b1ac, plus embedded pools @ 0x0801b118, 0x0801b140. (Task said "208 B";
true extent with pools is 220 B per hardened protocol.)

**What it does:** Switch on s[17]. Case 0/1: ChipSlot_Setup(s, 0x246, 0),
ChipSlot_IncUse(s, 2/3), stores to s+88/96/92/100. Case 2: Wrapper_D770(s,
0x847, 1), ChipSlot_IncUse(s, 1), stores. Tail: `t = *(u16*)0x081705b0;
tbl = 0x020031e4 + ((t>>4)<<1); t = *tbl & 3; if (t>3) t=3; p69=s+69;
t<<=2; m=-13; *p69 = (*p69 & m)|t; s[34]=13; Text_SelectBlobIdx(0xa0).`

**Decisive idioms:**
1. **`int t` (not `u8 t`):** The `u8 t` version gives `cmp r1,#3; bls` (unsigned)
   + shift-pair `lsls r0,r1,#26; lsrs r1,r0,#24` + `orrs r1,r0; strb r1,[r2]`.
   Changing to `int t` gives ROM-exact `cmp r1,#3; ble` (signed) + single
   `lsls r1,r1,#2` + `orrs r0,r1; strb r0,[r2]`. The signed `ble` proves the
   original used a signed int for the clamp temp.
2. **Single-instruction inline asm for the `adds` copy:** ROM has
   `adds r0,r1,#0` (0x1c08) before `cmp r0,#3` — a copy of t from r1 to r0
   for the compare. gcc coalesces all C-level temps (`int c=t`, `m=t`,
   barriers, block-scoped r0 pin all eliminated). Forced via:
   ```c
   {
       register int c __asm__("r0");
       __asm__ volatile("add %0, %1, #0" : "=r"(c) : "r"(t));
       if (c > 3)
           t = 3;
   }
   ```
   NOTE: GAS 2.42 rejects `adds r0,r1,#0` mnemonic in Thumb-16 ("instruction
   not supported in Thumb16 mode"); `add r0,r1,#0` (no 's') assembles to the
   identical encoding 0x1c08 (verified via objdump). Use `add` not `adds` in
   inline asm for 3-operand Thumb-16 adds.
3. **old_agbcc:** Decisive per wave27-C (16 vs 25 diffs on identical C);
   retained for the match.

**Verification:** Hardened protocol PASS. Clean-room recompile (cpp →
old_agbcc -O2 -mthumb-interwork → as), link at 0x0801b0dc via custom .ld,
objcopy -j .text.w28b_0801b0dc, all non-empty (o=1240, elf=1112, bin=220),
dd baserom at file offset 0x1b0dc count=220, `cmp -l` 0 diffs. Neighbor check:
section occupies 0x0801b0dc–0x0801b1b7; bytes at 0x0801b1b8+ are next
function's code, undisturbed.

**Staged:** `staging/wave28_B/w28b_0801b0dc_MATCHED.c`
(also `w28b_0801b0dc_MATCHED_final.c`, `w28b_0801b0dc_match220.bin`).

**Callees stubbed:** ChipSlot_Setup=0x0800D6E0, ChipSlot_IncUse=0x0800D9EC,
Wrapper_D770=0x0800D770, Text_SelectBlobIdx=0x0804A378 (all MATCHED in registry).

---

## BLOCKED

### 0x0803643c: WalkBits_0803643C (444 B — BLOCKED, structural size mismatch)

**True extent:** 444 B (0x0803643c–0x080365f8), verified from ROM bytes.
Trailing pool 0x0200BCE8 @ 0x080365f4 (disasm misdecodes as `pop`; verified
from bytes: `e8 bc 00 02`).

**Blocker (precise):** The v3 C (staging/wave25_D/w25d_0803643c_v3.c, also
staging/wave27_B/v_0803643c/f.c) generates **380 bytes**, not 444 — a 64-byte
structural deficit. Both main agbcc and old_agbcc give bin=380. The ROM
function has an extra block at 0x080365b6–0x080365de (the `if (sp4 != r6)`
compare via `lsrs r6,r0,#24; mov r2,sp; ldrb r2,[r2,#4]; lsls; cmp` sequence)
that the C does not generate; gcc optimizes the `u8 sp4 != u8 r6` compare
to a simpler form, losing ~64 bytes of code.

The wave27-B "60 diffs" was measured against a size-mismatched build and is
not actionable. The .s sed patch (w27b_0803643c_patch.py) for the 0x10000
hoist and the C-level pin work for cnt→r5 are moot until the C generates the
full 444 bytes. This needs coordinator-level work: either the C is missing
logic (the `sp4`/`r6` compare needs a formulation that defeats gcc's
u8-compare optimization) or a different base version exists.

**Tried:** v3 C with main agbcc (380 B), v3 C with old_agbcc (380 B).
**Staged:** `staging/wave28_B/w28b_0803643c_BLOCKED_v1.c` (best attempt).

### 0x0801c428: ChipFxTick_0801C428 (280 B true extent — BLOCKED, 174 diffs best)

Chip FX state machine. True extent 280 B (278 code + 2 pad @ 0x801c53e);
verified from ROM bytes.

**What matches:** Prologue, switch dispatch, `(s8)--p[18]` countdown, nibble
via `((u32)*q<<28)>>28` + barrier, `ldrsh` table loads (via s16 extern params
idiom — already in v7 base), call-2 and call-3 sequences, pools (0x082268C8,
0x082268C4).

**Blocker (precise):** Call-1 register allocation. ROM:
```
801c476: movs r5, #0
801c478: ldrsh r3, [r1, r5]   @ a1→r3, zero-offset in r5; n1 stays in r2
```
Mine (v1, 183 diffs, 284 B):
```
mov r8, r2                    @ save n1 (4 bytes overhead)
ldrsh r2, [r1, r3]            @ a1→r2, zero-offset in r3
...
mov r2, r8                    @ restore n1
```
gcc allocates a1 to r2 (clobbering n1), forcing the `mov r8,r2` / `mov r2,r8`
save/restore (+4 bytes → 284 vs 280, cascading diffs). ROM allocates a1 to r3
with the zero offset in r5, no save needed.

**Tried:**
- v1 (base v7): 183 diffs, 284 B.
- Pin `register s16 a1 __asm__("r3")`: 174 diffs, still 284 B (pin perturbed
  allocation; call-1 became `ldrsh r0,[r1,r3]`, worse).
- Clobber-reservation `__asm__ volatile("" : : "r"(t1) : "r2")` before a1 load:
  broke build (276 B, miscompile — clobbering r2 while n1 lives there is the
  catch-22 noted in wave27-D).

The s16-extern-params idiom (task's suggested angle) is already applied in the
v7 base and correctly forces `ldrsh` (vs `ldrh` with u16 params); it does not
address the r2-vs-r3 dest allocation. The allocator "stubbornly picks r2"
(wave27-D) across reordering, both compilers, and barrier removal.

**Staged:** `staging/wave28_B/w28b_0801c428_BLOCKED_v1.c` (183 diffs),
`w28b_0801c428_BLOCKED_va1.c` (174 diffs, pin attempt).

---

## New idioms / lessons

1. **`int` vs `u8` for clamp temp controls signedness of compare:**
   `u8 t = *tbl & 3; if (t > 3)` → `bls` (gcc proves non-negative, uses
   unsigned). `int t = *tbl & 3; if (t > 3)` → `ble` (signed). If ROM has
   `ble`/`bgt` on a clamp, the original used a signed int temp. (0x0801b0dc)

2. **GAS 2.42 rejects `adds Rd,Rn,#imm` in Thumb-16:** The mnemonic
   `adds r0,r1,#0` fails with "instruction not supported in Thumb16 mode",
   but `add r0,r1,#0` (no 's') assembles to the identical encoding 0x1c08
   (objdump confirms `adds r0,r1,#0`). Use `add` without 's' in inline asm
   when targeting the 3-operand Thumb-16 adds encoding. (0x0801b0dc)

3. **Single-instruction inline asm as last resort for coalesced copies:**
   When gcc coalesces a temp across all C formulations (tried: separate var,
   `m=t`, opaque barrier, block-scoped pin), a `register __asm__("r0")` +
   volatile asm emitting the exact instruction is the minimal intervention.
   Document as asm-assisted, not pure C. (0x0801b0dc)

4. **Size mismatch invalidates diff counts:** A "60 diffs" claim against a
   380-byte build vs 444-byte ROM is meaningless. Always assert bin size ==
   true extent before counting diffs. (0x0803643c)

5. **Verify pools from bytes, not disasm:** The trailing pool at 0x080365f4
   disassembles as `pop {r3,r5,r6,r7}` but is actually the pool word
   0x0200BCE8 (`e8 bc 00 02`). The hardened protocol's "pools verified from
   ROM bytes" rule caught this. (0x0803643c)

---

## For coordinator

- **0x0801b0dc READY TO LAND:** `staging/wave28_B/w28b_0801b0dc_MATCHED.c`,
  old_agbcc, 0 diffs over 220 B true extent. Section `.text.w28b_0801b0dc`
  → rename to project convention at landing. Note the inline-asm
  single-instruction assist (documents as asm-assisted match).
- **0x0803643c:** Needs C that generates 444 bytes before the sed/pin work
  can proceed. The v3 base is 64 bytes short.
- **0x0801c428:** Needs a new angle on the call-1 r2-vs-r3 allocation. The
  s16-params idiom is already in place; the wall is purely the dest register
  choice for `a1 = t1[idx*4]`.
