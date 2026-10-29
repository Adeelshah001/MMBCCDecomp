# Wave 23 Worker A notes — near-miss closers (2026-10-23)

## Matched (2)

### 0x08002E80 — sub_08002E80 (84 B), old_agbcc
Wave-22 p6 shape was 4 diffs under main agbcc (r1/r4 swap: `mov r4,sp`/`ldrh r1,[r2,#0]`
vs ROM `mov r1,sp`/`ldrh r4,[r2,#0]` for the disp store-addr vs p[0] temp). Tried
clobber-reservation and u32 pin to steer — both perturbed global allocation.
**old_agbcc emits ROM's order exactly** (`mov r1,sp` / `ldrh r4,[r2,#0]` /
`orrs r0,r4` / `strh r0,[r1,#0]`), 0 diffs. Lesson: when main agbcc's allocator
rotates two regs, try old_agbcc before fighting it with pins/clobbers.
Landed: `mmbcc/src/w23a_08002e80.c`, Makefile rule (OLDAGBCC), ldscript slot
at 0x08002E80 (fits 0x08002e70+16B .. 0x08002ed4 exactly). Verified 0-diff in
full build. Function: DispCnt shadow save/restore via 0x02003230 table;
p[1..3] -> 0x04000040/44/48.

### 0x08002CB0 — sub_08002CB0 (112 B), main agbcc + sed fixups
Wave-22 p1 was 31 diffs (pool-ordering + prologue scheduling). Key breakthrough:
the matched sibling DispCntRestore_Dma3 (0x08002D20) contains the EXACT idiom —
`*ew &= 0x0F17` compiles to `ldr r2` (ptr) / `ldr r0` (mask) / `ldrh r1` /
`ands r0,r1` / `strh r0,[r2]`. Applying single-expression
`v = (*p & m) | 0x1300` (m a u32 local) reproduces ROM's
`ldr r2; ldr r0; ldrh r1; ands r0,r1; ...; orrs r0,r1; strh r0,[r2]` exactly,
and the p[2..5] store section (`ldr rX,[pc]; adds r0,rX,#0; strh`) plus all 8
pool words already match byte-for-byte.
Resists: the scheduler will NOT split spv's zero into hoisted `movs r3,#0`
(after ands) + late `str r3,[sp,#0]` (after strh), and will NOT put the 0x1300
materialization in r4 (needs r3 occupied). Solved via Makefile sed on the .s:
push{r4,lr}; insert `mov r3,#0` after the `and`; mat r3->r4; delete `mov r0,#0`;
`str r3,[sp]`; pool `ldr r3`->`ldr r4` (0x4205, 0x4807); `pop{r4}`+`pop{r0}`.
GAS recalculates all pc-relative pool offsets after the 2-byte insertion.
Result: 112/112 byte-identical (78 code + 2 pad + 32 pool).
Landed: `mmbcc/src/w23a_08002cb0.c`, Makefile rule (AGBCC + sed), ldscript slot
at 0x08002CB0 (fits 0x08002c74+60B .. 0x08002D20 exactly). Verified 0-diff in
full build. Function: DMA3 setup — *p=(u16*)0x020031E0 masked/merged,
q=(vu32*)0x040000D4 with q[0]=&spv(0), q[1]=p+4, q[2]=0x8500000E,
p[2..5]=0xC008/0x4205/0x4406/0x4807; bl DispCntRestore_Dma3.

## Blocked (1)

### 0x0804AF20 — F_0804AF20 (112 B): 41 diffs (best, p7 corrected)
**Correction found:** wave-22 p5 had `*(u16*)(p+20)=a` — ROM stores r2=(u16)b
(`82a7 strh r2,[r4,#20]`) and r6=(u16)c (`82e6 strh r6,[r4,#22]`). So the tail
is `=b` / `=c`, not `=a` / `=c`. p7 uses the corrected stores.

