# Wave 5 Batch POOL-H2 — Match Notes (2026-10-20)

Worker: matching-C, batch POOL-H2 (30 functions, 40–119 B).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place,
never copied). Toolchain: main `agbcc` / `old_agbcc` at `-O2 -mthumb-interwork`,
exact per-function build rule from the task.
Verification: link each `.o` section at its ROM address (2-byte Thumb stubs at
callee addresses via linker script), `objcopy -O binary --only-section`,
byte-diff vs ROM. Scratch: `/tmp/wave5_h2/` (probes `p_*.c`, `best_*.c`,
`final_*.c` = staged source as compiled).

Result: **13 MATCHED, 6 BLOCKED, 11 NOT_ATTEMPTED.**

## Matched (13)

All staged C in `/tmp/wave5_h2/final_*.c` (coordinator lands into `mmbcc/src/`).
Absolute symbols in trailing `__asm__` `.set` block (GAS 2.42 rule: .set AFTER
code). Callee externs resolve to stubs at verify time; at final link they
resolve to real definitions (or remain `.set` until matched).

| Addr | Name | Bytes | Compiler | Semantics |
|------|------|-------|----------|-----------|
| 0x08035128 | Task_35128 | 72 | old_agbcc | `tbl[p[0x46a8]]` poll via sub_0804dcd0; if (s8)r!=0: p[4]=3,p[5]=0; if p[0x46a8]==3: p[0x46b7]=3, return 1. |
| 0x08035bc8 | Task_35BC8 | 84 | agbcc | s8 v=p[0x46aa]; if v>12: v-=13, flag=1; p[0x46a9]=3; Text_SelectBlobIdx(0x66); EW[0x28]=(v<<4)+0x10; EW[0x2a]=flag*24+0x20. |
| 0x08035c1c | Task_35C1C | 64 | agbcc | 3x GatedDispatch(base[0x13],0x2f,4,2,0) / (base[0x12],0x32,4,2,0) / (base[0x11],0x35,4,2,0). |
| 0x08035da4 | Task_35DA4 | 80 | agbcc | Sibling of 35BC8: v>3 ? v-=4; EW=(v<<4)+0xf8. |
| 0x080366e8 | Task_366E8 | 68 | old_agbcc | s8-indexed table poll; if (s8)r!=0: p[1]=3,p[2]=p[3]=0. |
| 0x08037598 | Task_37598 | 48 | agbcc | GatedDispatch(*(p+0x20),0x14,1,7,2); Gfx_BlitRequest(*0x0822EF0C,0x1b,1,1,2). |
| 0x08037a30 | Task_37A30 | 76 | old_agbcc | (u8)poll switch: r==1→p[1]=3, r==2→p[1]=4, p[2]=p[3]=0. |
| 0x08037ad8 | Task_37AD8 | 116 | agbcc | Mode dispatcher: v==4→p[1]=2; v==9→InitRec8+ p[0x4698]=0; v==8→InitRec8+p[0x4698]=5; else p[1]=1; Teardown/Setup. |
| 0x08038f3c | Task_38F3C | 76 | old_agbcc | Sibling of 37A30 (p[2] before p[3]). |
| 0x08038fe4 | Task_38FE4 | 116 | agbcc | Sibling of 37AD8 (v==7/0xb/0xc; p[0x4698]=4). |
| 0x08045ebc | Task_45EBC | 64 | agbcc | Zero *(p+0x46a8/0x46ac), *(p+4)=1, p[0x46ae]=0, p[0x46af]=1; Teardown/Setup; return 0. |
| 0x0804827c | Task_4827C | 64 | agbcc | Zero *(p+0x46a4/0x46a8), p[2]=1,p[3]=0, p[0x46a4/0x46a5/0x46a6]=0; Teardown/Setup. |
| 0x080496a8 | SramInit_496A8 | 64 | agbcc | SRAM: sub_0804db24(buf,base+0x10,0x010000d8); sub_0804db28(buf+1,base+0x370,0x05000003); *(base+0x20)=0x3e8. |

### Key idioms used

1. **Table base loaded first** (0x08035128, 0x080366e8): declare `u32 *tbl = gRom_X;`
   before the index computation to get `ldr r1,[pc]` (base) before `ldr r0,[pc]`
   (offset). old_agbcc needed for the `ldrb r2` / `lsls r0,r2,#2` allocation.

2. **Literal-0 CSE for r4/r5** (0x08035c1c): use literal `0` in the calls (not
   `u32 z=0`) — the compiler CSEs it into r4 while the pointer goes to r5,
   matching ROM. A named `u32 z` swaps them.

3. **`u32 z=0` inside if-branch** (0x080366e8, 0x08037a30): materializes
   `movs r1,#0` BEFORE `movs r0,#3`, matching ROM's constant order.

4. **Goto-beq for branch structure** (0x08037a30, 0x08038f3c): `if (r==1) goto L1;
   if (r==2) goto L2;` generates ROM's `cmp/beq` (not compiler's `bne`).

5. **Store order p[3] before p[2]** (0x08037a30): ROM stores p[3] then p[2];
   write them in that order in C.

6. **`u32 off` variable for runtime subtract** (0x0804827c): `u32 off=0x46a8;
   p[off-2]=0` gives `subs r4,#2` (not folded to 0x46a6).

7. **Zero declared before pointer** (0x080496a8): `u32 z=0; u8 *p10=base+0x10;`
   gives `movs r4,#0` before `adds r1` (ROM order).

8. **`(0xdc<<2)` for shift-materialized constants** (0x080496a8): `base+(0xdc<<2)`
   gives `movs r2,#0xdc; lsls r2,#2` (not pooled 0x370).

