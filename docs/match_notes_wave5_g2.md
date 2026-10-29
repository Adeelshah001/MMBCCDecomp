# Wave 5 Batch G2 — Match Notes (worker, 2026-10-20)

Batch POOL-G2: 16 functions (120–499 B). Result: **4 MATCHED, 5 BLOCKED,
7 NOT_ATTEMPTED** (time). Baserom SHA-1 verified
`72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place). Toolchain:
`mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc`, exact project build
rule. Verification: link `.o` section at ROM address (absolute
callees/data via trailing `__asm__` `.set`), `objcopy -O binary
--only-section`, byte-diff vs baserom. Scratch: `/tmp/wave5_g2/`
(`t*.c` probes, `build.sh`, `verify.py`, `dis_*.txt`).

All 4 matches use **main agbcc** (`-O2 -mthumb-interwork`). No
old_agbcc or no-interwork needed in this batch.

## MATCHED (4)

### Task_360C4 @ 0x080360c4 (200 B, 0 diffs)
Switch on `p[3]` (5 cases, JT). `push {r4,lr}`; Teardown; switch;
Setup; return 0.
- case0: `s=(s16)sub_08024514((u8)sub_080241F8(0x1000))`;
  `if ((u8)sub_0800B148(1,s,0)) p[3]++`.
- case1: `if ((u8)sub_0800B2D8()) if ((u8)sub_0800B320(0x0822EB44,0,0,0)) p[3]++`.
- case2: `if ((u8)sub_0800B308()) p[3]++;` falls through to case3.
- case3: `if ((u8)sub_0800B2B4()) p[3]++`.
- case4: `if ((u8)sub_0800B2F0()) { p[0x4699]=0; p[4]=0; p[3]=1; }`.
The `p[3]++` tails merge into a shared `ldrb/adds/b store` (case2's
store is inline due to fallthrough). First-try match.
C: `/tmp/wave5_g2/t360c4.c`.

### Task_40798 @ 0x08040798 (156 B, 0 diffs)
Seven `sub_08006A54` (Gfx_BlitRequest, wave2) calls:
`(ptr[i], 0x2f, 1/3/5/7/9/11/13, 8, 0)`. Pointers loaded via
`ldr r0,[pc]; ldr r0,[r0]` from ROM 0x082325E4, 0x082325EC, 0x082325F4,
0x082325FC, 0x08232604, 0x08232614, 0x0823261C. The 5th arg (0) goes on
the stack (`sub sp,#4; str r4,[sp]` with r4=0). Passing literal `0`
(not a `u32 zero` variable) reproduces ROM's `ldr;ldr;mov r4,#0;str`
scheduling. C: `/tmp/wave5_g2/t40798b.c`.

### Task_45200 @ 0x08045200 (156 B, 0 diffs)
Same shape as Task_40798 but arg1=1 (not 0x2f). Pointers from
0x08232C04, 0x08232C0C, 0x08232C14, 0x08232C1C, 0x08232C24, 0x08232C34,
0x08232C3C. C: `/tmp/wave5_g2/t45200.c`.

### Task_4529C @ 0x0804529c (156 B, 0 diffs)
Same shape as Task_40798 (arg1=0x2f). Pointers from 0x08232C04..
0x08232C3C (same table as Task_45200). C: `/tmp/wave5_g2/t4529c.c`.

## BLOCKED (5)

