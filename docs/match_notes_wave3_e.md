# Wave 3 batch 5 worker E notes (2026-10-20)

Worker: matching-C, batch5 (15 leaf functions).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place,
never copied). Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc`.
Build rule (exact): `cpp -I mmbcc/include <src>.c -o <x>.i && agbcc -O2
-mthumb-interwork -Wimplicit -Wparentheses -o <x>.s <x>.i &&
arm-none-eabi-as -mthumb -mcpu=arm7tdmi -o <x>.o <x>.s`.
Verification: compiled staged `mmbcc/src/wave3_e.c` under each of 3 flag sets,
linked each section at its ROM address against 2-byte Thumb stubs at the real
callee addresses (`.thumb; bx lr`), then `objcopy -O binary --only-section`
and byte-diff vs ROM. Scratch: `/tmp/wave3_e/` (`build.sh`, `verify.py`,
probes `p*.c`).

Result: **15 MATCHED, 0 BLOCKED.** Three flag sets needed (see below) —
coordinator must split `wave3_e.c` or use per-file overrides (precedent:
Text_SelectBlob/old_agbcc).

## Matched (15)

All staged in `mmbcc/src/wave3_e.c`, one `.text.w3e_<name>` section per
function. Absolute symbols in trailing `__asm__` `.set` block (GAS 2.42
rule: .set AFTER code). EntryMgr_Teardown is extern-only (already matched in
src/entrymgr.c — no .set, no duplicate symbol).

| Addr | Name (tentative) | Bytes | Compiler | Semantics |
|------|------------------|-------|----------|-----------|
| 0x08000A18 | EmptyStub_0A18 | 2 | agbcc | `void f(void){}` → `bx lr` |
| 0x08025A08 | GetByte1_25A08 | 4 | agbcc | `return p[1];` |
| 0x0804005C | ConstZero_4005C | 4 | agbcc | `return 0;` |
| 0x08011C50 | GetLimit_11C50 | 4+4pool | agbcc | `return 0x4867;` pool-loaded; caller (sub_08011C80) cmps u16 idx >= retval |
| 0x0802472C | ConstZeroS16_2472C | 6 | **old_agbcc** | `if ((u32)a<<24) return 0; return 0;` → `lsls r0,#24; movs r0,#0; bx lr`; callers sign-extend (s16) |
| 0x080030BC | StoreTwoHalves_030BC | 6 | agbcc | `p[4]=a; p[5]=b;` (u16) |
| 0x080361DC | TeardownWrap_361DC | 8 | agbcc | `EntryMgr_Teardown();` — push/bl/pop{r0}/bx r0 shape, bl verified vs stub at 0x08004F18 |
| 0x080174CC | SetXY_174CC | 8 | agbcc | `o+=0x78; *(u16*)(o+4)=x; *(u16*)(o+6)=y;` (struct+0x7C/0x7E) |
| 0x0801007C | WriteEwramHalf_1007C | 8+4pool | agbcc | `*(u16*)(0x02005160+0x46)=v`; base-in-u32-local idiom |
| 0x0804DEDE | DivZeroStub_4DEDE | 8 | **agbcc, NO -mthumb-interwork** | `sub_0804DD9C(); return 0;` epilogue `pop {pc}`; div-by-zero path of sub_0804DE70 |
| 0x08004164 | SetField204_04164 | 10 | agbcc | `*(u32*)(p+0x204)=v`; 0x204 via `movs r2,#0x81; lsls r2,#2` |
| 0x08003090 | InitTriple_03090 | 10+2pad+4pool | agbcc | `p[0]=a; p[1]=0x0816E2CC; p[2]=c;` (r2 unused) |
| 0x080267B4 | InitRec8_267B4 | 12 | agbcc | 8-byte record: `w0=0x13, b1=kind, w4=0`; explicit `u32 v` temp |
| 0x08024734 | TableGet_24734 | 12+4pool | agbcc | `return gTbl_0822D69C[i];` pool load scheduled between the shifts |
| 0x08028874 | SetPairZero_28874 | 12 | agbcc | `p[0]=(u8)v; p[1]=0;` |