9. **Tail-merged mode dispatcher** (0x08037ad8, 0x08038fe4): the v==4 and else
   branches share the p[1]/p[2]/p[3] stores via compiler tail-merging; write
   them as separate if/else-if with `u32 z` in each.

## Blocked (6)

### 1. ObjInit_21E64 @ 0x08021e64 — BLOCKED (r5 zero-CSE)

ROM: `push {r4,lr}`; `movs r0,#0; str r0,[r4,#0x6c]`; two-step OR; ChipSlot
calls; idx calc; mask; `s[0x22]=0`; `s[0x12]=0xff`.

Both agbcc and old_agbcc keep the zero in r5 (`push {r4,r5,lr}`), using it for
both the `*(u32*)(s+0x6c)=0` and `s[0x22]=0` stores. ROM materializes fresh
`movs r0,#0` each time. 5 probes tried (block-scoped locals, late mask
declaration, old_agbcc). The idx/mask tail is otherwise perfect with
old_agbcc + `int mask=-0xd` (gives `movs r0,#0xd; negs r0,r0`).

Best C: `/tmp/wave5_h2/p_21e64e.c` (55 diffs, all from r5).

### 2. ObjInit_230A0 @ 0x080230a0 — BLOCKED (2-byte redundant move)

ROM has `adds r0,r1,#0` (mov r0,r1) before `cmp r0,#3` at 0x080230dc. 9 C
variants tried (int/u32 idx, `=3` vs `&=`, ternary, assignment-in-if,
goto). None reproduce the move; compiler always does `cmp r1,#3` directly.
Otherwise byte-perfect (including r5 prologue which ROM uses!).

Best C: `/tmp/wave5_h2/best_230a0.c` (2-byte diff only).

### 3. Task_35E5C @ 0x08035e5c — BLOCKED (control flow)

s8-indexed table poll with nested if/else and r1=0 propagation. 60 diffs.
The `ldrsb r1,[r5,r1]` (indexed with zero) and the branch structure not
reproduced. 2 probes tried.

### 4. FindZero_25958 @ 0x08025958 — BLOCKED (loop regalloc)

Loop over s16 i=0..0x1d checking p[i*4+0x14]. ROM: `lsls r2,r3,#2;
adds r0,r2,r4` with `bne` layout. Compiler uses r0 and `beq`. 4 variants
tried (do-while, while(1), goto, explicit pointer).

### 5. Task_281F0 @ 0x080281f0 — BLOCKED (branch regalloc)

ROM: `strb r0,[r4,#6]` (r0=0) then `ldrb r0,[r4,#1]` (reload) for p[1]++.
Compiler keeps p[1] in register without reload. Goto-beq tried; 19 diffs.

### 6. Text_4C288 @ 0x0804c288 — BLOCKED (thunk call)

Linked-list walk calling via `bx r3` thunk at 0x0804c278. 61 diffs. The
`tst/beq` entry and loop structure not reproduced. 1 probe tried.

### 7. Text_4CC64 @ 0x0804cc64 — BLOCKED (complex init)

Magic-guarded (0x68736d53) init with two loops and sub_0804dcd0 calls.
78 diffs. 1 probe tried.

## Not attempted (11)

0x08022320, 0x080223e4 (ObjInit family, same r5 blocker as 0x08021e64),
0x08028244, 0x0803af98, 0x08042ec0, 0x080481fc, 0x0804b980, 0x0804c58c,
0x0804ccb8.

## Recomp-relevant discoveries

- **sub_0804dcd0** (unmatched): polled by 5 task-mode functions. Takes (ptr/u32,
  u32); returns s8 (lsls#24+cmp#0) or u8 (lsls#24+lsrs#24). Likely a
  "mode available?" poll. Called with table values from ROM tables
  0x0822ea80, 0x0823010c, 0x08230da8, 0x08231764, 0x0822eb6c.
- **Task mode offsets**: 0x4698/0x4699/0x469c (mode selectors), 0x46a4-0x46af
  (init region), 0x46b7 (index). Consistent with wave4_k findings.
- **Text_SelectBlobIdx(0x66)** used by 0x08035bc8/0x08035da4 (UI text for
  these modes).
- **EWRAM 0x02004ce0**: struct with u16 at +0x28/+0x2a (position-ish,
  computed from mode value).
- **SRAM init** (0x080496a8): reads 0x010000d8 bytes? (size arg) — actually
  0x0804db24/0x0804db28 are save primitives; the sizes 0x010000d8 and
  0x05000003 look like mode+size packed.
- **GatedDispatch/Gfx_BlitRequest** are used as mode action wrappers
  (0x08035c1c, 0x08037598).
- **InitRec8_267B4** (sub_080267b4) called with (0x020070f0, 8) in mode
  transitions — 8-byte record init, kind 8.

## New idioms (for catalog)

1. **Literal-0 vs named-zero for r4/r5**: literal `0` in calls CSEs to r4
   (pointer in r5); named `u32 z=0` swaps them. (0x08035c1c)
2. **Goto-beq**: `if (x==1) goto L1; if (x==2) goto L2;` forces the ROM's
   `beq`-into-branch layout vs compiler's `bne`-skip. (0x08037a30)
3. **Shift-materialized constants**: `(0xdc<<2)` emits `movs/lsls`, not a pool.
   (0x080496a8)
4. **Declaration order for movs/adds**: `u32 z=0;` before `u8 *p=base+off;`
   emits `movs` before `adds`. (0x080496a8)