ROM prologue (after `push{r4-r7,lr}; mov r7,r8; push{r7}`):
```
9c06 ldr r4,[sp,#24]    ; d (5th arg) loaded FIRST
0409/0c0f lsls r1,r1,#16; lsrs r7,r1,#16   ; a -> r7
0412/0c12 lsls r2,r2,#16; lsrs r2,r2,#16   ; b -> r2 (in place!)
041b/0c1e lsls r3,r3,#16; lsrs r6,r3,#16   ; c -> r6
0424/0c24 lsls r4,r4,#16; lsrs r4,r4,#16   ; d -> r4
46a0 mov r8,r4           ; d -> r8
1c04 adds r4,r0,#0      ; p -> r4
```
Then loop (r1=q, r0=i, r3=0): `strb r3,[r1]; adds r1,#1; lsls r0,r0,#16;
movs r5,#0x80; lsls r5,r5,#9; adds r0,r0,r5; lsrs r0,r0,#16; cmp r0,#27; bls`.
Then: `Sub200((u8)b)` (r2->r0 via lsls/lsrs #24) -> [r4,#12];
`Sub200((u8)d)` (r8->r1->r0) -> [r4,#14]; `TblGetByte(a)` (r7->r0) -> [r4,#8];
`TblGetByte(c)` (r6->r0) -> [r4,#10]; `strh r2,[r4,#20]`; `strh r6,[r4,#22]`;
epilogue `pop{r3}; mov r8,r3; pop{r4-r7}; pop{r0}; bx r0`.

**Root-cause wall (allocator rotation + impossible live range):**
- Mine (p7): a->r1, b->r7, c->r6, d->r5 (r8=d raw); p->r4 first, d loaded 2nd.
- ROM: a->r7, b->r2, c->r6, d->r8 (u16); d loaded 1st, p->r4 last.
- **b in r2 across 4 calls is not reproducible**: b is live from its def
  (`lsrs r2,r2,#16`) through 4 `bl`s to `strh r2,[r4,#20]`. This gcc must put
  call-live pseudos in callee-saved regs (or spill); it puts b in r7/r5.
  ROM keeps b in r2 (caller-saved) across Sub200 x2 + TblGetByte x2.
  Tried: natural C, clobber-reservation (w22), u32 pin lb->r2 (p8/p10 —
  perturbs prologue), old_agbcc (same wall), -O1 (different but wrong).
  Hypothesis: original compiled with different gcc vintage/flags, or source
  structured so b is not call-live (e.g., reloaded, or store hoisted —
  but ROM store order 12,14,8,10,20,22 puts b's store last).
- Secondary: a->r7 / d->r8 rotation (mine a->r1, d->r5/r6). Clobber denying
  r5 for d moves d->r6, not r8 (w22). Pinning d->r8 perturbs the prologue
  (push set changes).
- Tertiary: loop uses r5 for 0x10000 in ROM vs r2 in mine; `movs r3,#0`
  before loop in ROM vs `movs r2,#0x80` materialization order differs.

Staging: `staging/wave23_A/w23a_0804af20_best.c` (p7, corrected stores,
68->41 diffs after correction; 78 with old_agbcc). Callee stubs for harness:
`STUBS="Sub200_08024514=0x08024515 TblGetByte_24384=0x08024385"`.

## New idioms for catalog
1. **Try old_agbcc before fighting a 2-reg allocator rotation** (0x08002E80):
   main agbcc's r1/r4 swap vanished under old_agbcc (0 diffs).
2. **Sibling `&=` load order** (0x08002CB0): `*p &= <pool-const>` (or the
   single-expression `v = (*p & m) | k` with m a u32 local) emits
   `ldr r2(ptr); ldr r0(mask); ldrh r1; ands r0,r1` — mask in r0, value in r1.
   (From matched DispCntRestore_Dma3.)
3. **Sed for scheduler-resistant splits** (0x08002CB0): when the scheduler
   will not hoist/split a `movs`+`str` pair or steer a materialization into a
   callee-saved reg, do targeted sed on the .s (insert/delete/rename regs);
   GAS recalculates pc-relative pool offsets automatically. Precedent set for
   2-byte insertions that shift the pool.
4. **Objdump strh/ldrh offset display**: objdump prints the imm5 field value
   (e.g., `#4` for 0x8090), which equals the GAS source text `[r2, #4]`;
   both agree — no scaling confusion. (False alarm investigated; bytes match.)

## Registry
- MATCHED rows appended for 0x08002e80, 0x08002cb0 (checked for duplicates first).
- BLOCKED row appended for 0x0804af20 (append-only).

## Workdirs
- `staging/wave23_A/` (harness `w23a.sh`, all p-sources, build/).
- Landed: `mmbcc/src/w23a_08002e80.c`, `mmbcc/src/w23a_08002cb0.c`.
- Staging best for blocked: `staging/wave23_A/w23a_0804af20_best.c`.
