# Wave 3 batch 2 worker notes (2026-10-20)

Worker: matching-C, batch 2 (15 leaf functions, 0x0804C278..0x08010DDC).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) /
`old_agbcc`. Build rule (exact): `cpp <src>.c -o <x>.i && agbcc -O2
-mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link each `.o` with section placed at the ROM address
(`arm-none-eabi-ld -T`), `objcopy -O binary --only-section`, byte-diff
vs ROM. For `bl` callees, a 2-byte Thumb stub (`.thumb_func; bx lr`)
was assembled and placed at the real callee address (a `--defsym` to
the absolute address makes ld insert a `__*_from_thumb` veneer, which
breaks the byte-diff; the stub approach from wave2_workerA is required).
Scratch: `/tmp/wave3_b/` (`mv.py`, `verify_all.py`, probes).

Result: **15/15 MATCHED**, 0 BLOCKED. All staged in
`mmbcc/src/wave3_b.c` (one section per function, absolute symbols in a
single `__asm__` block at end of file). Results in
`docs/wave3_b_results.tsv`.

## Per-function summary

| Addr | Name (tentative) | Bytes | Compiler | Behavior |
|------|------------------|-------|----------|----------|
| 0x0804C278 | TailCallR3 | 2 | naked+asm | `bx r3` tail-call trampoline |
| 0x080256DC | SetU8_Off1 | 4 | agbcc | `p[1] = v` |
| 0x0804B970 | ArmTrampoline | 4 | naked+asm | `adr r2; bx r2` -> ARM @0x0804B974 |
| 0x080257B8 | GetU16_Off14 | 4 | agbcc | `return *(u16*)(p+14)` |
| 0x08024760 | EwGet16_18 | 6+pool | agbcc | `return ew02007090.f18` |
| 0x0800EDF0 | EwSet16_14 | 6+pool | agbcc | `ew02005130.f14 = v` |
| 0x0800EE2C | EwSet16_16 | 6+pool | agbcc | `ew02005130.f16 = v` |
| 0x08004170 | ListPushFront | 8 | agbcc | `node->next=*head; *head=node` |
| 0x0800EE44 | EwSet8_68 | 8+pool | agbcc | `ew02005160.f68 = v` |
| 0x08011F7C | TickWrapper | 8 | agbcc | wrapper -> ChipSlot_Tick (BLOCKED) |
| 0x080082CC | SetHalf8000 | 10 | naked+asm | `*p = 0x8000` (+redundant mov) |
| 0x08010364 | EwSet8_72 | 10+pool | agbcc | `ew02005160.f72 = 1` |
| 0x0804A3FC | EwSet16_128 | 10+pool | agbcc | `ew0200BD20.f128 = 0` |
| 0x08026710 | TblGet11 | 12+pool | agbcc | `rom0822740C[a].f11` (16-B entries) |
| 0x08010DDC | EwSet8Ret1_20 | 12+pool | agbcc | `ew020051B0.f20=(u8)v; return 1` |

## New idioms discovered

1. **Struct-view for absolute addresses**: `*(u16*)(base + 14) = v` with
   `base` an absolute (`.set`) symbol folds to `strh r0,[r1,#0]` with a
   relocated pool (`base+14`). To reproduce ROM's `strh r0,[r1,#14]`
   with pool=`base`, declare a struct for the region
   (`struct { u8 _00[14]; u16 f14; }`) and assign the field. The original
   code clearly uses structs for these EWRAM regions. (Probes:
   EwSet16_14b vs EwSet16_14c.)
2. **GAS 2.42 rejects `s`-suffixed Thumb mnemonics**: `lsls`/`adds` in
   inline asm fail with "instruction not supported in Thumb16 mode".
   The unsuffixed forms (`lsl`, `add`) assemble and encode to
   byte-identical output (verified: `lsl r2,r2,#8` -> `12 02`, same as
   ROM's `lsls`). agbcc itself emits the unsuffixed forms.
3. **`naked` is supported by this agbcc** and emits no prologue/epilogue,
   making it a clean fallback for compiler-allocation mismatches
   (verified with a 2-byte `bx lr` probe).
4. **`--defsym sym=0xaddr` breaks `bl` verification**: ld inserts a
   `__sym_from_thumb` interworking veneer (absolute symbols default to
   ARM). Use assembled 2-byte Thumb stubs (`.thumb_func; bx lr`) placed
   at the real address instead (wave2 method, confirmed).
5. **Forced redundant truncation**: `(u8)(v|1) & 1` reproduces an
   original-compiler redundant `(u8)` truncation (`lsls/lsrs #24`) that
   this agbcc folds away, while still folding the return value to
   constant 1 (used in EwSet8Ret1_20).

## Recomp-relevant discoveries

- **EWRAM map fragments** (all tentative): `0x02005130` (u16 fields at
  +12/+14/+16/+18, byte/flag users nearby), `0x02005160` (byte fields at
  +68/+72), `0x020051B0` (flag byte at +20 with set/return-1 and
  is-clear reader pair at 0x08010DDC/0x08010DEC), `0x02007090` (u16 at
  +18 read by 14 callers in 0x08042xxx-0x08045xxx, compared against 7),
  `0x0200BD20` (u16 at +128, zeroed).
- **ROM table at 0x0822740C**: 16-byte entries; byte at offset 11 read
  by index (u8). Neighboring functions (0x08024670+) read offsets
  +14/+15 of the same table with an index bound of 248, suggesting a
  ~249-entry table (possibly sprite/palette related; callers do
  `(x&0xFF)` clamping nearby).
- **ARM code exists**: 0x0804B974 is ARM (`add r2,r3,r0,lsl r1;
  add r0,r3,#0; bx lr`), reached via the Thumb trampoline at
  0x0804B970. The recomp will need to handle this ARM fragment.
- **Text window dispatch**: `sub_0804C288`/`sub_0804C2FC` load a
  function pointer from `[struct+44]` into r3 and tail-call via
  `TailCallR3` (0x0804C278) — a per-window draw callback mechanism.
- **ListPushFront** (0x08004170) is a generic singly-linked-list
  prepend used by sub_080093D0/sub_08009490/sub_0800954C.

## Blockers

None. All 15 matched.

## Landing notes for coordinator

- Sections and exact ROM addresses (all 4-byte aligned):
  `.text.w3b_tailcallr3` @0x0804C278 (2 B code),
  `.text.w3b_setu8_1` @0x080256DC (4),
  `.text.w3b_armtramp` @0x0804B970 (4),
  `.text.w3b_getu16_14` @0x080257B8 (4),
  `.text.w3b_ewget16_18` @0x08024760 (6+pool),
  `.text.w3b_ewset16_14` @0x0800EDF0 (6+pool),
  `.text.w3b_ewset16_16` @0x0800EE2C (6+pool),
  `.text.w3b_listpush` @0x08004170 (8),
  `.text.w3b_ewset8_68` @0x0800EE44 (8+pool),
  `.text.w3b_tickwrap` @0x08011F7C (8),
  `.text.w3b_sethalf8000` @0x080082CC (10),
  `.text.w3b_ewset8_72` @0x08010364 (10+pool),
  `.text.w3b_ewset16_128` @0x0804A3FC (10+pool),
  `.text.w3b_tblget11` @0x08026710 (12+pool),
  `.text.w3b_ewset8ret1_20` @0x08010DDC (12+pool).
- Section tail-pad idiom applies: GAS emits a 2-byte `46c0` pad after
  the 2-byte TailCallR3, the 8-byte TickWrapper, and the 10-byte
  SetHalf8000; ROM has `00 00` there. Strip or zero-fill on landing
  (same handling as wave2 ChipSlot_Setup).
- The `ChipSlot_Tick` `.set` in wave3_b.c is temporary (target is
  BLOCKED in wave2); remove it when ChipSlot_Tick is matched.
- Suggested ldscript lines (coordinator to integrate):
```
. = 0x0804C278; .text.w3b_tailcallr3 : { build/wave3_b.o (.text.w3b_tailcallr3); }
. = 0x080256DC; .text.w3b_setu8_1 : { build/wave3_b.o (.text.w3b_setu8_1); }
. = 0x0804B970; .text.w3b_armtramp : { build/wave3_b.o (.text.w3b_armtramp); }
. = 0x080257B8; .text.w3b_getu16_14 : { build/wave3_b.o (.text.w3b_getu16_14); }
. = 0x08024760; .text.w3b_ewget16_18 : { build/wave3_b.o (.text.w3b_ewget16_18); }
. = 0x0800EDF0; .text.w3b_ewset16_14 : { build/wave3_b.o (.text.w3b_ewset16_14); }
. = 0x0800EE2C; .text.w3b_ewset16_16 : { build/wave3_b.o (.text.w3b_ewset16_16); }
. = 0x08004170; .text.w3b_listpush : { build/wave3_b.o (.text.w3b_listpush); }
. = 0x0800EE44; .text.w3b_ewset8_68 : { build/wave3_b.o (.text.w3b_ewset8_68); }
. = 0x08011F7C; .text.w3b_tickwrap : { build/wave3_b.o (.text.w3b_tickwrap); }
. = 0x080082CC; .text.w3b_sethalf8000 : { build/wave3_b.o (.text.w3b_sethalf8000); }
. = 0x08010364; .text.w3b_ewset8_72 : { build/wave3_b.o (.text.w3b_ewset8_72); }
. = 0x0804A3FC; .text.w3b_ewset16_128 : { build/wave3_b.o (.text.w3b_ewset16_128); }
. = 0x08026710; .text.w3b_tblget11 : { build/wave3_b.o (.text.w3b_tblget11); }
. = 0x08010DDC; .text.w3b_ewset8ret1_20 : { build/wave3_b.o (.text.w3b_ewset8ret1_20); }
```
