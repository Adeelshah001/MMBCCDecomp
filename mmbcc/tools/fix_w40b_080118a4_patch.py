#!/usr/bin/env python3
"""Wave 40 landing wrapper: .s patch for w40b_080118a4.
Replacement logic extracted VERBATIM from the worker's verified
in-place patch script; only the I/O was re-wired to argv in/out.
"""
import sys
s = open(sys.argv[1]).read()
def rep(old,new,tag):
    global s
    assert s.count(old)==1, f"{tag}: count={s.count(old)} for {old!r}"
    s=s.replace(old,new)
# P1 arg-order
rep("\tadd\tr2, r0, #0\n\tadd\tr0, r4, #0\n\tldr\tr1, [r5]\n\tldrb\tr1, [r1, #19]\n\tldr\tr3, [sp, #12]\n\tldr\tr4, [sp, #16]\n\tstr\tr4, [sp]\n\tldr\tr4, [sp, #20]\n\tstr\tr4, [sp, #4]\n\tbl\tSub_08010FDC\n",
    "\tadd\tr2, r0, #0\n\tldr\tr0, [r5]\n\tldrb\tr1, [r0, #19]\n\tldr\tr3, [sp, #12]\n\tldr\tr0, [sp, #16]\n\tstr\tr0, [sp]\n\tldr\tr0, [sp, #20]\n\tstr\tr0, [sp, #4]\n\tadd\tr0, r4, #0\n\tbl\tSub_08010FDC\n","P1")
# P2 &8 beq retarget: beq .L10 (the &8 test) -> new label after trunc
rep("\tbeq\t.L10\t@cond_branch\n\tmov\tr0, #64\n\torr\tr4, r4, r0\n.L10:\n\tlsl\tr0, r4, #24\n\tlsr\tr4, r0, #24\n\tldrh\tr0, [r2, #20]\n",
    "\tbeq\t.L10b\t@cond_branch\n\tmov\tr0, #64\n\torr\tr4, r4, r0\n.L10:\n\tlsl\tr0, r4, #24\n\tlsr\tr4, r0, #24\n.L10b:\n\tldrh\tr0, [r2, #20]\n","P2")
# P3 success block
rep("\tstr\tr1, [r5]\n\tmov\tr0, #1\n\tstrb\tr0, [r5, #4]\n\tmov\tr0, #0\n\tstrb\tr0, [r5, #5]\n\tstrb\tr0, [r5, #6]\n\tstrb\tr0, [r5, #7]\n",
    "\tstr\tr1, [r5]\n\tmov\tr1, #0\n\tmov\tr0, #1\n\tstrb\tr0, [r5, #4]\n\tstrb\tr1, [r5, #5]\n\tstrb\tr1, [r5, #6]\n\tstrb\tr1, [r5, #7]\n","P3")
# P4 clear_inc (.L14 block)
rep(".L14:\n\tldrb\tr0, [r5, #4]\n\tadd\tr0, r0, #1\n\tstrb\tr0, [r5, #4]\n\tmov\tr0, #0\n\tstrb\tr0, [r5, #5]\n\tstrb\tr0, [r5, #6]\n\tstrb\tr0, [r5, #7]\n",
    ".L14:\n\tldrb\tr1, [r5, #4]\n\tadd\tr1, r1, #1\n\tmov\tr0, #0\n\tstrb\tr1, [r5, #4]\n\tstrb\tr0, [r5, #5]\n\tstrb\tr0, [r5, #6]\n\tstrb\tr0, [r5, #7]\n","P4")
open(sys.argv[2], "w").write(s)
