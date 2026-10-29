# Wave 4 batch I worker notes (2026-10-20)

Worker: matching-C, batch I (64 small functions, <40 bytes).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc`. Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i &&
agbcc -O2 -mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link each `.o` section at its ROM address (absolute symbols
via `.set`), then `objcopy -O binary --only-section` and byte-diff vs ROM.
Scratch: `/tmp/wave4_i/`. All 62 MATCHED functions verified 0 diffs after
linking, in the final files `mmbcc/src/wave4_i.c` (17, main agbcc) and
`mmbcc/src/wave4_i_old.c` (45, old_agbcc).

Result: 62 MATCHED, 2 BLOCKED.

## Key finding: this batch is old_agbcc code

45 of 64 functions match ONLY with old_agbcc. Main agbcc mis-allocates the
indirect-dispatch shape: it emits `ldrb r1,[r0,#X]` (index straight into
r1), while the ROM has `ldrb r3,[r0,#X]; lsls r1,r3,#2` (index in r3,
scaled into r1). Any function containing the
`ldr r2,[pc]; ldrb r3,[r0,#off]; lsls r1,r3,#2; adds r1,r2; ldr r1,[r1];
bl _call_via_r1` sequence needs old_agbcc. The 17 main-agbcc matches are
the non-dispatcher wrappers (direct bl calls, EntryMgr sequences).

## New idioms (extend the catalog)

- **old_agbcc dispatcher**: `u32 *tbl = gTbl_X; u32 idx = s[OFF];
  ((void (*)(u8 *))tbl[idx])(s);` — old_agbcc puts tbl in r2, idx in r3,
  target in r1 → `bl _call_via_r1`. Main agbcc merges idx into r1.
- **u8 zero local**: `u8 zero = 0; s[3] = zero;` forces the zero into a
  dedicated register (r2/r1) instead of reusing the constant register.
  Required for EntMgr_Reinit* (0x08027730, 0x08027748, 0x0803510C,
  0x08035E40, 0x080482BC).
- **int mask = -7**: `p[3] &= ~6` makes old_agbcc emit `movs r0,#0xF9`
  (8-bit); the ROM has `movs r0,#7; rsbs r0,r0,#0` (32-bit -7). Declaring
  `int mask = -7; p[3] &= mask;` reproduces it (0x08027CFC).
- **No u16 local before arithmetic**: `u16 v = GetRomTableU16(idx);
  return base + v;` makes agbcc truncate v early (`lsls/lsrs` before the
  `adds`). Using the call inline — `return GetRomTableU16(s[1]) +
  *(u16 *)(s + 14);` — with the call as the FIRST operand reproduces
  `adds r0,r4,r0` (0x0802588C, 0x080258A4, 0x080265F8).
- **Struct-copy for ldm/stm**: `Tbl3 t = *(Tbl3 *)gTbl_080E9C04;`
  produces the `ldm r1!,{r3,r4,r5}; stm r2!,{r3,r4,r5}` 12-byte stack copy
  (0x08023278). Three separate word stores do not.
- **Explicit off local for _call_via_r2**: `u32 off = idx << 2; u32 fn =
  *(u32 *)((u32)tbl + off);` lands the target in r2 → `bl _call_via_r2`
  (0x0804DA00).
- **Paren order matters**: `s + (a * 4 + 0x14)` vs `s + a * 4 + 0x14`
  changes `adds` scheduling (0x08025934).

## Matched (62)

All in `mmbcc/src/wave4_i.c` (main) / `mmbcc/src/wave4_i_old.c` (old),
one `.text.w4i_<name>` section per function. Absolute data symbols in the
trailing `__asm__` `.set` block of each file (GAS 2.42 rule); no
duplicates between the two files or vs other sources (checked). Callee
externs (`Text_SelectBlob`, `EwSet8_72`, `GetRomTableU16`, `TblGet11`,
`GetU16_Off14`, `GetU16_10`, `GetU8_19`, `GetField22_U16`,
`GetField24_U8`, `GetByte1_25A08`, `SetU8_0_FF1`, `CpuFastSet`,
`EntryMgr_Teardown/Setup`, `_call_via_r3`) resolve to their real
definitions at final link — not `.set` here.

Landing notes for the coordinator:
- 7 functions carry an explicit 2-byte 0000 tail pad in ROM (static
  `sPad_*` in the source, cf. wave3_a GetIndexedU8): SelBlob_Ret
  (0x0800303C), CallEwSet8_72 (0x0800EE8C), Wrap_GetRomTableU16
  (0x08024634), Wrap_TblGet11 (0x0802465C), GetEnt_IdxByte1
  (0x080251B8), AddTbl_S14_Idx (0x080258A4). Sections are exact size.
- `mmbcc/src/wave4_i_old.c` needs the old_agbcc Makefile override (same
  pattern as `$(BUILD)/wave3_e_old.o`).
