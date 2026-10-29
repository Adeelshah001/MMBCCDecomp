# MMBCCDecomp — Wave 2 matching notes (worker B, coordinator-verified)

Date: 2026-10-20. Targets: the `0x0800DD08` leaf-utility cluster
(`sub_0800DD2C`, `sub_0800DD08`, `sub_0800DD4C`) — horizontal-mirror-aware
2D vector helpers. Each tests bit 7 of a flag byte at struct offset +35
and negates the X component when set; the s32 vector lives at +80/+84.
No `bl`, no literal pools, pure Thumb leaves.

## MATCHED

- `Vec2_SetMirrored`@0x0800DD2C (30/30 B): `o->x = (o->flip & 0x80) ? -x : x; o->y = y;`
  — `mmbcc/src/vec2.c`, `.text.vec2_setmirrored`.
- `Vec2_AddMirrored`@0x0800DD4C (38/38 B): `o->x += (o->flip & 0x80) ? -x : x; o->y += y;`
  — `mmbcc/src/vec2.c`, `.text.vec2_addmirrored`.
- Both require **old_agbcc** (`Makefile` per-file override, same pattern
  as `text.o`). Main agbcc diverges on register allocation for the
  `(u8 *)o; p += 35` shape (evidence: `/tmp/wave2_B/vD.s` vs `vD_old.s`
  in the worker's scratch; coordinator re-verified: main agbcc diffs at
  9 bytes on dd2c, 15 on dd4c).

## BLOCKED — `Vec2_CopyMirrored`@0x0800DD08 (27/34 bytes)

Behavior: copies `s->{x,y}` to `d->{x,y}`, negating x when the *source's*
flip flag is set; returns `d`. Single systematic difference: ROM assigns
`(d,y)→(r4,r3)`; every build assigns `(d,y)→(r3,r4)`. Affected bytes:
+2 (`1c04` vs `1c03`), +6 (`6d4b` vs `6d4c`), +22, +24, +26, +30
(`bc04` vs `bc02`), +32 (`4710` vs `4708`). Instruction sequence, load
order, flag-check shape (`ands; cmp r0,#0; beq`), `negs r2,r2`, and
epilogue shape are otherwise identical.

Exhaustion: ~22 source variants (explicit `dd=d` positions, `d` used
directly, `u8 *p` local positions, x/y decl/assign order swaps, ternary,
`s32*` destination, unused 3rd param, `unsigned` x/y) × {agbcc,
old_agbcc} × {-O1, -Os, -O2}. Both compilers immovably produce d→r3,
x→r2, y→r4 (x is pinned to r2 by the `negs` use in all shapes).
Best-effort C kept at `/tmp/wave2_B/dd08.c`; functionally identical.
A struct-layout hypothesis (e.g. `d` as a different type forcing the
register) remains the only unexplored angle — revisit if Wave 2+ work
produces a new register-pressure idea.

## New idioms (worker B; coordinator-verified on the two matches)

1. **old_agbcc vs agbcc regalloc** (extends the Text_SelectBlob finding to
   a second site): for the `u8 *p=(u8*)o; p+=35; if ((*p&0x80)!=0)` shape,
   main agbcc moves x→r3 and computes the address in r0; old_agbcc keeps
   the byte pointer in r3 and x in r1 — matching the ROM.
2. **Two-`adds` byte-pointer idiom:** `u8 *p=(u8*)o; p+=35;` as separate
   statements reproduces `adds r3,r4,#0` + `adds r3,#35` (not folded).
3. **`!= 0` on the masked flag** reproduces the ROM's redundant
   `ands; cmp r0,#0; beq`.
4. The `adds r4,r0,#0` is the compiler's own spill of `o` (r0 clobbered
   by `movs r0,#128`) — no source-level temp wanted.
5. Return-address pop register follows the return value
   (`pop {r2}; bx r2` when returning `d`; `pop {r0}; bx r0` for void).

---

## Worker D — EntryMgr setup/teardown + GatedDispatch (all MATCHED)

### `EntryMgr_Teardown`@0x08004F18 (88/88 B) + hooks — MATCHED
Teardown of the 3-entry manager at `0x02003670`: calls `sub_08004208` on
`base+44`, `base+0x264`, `base+0x49C`; clears byte at `0x02005028`; then a
mode-conditional branch to two vestigial no-op hook slots. **old_agbcc**
required: main agbcc schedules `ldrb` before `movs r0,#248` (4-byte diff
at span offsets 40–43) — scheduler divergence between the variants, not
just regalloc. `mmbcc/src/entrymgr.c`, `.text.entrymgr_teardown`.

