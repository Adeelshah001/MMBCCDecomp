# Wave 13 Worker D — Match Notes (leaves-up layer, docs/wave13_layer.tsv)

Layer: 30 candidates (docs/wave13_layer.tsv), all pure leaves (n_bl=0), ordered by caller count.
True sizes re-derived per function (func_stats.tsv often excludes trailing pools).

## New Idioms (verified byte-identical via harness)

### 13. Volatile u16 stack var forces per-access stack traffic
`volatile unsigned short v;` keeps every read/write on the stack (`sub sp,#4`,
`mov rX,sp` per access) under old_agbcc -O2, matching ROMs that never promote
the local. Non-volatile promotes to register.

### 14. Pinned-zero + stack-slot copy pattern
`register unsigned int zero __asm__("r4") = 0; unsigned int w = zero;` yields
ROM's `movs r4,#0; str r4,[sp]` (pinned reg for later use + address-taken stack
slot for DMA). Pinning the address-taken var directly is ignored by old_agbcc
(warning only).

### 15. `add` (no S) in inline asm assembles to flag-setting `adds`
In divided syntax, `add r0, r2, r3` in `__asm__` encodes as `adds r0, r2, r3`
(0x18D0). Usable to force exact `adds` operand order with pinned regs as `%0/%1`
operands, bypassing the C allocator's operand swap.

### 16. Tied-opaque defeats base+offset folding for table access
`tbl[0x11B0]` with constant tbl folds to absolute `ldrb [0x020047B0]`; making
tbl tied-opaque (`__asm__ volatile("" : "=r"(tbl) : "0"(0x02003670))`) forces
ROM's `ldr rX,[pc]; adds r0,r2,rX; ldrb` base+offset form with pool-loaded offset.

### 17. `|` operand order selects `orrs` destination register
`out[2] = d | (c << 8)` yields ROM's `orrs r3, r1` (accumulate into d's reg);
`(c << 8) | d` yields `orrs r1, r3` instead.

## MATCHED

### 0x08046ca0 — ChipSlot_InitEntry (92 B, old_agbcc)
Struct+array init: p[4]=p[5]=0; p[2]=p[3]=(b?25:20) via duplicated-store
tail-merge (`p[5]=b` in then-branch, `p[5]=0` in else); p[8]=b;
*(u16*)(p+6)=0x800A via tied-opaque pool; `for (i=0; i<a+1; i++) q[i]=0;`
(old_agbcc for-loop entry-check lowering: `adds r2,#1; cmp r0,r2; bge`);
q[0]=0x8000. True size 92 (func_stats 88 excluded pool).

### 0x08002d20 — DispCntRestore_Dma3 (100 B, old_agbcc)
`volatile u16 v` on stack; v=REG_DISPCNT(0x04000000, in r4 via natural alloc);
v&=0xF0E8; *(u16*)0x020031E0&=0x0F17 (non-volatile, CSE into `orrs`);
v|=masked; REG_DISPCNT=v; DMA3: SAD=(u32)ew+4 (`adds r2,#4`), DAD=0x04000008,
CNT=0x8400000E, `(void)dma[2]` dummy read. True size 100.

