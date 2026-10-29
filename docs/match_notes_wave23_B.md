# Wave 23-B: Rect-fill family (0x08006AD8 / 0x08007134 / 0x080065BC / 0x08006374)

Worker B, 2026-10-23. No matches landed; detailed analysis + idioms below.

## Function sizes (corrected)

- 0x08006AD8: **768 B** (0x6AD8–0x6DD8), not 240 B. Wave-22 note's "768 B" was correct;
  my early "240 B" was the offset of the epilogue branch target, not the function end.
- 0x08007134: 480 B (0x7134–0x7314)
- 0x080065BC: 416 B (0x65BC–0x675C)
- 0x08006374: 420 B (0x6374–0x6518)

All four share the callee family: FlagA_8628 (@0x08008628), FlagA_8654 (@0x08008654),
FlagA_8680 (@0x08008680), GetPtr_08008610 (@0x08008610), SetIfXZero (@0x08008BB8) —
all MATCHED and landed. 0x08007134 additionally calls 0x08006AD8 itself (plus
unmatched 0x080060C4/0x080062B4/0x08007464). 0x08006374 calls 0x080065BC (2×).

## 0x08006AD8 — full semantic decode (768 B, no literal pool)

Prototype: `void sub_08006AD8(u8 *ctx, u32 a, u16 b, u16 c, u8 d, u8 e)`
(ctx = 0x02004830 via Gfx_BlitRequest; a = u16 tile list or 0; b = s16 row adj;
c = s16 index; d = s8 height-ish; e = u8 variant 0..3).

High-level: tilemap rect-fill engine. Validates (b,c,d) against FlagA limits,
computes dst = GetPtr_08008610(ctx) + ((s16)c << ((s8)flag+1)) + b*2, then:
- Loop 1 (a != 0): per-row, reads u16 tile t from *a++; if (t & 0x8000) break to loop 2;
  writes tilemap entry `*(u16*)(*(u32*)(ctx+4) + (row<<1)) = t|X` and two
  SetIfXZero shadow writes (x = mode&1 / mode&2).
- Loop 2: simpler fill of W|Y via SetIfXZero.
Row counter = *(u16*)(ctx+2), limit = *(u16*)ctx. mode ∈ {0,1,2} from c-range checks.
X/Y/W/mode/flag are u32/u8 locals: X=0/0x600, Y=50/51, W=0xB000/0xC000,
flag=(u8)FlagA_8654(ctx).

## New idioms discovered (all verified via isolated probes)

1. **Shift-first u8 increment**: `i = (u8)(((i << 24) + 0x1000000) >> 24);`
   generates ROM's `lsls r0,r1,#24 / movs r2,#128 / lsls r2,#17 / adds r0,r2 /
   lsrs r3,r0,#24` dance. Plain `i++` emits adds-first instead. (Same idiom as
   w19d_08022868's `idx`, independently rediscovered.)
2. **hs pattern**: `u32 hs = (u32)h << 24; if ((s32)hs <= 0) return;` keeps h<<24
   in a register for the whole function; loop conditions written as
   `(s32)((u32)i << 24) < (s32)hs`.
3. **For-loop with shifted post**: 
   `for (i = 0; (s32)((u32)i<<24) < (s32)hs; i = (u8)(((i<<24)+0x1000000)>>24))`
   generates ROM's head-check + body + latch-check (`cmp r0,r8; blt body`) shape.
4. **m1/m2 single-computation**: `(mode&1)<<24` → [sp,#32], `(mode&2)<<24` → r7,
   computed once on loop-1 entry; loop back-edge jumps to workA (0x8006C94),
   skipping the setup. (Compiler LICM/preheader placement.)
5. `ctx[10] &= ~1` clears bit 0 (not bit 1): ROM does `movs r0,#2; negs r0,r0`
   (= -2 = 0xFFFFFFFE), i.e. `& ~1`. My earlier `& ~2` was a misread.
6. `(t & 0x1FF)` must avoid a literal pool: ROM materializes via
   `movs r0,#128; lsls r0,#2 (=0x200); subs r0,#1`. Plain `(t & 0x1FF)` in my
   build emitted `.word 511` pool.

## Blocker: prologue register-allocation wall (0x08006AD8)

ROM prologue (16 B):
```
push {r4-r7,lr}; mov r7,sl; mov r6,r9; mov r5,r8; push {r5,r6,r7}; sub sp,#40
adds r6,r0,#0            ; r6 = ctx
str r1,[sp,#0]           ; [sp,#0] = a
ldr r0,[sp,#72]; ldr r1,[sp,#76]   ; d, e
lsls/lsrs r2,#16; mov r9,r2        ; r9 = (u16)b
lsls/lsrs r3,#16; str r3,[sp,#4]   ; [sp,#4] = (u16)c
lsls/lsrs r0,#24; mov r8,r0        ; r8 = (u8)d
lsls/lsrs r1,#24; str r1,[sp,#8]   ; [sp,#8] = (u8)e
ldr r0,[sp,#0]; mov sl,r0         ; sl = a (cached)
```

My best C (staging/wave23_B/w23b_08006AD8.c, v3) gets `sub sp,#40` right but
allocates r8=ctx, sl=a (no stack spill), r5=b, r7=c — vs ROM's r6=ctx,
[sp,#0]=a, r9=b, [sp,#4]=c, r8=d. The specific hi-register choices (r6/r9/r8/sl)
plus selective param spills (a,c,e spilled; b,d in regs) do not emerge from
natural C; `register __asm__("r9"/"r8")` pinning was tried and perturbed the
rest of codegen (size 756 vs 768, worse diffs). This is a scheduler/allocator
wall, not a logic wall — the body semantics are fully understood.

Best staging: staging/wave23_B/w23b_08006AD8.c (752 B, 705 diffs, all from
prologue cascade). Also staged: v2/v3/v4 variants and probe*.c idiom probes.

## Other three — not attempted (time-boxed on 0x08006AD8)

- 0x08007134 (480 B): similar c/b validation prologue to 0x08006AD8, then calls
  0x08006AD8 + 3 unmatched callees. Likely tractable via sibling transfer once
  0x08006AD8's prologue idiom is cracked.
- 0x080065BC (416 B): 8-arg variant (u8 a,b,c + u8 d + u16 e,f + ...), different
  validation shape; calls 0x080067BC/0x0800695C/0x08008BC8/0x0800909C (unmatched).
- 0x08006374 (420 B): outer FillRect validator (Worker B wave-22 first pass at
  staging/wave22_B/w22b_08006374.c, 377 diffs); calls 0x080065BC 2×.

## Recommendation

The rect-fill family's blocker is the prologue allocator wall, not the loop
logic. The loop idioms above are proven and transferable. Next step: crack the
`r6/r9/r8/sl + selective spill` prologue on 0x08006AD8 (possibly via a new
pinning idiom that doesn't perturb the body, or via old_agbcc with different
variable ordering), then sibling-transfer to the other three.