### `EntryMgr_HookA`@0x08004F70 (10/10 B), `EntryMgr_HookB`@0x08004F7C (2/2 B) — MATCHED
Vestigial hook slots called only from Teardown's mode-conditional:
HookA forwards to the empty `sub_080057FC`; HookB is empty (`bx lr`).
Worker D verified their bytes reproduced except the section-end pad;
coordinator added the 2-byte zero pad and verified the full 104-byte
span `0x4F18–0x4F7C` byte-identical in the built ROM, so both count as
MATCHED (worker-D names: HelperA/HelperB).

### `EntryMgr_Setup`@0x08004F80 (108/108 B) — MATCHED
Twin/variant of Teardown (same base, same offsets `44/0x264/0x49C/0x11AE`,
same flag idiom): calls `sub_0800D568`/`sub_0800D59C` on `*(u32*)0x020066F0`,
sets `*(base+0x11AE) |= 2`, branches to `sub_080050E0`/`sub_08004FEC`,
calls `sub_0800419C` on the three entries (order `0x49C, 44, 0x264`),
then `(*(u32*)base)++`. **old_agbcc** for the whole TU (main agbcc
mis-allocates the flag pointer and the `153*4` materialization reg).
`mmbcc/src/entrymgr.c`, `.text.entrymgr_setup`.

### `GatedDispatch`@0x08006DD8 (88/88 B) — MATCHED
Flag-gated forwarder: returns 0 while `*(u8*)(0x02004830+0x265)` is set,
else returns `(u8)sub_08006E6C(0x02004830, p, (s16)(u16)a, (s16)(u16)b,
(s8)(u8)c, (u8)d)` with the last two args on the stack. **Main agbcc**
(no old_agbcc needed). `mmbcc/src/gateddispatch.c`,
`.text.gateddispatch`, incl. 2-byte zero tail pad (`sGatedDispatchPad`).

### New idioms (worker D; coordinator-verified on landing)
1. **Ignored-arg helpers**: tiny callees take the base pointer as an
   (ignored) argument — reproduces the ROM's `adds r0, r4, #0` before
   each `bl`.
2. **`u8 *p` reuse for regalloc**: one local reused for the `0x02005028`
   store-pointer and the `base+0x11AE` computation pins the ROM's
   `ldr r0` / `adds r1, r4, r0` allocation.
3. **`!=` for branch layout**: `if ((x & 0xF8) != 8) A(); else B();`
   emits `beq` to the out-of-line B-block after the pool; `==` inverts it.
4. **Section tail pad**: `static const u8 sPad[2] = {0,0}` in the code
   section reproduces the ROM's `0000` tail pad — GAS otherwise ends a
   non-4-aligned code section with its nop fill (`c046`).
