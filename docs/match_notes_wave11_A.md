# Wave 11 Worker A — Matching Notes

## New Idioms Discovered

### 1. Explicit trailing pad via top-level asm
For non-4-aligned code extents, GAS emits `46c0` nop pad but ROM has `00 00`.
Fix: append after the function:
```c
__asm__(".section .text.w11a_<addr>,\"ax\",%progbits\n.byte 0, 0\n.previous");
```
Makes section 4-aligned so GAS adds no pad. Used for: 20230, 24744, 4c53c, 1d68, ef8, 23b64, 23d10, 25490.

### 2. Switch defeats `<C`→`<=C-1` frontend folding
old_agbcc folds `x < 0x60` to `cmp #0x5F; bls`, but ROM had `cmp #0x60; blt`.
A `switch` with the same cases emits the unfolded decision tree. (3fe00)

### 3. Barrier-before-copy
`__asm__ volatile("": "+r"(xx));` before `t = xx` with pinned regs forces a real
`adds` copy instead of fusion. (24744, from wave10_R)

### 4. Tied-opaque pool load
`__asm__ volatile("" : "=r" (v) : "0" (CONST));` forces `ldr rN,[pc]` and prevents
the compiler folding arithmetic (e.g. `+0x44`) into the pool constant.
Used for: ee50, d104, 3f440, 3fd9c, 4c610, 11054, 173fc, 36318, 3fa48, 4acdc.

### 5. `(u32)-3` emits `movs; negs` naturally
Do NOT use inline `negs`/`rsb` (GAS 2.42 rejects `negs r1,r1` in inline asm and
`rsb` width suffixes; gcc's `neg` pseudo-op assembles fine). (d104)

### 6. Second-param-in-r1
If ROM uses r1 directly with no `adds r1,r0,#0`, the pointer is the 2nd param
(check caller; e.g. 4c53c caller at 0x0804c45e passes `(byte in r0, ptr in r1)`).

### 7. Pin `v` to free `r1`
When the compiler misallocates a zero-extend (xx→r3), pinning the competing
variable (v→r3) can push xx back to r1. (4c610)

### 8. Two-step offset+base for `adds` operand order
`adds r0,r0,r1` vs `adds r0,r1,r0` are semantically identical but encode differently.
Splitting: `off = q[9]*4; tt = (u32*)off; tt = (u32*)((u8*)tt + pool);`
gives `adds r0,r0,r1`. (173fc, 26554)

### 9. Deferred-extend via u32 param + explicit asm shifts
ROM pattern: `lsls r2,r2,#24` at entry, `lsrs r2,r2,#19` at end (no `lsrs` at entry).
Achieve with u32 param (no auto-extend) + explicit:
```c
register u32 xx __asm__("r2") = x;
__asm__ volatile("lsl %0, %0, #24" : "+r" (xx));
// ... code ...
__asm__ volatile("lsr %0, %0, #19" : "+r" (xx));
```
(21c0c)

### 10. Pin p to r0 prevents copy
`register Node *pp __asm__("r0") = p;` prevents the compiler from copying p to
another register. (4bdc0)

### 11. `q[i] = t + 1` avoids r4 spill
vs `v += 1; q[i] = v` — the former keeps t in r0 as temp, the latter allocates
a live variable forcing r4+push/pop. (23b64)

### 12. Block-scoped variable forces r0 reload
```c
{
    u8 *b2 = *(u8 **)(p + 8);
    b2[bb] = tmp;
}
```
The new scope forces the compiler to use r0 for the reload instead of reusing r3. (25490)

### 13. Signed pool for `blt` vs `bcc`
If ROM has `blt` (signed) not `bcc`/`bcs` (unsigned), declare the pool as `int`
not `u32`. (3fa48)

### 14. Inverted if for `bhi`
`if (v <= 9) v+=1; else v+=0x54;` gives `bhi` (ROM) vs `if (v>9)` giving `bls`. (23b64)

### 15. u32 param avoids u8 extend
If ROM has no `lsls/lsrs` at entry for a byte param, declare it as `u32` and use
`(u8)x` at the store. (4acdc)

## Blocked

### F_2FC4C @ 0x0802fc4c (3-byte diff)
Final RMW: ROM has `ldrh r3,[r1,#10]; adds r0,r3,r2; strh r0,[r1,#10]`,
mine has `ldrh r0,[r1,#10]; adds r2,r0,r2; strh r2,[r1,#10]`.
Pinning tt to r3 did not help. Needs different approach.

### F_25230 @ 0x08025230 (60B)
Complex nested loop with non-standard control flow. The `q[0]==0xFF` pre-check
and the loop-back structure don't match standard do-while/for patterns.
Needs manual control-flow analysis.

## Notes
- The 26554/265b0/265d0 trio was also in wave11_B's batch; they landed first.
  Removed from my landing to avoid overlap. (Coordinator should dedupe.)
- All 23 landed functions verified at correct addresses via `arm-none-eabi-nm`.
- Build is green (`make` succeeds).
