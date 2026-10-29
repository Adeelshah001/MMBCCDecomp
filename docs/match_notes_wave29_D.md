# Wave 29-D Match Notes (Worker D, bulk + blocked revisits)

Worker D, 2026-10-23. Staging: `staging/wave29_D/` (C sources, verify.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: all 5 bulk targets NOT-IN-REGISTRY. No skips. No claims (nothing reached 0 diffs).

## Summary

- **0x0803AC4C**: 18 diffs best (v4, main agbcc). Closest. BLOCKED on register allocation.
- **0x0801E77C**: 176 diffs best (v2, old_agbcc). BLOCKED on prologue allocation.
- **0x080096BC, 0x08006FE8, 0x08024A30**: Triaged, not attempted in depth (time; all high complexity with r8/r9/sl).

## BLOCKED (attempted)

### 0x0803AC4C — Task_0803AC4C (252 B, 18 diffs best)

**Family:** Text_SelectBlobIdx dispatch (0x66/0x67/0x68) with EWRAM 0x02002F50 bit-tests,
EWRAM 0x02004CE0 setup. Sibling of matched Task_38AD4 (0x08038AD4), but different
structure (sequential ifs, not switch).

**Structure decoded:**
- Prologue: `push {r4-r7,lr}; p→r4; ret→r6=0; w=*(u16*)(0x2002F50+6)→r1`
- Bit32 block: if (w&32): q=p+0x469a; if (*q!=0) {(*q)--; goto snd} else {tbl lookup; if v==1 goto hw4; *q=v-1; goto snd}
- Bit16 block: if (w&16): q=p+0x469a; t=*q; off=0x469b; pa=p+off; off-=3; pb=p+off; v=tbl[a-b]; if (t<v-1) *q=t+1 else {if v==1 goto hw4; *q=0}; (falls through to snd)
- snd: Text_SelectBlobIdx(0x66); ret=3
- hw4: if (w2&1) {Text_SelectBlobIdx(0x67); ret=1} else if (w2&2) {Text_SelectBlobIdx(0x68); ret=2} where w2=*(u16*)(0x2002F50+4)
- tail: *(u16*)(0x2004CE0+40)=(p[0x469a]<<4)+72; *(u16*)(0x2004CE0+42)=(p[0x4698]<<4)+8; return ret

**Key findings (new idioms):**
1. **Anti-merge barrier:** `__asm__ volatile("")` between `(*q)--` and `goto snd`
   prevents gcc's cross-jumping tail-merge. Without it, gcc merges the two
   `subs/strb/b` sequences into a shared block with `bne` (ROM has `beq` + two
   separate sequences). Zero bytes overhead.
2. **Explicit goto for beq:** `if (*q == 0) goto tbl32;` (instead of if/else)
   gives ROM's `beq` direction. Combined with the barrier, the branch structure
   matches exactly.
3. **u32 temp for ands:** `u32 m = 32; if ((m &= w) != 0)` gives `movs r0,#32;
   ands r0,r1` (dest=r0). Confirms w28d idiom.
4. **Two-step EWRAM load:** `u8 *hw = gEwram_02002F50; w = *(u16 *)(hw + 6);`
   gives `ldr r0,[pc]; ldrh r1,[r0,#6]`. Prevents gcc from folding +6 into the pool.
5. **r7 pin for off:** `register u32 off __asm__("r7")` (block-scoped) gives
   `ldr r7,[pc]; adds r1,r4,r7; subs r7,#3; adds r0,r4,r7` exactly matching ROM's
   B16. BUT the pin does NOT cause gcc to push r7 (prologue broken).

**Remaining walls (18 diffs):**
1. **push/pop r7 (2 bytes):** ROM `push {r4-r7,lr}` / `pop {r4-r7}`; mine
   `push {r4-r6,lr}` / `pop {r4-r6}`. The r7 pin (block or function scope)
   marks r7 "fixed" so gcc uses it but doesn't save it. No C variant found to
   make gcc naturally allocate r7 AND push it.
2. **B32 o1/o2 allocation (12 bytes):** ROM `ldr r5(0x469b); adds r1,r4,r5;
   ldr r7(0x4698); adds r0,r4,r7`; mine `ldr r1(0x469b); adds r0,r4,r1;
   ldr r5(0x4698); adds r1,r4,r5`. Tried: immediates, u32 vars, function-scope
   vars, r5/r7 pins (r5 pin broke p→r4!), clobber-reservation (worse). The
   r5/r7 callee-saved choice for single-use offsets is not reproducible.
3. **B16 pa/pb swap (5 bytes):** ROM `pa→r1, pb→r0`; mine `pa→r0, pb→r1`.
   Declaration order swap did not help.

Staged: `staging/wave29_D/w29d_0803ac4c_v4.c` (18 diffs, best).
Also staged: v1-v10 (progression).

### 0x0801E77C — Task_0801E77C (254 B, 176 diffs best)

**Structure:** Switch on p[14] (0-3) with fallthrough from case 0 to case 1.
- Prologue: `push {r4,r5,lr}; sub sp,#8; p→r4; tbl=&gAddrZero[0x20051c8]+p[16]*12→r2;
  two u32 stack slots zeroed; st=p[14]→r5`
- Case 0: ChipSlot_IncUse(p,8); p[14]++; p[19]=st; *(u16*)(p+120)=60;
  NewNode_0801D278(p,p+19,sp); (falls through)
- Case 1: v=*(u16*)(p+120); if (*(s16*)(p+120)!=0) {v--; *(u16*)(p+120)=v; if v==0 SelBlob_Ret(110)};
  if ((u8)(p[119]-3)>1) break; p[14]++; Set_08004E24(1);
- Case 2: if ((s8)Cmp_08004E0C(3)==0) break; p[14]++; *(u16*)0x20031E0 &= 0xEDFF &= 0xDBFF; Fwd_10BA0();
- Case 3: t=tbl[6]; if t!=0 {*(u32*)(p+12)=2; *(u32*)(p+20)=*(*(u32*)(0x82243d8+p[9]*4)+8)} else {p[13]=p[15]=p[14]=0}; tbl[1]=0;

**Key findings:**
- **old_agbcc decisive for prologue:** Gives `ldrb r1,[r4,#16]; lsls r0,r1,#1;
  adds r0,r0,r1; lsls r0,r0,#2` exactly (main agbcc uses r0/r1 swapped).
- **m-constraint for stack slot:** `__asm__ volatile("" :: "m"(sp1))` forces the
  second `str` (gcc DSE eliminates unused sp1). But gcc merges the two `movs r0,#0`
  into one (ROM has two movs).
- **tbl→r2:** `register u8 *tbl __asm__("r2")` works, but gcc then computes the
  shifts directly in r2 (ROM does shifts in r0, then `adds r2,r0,r1`). Two-step
  (off variable + pinned tbl) still computes in r2.

**Remaining walls:** Prologue allocation (pool→r6 vs r1, tbl→r3 vs r2, extra
r6 push). The `p[16]*12` → `adds r2,r0,r1` with pool in r1 is not reproducible.

Staged: `staging/wave29_D/w29d_0801e77c_v2.c` (176 diffs with old_agbcc, best).

## TRIAGED (not attempted in depth)

### 0x080096BC — sub_080096BC (260 B)
Tile-copy loop, 5 params (4 regs + 1 stack), uses r8/r9/sl (full callee-saved
save/restore). Pools: 0x6010000 (VRAM), 0x81720b4, 0x81720cc. Calls Memcpy16
(0x8000758, MATCHED). Complex loop with bit-tests. High difficulty.

### 0x08006FE8 — sub_08006FE8 (264 B)
6 params, GetPtr family (calls 0x8008680, 0x8008628, 0x8008610, 0x8008654).
Uses r8/r9/sl. Complex control flow with nested loops. High difficulty.

### 0x08024A30 — sub_08024A30 (268 B)
11 callees (0x80258d8, 0x802493c, 0x8025478, 0x80254b4, 0x8025934, etc.).
Uses r8/r9/sl. Complex dispatch. High difficulty.

## New idioms discovered

1. **Anti-merge barrier:** Empty `__asm__ volatile("")` prevents gcc's
   cross-jumping from merging identical `subs/strb/b` tails. Zero bytes.
   Critical for matching ROM's `beq` + duplicated sequences.
2. **Explicit goto for branch direction:** `if (c) goto L;` gives `beq L`,
   while if/else may give `bne` after optimization. Use explicit gotos when
   ROM's branch direction matters.
3. **Two-step EWRAM load:** `u8 *hw = SYM; v = *(u16 *)(hw + N);` prevents
   gcc from folding the offset into the pool reloc, giving `ldr rX,[pc];
   ldrh rY,[rX,#N]`.
4. **m-constraint stack force:** `__asm__ volatile("" :: "m"(var))` forces gcc
   to keep a stack slot and its initialization store, defeating DSE for
   unused out-params. Zero bytes.
5. **old_agbcc for prologue:** On 0x0801e77c, old_agbcc gave correct
   `ldrb r1` + shift sequence vs main agbcc's swapped regs. Always try both.

## Tooling
- `staging/wave29_D/verify.sh` — hardened harness (adapted from w28d).
- `staging/wave29_D/w29d_0803ac4c_v*.c` (v1-v10) — 0x0803ac4c progression, v4 best (18 diffs).
- `staging/wave29_D/w29d_0801e77c_v*.c` (v1-v6) — 0x0801e77c progression, v2 best (176 diffs, old_agbcc).
- `staging/wave29_D/rom_*.bin`, `dis_*.txt` — ROM extracts and disassemblies.
- `staging/wave29_D/exp_b16.c` — isolated B16 pattern experiment.

## Summary for coordinator
- **BLOCKED:** 0x0803AC4C (18 diffs; walls: r7 push/pop, B32 o1/o2→r5/r7, B16 pa/pb swap).
  Best staged at `staging/wave29_D/w29d_0803ac4c_v4.c`.
- **BLOCKED:** 0x0801E77C (176 diffs; walls: prologue tbl→r2/pool→r1 allocation).
  Best staged at `staging/wave29_D/w29d_0801e77c_v2.c` (use old_agbcc).
- **TRIAGED:** 0x080096BC, 0x08006FE8, 0x08024A30 — high complexity (r8/r9/sl,
  5-6 params), not attempted in depth due to time.
- **Progress:** 0/5 bulk matched. 0x0803ac4c is close (18 diffs) and may be
  crackable with the sed-patch for push/pop + further allocation work.