### 0x08002678 — PalDmaInit_02678 (108 B, old_agbcc)
Stack-marker DMA3 (like Init_080021C4): dma[0]=&w, dma[1]=0x03002420,
dma[2]=0x85000100, dummy; dma[0]=0x03002420, dma[1]=0xA0<<19 (0x05000000),
dma[2]=0x84000100, dummy. Then q[0x400..0x402]=32 via inline asm (pinned
r2=q, r3=i; `add r0,%1,%0` for ROM's adds-operand-order); *(u16*)(q+0x404)=0
(r4 zero), *(u16*)(q+0x406)=0x400 (r3). True size 108.

## BLOCKED

### 0x08005338 (104 B) — 4th if offset-load register
Tries: f_08005338.c (tbl pinned r2), f_08005338_t.c (ternary), cc-pin variant.
Best: 3-byte diff at file offsets 56,57,59. ROM 4th if:
`4b0a ldr r3,[pc,#40]; 18d0 adds r0,r2,r3; 7803 ldrb r3,[r0]`
(offset 0x11B3 pooled directly into d's register r3, tbl preserved in r2).
Mine: `480a ldr r0,[pc,#40]; 1812 adds r2,r2,r0; 7813 ldrb r3,[r2]`
(offset into r0, tbl clobbered). First three ifs match exactly
(`ldr r5/r4/r1; adds r0,r2,rX; ldrb rX,[r0]`); final `orrs`/`strh` match.
Unpinned-tbl variant gets if-4 right but swaps c/tbl regs (c→r2,tbl→r1 vs
ROM c→r1,tbl→r2). Pinning c to r1 adds spurious zero-extensions.
Resistant: allocator refuses to reuse r3 for the 4th offset when tbl is pinned
to r2.

### 0x08004e008 (82 B) — memset byte-loop epilogue
Tries: f_08004e008.c, f_08004e008_b.c (noiw). Best: word loops match exactly
(`stmia r1!,{r3}` x4 unrolled, `subs`/branch structure, `pop {r4,r5,pc}` via
noiw). Blocked on byte-loop epilogue. ROM:
`adds r3,r1,#0; b check; loop: strb r4,[r3]; adds r3,#1; check: adds r0,r2,#0;`
`subs r2,#1; cmp r0,#0; bne loop; adds r0,r5,#0`
(old_agbcc `while(n--)` goto-check lowering, checking pre-decrement value).
Mine (`while(m--)`): generates `subs r2,#1; movs r0,#1; negs r0; cmp r2,r0`
(post-decrement wrap check vs -1). 6-byte size diff (88 vs 82). Resistant:
unsigned wrap semantics defeat the pre-decrement check pattern.

### 0x0800d420 (96 B) — shift-increment loop counter
Tried: f_0800d420.c. ROM loop:
`lsls r0,r0,#16; movs r7,#0x80; lsls r7,#9; adds r0,r0,r7; lsrs r0,r0,#16`
(i.e. `i=((i<<16)+0x10000)>>16`, a 16-bit increment done in shifted domain).
old_agbcc `unsigned short i; i++` yields `adds r0,#1; lsls; lsrs` (add-first,
not shift-first). Also regalloc differs (ROM: base in r2, save in r6, zero in
r5, 5-reg push; mine: 3-reg push). Resistant: shift-first increment idiom
unknown.

### 0x08004208 (58 B) — nested clear regalloc
Tried: f_08004208.c (u32 2D and byte-offset forms). ROM: 4x32 u32 clear,
`r2=(r1<<16)>>9` (i*128) hoisted, inner `j*4+r2`, short counters. Mine computes
`i*32` (`>>11`) or mismatched regs; 2-byte size diff. Resistant: allocator
won't hoist i*128 with ROM's exact r1/r2/r3 assignment.

### 0x0800a094 (64 B) — shift-increment (same as 0x0800d420)
Base 0x02004E40; clears 244 bytes via shift-increment `((i<<16)+0x10000)>>16`
(bound 243); then *(+16)=4, *(+0..3)=0, *(+19)&=-5. Not attempted in C:
shift-increment idiom already established resistant at 0x0800d420.

### 0x0803fdbc (58 B) — non-standard prologue
No `push` at entry (starts `lsls r0,r0,#16`); ends `bx lr` without pop.
Interior fragment or custom convention; not matchable via standard C.
Similar to wave12_C 0x0804C2CC.

### 0x08002620 (72 B) — ip-spill offset optimization
Tried: f_08002620.c. DMA part matches (`mov rX,sp; str; lsrs; orrs 0x85000000`).
Blocked on base stores: ROM does `mov r4,ip; adds r4,#0xCC` (restore base from
ip for each store); mine optimizes second store to `add r4,r4,#4` (reusing
r4=base+0xC8). 30+ byte diffs from prologue. Resistant: allocator's
sequential-offset optimization.

### 0x080255f4 (66 B) — counter-register clobber
Tried: f_080255f4.c (multiple variants). ROM reuses r1 (loop counter) for the
`ldrb` (`ldrb r1,[r2]` clobbers counter, reconstructed via shifts); mine emits
extra `add r1,r2,#0` copy. 2-byte size diff (68 vs 66). Resistant: allocator
won't clobber live counter register.

### 0x0804bfd4 (66 B) — far pools
References pools at 0x804c280/0x804c284 (680-byte pc offset), not adjacent.
Also pools at 0x804c018/0x804c01c. Cannot match standalone with adjacent-pool
harness; ldr offsets encode far distance. Requires full-ROM context.

### 0x0800291c (68 B) — multiply-accumulate loop
Tried: f_0800291c.c. 256-iter loop with `muls`, 3-word struct, mixed
`>>5`/`*` ordering (third word does `>>5` before `*`). Mine 92-108 B vs 68 B;
compiler won't reproduce the tight 5-register allocation with lr save/restore.
Resistant: complex loop-carried optimization.

### 0x0800410c (74 B) — same as 0x08004208
4x32 u32 clear with i*128 hoist; identical structure to 0x08004208.
Not attempted: same resistant regalloc.
