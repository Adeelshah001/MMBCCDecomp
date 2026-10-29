# Wave 24-A: Rect-fill family (0x08006AD8 / 0x08007134 / 0x080065BC / 0x08006374)

Worker A, 2026-10-23. No matches landed. Major progress on the prologue
allocator wall via the pinned-COPY-register idiom (w12b), but the
**selective-spill** sub-wall persists: pinned copies deliver ctx/b/d/pa to
their ROM hi regs, yet the unpinned params (c,e) take registers (r5/r7)
instead of spilling.

## Registry check

None of the four targets appear in docs/match_status.tsv (the 0x08006AD8
grep hit is only the neighboring Gfx_BlitRequest @0x08006A54). All four
were live targets.

## 0x08006AD8 — TilemapRectFill (768 B) — BLOCKED, best v8 (723 diffs)

Staging: `staging/wave24_A/w24a_08006AD8_v8.c` (also v5/v6/v7/v9/v10,
pin1). Verified with hardened harness: 768/768 bytes, 723 diffs.

### What works (v8)

The **pinned-COPY-register idiom** (w12b) cracks the hi-reg assignment:
```c
register u8 *ctx_c __asm__("r6") = ctx;   /* -> adds r6,r0,#0 */
register s16 b_c __asm__("r9") = b;       /* -> lsls/lsrs r2,#16; mov r9,r2 */
register s8 d_c __asm__("r8") = d;        /* -> lsls/lsrs r0,#24; mov r8,r0 */
register u8 *pa __asm__("sl"); pa = a;    /* -> ldr r0,[sp,#0]; mov sl,r0 */
```
Pinning the COPY (not the primary) is decisive — pinning primaries
(v_pin1) perturbs the scheduler. The explicit `pa = a` cached-copy
structure reproduces the ROM's spill-then-reload (`str r1,[sp,#0]` ...
`ldr r0,[sp,#0]; mov sl,r0`).

Corrected types from matched caller Gfx_BlitRequest (mmbcc/src/gfx.c):
`void sub_08006AD8(u32 ctx, u32 a, s16 b, s16 c, s8 d, u8 e)`.
The w23b v3 used u16/u16/u8; the ROM sign-extends at use sites
(`asrs`), so s16/s16/s8 is required.

### Blocker: selective spill

ROM prologue (verified from ROM bytes):
```
adds r6,r0,#0; str r1,[sp,#0]; ldr r0,[sp,#72]; ldr r1,[sp,#76]
lsls/lsrs r2,#16; mov r9,r2          ; b -> r9
lsls/lsrs r3,#16; str r3,[sp,#4]     ; c -> SPILL
lsls/lsrs r0,#24; mov r8,r0          ; d -> r8
lsls/lsrs r1,#24; str r1,[sp,#8]     ; e -> SPILL
ldr r0,[sp,#0]; mov sl,r0            ; pa -> sl
```
v8 produces: ctx->r6 ✓, b->r9 ✓, d->r8 ✓, pa->sl ✓, a->spill ✓,
but **c->r5, e->r7** (registers) vs ROM's spills. Frame `sub sp,#44`
vs ROM `sub sp,#40`. The c/e spill decision is a graph-coloring
priority outcome I could not influence via: declaration order (v6/v9),
opt levels (-O1/-Os), old_agbcc, agbcc_arm (ARM codegen, useless),
pinning fewer/more (v10: dropping b/d pins collapses everything).

Hypothesis: c/e lose to dst/m2 (r5/r7) in the ROM's coloring because
dst/m2 have longer live ranges × more loop refs; in my C the params
are colored before the late-born body vars. Dummy live-range tricks
not yet tried for boosting dst/m2 priority.

### Allocator intelligence (probes)

- agbcc's callee-saved preference is NOT a fixed order: 6-param probe
  gave r4,r8,r5,r9,r6,r7; 10-param probe gave r4,r5,r6,r8,r7+spills.
  It's graph coloring; node processing order (priority) varies.
- Consistent across -O1/-O2/-Os and main/old_agbcc for these shapes.

## 0x08007134 — RectFill variant (480 B) — BLOCKED, best v4 (426 diffs)

Staging: `staging/wave24_A/w24a_08007134_v2.c` (v2/v3/v4). v4: 500/480
bytes, 426 diffs. Loop body incomplete in v4 (placeholder).

ROM prologue: ctx->r5, b->r9, c->r7, d in r3, e->spill[0], mode->spill[4].
Pins deliver ctx_c->r5, b_c->r9, r8v->r8 correctly, but **c->r6, e->r7**
vs ROM **c->r7, e->spill** (swapped). Same selective-spill wall as 6AD8.

