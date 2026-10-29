# MainLoop @0x080004FC — matching notes (BLOCKED)

Date: 2026-10-20. Worker: Phase-3 Wave-1.

## Bounds
- Start `0x080004FC`, next function `0x08000624` → 296 bytes (0x128).
- Section `.text.mainloop` in `mmbcc/src/mainloop.c` (stub still in place).

## ROM disassembly summary (all 20 bl callees confirmed)
Prologue saves r4-r7, r8, r9, sl, lr. Five long-lived locals:
- r9 = incoming r0 (passed to `sub_08000E04(arg, 1)` at frame end)
- r8 = `0x02000ED0` (EWRAM base, pool word @0x080005FC)
- sl = r8 + 0x2000 = `0x02002ED0` (computed once pre-loop)
- r7 = `0x03000565` (pool), r6 = r7-1 = `0x03000564` (frame-sync flag bytes)

Loop body (`0x08000518`–`0x080005FA`, `b` back to `0x08000518`):
1. `bl sub_0804A450`, `bl sub_08004624`, `bl sub_08002A1C`
2. Toggle: `*(u16*)(r8+0x2202) = (*(u16*)(r8+0x2202) == 0)` —
   `movs r2,#0; ldr r1,=0x2202; add r1,r8; ldrh r0,[r1]; cmp r0,#0;
   bne +2; movs r2,#1; movs r0,#0; strh r2,[r1]` (address recomputed EACH frame)
3. `*(u16*)sl = 0` — `mov r3,sl; strh r0,[r3]` (r0=0 shared from step 2)
4. `bl sub_08001D98`
5. VBlank wait:
   - `while (*(u8*)0x03000564 < *(u8*)0x03000565);` (two ldrb, `bcc`)
   - `if (*(vu16*)0x04000006 != 161) goto wait;` (VCOUNT)
   - `*(u8*)0x03000564 &= 0;` — emits dead `ldrb r0,[r6]` then
     `movs r0,#0; strb r0,[r6]` (compiler folded `ands r0,#0` → `movs r0,#0`)
6. `bl sub_0800105C`, `bl sub_08001C88`, `bl sub_080046B0`, `bl sub_080050F0`
7. `*(vu16*)0x04000000 &= 0xFF7F;` (DISPCNT, clears OBJWIN bit15) —
   `movs r2,#128; lsls r2,#19; ldrh r0,[r2]; ldr r3,=0xFF7F;
   adds r1,r3,#0; ands r0,r1; strh r0,[r2]`
8. `bl sub_080026E4/2D20/2DCC/2E50/2E80/2EE0/21FC/08C0`
9. Keypad combo (all-fail → skip to step 10):
   - `*(u8*)0x02002F80 == 0`
   - `(((u16*)0x02002EE0)[1] & 1) == 0` — note `[r0,#2]` addressing, pool has `0x02002EE0`
   - r5 = `0x02002F50` (pointer kept in r5); key1=`[r5]`:
     `(key1&12)==12 && (key1&1) && (key1&2)`
   - key2=`[r5,#4]`; `(key2&12) || (key2&1) || (key2&2)`
   - Masks materialized once and reused via `adds r0,r3,#0` copies
     (r3=1, r2=12, r4=2) — old-GCC constant-reuse quirk
   - Then: `sub_08000E64(1); sub_08000D90(1, 0x08000419); sub_080267F8(0x020070F0);`
10. `sub_08000E04(r9, 1)`; `b frame_top`

Pool (10 words @0x080005FC): `02000ED0 03000565 00022002 04000006
0000FF7F 02002F80 02002EE0 02002F50 08000419 020070F0`.

## What was tried (≈30 variants)
- Plain `-O2 -mthumb-interwork`: constant base `0x02000ED0` gets fully
  constant-propagated (frameState/toggle become pool words `02002ED0`/`02022ED2`);
  base disappears; arg→r8. Wrong.
- `-O1`: worse (464B, different idioms). `-O3`: same as `-O2`. `-Os`: worse.
- `-fno-gcse`, `-fno-cse-follow-jumps`, `-fno-rerun-cse-after-loop`,
  `-fno-expensive-optimizations`, `-fno-schedule-insns`, `-fno-force-mem`,
  `-fregmove`, `-foptimize-register-move`: no change to the hoisting.
- Inline `(base + 0x2000)` / `(base + 0x2202)` (no named offset vars):
  base stays runtime in a reg, BUT the compiler hoists `base+0x2202`
  (pool `ldr`+`add`) and computes `base+0x2000` in-loop — exactly backwards.