### Task_351D8 @ 0x080351d8 (314 B) — tail-merging divergence
Switch on `p[0x46A9]` (5 cases, JT). Prologue/dispatch/JT layout
matched (incl. agbcc's pool-holds-JT-base idiom). Blocker: ROM case2
has an **inline** `(u8)` check (`lsls r0,#24; cmp r0,#0; beq ret`)
then `ldr r2,[pc]; adds r1,r5,r2; b` to the shared increment;
case1 and case3 **share** the check at 0x80352a2. Both agbcc and
old_agbcc (at -O2 and -O1) tail-merge case2's check into the shared
one (`bl; b shared`). Tried: `if (x)`, `if (x==0) break;`, `if (x!=0)`,
explicit `goto` to a `check:` label, `u32 t` temporary — the merger
sees through all of them. 146 diffs, all downstream of the merge.
Best C: `/tmp/wave5_g2/t351d8c.c`.
Semantics (for recomp): case0 inits (sub_08004E44, sub_08004DFC,
sub_0800BEE0(0x40,0x80), sub_08005A9C(22), sub_08035A24(p),
p[0x46A9]++) then falls through to case1; case4 does
`gEwram02004E40[20]|=1` and a `(w&8)/(w&2)` branch setting
p[0x46A8]/p[0x46A9] + Text_SelectBlobIdx(0x67), ret=1.

### Task_37600 @ 0x08037600 (248 B) — register allocation
Bit-test state machine on `*(u16*)0x02002F50` / `*(u16*)0x02002F54`.
ROM: base in **r1**, value in **r4** (`ldr r1,[pc]; ldrh r4,[r1]`).
Both compilers put base in r4/r0 and value in r1/r3. Tried: `u8*`
base local, direct `*(u16*)0x02002F50`, separate decl/assign, decl
order swaps, `0x40 & v` operand swap, old_agbcc. The branchless
`(b&0x40)?0x40:0` via `negs; asrs #31; ands` IS reproduced (ternary),
but the r1/r4 allocation is not. 214 diffs.
Semantics (for recomp): computes r2 from flag bits (0x40→branchless,
0x80/1/2→branched); switch: 2→Text_SelectBlobIdx(0x68),ret=2;
1→0x67,ret=1; 0x40→if (s8)p[0x4698]>0 {0x66; p[0x4698]--};
0x80→if (s8)p[0x4699]<=1 {0x66; p[0x4698]++}; epilogue writes
`*(u16*)(0x02004CE0+40)=16` and `*(u16*)(0x02004CE0+42)=((s8)p[0x4698]<<4)+8`.
Best C: `/tmp/wave5_g2/t37600f.c`.

### Task_374B8 @ 0x080374b8 (194 B) — register allocation
Table-driven Gfx_BlitRequest/GatedDispatch sequence; uses r8 for the
0x0822EF0C pointer (reproduced: `mov r6,r8; push {r6}` prologue).
ROM: p in **r4**. Compiler puts p in **r5**. 112 diffs (old_agbcc;
119 with main). The r8 usage and call sequence are correct; only the
p register differs.
Semantics: `q=p+0x469F`; `sub_08006A54(*gRom0822FF4C[q[0]],2,1,10,2)`;
`sub_08006DD8(gRom0822FE60[q[0]*3],10,1,7,2)`; `sub_08006A54(*p8,17,1,1,2)`;
`sub_08006A54(*gRom0822FF58[q[0]],2,3,10,2)`;
`sub_08006DD8(gRom0822FE60[q[0]*3+1],10,3,7,2)`; `sub_08006A54(*p8,17,3,1,2)`;
`sub_08006A54(*gRom0822EF14,2,5,10,2)`; `sub_08006A54(*gRom0822EF04,2,7,16,2)`.
Best C: `/tmp/wave5_g2/t374b8.c`.

### Task_49A08 @ 0x08049a08 (148 B) — register allocation
Task init with bit-counting loop. ROM: p in **r3** (`adds r3,r0,#0`).
Compiler puts p in r2. 122 diffs.
Semantics: zeroes `*(u32*)(p+0x46A8)`, `*(u32*)(p+0x46AC)`, 8 words at
p+0x46B8; p[5..7]=0; for i=0..31: if (*(u32*)(p+24) & (1<<i)) {
p[0x46AA]++; p[0x46B8+idx]=i; idx++; }; if (p[0x46AA]>3) {
p[0x46AC]=0; p[0x46AD]=1; }; *(u32*)(p+4)=1; Teardown/Setup; return 0.
Best C: `/tmp/wave5_g2/t49a08.c`.

### Task_4C8EC @ 0x0804c8ec (200 B) — structural
Script-context init. Sets HW regs (0x04000084=0x8f, 0x04000080=0/0x77,
0x04000063 bytes), checks magic `*(0x03007FF0)==0x68736D53`, inits
EWRAM ctx at 0x0200CD80 with 9 ROM code pointers, calls
sub_0804DB28 (save), sets p[1]=1,p[28]=17,p[0x41]=2,p[0x5C]=0x22,
p[0x81]=3,p[0x9C]=0x44,p[0xC1]=4,p[0xDC]=0x88. 223 diffs; instruction
scheduling differs throughout. Best C: `/tmp/wave5_g2/t4c8ec.c`.

## NOT ATTEMPTED (7, time)
0x08036a14 (402 B, switch p[5]/6 cases), 0x08036dac (386 B),
0x08038ad4 (306 B, same family as blocked 0x08037600 but r1/r3/r4
variant — may be matchable with the r3 allocation), 0x08039058
(370 B), 0x0803aaa8 (412 B), 0x0803ac4c (238 B), 0x080493ec (364 B).

## New idioms / notes
- **agbcc JT layout confirmed by controlled test**: `ldr r1,.L11`
  loads the JT *base address* from a pool word (`.L11: .word .L9`),
  then `.L9: .word case0, ...` holds the entries. The pool word that
  looks like "JT[0]" is actually the table address, not a case.
- **Literal-0 stack arg**: passing literal `0` (not a `u32 zero`
  variable) for a stack-passed arg reproduces ROM's
  `ldr;ldr;mov r4,#0;str r4,[sp]` scheduling (Task_40798).
- **Branchless select**: `(b & 0x40) ? 0x40 : 0` compiles to
  `ldrh; and; lsl/lsr #16; negs; asrs #31; ands` (Task_37600) — a new
  codegen pattern for ternaries.
- **r8 save idiom**: `push {r4,r5,r6,lr}; mov r6,r8; push {r6}` —
  Thumb cannot push high regs directly; the compiler spills r8 via
  r6 (Task_374B8).

## Recomp-relevant discoveries
- Task_40798/45200/4529C: 7x Gfx_BlitRequest pattern with ROM pointer
  tables at 0x082325E4 and 0x08232C04 (7 entries, 8 bytes apart).
  The (0x2f vs 1) arg1 distinguishes two modes.
- Task_360C4: mode dispatch on p[3] with poll functions sub_0800B2D8/
  sub_0800B308/sub_0800B2B4/sub_0800B2F0 and ROM table 0x0822EB44.
- Task_37600: flag-bit state machine driving Text_SelectBlobIdx
  (0x66/0x67/0x68) and EWRAM 0x02004CE0 updates — likely UI cursor/
  selection logic.
- Task_4C8EC: script magic 0x68736D53 at *(0x03007FF0); EWRAM script
  ctx at 0x0200CD80 with 9 code pointers (0x0804D8A9, 0x0804C565,
  0x0804C579, 0x0804DA01, 0x0804C4FD, 0x0804CB29, 0x0804C289,
  0x0804CF0D, 0x0804CFD5).