Full semantic decode (from ROM disassembly):
- Validates (d) like 6AD8 validates (c); mode in [sp,#4].
- If (s16)c < 0: r8 = (u8)(2 + c), c = 0.
- sl = (s16)c; if (sl + (s8)r8 >= (s8)FlagA_8628(ctx)) r8 = (u8)(flag - c);
  if ((s8)r8 <= 0) return.
- Pool (0x7314): 0x1FF; 0x081720FA/0x081720F4/0x0200481E.
  b = (b & 0x1FF) | *(u16*)(0x081720FA + ((e&3)<<2));
  w6 = *(u16*)(0x081720FC + ((e&3)<<2)); if (e & 48) w6 = *(u16*)(0x081720F4 + ((e&48)>>3)).
- dst = GetPtr_08008610(ctx) + (((s16)d << (s8)flag) << 1) + (sl << 1).
- Writes b and 0 to tilemap; loop with SetIfXZero calls (mode&1 / mode&2),
  dst+64 vs dst+128 selected by *(u8*)0x0200481E & 1.
- w23b's claim that it calls 0x08006AD8 is WRONG (no such bl in the
  disassembly; xrefs were incomplete).

## 0x080065BC — FillRect (416 B) — BLOCKED, not attempted

Prologue decoded (7 params: ctx,b,c,d,e,f,g):
```
mov r9,r0                ; ctx -> r9
lsls/lsrs r1,#24; str [sp,#0]  ; b -> spill
lsls/lsrs r2,#24; str [sp,#4]  ; c -> spill
lsls/lsrs r3,#24; mov sl,r3    ; d -> sl
lsls r0,#24; lsrs r7,r0,#24; str r7,[sp,#8]  ; e -> r7 + spill
lsls r4,#16; lsrs r6,r4,#16    ; f -> r6
lsls r5,#16; lsrs r5,r5,#16; str r5,[sp,#12] ; g -> r5 + spill
```
Note e and g have BOTH a register and a spill (like 6AD8's pa pattern).
Body not decoded; time-boxed on 6AD8/7134.

## 0x08006374 — FillRect outer (420 B) — BLOCKED, not attempted

Prologue decoded (8 params), near-identical structure to 0x080065BC:
ctx->r9, b/c/d->spill, (stack u8)->r6->sl, f/g->spill. Calls 0x080065BC
2x per w23b (not re-verified). Body not decoded.

## Recommendations

1. The pinned-COPY idiom (w12b) is the right tool for the hi-reg
   prologues — it deterministically delivers ctx/b/d/pa. The remaining
   work is purely the selective-spill heuristic.
2. Try boosting dst/m2 coloring priority (dummy live-range uses at
   function top, or `asm(""::"r"(dst))` keeps) to force c/e spills.
3. 0x08007134's simpler frame (16 B) may crack first; its c/e swap is
   the same wall in miniature.
4. 0x080065BC/0x08006374 share a prologue template — crack one,
   transfer to the other.

---

# Wave 24-A (parallel): 0x0804AF20 closer — MATCHED

Worker A (0x0804AF20 track), 2026-10-23. Appended alongside the rect-fill
notes above; separate target, separate staging (`staging/wave24_A/` shared
dir, `w24a_0804af20*` / `sed_0804af20*` files).

## MATCHED: 0x0804AF20 — InitRec28_4AF20 (112 B), main agbcc -O2 + sed

Zeroes a 28-byte record at p, then fills fields:
- `p[8]  = (u16)TblGetByte_24384(a)`   `p[10] = (u16)TblGetByte_24384(c)`
- `p[12] = Sub200_08024514((u8)b)`     `p[14] = Sub200_08024514((u8)d)`
- `p[20] = a`                          `p[22] = c`
(bytes 0–7, 16–19, 24–27 stay zero). Callees already matched:
Sub200_08024514 (v<=199?0:v-200), TblGetByte_24384 (u8 table lookup).

Verified: clean rebuild (.c → .s → sed → as → ld at 0x0804AF20 → objcopy)
`cmp` vs baserom = **0 diffs, 112/112 bytes**; disassembly identical;
section `.text.w24a_0804AF20` = 0x70 bytes, no pool. All artifacts non-empty
(.o/.elf/.bin/ROM extract asserted). Registry check: no MATCHED row for
0x0804af20 (3 BLOCKED rows only) — no duplicate.

### The critical correction: wave-23's store decode was WRONG
Wave-23 notes claimed `82a7 = strh r2,[r4,#20]` (p+20=b). Re-decode:
`0x82A7` → strh, imm5=10, Rn=r4, **Rd=r7** → `strh r7,[r4,#20]`, and r7=a.
So the tail is **p+20=a, p+22=c** (wave-22 p5's `=a` was right all along).
Root cause: wave-23 idiom #4 ("objdump prints imm5, no scaling confusion") is
**incorrect — objdump scales strh/ldrh immediates by 2** (imm5=10 displayed
as #20; GAS `[r4,#20]` assembles to imm5=10). That note's "false alarm"
conclusion was itself the false alarm; the scaling is real and the Rd field
was misread as r2 instead of r7.

With =a/=c the "impossible" register wall **vanishes**: b is dead after call 1
(`Sub200((u8)b)`), so b can stay in caller-saved r2 — no call-live pseudo in
a caller-saved reg needed. Allocation is fully consistent with gcc: p→r4
(whole fn), a→r7 (live calls 1–3, strh needs low reg), c→r6 (live calls 2–4),
d→r8 (live across call 1), b→r2 (dead after call 1).

### The loop-mat hoisting investigation (why sed was needed)
ROM loop materializes 0x10000 **in-loop** (`movs r5,#0x80; lsls r5,r5,#9`).
gcc 2.9-arm-000512 hoists it out of any call-free loop. Proven:
- t-idiom `i=(t=((u32)i<<16)+0x10000)>>16` gives ROM's exact
  lsls/movs128/lsls9/adds/lsrs shape (wave-22 idiom holds), but mat hoists.
- for / do-while / t-in-body / t-in-increment variants: all hoist.
- old_agbcc -O2/-O1/-Os, main -O1, noiw: all hoist (or break prologue).
- `-fno-loop-optimize`, `-fno-gcse`, `-fno-strength-reduce`,
  `-fno-rerun-cse-after-loop`, `-fno-rerun-loop-opt`, `-fno-thread-jumps`,
  `-fno-crossjumping`, `-fno-schedule-insns{,2}`, `-fno-unroll-loops`,
  `-fno-force-mem`, `-fno-if-conversion`: **all still hoist** (flags accepted —
  bogus `-fno-` names error, so they took effect; the motion is not from any
  optional pass).
- `-Os` keeps the mat in-loop but drops the r8 save (100 B, wrong prologue).
- Control experiment: the SAME t-idiom loop **with a call in the body keeps
  the mat in-loop** (mat reg r1/r2 gets call-clobbered, defeating the motion).
  Both previously matched in-loop-mat functions (w16b_08025754, w19d_08022868)
  have calls in their loops — consistent.
Conclusion: this gcc cannot emit the in-loop mat for a call-free loop at -O2
under any flag combination tried → sed fixup (precedent: wave-23 0x08002CB0).

### The .s transform (staging/wave24_A/sed_0804af20.sed)
Applied to main-agbcc -O2 output; 20 mechanical edits, byte-neutral (112 B):
- Prologue: `ldr r4,[sp,#24]` (d) first; extends a→r7, b→r2, c→r6, d→r4→r8;
  `mov r8,r4`; p→r4 moved last; q→r1, i=0, zero→r3.
- Loop: zero r2→r3; hoisted `mov r3,#128/lsl r3,#9` deleted; in-loop
  `mov r5,#128; lsl r5,r5,#9; add r0,r0,r5` inserted; `strb r3,[r1]`.
- Post-loop: b r5→r2; d r6→r8 via `mov r1,r8` (lsls can't take high reg);
  a r8→r7 (`adds r0,r7,#0`); c r7→r6; tail `strh r7,[r4,#20]` /
  `strh r6,[r4,#22]` (direct — strh can't take high regs, confirming a,c in
  low regs).
Verified two ways: Python transform (sed_0804af20.py) and the .sed script
produce identical .s; both assemble to 0-diff binaries (incl. clean-room
rebuild in build/verify/).

### Landing kit (coordinator)
- `staging/wave24_A/w24a_0804af20.c` — clean source, section
  `.text.w24a_0804AF20`, symbol `InitRec28_4AF20`.
- `staging/wave24_A/sed_0804af20.sed` — Makefile `sed -i -f` fixups
  (mirrors the w23a_08002cb0 inline-sed rule pattern).
- ldscript slot: 0x0804AF20, 112 B code, no pool (neighbors: coordinator to
  place — true extent verified 0x70).
- Registry: append MATCHED row for 0x0804af20 (checked — no existing MATCHED
  row; 3 BLOCKED rows remain as history).
- Did NOT write to match_status.tsv or mmbcc/src/ (coordinator lands).

## New idioms for catalog
1. **Re-decode strh/ldrh by hand when a wall depends on it**: objdump scales
   the imm5 by 2 for display (`#20` = field 10); always decode Rd/Rn/imm5 from
   the halfword yourself before concluding which variable is stored.
   (Corrects wave-23 idiom #4.)
2. **Call-free-loop invariant hoist is undefeatable in gcc 2.9-arm-000512**:
   no -O level or -fno-* flag keeps a constant materialization in-loop; only
   a call in the loop (clobbering the mat reg) does. When ROM shows in-loop
   mat in a call-free loop, go straight to sed — don't burn the flag matrix.
3. **Dead-after-first-call ⇒ caller-saved is fine**: a pseudo used once before
   any call can live in r0–r3 even if defined in the prologue; the "must be
   callee-saved" wall only applies to truly call-live pseudos. Re-examine the
   store decode before assuming the wall is real.

## Workdir (0x0804AF20 track)
- `staging/wave24_A/` (shared with rect-fill track): w24a.sh, w24a_opt.sh,
  w24a_noloop.sh, w24a_nogcse.sh, sed_0804af20.py, sed_0804af20.sed,
  w24a_0804af20.c (landing source), w24a_0804af20_p11.c / p12.c (probes),
  inc_test*.c (loop experiments), build/ (incl. build/verify/ clean-room),
  rom_ref.bin. Kept intact.
