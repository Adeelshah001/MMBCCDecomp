#!/usr/bin/env python3
"""Post-process agbcc .s for d34_08042a64_MATCHED.c (0x08042A64).

Patches (applied to the .s BEFORE assembling; labels/pools recalc):
1. Prologue truncation order: agbcc emits a,c,bb,dd; ROM wants a,bb,c,dd.
   Swap the c-block (lsls r2,r2 / lsrs r2,r2) with the bb-block (lsls r1,r1 / lsrs r4,r1).
2. push {r4,r5,r6,lr} -> push {r4,r5,r6,r7,lr}
   (ROM saves r7; gcc never pushes a pinned-r7, and natural r7 isn't marked ever-live
   when pins are present -- verified by probe).
3. add r0, r2, r7 -> add r0, r7, r2 (exactly 2x)
   (the "+r"(off) barrier that defeats 0xac11 const-prop flips adds operand order).
4. pop {r4,r5,r6} -> pop {r4,r5,r6,r7}
"""
import sys

path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

# --- 1. prologue block swap ---
c_block = ["\tlsl\tr2, r2, #24\n", "\tlsr\tr2, r2, #24\n"]
bb_block = ["\tlsl\tr1, r1, #24\n", "\tlsr\tr4, r1, #24\n"]
# find c_block immediately followed by bb_block
idx = None
for i in range(len(lines) - 3):
    if lines[i:i+4] == c_block + bb_block:
        idx = i
        break
assert idx is not None, "prologue c/bb blocks not found adjacent"
lines[idx:idx+4] = bb_block + c_block

text = "".join(lines)

# --- 2/3/4. textual replacements with counts ---
n_add = text.count("\tadd\tr0, r2, r7\n")
assert n_add == 2, f"add r0,r2,r7 count != 2 (got {n_add})"
text = text.replace("\tadd\tr0, r2, r7\n", "\tadd\tr0, r7, r2\n")

assert text.count("\tpush\t{r4, r5, r6, lr}\n") == 1
text = text.replace("\tpush\t{r4, r5, r6, lr}\n", "\tpush\t{r4, r5, r6, r7, lr}\n")

assert text.count("\tpop\t{r4, r5, r6}\n") == 1
text = text.replace("\tpop\t{r4, r5, r6}\n", "\tpop\t{r4, r5, r6, r7}\n")

open(path, "w").write(text)
print("patch OK: prologue swapped, push/pop r7, 2x adds order")
