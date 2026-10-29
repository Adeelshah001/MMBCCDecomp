# Wave 8 Batch S — Match Notes (Worker S)

23/78 MATCHED (all old_agbcc, byte-identical per hardened protocol).
4 BLOCKED with precise diffs. 51 not attempted (toolchain lost mid-session).

## MATCHED

### Table accessor cluster (0x08024554–0x080247A8, 13 fns)
Pattern: `u8 TblGet_fXX(u16 idx)` — bounds-check `idx > 248`, return `tbl[idx*stride + off]`.
Idioms: `register u32 i __asm__("r1") = idx;` pin; `if (i > 248) return 0;`;
base pointer loaded into r0 before index scaling (`rom0822740C`, `ew02007090`).
All 32 bytes, old_agbcc places literal pool mid-function via early-goto shape.

### Triple flag functions (0x08008628/54/80)
`FlagA_86xx`: reads `gEwram_02003670[0x11ae]`, three-way select returning A/B/C as s8.
Idioms: goto-structure (`if (p[11]) goto Ldef; ...`); empty `__asm__ volatile("":"+r"(r))`
barrier defeats range analysis so `lsls/asrs` sign-extension is emitted.

### 0x0804AD4C CtrTick_4AD4C / 0x0804A3C4 EwCopy_4A3C4
Same goto→pool→cold-block→epilogue pattern. `s32 *ctr` (ble not bls);
absolute-base-to-local for +120/+130 offsets; pinned r2=0x0200BD20, r1=0x02002EE0.
4A3C4 needed 44-byte section (42 code + `static const u16 pad=0` for the 00 00 gap).

### 0x0802637C Cmp8_2637C — 4× ldrh compare, old_agbcc.

### 0x0800300C TblValidate_300C
`(x<<16)>>13` shift-split trick: `register u32 xr __asm__("r0") = (u32)x << 16;`
before loads, `xr >> 13` after.

### 0x0800C92C FillPairs_C92C
56-byte section (48 code + 8-byte pool at +0x30). Do-while with mixed
signed/unsigned compares reproduces s16-increment shift dance.

### 0x0800960C TblInit_960C (52 bytes: 46 code + 2 pad + 4 pool)
Initializes 4× 8-byte table entries at 0x02004E18.
Hard-won idioms:
- Dual counter: r2 holds u16 `i`, r0 holds s16 `si` derived each iteration.
- `register u16 z __asm__("r4")` needs OPAQUE asm init
  (`__asm__ volatile("movs %0,#0":"=r"(z))`) — direct `= 0` ignores the r4 pin.
- `p[1] |= 0xFF` folds to a direct store; forced via
  `__asm__ volatile("movs %0,#255":"=r"(m))` with `register u32 m __asm__("r3")`.
- `si*8` in r1: `register s32 se __asm__("r0") = i;` + empty barrier asm to defeat
  the combiner's `(i<<16)>>13` strength-reduction, then `e = se*8`.
- `p = (u8*)e; p += (int)tbl;` yields `adds r1,r1,r5` (operand order matters).
- Explicit shifts for the u16/s16 conversions:
  `si = (s32)(i<<16)>>16; ... si<<=16; i = (u16)((u32)si>>16); si>>=16;`

### 0x0803FA1C CheckId_FA1C
`return (x==64||x==17||x==0x1040||x==0x13A0)?1:0`.
Idioms: goto-beq chain; constants as `(130<<5)`/`(157<<5)` so compiler emits
`movs+lsls` instead of pool; `bgt` (signed) forced via `int sx = (u16)x;`
temporary; `register int sx2 __asm__("r1") = sx` for the `adds r1,r0,#0` copy.

## BLOCKED (precise diffs)

### 0x0803FB9C (44B) — mid-function pool in dead code
Pool 0x2201 at offset 0x1c (bytes `22 01 00 00`, disassembles as `movs r2,#1`).
`ldr r0,[pc,#16]` at 0x803fba4 loads it. Branches skip over it.
`__asm__ volatile(".word 0x2201")` placed between `goto Lend` and `L2:` is
DELETED by GCC as unreachable code. No C-level way to emit data in dead code
found. Second pool 0x4201 at 0x803fbc8 (outside window).

### 0x0803FC8C (46B) — same + outside pools
Pool 0x1021 at offset 0x18 (`10 21 00 00`, disassembles as `asrs r1,r4,#32`).
Same dead-code deletion problem. Pools 0x2000/0x3000 at 0x803fcbc/0x803fcc0
(outside).

### 0x0802FBF0 (46B) — compiler CSE defeats pool
`p2 = pp + 0x18B` where `p1 = pp + (197<<1)` (= pp+0x18A).
Compiler emits `adds r0,#1; adds r2,r2,r0` (0x18A+1) instead of
`ldr r0,[pc,#28]; adds r2,r2,r0`. Opaque barrier on the offset did not prevent
the CSE. Pools 0x18B/0x02005168 at 0x803fc20/0x803fc24 (outside window).

### 0x0804CD34 (46B) — partial, ran out of time
Got: `push {r4,lr}`, `movs r4,#182` + `lsl %0,%0,#8` via opaque asm
(`lsls` mnemonic rejected by GAS without `.syntax unified`; `lsl` works),
`adds r1,r4,#0`, all three PC-relative ldrs.
Remaining: `qb += 12` folds to `strh r1,[r0,#12]` instead of
`adds r0,#12; strh r1,[r0,#0]` (memory barrier did not prevent);
dead `ldrb r0,[r2,#4]` before `movs r0,#0; strb r0,[r2,#4]` not reproduced.
Pools 0x03007FF0/0x68736D53/0x040000C6 at 0x804cd64/68/6c (outside).

## Toolchain note
`arm-none-eabi-as`/`ld`/`objcopy` vanished mid-session (were working, then
"command not found"; not in apt, not on disk). 51 functions not attempted.
All staged C files, mk.sh, and disassemblies remain in staging/wave8_S/.