Flag sets per section (coordinator: split wave3_e.c into 3 TUs or per-file
override):
- 13 sections: `agbcc -O2 -mthumb-interwork` (standard)
- `.text.w3e_zero16_2472c`: `old_agbcc -O2 -mthumb-interwork`
- `.text.w3e_divzero_4dede`: `agbcc -O2` **without** `-mthumb-interwork`

## Hard-won matches

### 0x0802472C — dead shift kept only by old_agbcc (15+ probes)
ROM: `lsls r0,r0,#24; movs r0,#0; bx lr` (6 B). ~15 source shapes tried with
agbcc (plain `a<<=24`, comma ops, do-while(0), switch-default, goto-label,
explicit-register asm vars, ternaries): agbcc's DCE deletes the shift in
every shape, or keeps it only with stack junk (`if ((a<<24)==0)...` →
`push{lr}; lsls; movs; pop{r1}; bx r1`). old_agbcc with
`if ((u32)a << 24) return 0; return 0;` emits exactly the ROM bytes. So
old_agbcc is not only a scheduler difference — its DCE keeps a shift feeding
a folded branch where agbcc deletes it. (Callers at 0x7DE8/0x7E9C/0x99FC/
0x9C7C use the result as s16, hence the s16 return type.)

### 0x0804DEDE — no-interwork TU (`pop {pc}` epilogue)
ROM: `push{lr}; bl 0x0804DD9C; movs r0,#0; pop{pc}` (8 B). Both agbcc and
old_agbcc **with** `-mthumb-interwork` emit `pop {r1}; bx r1`. Omitting
`-mthumb-interwork` (plain `agbcc -O2`) emits exactly `pop {pc}`. This is a
div-by-zero stub: sub_0804DE70 (custom divmod routine) does `beq 0x0804DEDE`
when the divisor (r1) is 0. No matched object in the project previously
exhibited `pop {pc}` — likely a libgcc-style TU compiled without interwork.
**ldscript caveat:** 0x0804DEDE is 2-aligned but agbcc marks the section
4-aligned (`.align 2,0`), so plain `. = 0x0804DEDE;` lets ld slide the
function to 0x0804DEE0 (verified). Use explicit address + SUBALIGN:
`.text.w3e_divzero_4dede 0x0804DEDE : SUBALIGN(2) { build/wave3_e_noiw.o
(.text.w3e_divzero_4dede); }` — verified byte-identical.

### 0x0801007C — base-in-u32-local anti-folding (confirms worker A's idiom)
ROM: `ldr r1,[pc,#4]` (pool=0x02005160); `adds r1,#0x46`; `strh r0,[r1]`.
`*(u16 *)(0x02005160 + 0x46) = v;` folds to a single pool word 0x020051A6
(6 B, wrong). `u32 base = (u32)gEwram5160; *(u16 *)(base + 0x46) = v;`
(with `gEwram5160` extern + `.set 0x02005160`) gives the exact ROM shape.
Same idiom worker A found for 0x0800EDE4 — EWRAM base+offset stores are
written base-in-local in the original source.

### 0x080267B4 — explicit temp pins the zero to r2
ROM: `movs r2,#0x13; str r2,[r0]; movs r2,#0; strb r1,[r0,#1]; str r2,[r0,#4]`.
Naive `*(u32*)p=0x13; p[1]=kind; *(u32*)(p+4)=0;` puts the zero in r1
(`movs r1,#0` after the strb). With `u32 v = 0x13; ...; v = 0;` the compiler
keeps v in r2 throughout → exact match.

## New idioms discovered
- **old_agbcc DCE keeps shift-into-folded-branch** where agbcc deletes it
  (0x0802472C). Probe old_agbcc when a kept-but-unused computation blocks.
- **No-interwork epilogue**: omitting `-mthumb-interwork` gives `pop {pc}`;
  with it, `pop {rX}; bx rX`. First observed case (div-zero stub).
- **SUBALIGN(2) for 2-aligned functions**: agbcc's `.align 2,0` makes
  sections 4-aligned; ld slides them up at 2-aligned `. =` placements.
  Explicit section address + `SUBALIGN(2)` pins them (verified).
- Pool-align padding inside a section is `0000` (agbcc `.align 2,0`),
  matching ROM; only trailing section pads are `46c0` (strip).

