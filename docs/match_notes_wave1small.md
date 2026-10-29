# Wave 1 small/templated — worker notes (2026-10-20)

## Task_Register @0x08000D90 — MATCHED (48/48 bytes)
`mmbcc/src/task_register.c`, section `.text.task_register`, flags `-O2 -mthumb-interwork`.
- 24-byte entries; `[e+4]=handler`, `[e+8]=0x03000FA0+index*2560` (task stack),
  `[e+2]=0` (half), `[e+1]=0`, `[e+0]=2`.
- Key trick: stack base emitted as `(tableBaseReg - 0x1428)`. A `u32 baseAddr`
  temp modified by `-= 0x1428` defeats constant folding (else compiler pools
  0x03000FA0 directly). Statement order matters: `stackOff = index*2560`
  before `baseAddr -= 0x1428`, and `&TASK_TABLE[index]` for the entry ptr.

## HwInit_WaitCntDma @0x0800063C — MATCHED (96/96 bytes)
`mmbcc/src/hwinit.c`, section `.text.hwinit`, flags `-O2 -mthumb-interwork`.
- WAITCNT=0x45B7; DMA3 via `vu32 *dma3` at 0x040000D4 with `dma3[0/1/2]`
  (single pool entry + offsets — separate macros produce 3 pool entries).
- SAD=sp via `u32 spSave; spSave=0; dma3[0]=(u32)&spSave;` (twice).
- Dead `(void)dma3[2]` volatile readbacks of DMA3CNT are in the original.
- Tail zeroes `[0x02002ED2]`, `[0x02002ED0]` = base 0x02000ED0 + 0x2002/0x2000
  (this corrects my earlier misread of 0x202; symbols_phase2.md §1.2's
  0x02002ED2/0x02002ED0 stands).
- Key trick: `asm volatile("" : "+r" (ewramBase))` barrier keeps the base
  opaque; otherwise -O2 folds and re-bases the pair as (0x02002ED2, -2).
  (An earlier `"=r"`-output variant produced right bytes but WRONG semantics
  — output went to a different reg than the input; `"+r"` is correct.)

## StridedCopy @0x08000C68 — BLOCKED (38/52 bytes match)
`mmbcc/src/strided_copy.c` holds best-effort C, clearly marked NOT MATCHED.
- Structure, loop, `pop{r0}/bx r0` epilogue all reproduce; 14 bytes differ
  purely from register allocation: ROM has d=r4, dst=r3, sstep=r5;
  agbcc -O2 gives d=r5, dst=r4, sstep=r3. Tried: decl-order permutations,
  split decl/init, type variants (int/long/short/u8/u16/u32), inlining ds,
  -O1/-Os, static — allocator is stable. Explicit `register asm()` pins get
  the registers but break the `lsls r0,r5,#24` scratch pattern (and the old
  gcc's local explicit-reg support is unreliable).
- Semantics confirmed: `*dst=*src` halfwords; steps `(s8)byte*2` recomputed
  per iteration (idempotent); count is u16 with wraparound decrement;
  updated src written back to `[d+12]`.
