# Wave 3 batch 4 — worker D match notes (2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: main `agbcc` / `old_agbcc` at
`-O2 -mthumb-interwork`, exact per-function build rule from the task.
Verification: link each section at its ROM address (absolute `.set` symbols
resolve pools/bl targets), `objcopy -O binary --only-section`, byte-diff
vs ROM. All MATCHED functions below are full-section identical (code +
pads + pools), except `NullCallback` where only the 2 code bytes are ROM's
(the 2-byte gas nop pad must be stripped at landing).

Result: 14/15 MATCHED (13 compiled C + 1 asm-staged), 1 BLOCKED (0x0804DE64).

## New idioms discovered

1. **`noreturn` + inline-asm `b` for tail-jump fragments.** agbcc (both
   variants) never performs tail-call optimization: `return callee(...)`
   always emits `push {lr} / bl / pop {r1} / bx r1`. For a fragment ending
   in a direct `b` to another function (0x0804BE44 `Script_NextOp`), this
   works:
   ```c
   __attribute__((noreturn)) void F(u32 a, u8 *s) {
       u8 *p; u32 v;
       p = *(u8 **)(s + 0x40);
       *(u8 **)(s + 0x40) = p + 1;
       v = *p;
       __asm__ volatile ("b sub_0804BE2A" :: "r"(a), "r"(s), "r"(p), "r"(v));
   }
   ```
   The 10 code bytes reproduced exactly with zero register moves (r0=a,
   r1=s, r2=p, r3=v already in place), no push/pop. BUT gcc appends a
   2-byte safety `bx lr` after the asm even for noreturn, so the fragment
   was staged as file-scope `__asm__` (exact 10 B + 0000 pad) instead.
   Lesson: the probe proves semantics/codegen; staging may still need asm.
2. **Constant-first register allocation** (`OrU8_1F`@0x0800B6E8): ROM does
   `movs r1,#4` BEFORE `ldrb r2,[r0,#0x1F]`. `s[0x1F] |= 4` and
   `s[0x1F] = 4 | s[0x1F]` both allocate the loaded byte to r1 and the
   constant to r2 (swapped). `u8 v = 4; v |= s[0x1F]; s[0x1F] = v;`
   matches. Generalizes: when ROM materializes an immediate before the
   load, hoist the immediate into a named local first.
3. **Anti-folding for pool splits** (`EwramGet_02005238`@0x08011BC8):
   `*(u32 *)(gBase + 8)` with `extern u8 gBase[]` folds the +8 into the
   pool word (single `ldr r0,[r0]`); assigning `u8 *base = gBase;` first
   keeps ROM's two-step `ldr r0,[pc] / ldr r0,[r0,#8]` (same idiom as
   wave-2 `Gfx_BlitRequest`'s `u8 *ctx = gReqCtx`).
4. **Index-form preservation** (`GetS16_7C`@0x080174E4): ROM is
   `adds r0,#0x78 / movs r1,#4 / ldrsh r0,[r0,r1]`. Writing
   `*(s16 *)(s + 0x7C)` folds to `adds r0,#0x7C / mov r1,#0`. The
   `s16 *p = (s16 *)(s + 0x78); return p[2];` form matches — i.e. the
   source really indexes element [2] of an s16 array at +0x78.
5. **`.align 2,0` gap bytes are 00, not c046**: for pool-carrying
   functions the compiler-emitted `.align 2,0` before the literal pool
   fills with zeros, so sections like `.text.w3d_ewramget` (6 code +
   00 00 + pool) are fully byte-exact with no sPad needed. Only
   section-END gaps need the `static const u8 sPad[2] = {0,0}` idiom
   (wave-2 note 4; used here for `OrU8_1F`, `SetU32_200`).

## BLOCKED — `DivZeroStub`@0x0804DE64 (name tentative)

ROM (10 B):
```
push {lr}          00b5
bl 0x0804DD9C      fff7 99ff
movs r0,#0         0020
pop {pc}           00bd
```
Semantics: call the 1-insn empty stub at 0x0804DD9C (`mov pc,lr`),
return 0. Context: it is the divide-by-zero exit of the division routine
at 0x0804DDA0 (`cmp r1,#0; beq 0x0804DE64` before any stack push, so the
jump is stack-balanced). A twin wrapper with identical bytes exists at
0x0804DD90 (calls the same stub, returns 0).

Best C (`u32 F(void){ sub_0804DD9C(); return 0; }`, extern void callee):
both `agbcc` and `old_agbcc` at -O2 -mthumb-interwork emit
`pop {r1}; bx r1` instead of `pop {pc}` — 9/10 bytes match, last 2 bytes
(`00bd` vs `01bc 0847`) diverge, and the replacement is 2 bytes longer
so everything downstream shifts. Variants tried: arg-carrying wrapper,
`u32 r = 0;` temp, nested-block return — all identical epilogue.

Decisive experiment: compiling the SAME probe WITHOUT `-mthumb-interwork`
emits `pop {pc}` exactly. So the ROM's epilogue comes from a non-interwork
compilation unit. Corroboration that the whole 0x0804DD90–0x0804DE6E
region is hand-written asm (or a foreign TU), not game C code:
- 0x0804DD9C is `mov pc,lr` — agbcc emits `bx lr` for empty Thumb
  functions (proven: `NullCallback`@0x08005208 needed C `void f(void){}`
  and got `bx lr`).
