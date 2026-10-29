# Wave 3 batch1 worker A notes (2026-10-20)

Worker: matching-C, batch1 (15 leaf functions).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place,
never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc`.
Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i && agbcc -O2
-mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: link each `.o` (absolute symbols via trailing `.set` block),
then `objcopy -O binary --only-section` and byte-diff vs ROM. Scratch:
`/tmp/wave3_a/`. All 10 MATCHED functions verified 0 diffs after linking.

Result: 10 MATCHED, 5 BLOCKED. All matched with main agbcc (no old_agbcc needed).

## Matched (10)

All in `mmbcc/src/wave3_a.c`, one `.text.w3a_<name>` section per function.
Absolute symbols in trailing `__asm__` `.set` block (GAS 2.42 rule).

| Addr | Name (tentative) | Bytes | Semantics |
|------|------------------|-------|-----------|
| 0x08017474 | GetField17_U8 | 4 | `return s[17];` — 49 bl callers, hot accessor |
| 0x080265F4 | GetField22_U16 | 4 | `return *(u16*)(s+22);` |
| 0x0802654C | GetField24_U8 | 4 | `return s[24];` |
| 0x0800EDE4 | SetEwram5130_12 | 12 | `*(u16*)(0x02005130+12) = v;` |
| 0x0804A3F0 | GetEwramBD20_130 | 12 | `return *(u8*)(0x0200BD20+130);` |
| 0x080174C4 | SetField120_U16Pair | 8 | `*(u16*)(s+120)=b; *(u16*)(s+122)=c;` |
| 0x080258F8 | GetIndexedU8 | 10+2pad | `return *(u8*)(a+((u16)b<<2)+21);` |
| 0x08002EE0 | CopyMosaicReg | 20 | `*(u16*)0x0400004C = *(u16*)0x02003240;` (REG_MOSAIC) |
| 0x080266F0 | GetRomTableU16 | 16 | `return *(u16*)(0x0822740C+(idx<<4)+6);` |
| 0x0800440C | InitLinkedNode | 16 | `*0x0200081C=s; *(s+12)=s+20;` |

Landing caveat: GetIndexedU8 section is 12 B (10 code + `46c0` pad); ROM is
10 B. Strip the pad (explicit next-section address) like ChipSlot_Setup.

## Blocked (5)

### 1. sub_0804BDA2 @ 0x0804BDA2 — BLOCKED (thunk, belongs in asm)

ROM (2 B): `4718  bx r3`. Called via `bl` from sub_0804B980 at 0x0804B9BC and
0x0804B9C4; callers set r3 = `*(r0+0x20)` (nonzero-checked callback) and
r0 = `*(r0+0x24)` (arg). It is a duplicate of the libgcc `_call_via_r3`
thunk (0x0804DCD8) but WITHOUT the trailing nop.

Tried: `void f(u32 a, u32 b, u32 c, void (*fn)(void)) { fn(); }` — agbcc
with `-mthumb-interwork` emits `push {lr}; bl _call_via_r3; pop {r0}; bx r0`
(12 B), NOT a bare `bx r3`. The interwork flag forces all indirect calls
through the `_call_via_rN` thunks. A bare `bx r3` is not producible from C.

Recommendation: add to `mmbcc/asm/thunks.s` as a 2-byte `_call_via_r3`-style
thunk at 0x0804BDA2 (no nop pad), like the Wave 0 libgcc thunks.

### 2. sub_0803D9EC @ 0x0803D9EC — BLOCKED (mid-function fragment)

ROM (6 B): `f7c7 fac8  bl 0x08004F80 (EntryMgr_Setup)` then
`e04f  b.n 0x0803DA92`. The `b` target 0x0803DA92 is a SHARED EPILOGUE
(`ldr r0,[sp,#20]; sub sp,#100; pop {r3-r5}; mov r8,r3; ...; pop {r2}; bx r2`)
belonging to the big function at 0x0803D9F4+. The bytes at 0x0803D9EC are a
fallthrough continuation from 0x0803D9E8 (`bl 0x08004F18`), NOT a function
entry (0 bl callers; tier B but byteclass=unknown).

Tried: `void f(void) { EntryMgr_Setup(); sub_0803DA92(); }` gives
`push {lr}; bl; bl; pop {r0}; bx r0` (compiler must save lr). With
`__attribute__((noreturn))` on sub_0803DA92: `push {lr}; bl; bl; nop` —
still saves lr and uses `bl` not `b`. The ROM's `bl; b` with NO prologue is
not producible: C cannot express "call then jump to another function's
epilogue without saving lr".

### 3. sub_0802C6E6 @ 0x0802C6E6 — BLOCKED (mid-function fragment, tier D)

ROM (6 B): `6830  ldr r0,[r6,#0]`; `8085  strh r5,[r0,#4]`; `e018  b.n 0x0802C71E`.
Tier D in func_list_v2 ("contains_v1_02C71E", demoted as mid-function).
r6/r5 are LIVE registers from the enclosing giant function (0x0802BDF6+,
a big switch/dispatcher using r6/r7/r8/sb/sl across chunks); the `b` target
0x0802C71E is also mid-function. The single `bl` caller (0x0802BE9E) is
intra-function. There is no C that names r6/r5 as live-in registers;
global register variables (`register ... __asm__("r6")`) would be a fiction
(the original is plain register allocation in one big function).

### 4. sub_0804DF9E @ 0x0804DF9E — BLOCKED (`pop {pc}` not producible)

ROM (8 B): `b500 push {lr}`; `f7ff fefc bl 0x0804DD9C`; `2000 movs r0,#0`;
`bd00 pop {pc}`. Both agbcc and old_agbcc with `-mthumb-interwork` emit
`pop {r1}; bx r1` (0xBC02/0x4708) for this pattern, never `pop {pc}` (0xBD00).

The ROM has exactly 4 instances of `pop {pc}` in the first 0x50000 bytes,
all the same wrapper pattern (`push {lr}; bl X; movs r0,#0; pop {pc}`), all
in the SRAM region: 0x0804DD98, 0x0804DE6C, 0x0804DEE6, 0x0804DFA6 (vs 479
instances of `pop {r1}; bx r1`). These were likely compiled without
interwork or hand-written; not matchable under the project's build rule.

### 5. sub_0804C558 @ 0x0804C558 — BLOCKED (register allocation)

ROM (10 B): `6c0a ldr r2,[r1,#64]`; `1c53 adds r3,r2,#1`; `640b str r3,[r1,#64]`;
`7813 ldrb r3,[r2,#0]`; `4770 bx lr`. Semantics: cursor advance —
`p = *(u8**)(s+64); *(u8**)(s+64) = p+1;` plus a byte load, but the loaded
byte goes to **r3**, not r0 (the ABI return register).

Tried: direct C (`u8 f(u32 dummy, u8 *s) { u8 *p=*(u8**)(s+64); *(u8**)(s+64)=p+1;
return *p; }`), 4-arg version, reordered loads, volatile reads. The compiler
CONSISTENTLY allocates the temp and the loaded byte to r0
(`adds r0,r2,#1; ...; ldrb r0,[r2]`). The ROM's choice of r3 for both is not
reproducible; it implies r0 was live in the original context (but the
function as a standalone leaf has no live r0). 0 bl callers.

## New idioms / codegen notes

- **Absolute-base + offset**: to get `ldr rN,=base; strh r0,[rN,#12]` (not
  folded to `ldr rN,=base+12`), load the base into a local first:
  `u8 *base = gBase; *(u16*)(base+12) = v;`. If written as
  `*(u16*)(gBase+12) = v;` the linker folds to `=base+12` with offset #0.
- **`(u16)b << 2`**: `u32 off = ((u16)b) << 2;` gives `lsls #16; lsrs #14`.
  Writing `(u16)(b<<2)` instead gives `lsls #18; lsrs #16` (different!).
- **In-place `adds`**: `s += 120;` is required to get `adds r0,#120`
  (modifying r0); `*(u16*)(s+120)=...` keeps the base in r3.
- **Split adds**: `t = s; t += 20;` gives `adds r1,r0,#0; adds r1,#20`
  (two instructions); a single `s+20` folds differently.
- **`pop {pc}` (0xBD00)**: not emitted by agbcc/old_agbcc under
  `-mthumb-interwork` (always `pop {r1}; bx r1`). 4 ROM instances, all in
  SRAM wrappers — treat as unmatchable under the build rule.
- **Bare `bx rN`**: not emitted under `-mthumb-interwork` (indirect calls go
  via `bl _call_via_rN`). Handled in `asm/thunks.s`, not C.
- **Section tail pad**: agbcc pads sections with `46c0` (`mov r8,r8`). When
  ROM has no pad (next function immediately after), the landing must strip
  it (GetIndexedU8: 10+2).

## Recomp-relevant discoveries

- **0x02005130**: EWRAM struct; 0x0800EDE4 writes u16 at +12, batch2's
  0x0800EDF0 writes u16 at +14. Likely display/graphics config (near the
  mosaic and BGCNT-style setters in 0x0800EDxx).
- **0x0822740C**: ROM table, 16-byte entries. 0x080266F0 reads u16 at
  `base+(idx<<4)+6`; batch2's 0x08026700 reads u8 at `base+(idx<<4)+11`.
  Sibling accessors on the same table — likely chip or character data.
  18 bl callers on the u16 accessor.
- **0x0200081C**: holds a pointer to a node struct; node+12 points to
  node+20 (intrusive list or fixed-layout header, 20-byte header).
- **0x0400004C (REG_MOSAIC)** is refreshed from EWRAM 0x02003240 by
  CopyMosaicReg (0x08002EE0).
- **0x080174xx cluster**: struct with u8 at +16/+17 (bit-test at +16 via
  0x08017494, max-set at +17 via 0x08017478, inc at +17 via 0x08017488) and
  a u16 pair at +120 (0x080174C4). The +17 byte with 49 callers (0x08017474
  getter) is a hot field — possibly a status/flags byte.
- **0x080258F8**: `a + (b<<2) + 21` byte lookup — 4-byte stride table with a
  byte field at +21; likely per-index record access.
- **SRAM region quirk**: 0x0804DD9C is `mov pc, lr` (unusual return);
  the four `pop {pc}` wrappers surround it. Timing-critical or hand-tuned
  code — recomp should preserve exact behavior.

## ldscript lines needed (coordinator)

```
. = 0x08017474; .text.w3a_getfield17_u8 : { build/wave3_a.o (.text.w3a_getfield17_u8); }
. = 0x080265F4; .text.w3a_getfield22_u16 : { build/wave3_a.o (.text.w3a_getfield22_u16); }
. = 0x0802654C; .text.w3a_getfield24_u8 : { build/wave3_a.o (.text.w3a_getfield24_u8); }
. = 0x0800EDE4; .text.w3a_setewram5130_12 : { build/wave3_a.o (.text.w3a_setewram5130_12); }
. = 0x0804A3F0; .text.w3a_getewrambd20_130 : { build/wave3_a.o (.text.w3a_getewrambd20_130); }
. = 0x080174C4; .text.w3a_setfield120_u16pair : { build/wave3_a.o (.text.w3a_setfield120_u16pair); }
. = 0x080258F8; .text.w3a_getindexedu8 : { build/wave3_a.o (.text.w3a_getindexedu8); }  /* strip 2-B pad */
. = 0x08002EE0; .text.w3a_copymosaicreg : { build/wave3_a.o (.text.w3a_copymosaicreg); }
. = 0x080266F0; .text.w3a_getromtableu16 : { build/wave3_a.o (.text.w3a_getromtableu16); }
. = 0x0800440C; .text.w3a_initlinkednode : { build/wave3_a.o (.text.w3a_initlinkednode); }
```

Absolute symbols newly introduced (add to the project's symbol table or keep
the trailing `.set` block in wave3_a.c until real definitions land):
`gEwram_02005130=0x02005130`, `gEwram_0200BD20=0x0200BD20`,
`gRegMosaic=0x0400004C`, `gEwram_02003240=0x02003240`,
`gRom_0822740C=0x0822740C`, `gEwram_0200081C=0x0200081C`.