- Named `u16 *frameState = base+0x2000` (any position, init or assignment,
  inside or outside loop): triggers FULL constant folding of base when base
  is a literal; when base is extern, both addresses hoist and base dies.
- Extern absolute symbol for base (`.set gEwram0ED0, 0x02000ED0`):
  prevents folding, base stays runtime — but hoisting still backwards,
  and register allocation shifts (arg→r8/r7, base→r6, etc.).
- `register __asm__("sl")` / `__asm__("r8")`: forces regs but changes
  codegen shape (`mov r3,r8; add r1,r3,r4` instead of `add r1,r8`).
- Struct-based EWRAM access: different (worse) allocation.
- Statement reorder (clear-before-toggle), if/else toggle, named temp for
  toggle, `u16 z=0` variable, comma-operator keypad, nested-if keypad:
  none flip the hoisting decision.

## Root cause (blocker)
agbcc `-O2` LICM/CSE **always hoists `base+0x2202` (the RMW address) and
never `base+0x2000`**, in every source variation tested. The ROM does the
opposite: `sl = base+0x2000` hoisted pre-loop (`movs r1,#128; lsls r1,#6;
add r1,r8; mov sl,r1`), `base+0x2202` recomputed each frame
(`ldr r1,=0x2202; add r1,r8`). Because the hoisted address feeds `sl`
(3rd high reg saved), the whole prologue register allocation diverges
(ROM: `mov r7,sl; mov r6,r9; mov r5,r8; push {r5,r6,r7}; mov r9,r0`;
best attempt: only r8/r9 saved, arg→r8). Cascade makes byte-match
impossible without the exact original source idiom, which was not found.

Secondary: `-mthumb-interwork` makes the *linker* emit `bx pc` veneers
(`__sub_XXXXXXXX_from_thumb`) for absolute callee symbols; test harness
worked around with `.thumb_func`+odd-address syms. Real build will need
the callees defined as Thumb somewhere (other workers' files) or the same
treatment — flagging for the coordinator, not changing the Makefile.

## Precise remaining diff (best attempt try7 vs ROM, first 64 bytes)
- `0x080004FC`: mine `f0b5 4f46 4646 c0b4 8146 3b48 8046 3b4f ...`
  (saves r8/r9 only; `ldr r5,=0x2202; add r5,r8` hoisted)
  vs ROM `f0b5 5746 4e46 4546 e0b4 8146 3c48 8046 ...`
  (saves sl/r9/r8; `movs r1,#128; lsls r1,#6; add r1,r8; mov sl,r1`)
- Length: mine 292B vs ROM 296B (pool has 9 words vs 10; missing `00022002`
  placement differs).
- Everything downstream of the prologue diverges in register allocation
  (r5 vs r1 for toggle addr, r1 vs r2 for boolean, etc.) although the
  *logic* (dispatch order, VBlank wait, keypad chain, DISPCNT idiom) was
  reproduced structurally.

## Verdict
**BLOCKED** — prologue LICM hoisting decision not reproducible with
agbcc `-O2` across ~30 source/flag variants. The dispatch body, VBlank
wait, and keypad logic are structurally mapped (see above) and ready for
whoever cracks the prologue idiom (likely an unusual source form for the
`0x02000ED0`-based addresses, e.g. a particular extern/struct/ordering the
original used).

## Frame-driver behavior notes (for recomp track)
- Frame pacing: spin on `IWRAM[0x03000564] < IWRAM[0x03000565]`
  (VBlank ISR presumably bumps the high byte), then require `VCOUNT==161`,
  then clear the low byte. A recompiler can treat this as "wait for VBlank".
- Per-frame EWRAM toggles: `u16 @0x02022ED2` flips 0/1 each frame;
  `u16 @0x02002ED0` cleared each frame. Unknown consumers (not in this fn).
- `DISPCNT &= 0xFF7F` every frame (OBJWIN off).
- Keypad combo on EWRAM mirrors `@0x02002F50/54` (bits 0,1 + bits 2,3 as a
  pair) re-registers task #1 (`Task_Register(1, 0x08000419)`) — likely a
  debug/reset combo; guarded by `*(u8*)0x02002F80==0` and
  `!(((u16*)0x02002EE0)[1] & 1)`.
- 20 `bl` callees/frame, all no-arg except `sub_08000E64(1)`,
  `sub_08000D90(1, 0x08000419)`, `sub_080267F8(0x020070F0)`,
  `sub_08000E04(arg, 1)`. No `bl` callers — entered via task table.
- `make` untouched (stub still builds green); `src/mainloop.c` NOT modified.