- `pop {pc}` epilogues (0x0804DD90, 0x0804DE64) — never emitted by agbcc
  under the project build flags.
Recommendation: match this region as a `.s` file (libgcc-style division
helpers: `__divsi3`/`__modsi3` family + div-zero stubs), not C. Do not
spend more C variants on it.

## Recomp-relevant discovery: script bytecode interpreter (~0x0804BE10)

The 0x0804BE44 fragment belongs to a bytecode/script engine:
- Dispatch: `subs r1,#1; bgt ...; bx ip` computed jump at 0x0804BE20–24.
- `Script_NextOp`@0x0804BE44: fetch next opcode byte, advance the script
  pointer at `[r1+0x40]`, then validate the pointer.
- `sub_0804BE2A` (validator, entered at 0x0804BE28 with a pre-load
  `ldrb r3,[r2]`): zeroes the opcode (r3) unless
  `0x08105CC8 <= r2 < 0x02000000` — i.e. the script pointer must stay
  inside a ROM window. Pool word `0x08105CC8` at 0x0804BE40.
- `sub_0804BE50`: reads a 4-byte big-endian-ish u32 from the script
  (`[r2+3],[r2+2],[r2+1],[r2]` via the 0x0804BE28 entry), validates,
  stores back to `[r1+0x40]`.
- `sub_0804BE70`: gosub — pushes `[r1+0x40]+4` onto a return stack at
  `[r1+0x44 + depth*4]`, depth byte at `[r1+2]` (cap 3), jumps to
  0x0804BE50.
- `sub_0804BE8C`: return — pops the stack back into `[r1+0x40]`.
Engine state struct (r1): +0x02 u8 call depth, +0x40 u32 script pointer,
+0x44 u32 return stack[3]. The interpreter reads scripts from ROM and
sanity-checks every pointer — the recomp must preserve this validation
behavior (a bad script pointer yields opcode 0, not a crash).

## Other notes for the coordinator

- `GetS16_7C`/`IncU8_12` (0x080174E4/0x08017458) belong to the
  0x0801745x/0x080174Ex accessor family wave-3C already saw
  (`IncU8_11`/`GetS16_78_3`): byte/s16 getters/setters on one struct.
- `TableU32_0820B6A4`@0x08011CC4: u32 table in ROM at 0x0820B6A4 indexed
  by u16 (callers at 0x0801192A, 0x08011CE2 — one is the next function
  at 0x08011CD4, suggesting a paired accessor).
- `EwramInit_02005260`@0x08011C04 writes a 3-dword EWRAM record
  (v, v, v+0x10) at 0x02005260; sole caller 0x080267F8 zeroes neighboring
  EWRAM bytes first — looks like UI/window record init.
- ldscript lines needed (coordinator integrates; do NOT add pads except
  where the section already carries them):
```
. = 0x08005208; .text.w3d_noop : { build/wave3_d.o (.text.w3d_noop); } /* strip 2 B pad: next fn at 0x0800520A */
. = 0x080257F8; .text.w3d_getu16_10 : { build/wave3_d.o (.text.w3d_getu16_10); }
. = 0x08023E30; .text.w3d_getu32_38 : { build/wave3_d.o (.text.w3d_getu32_38); }
. = 0x08026550; .text.w3d_getu8_19 : { build/wave3_d.o (.text.w3d_getu8_19); }
. = 0x08011BC8; .text.w3d_ewramget : { build/wave3_d.o (.text.w3d_ewramget); }
. = 0x08026DB0; .text.w3d_ewramset : { build/wave3_d.o (.text.w3d_ewramset); }
. = 0x08017458; .text.w3d_incu8_12 : { build/wave3_d.o (.text.w3d_incu8_12); }
. = 0x080174E4; .text.w3d_gets16_7c : { build/wave3_d.o (.text.w3d_gets16_7c); }
. = 0x0800EA08; .text.w3d_ewramset2 : { build/wave3_d.o (.text.w3d_ewramset2); }
. = 0x0800B6E8; .text.w3d_oru8_1f : { build/wave3_d.o (.text.w3d_oru8_1f); }
. = 0x08004158; .text.w3d_setu32_200 : { build/wave3_d.o (.text.w3d_setu32_200); }
. = 0x0804BE44; .text.w3d_script_nextop : { build/wave3_d.o (.text.w3d_script_nextop); }
. = 0x08011CC4; .text.w3d_tblu32 : { build/wave3_d.o (.text.w3d_tblu32); }
. = 0x08011C04; .text.w3d_ewraminit : { build/wave3_d.o (.text.w3d_ewraminit); }
```
- Absolute symbols newly introduced by wave3_d.c (keep the end-of-file
  `.set` block until each is matched for real): gEwram02005230,
  gEwram020070F0, gEwram02005130, gTbl0820B6A4, gEwram02005260,
  sub_0804BE2A. Check against existing `.set`s for duplicates at
  integrate time (gTbl0820B6A4 / the EWRAM bases may already exist).
- Scratch (probes, build/verify scripts, per-variant .s): /tmp/wave3_d/
  (ephemeral; key variants documented above).
