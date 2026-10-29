#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_08046960 (0x08046960).
ROM order: check (lsl/cmp/beq end, fallthrough inc), inc (ldrb/add/strb/b end),
  case3 (fallthrough end), end. agbcc: check (lsl/cmp/bne inc/b end),
  case3 (..., b end), inc (fallthrough end), end.
Patch: check bne->beq end, delete check's b; move inc block before case3
  (adding its trailing b end); delete case3's b end. Net -2 code bytes
  (142 -> 140, and the GAS nop fill disappears).
"""
import sys
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)

def find(pred, start=0):
    for i in range(start, len(lines)):
        if pred(lines[i].strip()):
            return i
    return -1

# Check block: after ".L17:" -> lsl, cmp, bne .L6, b .L16
i = find(lambda s: s == ".L17:")
assert i >= 0
assert lines[i+1].strip() == "lsl\tr0, r0, #24"
assert lines[i+2].strip() == "cmp\tr0, #0"
assert lines[i+3].strip().startswith("bne\t")
assert lines[i+4].strip() == "b\t.L16"
lines[i+3] = "\tbeq\t.L16\n"
del lines[i+4]
# Inc block .L6: ldrb, add, strb (3 lines, no trailing b since it fell through)
j = find(lambda s: s == ".L6:")
assert j >= 0
assert lines[j+1].strip() == "ldrb\tr0, [r4]"
assert lines[j+2].strip() == "add\tr0, r0, #1"
assert lines[j+3].strip() == "strb\tr0, [r4]"
inc_block = lines[j:j+4]
# Delete the .L6 label + block (will be re-inserted before case3)
del lines[j:j+4]
# Case3's trailing b .L16: after "strb r1, [r4]" (flag=0 store)
k = find(lambda s: s == "strb\tr1, [r4]")
assert k >= 0
assert lines[k+1].strip() == "b\t.L16"
del lines[k+1]
# Insert inc block (with trailing b .L16) before ".L11:" (case3)
m = find(lambda s: s == ".L11:")
assert m >= 0
lines[m:m] = inc_block + ["\tb\t.L16\n"]
open(path, "w").writelines(lines)
print("patch OK: check beq + inc moved + case3 b deleted")