5. **old_agbcc vs agbcc is a scheduler difference too**, not just
   regalloc (Fn1's 4-byte `movs`/`ldrb` order diff).
6. **CRITICAL — `.globl`/`.set` ordering for absolute `bl` targets
   (coordinator-found, proven by controlled test):** the `.set`
   defining an absolute callee address MUST come AFTER the referencing
   code in the `.s` file. If it precedes the code, GAS 2.42 binds the
   `R_ARM_THM_CALL` relocation to a synthetic LOCAL `*ABS*` symbol that
   the linker mis-resolves (observed: `bl` encoded as `ff f7 fe ff`,
   a self-branch); if it follows, the relocation binds to the GLOBAL
   symbol and links correctly. In C sources, put the `__asm__` `.set`
   block at the END of the file (compiler emits top-level asm in source
   order). The `text.c` top-of-file idiom was only ever proven for
   data symbols (ldr-pool), never for `bl` targets. When a callee gets
   matched for real, delete its `.set` line (duplicate-symbol otherwise).

---

## Worker C — Text_SelectBlobIdx + Gfx_BlitRequest (MATCHED), Obj_AddEntry (BLOCKED)

### `Text_SelectBlobIdx`@0x0804A378 (20/20 B: 18 code + 2 pad) — MATCHED
Tiny forwarder: zero-extends its `u16` arg, `bl sub_0800303C` (the
`Text_SelectBlob` caller that returns the index), sign-extends the
result to `s16`: `s16 Text_SelectBlobIdx(u16 idx) { return
sub_0800303C(idx); }`. First-try, instruction-identical with main
agbcc. The `pop {r1}; bx r1` epilogue is ordinary agbcc output for this
shape (cf. `Sram_Read`). `mmbcc/src/text_idx.c`, `.text.text_selidx`;
2-byte zero pad included (ROM `0000` at `0x4A38A`).

### `Gfx_BlitRequest`@0x08006A54 (76/76 B: 68 code + 8 pool) — MATCHED
Guarded forwarder: if `*(u8*)(0x02004830+0x265)` is nonzero, return;
else `sub_08006AD8(ctx, a, (s16)b, (s16)c, (s8)d, (u8)e)`. First-try
match with main agbcc, including register allocation (`ip` for `a`,
`r7` for ctx) and pool order (`02004830 00000265`) — the
extern-absolute-symbol idiom (`.set gReqCtx`) keeps the two literal
loads split and in ROM order. Name is tentative (inferred from the
shared callee with the tilemap blit path). `mmbcc/src/gfx.c`,
`.text.gfx_blitreq`.

### `Obj_AddEntry`@0x0802D7A0 — BLOCKED (name proposed, semantics understood)
10-param "append 16-byte entry" utility: guard
`if ((work[6]&2) && (u8)(a8-106)>3) return;`, then fills
`work[work[5]*16+420 … +435]` (bitfields from a1–a4, u16s a5–a7, bytes
a8/a9), bumps `work[5]`. Key discovery: needs **old_agbcc** — it emits
the ROM's 24-byte frame (8-byte aligned), while main agbcc emits 20.
Blocking diff: the `& ~2` bit-clear. ROM uses full 32-bit `and` with
`-3` (`movs r3,#3; negs`, CSE-kept in r3 across both RMWs); both
compilers narrow `u8 & ~2` → `& 253` when feeding a byte store.
~17 variants tried (u32/int temporaries, late mask assignment, unsigned
`0xFFFFFFFD`, `&=`/`|=` forms, operand swaps): all either still narrow
or break instruction order/registers. Best scratch:
`/tmp/wave2_C/sub_0802D7A0*.c` (variants a–g). Needs a new
narrowing-suppression idiom; revisit if one surfaces elsewhere.

### New idioms (worker C)
1. `old_agbcc` keeps 8-byte stack alignment (extra dead frame bytes);
   main `agbcc` doesn't — try `old_agbcc` when frame size mismatches
   by 4 (cheaper than inventing phantom locals).
2. `pop {r1}; bx r1` is normal agbcc output for tiny forwarding
   functions.
3. Narrowing hazard (open): `u8 & ~2` → `& 253` on both compilers;
   ROM's `& -3` not yet reproducible.

---

## Worker A — ChipSlot helpers (MATCHED), ChipSlot_Tick (BLOCKED)

### `ChipSlot_IncUse`@0x0800D9EC (16/16 B) — MATCHED
Thin wrapper: `sub_08004258(s + 0x70, (u8)idx)` — truncates arg1 to u8,
offsets the struct pointer by 0x70, tail-calls the table-slot
bookkeeping routine. **216 bl-callers — the #1 most-called utility in
the ROM.** Main agbcc, first try. `mmbcc/src/chipslot.c`,
`.text.chipslot_incuse`.

### `ChipSlot_Setup`@0x0800D6E0 (36/36 B: 34 code + 2 pad) — MATCHED
Wrapper: `sub_0800D800(s, 0, (u16)arg1, (u8)arg2, 0)` — 5th arg on the
stack (`sub sp,#4`); callee splits the u16 into `s[28]/s[29]`. Main
agbcc, first try. First landed function with size ≢ 0 mod 4: the
2-byte zero pad (`sChipSlotPad`) reproduces ROM `0000` at 0xD702
(GAS would emit `46c0`). `mmbcc/src/chipslot.c`,
`.text.chipslot_setup`.

### `ChipSlot_Tick`@0x0800D9FC — BLOCKED (name proposed, semantics mapped)
Big per-slot state update (302 B / 148 insns / 121 callers); 7-step
semantics fully mapped in `docs/wave2_workerA.md` (5-literal pool,
EWRAM pair array at `0x02005030`, relative-offset table walk).
**Hard blocker:** ROM `0xDA2A–0xDA2D` holds an explicit `(u8)`
truncation (`lsls r0,r2,#24; lsrs r0,r0,#24`) of `r2=((s[10]>>4)&1)`
in the else-branch of a diamond. 15+ source variants under both
compilers at -O2 (plus -O1/-Os spot checks): the compilers *always*
eliminate the cast via range analysis (`(x>>4)&1` is provably 0/1),
collapsing the diamond and shifting everything downstream by 2 bytes.
The ROM's explicit diamond + truncation is unproducible with the
available toolchain — the kind of thing a different gcc version would
explain. Secondary divergences (for when the blocker lifts): scheduler
hoists the table-entry load before the `(s8)s[117]` computation
(`ldrsb`-vs-`ldrb`+extend choice is anti-correlated with ordering);
ROM's `ip`/`r8` long-lived allocation not reproduced; second EWRAM
store recomputes its address from scratch in ROM. Best scratch:
`/tmp/wave2_A/ChipSlot_Tick.c`.

### New idioms (worker A)
1. `ldrsb Rd,[Rn,Rm]`/Rm=0 ⟺ `(s8*)tbl[idx]` vs `ldrb`+`lsl#24`/`asr#24`
   ⟺ `(s8)(u8*)tbl[idx]` (same table, mixed signed/unsigned views).
2. `0x10000` materialized as `movs#128`/`lsls#9` (no pool).
3. `*20` → `(x*4+x)*4`; stride-2 byte table; relative-offset table
   walk (`row += *(u32*)row`).
