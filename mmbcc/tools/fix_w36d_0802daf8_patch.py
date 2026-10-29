#!/usr/bin/env python3
"""Post-process old_agbcc .s for w36d_0802daf8 (0x0802daf8).
Patch 1 (dispatch): gcc folds `sb < 960` to `sb <= 959` (subs 3, ble);
  ROM keeps `sb < 960` (subs 2, blt). Change subs #3->#2 and ble->blt.
Patch 2 (check70): ROM has only `lsls r0,24` before the movs/cmp
  (lsls alone suffices for the ==0 test); agbcc emits lsls+lsrs for the
  u8 res variable. Delete the lsrs line (the trailing pad object in the
  C file restores the 140 B extent).
"""
import sys
path = sys.argv[1]
lines = open(path).read().splitlines(keepends=True)
# Patch 1
done1 = False
for i in range(len(lines) - 1):
    if (lines[i].strip() == "sub\tr0, r0, #3"
        and lines[i+1].strip().startswith("cmp\tr4, r0")):
        lines[i] = "\tsub\tr0, r0, #2\n"
        for j in range(i+1, min(i+4, len(lines))):
            if lines[j].strip().startswith("ble\t"):
                lines[j] = lines[j].replace("ble\t", "blt\t")
                done1 = True
                break
        break
assert done1, "patch 1 not found"
# Patch 2: delete the lsrs after the check70 lsls (the one followed by mov r6,#7)
done2 = False
for i in range(len(lines) - 2):
    if (lines[i].strip() == "lsl\tr0, r0, #24"
        and lines[i+1].strip() == "lsr\tr0, r0, #24"
        and lines[i+2].strip() == "mov\tr6, #7"):
        del lines[i+1]
        done2 = True
        break
assert done2, "patch 2 not found"
open(path, "w").writelines(lines)
print("patch OK: dispatch + check70 lsrs deleted")
