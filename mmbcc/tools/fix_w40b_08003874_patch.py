#!/usr/bin/env python3
"""Wave 40 landing wrapper: .s patch for w40b_08003874.
Replacement logic extracted VERBATIM from the worker's verified
in-place patch script; only the I/O was re-wired to argv in/out.
"""
import sys
s = open(sys.argv[1]).read()
def rep(old,new,tag):
    global s
    assert s.count(old)==1, f"{tag}: count={s.count(old)} for {old!r}"
    s=s.replace(old,new)
def rep_first(old,new,tag,expect):
    global s
    assert s.count(old)==expect, f"{tag}: count={s.count(old)} (expected {expect}) for {old!r}"
    s=s.replace(old,new,1)
# P1 prologue
rep("\tlsl\tr1, r1, #24\n\tadd\tr6, r0, #0\n\tlsr\tr1, r1, #24\n\tmov\tr9, r1\n",
    "\tadd\tr6, r0, #0\n\tlsl\tr1, r1, #24\n\tmov\tr9, r1\n\tmov\tr0, r9\n\tlsr\tr0, r0, #24\n\tmov\tr9, r0\n","P1")
# P2 entry b19
rep("\tldrb\tr0, [r6, #19]\n\tlsl\tr5, r0, #26\n",
    "\tldrb\tr1, [r6, #19]\n\tlsl\tr5, r1, #26\n","P2")
# P3 tbl pool scratch
rep("\tldr\tr1, .L3+4\n\tmov\tr8, r1\n",
    "\tldr\tr2, .L3+4\n\tmov\tr8, r2\n","P3")
# P4 block B b24: first occurrence only (block B precedes block C, which keeps r7)
rep_first("\tldrb\tr7, [r6, #24]\n\teor\tr1, r1, r7\n",
          "\tldrb\tr0, [r6, #24]\n\teor\tr1, r1, r0\n","P4",2)
# P5 block A b24
rep("\tldrb\tr2, [r6, #24]\n\teor\tr1, r1, r2\n",
    "\tldrb\tr7, [r6, #24]\n\teor\tr1, r1, r7\n","P5")
# P6 block A k (anchored by the following mov r3,#255, unique to block A)
rep("\tmov\tr7, r9\n\teor\tr0, r0, r7\n\tadd\tr0, r0, r1\n\tmov\tr3, #255\n",
    "\tmov\tr2, r9\n\teor\tr0, r0, r2\n\tadd\tr0, r0, r1\n\tmov\tr3, #255\n","P6")
# P7 final store
rep("\tmov\tr2, r9\n\tstrb\tr2, [r6, #27]\n",
    "\tmov\tr0, r9\n\tstrb\tr0, [r6, #27]\n","P7")
# P8 block B b19 temp: r0 -> r7 (FIRST occurrence only; blocks C/D keep r0).
# ROM uses r7 here because block B's upcoming b24 scratch is r0; C/D use r0
# because their b24 scratches are r7/r4. (Source-level r7 pin in B was avoided:
# v9 showed block-scoped pins cascade into later blocks' scratch choices.)
rep_first("\tldrb\tr0, [r6, #19]\n\tlsl\tr2, r0, #26\n",
          "\tldrb\tr7, [r6, #19]\n\tlsl\tr2, r7, #26\n","P8",3)
open(sys.argv[2], "w").write(s)
