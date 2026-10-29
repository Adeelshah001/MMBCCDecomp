#!/usr/bin/env python3
"""Wave 53-A sanction-candidate .s patch for 0x0800BFD0 (coordinator sanction
pending). Raw C: w53a_0800bfd0_e_both7.c, old_agbcc -O2 -mthumb-interwork,
232 B exact / 5 diffs. The patch renames two dead compiler temps to ROM's
registers; it changes no instruction, no pool word, no branch target, and
no call argument (full site-by-site case in RESULTS.md):

  Site A (inner-const pool temp, +141/+142):
    OLD: ldr r7, .L16+28 / add r6, r7, #0
    NEW: ldr r0, .L16+28 / add r6, r0, #0
    Same pool word (imm byte 0x15 unchanged); same r6 value (0x2001) and
    same adds flags. Temp dead after the adds in both versions (built r7
    next written by ldrh r7,[r3]; ROM r0 next written by adds r0,r6,r7).

  Site B (outer-increment const temp, +171/+172/+175):
    OLD: mov r7, #128 / lsl r7, r7, #9 / add r0, r2, r7
    NEW: mov r3, #128 / lsl r3, r3, #9 / add r0, r2, r3
    Same const value (0x10000), same adds result and flags. Temp dead
    after the adds in both versions; r3 is sp in the built source, but
    sp is dead at the outer increment (last use: inner-loop ldrh/adds)
    and is recomputed (mov r3,r8; add r3,ip; adds #8) before any read
    on the next iteration, and never read on the exit path (pop
    restores callee-saved regs; r3 itself is caller-saved scratch).

Twins pattern: each OLD block is asserted to occur exactly once and
each NEW block asserted absent, so the script refuses double-patching.
The .set lines are left untouched (standalone link resolves them).
Usage: python3 w53a_0800bfd0_patch.py <in.s> <out.s>
"""
import sys

inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()

old_a = "\tldr\tr7, .L16+28\n\tadd\tr6, r7, #0\n"
new_a = "\tldr\tr0, .L16+28\n\tadd\tr6, r0, #0\n"
old_b = "\tmov\tr7, #128\n\tlsl\tr7, r7, #9\n\tadd\tr0, r2, r7\n"
new_b = "\tmov\tr3, #128\n\tlsl\tr3, r3, #9\n\tadd\tr0, r2, r3\n"

assert text.count(old_a) == 1, f"Site A OLD count != 1: {text.count(old_a)}"
assert new_a not in text, "Site A NEW already present (double-patch?)"
assert text.count(old_b) == 1, f"Site B OLD count != 1: {text.count(old_b)}"
assert new_b not in text, "Site B NEW already present (double-patch?)"

text = text.replace(old_a, new_a).replace(old_b, new_b)
open(outp, "w").write(text)
print("w53a 0800bfd0 patch applied: Site A (pool temp r7->r0), "
      "Site B (outer temp r7->r3)")
