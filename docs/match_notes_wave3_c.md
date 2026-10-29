# Wave 3 batch C — worker notes (2026-10-20)

Worker: matching-C, targets = `## batch3` of `docs/wave3_batches.md` (15 leaf
functions). Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946`
(read in place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc`
(main); `old_agbcc` never needed — **15/15 MATCHED with main agbcc** at
`-O2 -mthumb-interwork`, exact project build rule. Scratch: `/tmp/wave3_c/`
(`mk.sh`, `verify.sh`, `p01`–`p15` probes, `pv/` variants, `final.c` =
staged file as compiled).

Staged: `mmbcc/src/wave3_c.c` (one `.text.w3c_<name>` section per function,
single trailing `__asm__` `.globl`/`.set` block). Results:
`docs/wave3_c_results.tsv`. Nothing blocked.

Address correction: the batch list drops a leading zero on three entries —
`0x08057FC` = `0x080057FC`, `0x0803130` = `0x08003130`,
`0x0802FC4` = `0x08002FC4` (raw 7-hex-digit values would point outside ROM).

## Per-function notes

- **NoopStub @0x080057FC** (2 B): `void f(void){}` → `bx lr`. Sole caller
  `EntryMgr_HookA@0x08004F70`. Already referenced by worker D as
  `extern void sub_080057FC(void)` + `.set` in `src/entrymgr.c` —
  coordinator must drop that `.set` on integration (duplicate otherwise).
- **SetU32_4 @0x08003130** (4 B): `*(u32*)(s+4)=v`. 5 callers in the
  0x08003154–0x08003FC8 cluster (a family of tiny struct setters;
  neighbor 0x08003134 zeroes the same field).
- **GetU8_0 @0x08025A0C** (4 B): `return s[0]`.
- **GetU8_12 @0x08017460** (4 B): `return s[0x12]`.
- **ToU8 @0x08024724** (6 B): `u8 f(u32 v){ return (u8)v; }` (`lsls`/`lsrs #24`).
  8 callers.
- **SetU32Pair @0x0802617C** (6 B): `p[0]=p[1]=v`.
- **G05130_SetU16_12 @0x0800EE38** (12 B incl. pool): store to
  `*(u16*)(0x02005130+0x12)`. First shape `*(u16*)(g_02005130+0x12)=v`
  miscompiled: the compiler emits pool `.word g_02005130+18` and the
  *assembler* folds it to `0x02005142`, with an unindexed `strh [r1]`.
  Fix (new idiom §1): `u8 *p = g_02005130; ((u16*)p)[9] = v;`
  → `ldr r1,[pc]` (pool `0x02005130`) + `strh r0,[r1,#0x12]`.
- **SetU8_0_FF1 @0x080256D4** (8 B): `s[0]=v; s[1]=0xFF`.
- **GetS16_78_3 @0x080174EC** (8 B): `s16 *p=(s16*)(s+0x78); return p[3];`
  → `adds r0,#0x78; movs r1,#6; ldrsh r0,[r0,r1]`. The single-expression
  `((s16*)(s+0x78))[3]` folds to `adds r0,#0x7E; movs r1,#0` (new idiom §2);
  probed variants `s16 *p=...; return p[3]` / `u8 *p=s+0x78; *(s16*)(p+6)` /
  `s+=0x78; return ((s16*)s)[3]` all give the ROM shape.
- **Wrap_ChipSlotTick @0x08021290** (10 B): `sub_0800D9FC(s)` forwarder.
  agbcc does **no** sibling-call optimization: a plain tail-position direct
  call compiles to `push {lr}; bl; pop {r0}; bx r0` (idiom §4). Callee is
  wave-2's BLOCKED `ChipSlot_Tick` candidate — referenced here via
  extern + `.set` (not landed anywhere else; verified absent from
  `src/`, `asm/`, `include/`).
- **G0BD10_Zero2 @0x0804A2CC** (16 B incl. pool): `g_0200BD10[0] =
  g_0200BD10[1] = 0` (`movs r0,#0; strh [r1]; strh [r1,#2]`, pool
  `0x0200BD10`).
- **IncU8_11 @0x08017488** (10 B): `s[0x11]++; return s[0x11];` — the ROM
  *reloads* the byte after storing (`ldrb r1; adds; strb; ldrb r0`),
  so it is increment-then-reload, not `return ++s[0x11]` (which would
  `movs r0,r1`).
- **G05130_GetS8_0A @0x0800EAB4** (16 B incl. pool): `u8 *p = g_02005130;
  return (s8)p[0x0A];` → `ldrb [r0,#0xa]; lsls #24; asrs #24`. Same
  assembler-folding trap as G05130_SetU16_12 (first attempt pooled
  `0x0200513A`); the local-base idiom fixes it.
- **Text_SelectBlobU16 @0x08002FC4** (14 B): `Text_SelectBlob(idx)` wrapper
  with the `lsls`/`lsrs #16` truncation. Ambiguity documented: `u16`
  param and `u32` param + explicit `(u16)` cast produce *identical* bytes;
  landed the `u16` form. `Text_SelectBlob` is extern-only here (defined in
  `src/text.c` — no `.set`, per the gfx.c duplicate-symbol rule).
- **G0CE08_IndirectCall @0x0804CA08** (20 B incl. pool): `g_0200CE08(a)`
  where `extern void (*g_0200CE08)(u32)` is absolute → `ldr r1,[pc];
  ldr r1,[r1]; bl _call_via_r1` (idiom §5). `_call_via_r1` is referenced
  implicitly by the backend (defined in `asm/thunks.s`); no C declaration.

## New idioms (worker C)