- `Dispatch_0816E2C0_2` (0x08001D98) has TWO pools (8 B) after a 2-byte
  0000 pad; section is 32 B total, next function at 0x08001DB8.

Recomp-relevant behavior discoveries (structure/metadata only):
- 28+ ROM function-pointer tables used as dispatchers, indexed by a
  byte at a struct offset (0,1,2,4,0x10): 0x0816E2C0, 0x0816E304,
  0x081705A4, 0x08173064, 0x081734F4, 0x08223D08, 0x08223E94,
  0x08226A24, 0x08226DD8, 0x08226EDC, 0x08226F2C, 0x08226FEC,
  0x0822701C, 0x0822709C, 0x08227140, 0x08227168, 0x082271C8,
  0x082271F4, 0x0822DC84, 0x0822EA6C, 0x0822EB58, 0x082300F8,
  0x08230D94, 0x08231098, 0x08232330, 0x082329B0, 0x08232D2C,
  0x08232E48, 0x08233A44, 0x08233AFC, 0x08233C54, 0x08234314,
  0x08234B74, 0x08234D4C, 0x08234D60, 0x08105F70, 0x080E9C04.
  The 0x08226xx tables are densely clustered (likely one subsystem's
  state handlers).
- 0x080045F8: `CpuFastSet(0x0805633C, 0x06007000 + ((*(u16*)0x020031E4
  & 0xC) << 12), 0x200)` — ROM→VRAM copy, 0x200 words, source bank
  selected by a flag nibble at 0x020031E4.
- 0x08024F08/0x08024F48: entity array at `*(0x02007090+0x14)`, 144-byte
  stride, count/index byte at +0x1B0; read u16 at +14 / +16 of entry.
  0x08024FF4/0x0802500C/0x08025024/0x080251B8 use the same base
  (0x02007090+0x18, or the entity array directly).
- 0x0804DA00: script-dispatcher shape — `tbl[*b->ptr++]` where b+0x40
  is a u8* cursor (auto-incrementing bytecode reader), table at
  0x08105F70.
- 0x0804CA1C / 0x0804DA20: indirect calls through EWRAM vectors at
  0x0200CE0C / 0x0200CD80 (runtime-patched function pointers).
- 0x08027CFC: clears bit 1 (mask -7) of `*(0x0200B7E0+3)`, then
  EntryMgr_Teardown.
- 0x08047600: copies a u16 header from `*(0x0200B7A8+4)` onto the
  struct, then dispatches `tbl[*(0x0200B7A8)]` with the EWRAM pointer
  as arg.
- EntryMgr wrappers (0x08027730/0x08027748/0x0803510C/0x08035E40/
  0x08047CC0/0x080482BC) reinitialize small entry structs (offsets
  1..5, 0xC, 0x46B4) around Teardown/Setup pairs — teardown/setup take
  no arguments; the struct pointer in r0 at the bl is incidental.

## Blocked (2)

### 1. sub_0803C20E @ 0x0803C20E — BLOCKED (mid-function fragment)

ROM (18 B):
```
c8f7b7fe bl   0x08004F80 (EntryMgr_Setup)
4046     mov  r0, r8
18bc     pop  {r3, r4}
9846     mov  r8, r3
a146     mov  sb, r4
f0bc     pop  {r4, r5, r6, r7}
02bc     pop  {r1}
0847     bx   r1
```
No prologue (starts with `bl`), restores r8/sb/r4-r7 — this is the
shared epilogue of the enclosing function (preceding bytes at
0x0803C1C0+ are its body, using r6 as base and r8/sb across the whole
span). Not a function entry; not producible from C. Same class as the
wave3_a blocked fragments.

### 2. sub_08047CC0 @ 0x08047CC0 — BLOCKED (scheduler divergence)

ROM (32 B), best C:
```c
u32 F(u8 *s)
{
    u8 v = s[0xc];
    s[0x46b4] = v;
    s[4] = 1;
    s[5] = 0;
    EntryMgr_Teardown();
    EntryMgr_Setup();
    return 0;
}
```
Both compilers emit (offsets +8..+16):
```
mine: 0a70 strb r2,[r1] | 0121 movs r1,#1 | 0171 strb r1,[r0,#4]
      0021 movs r1,#0   | 4171 strb r1,[r0,#5]
rom:  0023 movs r3,#0   | 0a70 strb r2,[r1] | 0121 movs r1,#1
      0171 strb r1,[r0,#4] | 4371 strb r3,[r0,#5]
```
The ROM hoists `movs r3,#0` above the first `strb` (reusing r3 the
instant the 0x46B4 offset dies); both agbcc variants materialize the
zero in r1 after the stores instead. Tried: `u8 zero` local (worse —
forces push {r4,lr}), `u32 off` variable (worse — r4), initialized vs
separate declaration, main vs old. The 8-byte scheduling delta is not
reachable with the allowed compilers/flags.
