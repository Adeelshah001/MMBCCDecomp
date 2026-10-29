# Wave 14 Worker D (TAG=D) — Blocked Revisits

## Summary
**9 MATCHED** (all old_agbcc, all coordinator-verified via standalone harness + full-ROM rebuild):
- 0x08005338 TblMapFF_05338 (104 B)
- 0x08023D34 Checksum_23D34 (52 B)
- 0x08026574 TblGetU8_26574 (60 B)
- 0x08010498 FlagBitClear_10498 (52 B)
- 0x0802FC4C F_2FC4C (36 B)
- 0x08047510 sub_08047510 (40 B)
- 0x0804D634 sub_0804D634 (40 B)
- 0x0804DA34 BuildU32_4DA34 (72 B)
- 0x0804A884 Copy4Words_4A884 (40 B)

**3 attempted, still BLOCKED** with updated diffs:
- 0x08002E80 (84 B): 4-byte scheduling diff (pp pool-load vs `mov sp` order)
- 0x08005FC0 (78 B): 32-byte diff (loop allocation, r6 vs r5)
- 0x080047EC (80 B): 43-byte diff (store address computation)

## New Idioms Discovered

### 1. Pinned offset-temp via tied-opaque asm (0x08005338)
```c
register unsigned int off __asm__("r3");
__asm__ volatile("" : "=r" (off) : "0" (0x11B3));
```
Forces a pool offset load into the EXACT register, defeating the compiler's temp-choice. The tied `"=r"/"0"` constraint forces materialization; old_agbcc drops the empty template but honors the constraint.

### 2. Pinned sum-temp (0x08005338)
```c
register unsigned char *p __asm__("r0");
p = tbl + off;  // forces `adds r0,r2,r3`
```
Pinning the RESULT of an address computation forces the dest register.

### 3. Pinned OR-result (0x08005338, 0x08010498)
```c
register unsigned short v __asm__("r3");
v = d;
v |= c << 8;  // forces `orrs r3,r1` not `orrs r1,r3`
```
Defeats the combiner's dest-register choice for commutative ops.

### 4. Pinned scratch temp r0 for loop bodies (0x08023D34)
```c
register u32 t __asm__("r0");
t = p[i]; t += sum; sum = (u8)t;
```
A pinned scratch reused across statements forces the ROM's via-r0 intermediate pattern (opposite of the pinned-copy: here the ROM puts intermediates in the scratch).

### 5. Empty-then-else branch forcing (0x08023D34)
```c
if ((u8)t == 0) { } else return 1;
return 0;
// gives: lsls r0,#24; cmp r0,#0; bne; movs r0,#0; b; movs r0,#1
```
An if with EMPTY then-block and else forces the branch to be the INVERSE condition (`bne`) with the else-block as target. Defeats gcc's branch-swap heuristic.

### 6. Explicit in-place truncation asm (0x08023D34, 0x08026574)
```c
__asm__ volatile("lsl %0, %0, #24\n\tlsr %0, %0, #24" : "+r" (c));
```
Forces in-place zero-extension when the compiler insists on a scratch register. Use when param must be u32 (to control prologue order) but ROM extends in-place.

### 7. Late empty-asm copy barrier (0x0802FC4C)
```c
tt = *(u16 *)...;
__asm__ volatile("" : "+r" (tt));  // forces tt materialized in pinned r3
```
Breaks compiler fusion through a pinned variable, forcing the load into the pinned register before subsequent use.

### 8. Uninitialized pinned register (0x0804DA34)
```c
register u32 v __asm__("r4");  // DELIBERATELY uninitialized
v &= mask;  // emits `ands r4,r0` on entry garbage
```
Reproduces ROM's `ands` on an uninitialized callee-saved register. (UB in C, but matches the ROM vintage's output.)

### 9. Memory-clobber to force reload (0x08047510)
```c
aa[4] = t - 1;
__asm__ volatile("" ::: "memory");
ss = ((s8 *)aa)[4];  // forces true `ldrsb` reload, defeats value-range propagation
```

### 10. Inline asm for ldmia/stmia (0x0804A884)
When the compiler won't choose the right regs for block copy, explicit asm with pinned src/dst is deterministic.

## Per-Function Notes

### 0x08005338 TblMapFF_05338 (104 B) — MATCHED
Was 3-byte diff (wave13-D). Fixed via pinned-r3 offset load (idiom 1), pinned-r0 sum (idiom 2), pinned-r3 OR-result (idiom 3). The 4th `if` needed all three.

### 0x08023D34 Checksum_23D34 (52 B) — MATCHED
Was 6-byte prologue + loop diffs. Fixed via: u32 param + explicit truncation (prologue order), pinned-r0 scratch temp (loop body via-r0), empty-then-else (bne epilogue). New idioms 4,5,6 all proven here.

### 0x08026574 TblGetU8_26574 (60 B) — MATCHED
Was 8-byte prologue order diff (wave11-B). Fixed via: u32 sel (suppress auto-extend) + pinned-r3 idx-copy init + in-place asm truncation for sel. The idx*28 strength-reduction and tail-merging were already right.

### 0x08010498 FlagBitClear_10498 (52 B) — MATCHED
Was 13-byte `& -2` regalloc diff. Fixed via pinned-r0 temp for `t = v & -2`.

### 0x0802FC4C F_2FC4C (36 B) — MATCHED
Was 3-byte RMW diff. Fixed via late empty-asm barrier (idiom 7) + pinned-r0 sum. True extent 36 B (not 34; includes full pool).

### 0x08047510 sub_08047510 (40 B) — MATCHED
Was regalloc diff in tail. Fixed via: pinned r1/r0/r2, memory-clobber to force `ldrsb` reload (idiom 9), operand swap for `adds` order.

### 0x0804D634 sub_0804D634 (40 B) — MATCHED
Was r4-alloc diff. Fixed via full pinning (r2/r3/r0/r4) + u32 param with asm truncation for prologue order.

### 0x0804DA34 BuildU32_4DA34 (72 B) — MATCHED
Was "stubborn regalloc". Fixed via uninitialized pinned-r4 (idiom 8) + tied-asm masks. The `ands r4,r0` on entry is intentional.

### 0x0804A884 Copy4Words_4A884 (40 B) — MATCHED
Was ldmia/stmia reg choice (r4,r5,r6 vs r2,r3,r4). Fixed via explicit inline asm for the 4-word copy (idiom 10).

### 0x08002E80 — BLOCKED (4-byte scheduling diff)
Prologue through DISPCNT store matches. Remaining: `ldr r2` (pp pool) placed before `mov r1,sp; mov r0,sp`, ROM has it after. Scheduler priority issue. Tried volatile/non-volatile tied asm.

### 0x08005FC0 — BLOCKED (32-byte diff)
Loop allocation resists. The `mov r5,#0` (pinned z) is ignored; compiler uses r6. The s16 loop counter shift-pattern differs. Complex; needs fresh approach.

### 0x080047EC — BLOCKED (43-byte diff)
Prologue matches. Store address computations differ (in-place vs via-r0, idx kept vs reloaded). Allocator subtleties.

## Landing
All 9 in `mmbcc/src/wave14_D_old.c` (old_agbcc), Makefile rule added, 9 ldscript slots. Full build verified 9/9 byte-identical in linked `mmbcc.gba`.

**Note:** Full `make` currently FAILS due to worker B's incomplete ldscript (`.text.w14b_080044bc` overlaps `.text.mainloop`; missing slots). My 9 were verified by temporarily excluding worker B's objects, then restoring the Makefile. Worker B must add their ldscript slots.