1. **Absolute-symbol + constant folds at assembly time.** For
   `extern`-absolute globals, `g + const` in C becomes pool
   `.word g+const`, which the *assembler* folds to a single address —
   destroying indexed addressing (`strh [r1,#0x12]` → `strh [r1]` with a
   bumped pool). Fix: copy the base into a local first
   (`u8 *p = g_02005130;`), then index off the local (`((u16*)p)[9]`,
   `(s8)p[0x0A]`). Seen at two sites (0x0800EE38, 0x0800EAB4).
2. **Two-statement base defeats nested address folding.** agbcc folds
   `((s16*)(s+0x78))[3]` to `adds #0x7E`, but `s16 *p = (s16*)(s+0x78);
   return p[3];` keeps `adds #0x78` + register offset `movs r1,#6;
   ldrsh [r0,r1]`. (Extends worker B's two-`adds` byte-pointer idiom to
   scaled array indexing.)
3. **capstone renders `00 00` as `movs r0, r0`.** The 2-byte gaps between
   Thumb functions in ROM are literally `00 00`, not a `mov` nop; gas
   pads sections with `c0 46` (`mov r8,r8`), so trailing section pads
   must be stripped at landing (established convention, re-confirmed).
4. **No sibling-call opt in agbcc.** Tail-position direct calls compile to
   `push {lr}; bl; pop {r0}; bx r0` with no source trickery (0x08021290,
   0x08002FC4). The `pop {r0}; bx r0` void epilogue matches wave-2 note §5.
5. **Indirect call through absolute function-pointer global** picks `r1`
   for the pointer when `r0` holds the single arg:
   `ldr r1,[pc]; ldr r1,[r1]; bl _call_via_r1` (0x0804CA08).

## Recomp-relevant discoveries

- `0x02005130`: EWRAM global struct (tentative `g_02005130`, `u8`-based)
  with an `s8` field at +0x0A and a `u16` field at +0x12. Both accessors
  have zero `bl` callers — invoked via function pointers or dead.
- `0x0200BD10`: two adjacent `u16` globals zeroed together (callers
  `sub_08000418`, `sub_080267F8`; the latter sits in the text-init
  neighborhood — `0x0804A2DC`, which also calls `Text_SelectBlobU16`,
  is the very next function).
- `0x0200CE08`: function-pointer global taking one `u32` arg, invoked via
  `_call_via_r1` (caller `sub_0804C2FC`) — a callback slot.
- `0x080174xx` family: one struct with counter bytes at `0x11`/`0x12`
  and an `s16[4]` (two pairs) at `0x78`. Three members matched here
  (`GetU8_12`, `IncU8_11`, `GetS16_78_3`); siblings (`0x08017458`,
  `0x08017474`, `0x080174C4`, `0x080174CC`, `0x080174E4`) sit in
  batches 1/4/5 — whoever takes those, the base+index idiom (§2) applies.
- `0x08002FC4` (`Text_SelectBlobU16`): u16-truncating wrapper on the
  text-bank path (`Text_SelectBlob@0x0804C6B4`), 4 call sites.
- `0x08021290` (`Wrap_ChipSlotTick`): forwarder to wave-2's blocked
  `ChipSlot_Tick` candidate, zero `bl` callers — likely called indirectly.

## Blockers

None. 15/15 MATCHED.

## ldscript lines (for coordinator)

```
. = 0x080057FC; .text.w3c_noopstub : { build/wave3_c.o (.text.w3c_noopstub); }
. = 0x08003130; .text.w3c_setu32_4 : { build/wave3_c.o (.text.w3c_setu32_4); }
. = 0x08025A0C; .text.w3c_getu8_0 : { build/wave3_c.o (.text.w3c_getu8_0); }
. = 0x08017460; .text.w3c_getu8_12 : { build/wave3_c.o (.text.w3c_getu8_12); }
. = 0x08024724; .text.w3c_tou8 : { build/wave3_c.o (.text.w3c_tou8); }
. = 0x0802617C; .text.w3c_setu32pair : { build/wave3_c.o (.text.w3c_setu32pair); }
. = 0x0800EE38; .text.w3c_g05130_setu16_12 : { build/wave3_c.o (.text.w3c_g05130_setu16_12); }
. = 0x080256D4; .text.w3c_setu8_0_ff1 : { build/wave3_c.o (.text.w3c_setu8_0_ff1); }
. = 0x080174EC; .text.w3c_gets16_78_3 : { build/wave3_c.o (.text.w3c_gets16_78_3); }
. = 0x08021290; .text.w3c_wrap_chiptick : { build/wave3_c.o (.text.w3c_wrap_chiptick); }
. = 0x0804A2CC; .text.w3c_g0bd10_zero2 : { build/wave3_c.o (.text.w3c_g0bd10_zero2); }
. = 0x08017488; .text.w3c_incu8_11 : { build/wave3_c.o (.text.w3c_incu8_11); }
. = 0x0800EAB4; .text.w3c_g05130_gets8_0a : { build/wave3_c.o (.text.w3c_g05130_gets8_0a); }
. = 0x08002FC4; .text.w3c_text_blobu16 : { build/wave3_c.o (.text.w3c_text_blobu16); }
. = 0x0804CA08; .text.w3c_g0ce08_indirectcall : { build/wave3_c.o (.text.w3c_g0ce08_indirectcall); }
```

Code lengths to keep (strip gas's trailing `c0 46` pad): NoopStub 2,
ToU8 6, SetU32Pair 6, Wrap_ChipSlotTick 10, IncU8_11 10,
Text_SelectBlobU16 14. The four pool functions
(`g05130_setu16_12` 12, `g0bd10_zero2` 16, `g05130_gets8_0a` 16,
`g0ce08_indirectcall` 20) are exact including pool; the rest have no pad.
