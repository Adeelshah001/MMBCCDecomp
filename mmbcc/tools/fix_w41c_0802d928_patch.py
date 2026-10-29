#!/usr/bin/env python3
"""Wave 41 landing wrapper: .s patch for w41c_0802d928 (0x0802d928, 464 B).
Patch logic extracted VERBATIM from the worker's verified patch script;
only the I/O was re-wired to argv in/out (Makefile convention).
(1) register-rename r4->r5, r5->r6, r6->r4, EXCEPT save/restore lines.
(2) tree-node beq: replace `bne .LCBxx; b .Lyy` pairs with single `beq .Lyy`.
(3) trailing `.align 2,0` after `bx r1` so pad bytes are 00 00 like ROM.
"""
import re, sys
skip = [re.compile(p) for p in [
    r"^\s*push\s*\{r4,\s*r5,\s*r6,\s*r7,\s*lr\}",
    r"^\s*mov\s*r6,\s*r8\s*$",
    r"^\s*push\s*\{r6,\s*r7\}",
    r"^\s*pop\s*\{r3,\s*r4\}",
    r"^\s*mov\s*r9,\s*r4\s*$",
    r"^\s*pop\s*\{r4,\s*r5,\s*r6,\s*r7\}",
]]
def rename(line):
    if any(p.search(line) for p in skip): return line
    line = re.sub(r"\br4\b", "TMP4", line)
    line = re.sub(r"\br5\b", "TMP5", line)
    line = re.sub(r"\br6\b", "TMP6", line)
    return line.replace("TMP4", "r5").replace("TMP5", "r6").replace("TMP6", "r4")
def tree_patch(lines):
    out = []
    i = 0
    patched = 0
    while i < len(lines):
        if (i + 1 < len(lines)
            and lines[i].strip() == "bne\t.LCB79"
            and lines[i+1].strip().startswith("b\t.L33")):
            out.append("\tbeq\t.L33\t@cond_branch\n"); i += 2; patched += 1; continue
        if (i + 1 < len(lines)
            and lines[i].strip() == "bne\t.LCB92"
            and lines[i+1].strip().startswith("b\t.L41")):
            out.append("\tbeq\t.L41\t@cond_branch\n"); i += 2; patched += 1; continue
        out.append(lines[i]); i += 1
    print(f"tree_patch: replaced {patched} bne+b pairs with beq")
    assert patched >= 1, f"expected >=1 tree patches, got {patched}"
    return out
s = open(sys.argv[1]).read()
renamed = [rename(l) for l in s.splitlines(True)]
treep = tree_patch(renamed)
out = []
for j, l in enumerate(treep):
    out.append(l)
    if l.strip() == "bx\tr1" and j + 1 < len(treep) and treep[j+1].startswith(".Lfe1:"):
        out.append("\t.align\t2, 0\n")
open(sys.argv[2], "w").write("".join(out))
print("w41c_0802d928 patch applied (reg-rename + tree beq + trailing align)")