## Recomp-relevant discoveries
- **Struct-init family at sub_08005434**: calls InitTriple_03090,
  StoreTwoHalves_030BC, and SetField204_04164 back-to-back — one
  constructor-ish routine initializing a struct with a ROM-pointer field
  (0x0816E2CC → `{0,0,0x08000400,0x20001000,...}`), two halfwords at +8/+0xA,
  and a word at +0x204.
- **0x174xx accessor family**: SetXY_174CC writes s16 pair at struct+0x7C/
  0x7E; siblings at 0x174D4/0x174DC/0x174E4/0x174EC read s16 at
  +0x78/+0x7A/+0x7C/+0x7E — looks like an object/sprite attribute block
  (position-ish fields). Useful for the title-screen glitch work (batch4
  owns 0x17458/0x174C4/0x174E4).
- **TableGet_24734** indexes a ROM pointer table at 0x0822D69C whose
  entries are 0x080Fxxxx code pointers (likely a dispatch/vector table).
- **InitRec8_267B4** (19 bl-callers) inits 8-byte records with magic 0x13
  + kind byte — a common record allocator/initializer across gameplay code.
- **GetLimit_11C50** returns constant 0x4867 used as a u16 capacity bound.

## Blockers
None — 15/15 MATCHED.

## ldscript lines needed (coordinator)
```
. = 0x08000A18; .text.w3e_empty_0a18      : { build/wave3_e.o (.text.w3e_empty_0a18); }
. = 0x08025A08; .text.w3e_getbyte1_25a08  : { build/wave3_e.o (.text.w3e_getbyte1_25a08); }
. = 0x0804005C; .text.w3e_constzero_4005c  : { build/wave3_e.o (.text.w3e_constzero_4005c); }
. = 0x08011C50; .text.w3e_getlimit_11c50   : { build/wave3_e.o (.text.w3e_getlimit_11c50); }
. = 0x0802472C; .text.w3e_zero16_2472c    : { build/wave3_e_old.o (.text.w3e_zero16_2472c); }
. = 0x080030BC; .text.w3e_store2h_030bc   : { build/wave3_e.o (.text.w3e_store2h_030bc); }
. = 0x080361DC; .text.w3e_teardownwrap_361dc : { build/wave3_e.o (.text.w3e_teardownwrap_361dc); }
. = 0x080174CC; .text.w3e_setxy_174cc     : { build/wave3_e.o (.text.w3e_setxy_174cc); }
. = 0x0801007C; .text.w3e_ewramh_1007c    : { build/wave3_e.o (.text.w3e_ewramh_1007c); }
.text.w3e_divzero_4dede 0x0804DEDE : SUBALIGN(2) { build/wave3_e_noiw.o (.text.w3e_divzero_4dede); }
. = 0x08004164; .text.w3e_setf204_04164   : { build/wave3_e.o (.text.w3e_setf204_04164); }
. = 0x08003090; .text.w3e_inittri_03090   : { build/wave3_e.o (.text.w3e_inittri_03090); }
. = 0x080267B4; .text.w3e_initrec8_267b4  : { build/wave3_e.o (.text.w3e_initrec8_267b4); }
. = 0x08024734; .text.w3e_tableget_24734  : { build/wave3_e.o (.text.w3e_tableget_24734); }
. = 0x08028874; .text.w3e_setpair0_28874  : { build/wave3_e.o (.text.w3e_setpair0_28874); }
```
Suggested split: `wave3_e.c` (13, standard flags) minus the two special
functions; `wave3_e_old.c` = ConstZeroS16_2472C (old_agbcc);
`wave3_e_noiw.c` = DivZeroStub_4DEDE (agbcc, no `-mthumb-interwork`).
Trailing-pad strip (gas `46c0` vs ROM `0000`) needed after: empty_0a18 (2B),
zero16_2472c (2B), store2h_030bc (2B), setf204_04164 (2B). The
inittri_03090 inter-pool pad is `0000` (matches ROM). EntryMgr_Teardown
resolves from entrymgr.c at final link (no stub needed); sub_0804DD9C,
gEwram5160, gTbl_0822D69C come from this TU's trailing .set block.

## Unfinished
Nothing in batch5 remains. The staged file compiles warning-free under all
three flag sets. Coordinator owns: Makefile/ldscript/match_status.tsv/
PROGRESS.md integration (not touched per instructions).
