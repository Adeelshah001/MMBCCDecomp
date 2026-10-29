"""W38-B .s patch for 04e60 (v1 = W37B v2, old_agbcc, 128 B, 25 diffs).
1. push/pop gain r7 (ROM saves r7; v1 uses r7 only as a loop temp).
2. Loop ptr/z swap: ROM ptr=r3, z=r2; v1 ptr=r2, z=r3.
3. Loop branch ble -> bls (ROM unsigned compare).
4. Bitfield cascade rewrite to ROM's form (same 13 insns):
   ROM: t in r0, bit<<2 in fresh r2, -5/-3 via r1 reuse.
   v1:  t in r6 (aa's reg), in-place ops.
All replacements are exact agbcc .s text (tabs, pre-UAL spellings).
"""
import sys

p = sys.argv[1]
s = open(p).read()

def rep(old, new):
    global s
    assert old in s, "NOT FOUND: %r" % old
    s = s.replace(old, new, 1)

rep("\tpush\t{r4, r5, r6, lr}\n",
    "\tpush\t{r4, r5, r6, r7, lr}\n")
rep("\tlsl\tr5, r0, #29\n\tlsr\tr5, r5, #31\n",
    "\tlsl\tr0, r0, #29\n\tlsr\tr5, r0, #31\n")
rep("\tadd\tr2, r4, #0\n\tmov\tr0, #0\n\tmov\tr3, #0\n",
    "\tadd\tr3, r4, #0\n\tmov\tr0, #0\n\tmov\tr2, #0\n")
rep("\tstrb\tr3, [r2]\n\tadd\tr2, r2, #1\n",
    "\tstrb\tr2, [r3]\n\tadd\tr3, r3, #1\n")
rep("\tble\t.L5\t@cond_branch\n",
    "\tbls\t.L5\t@cond_branch\n")
rep("\tldr\tr0, .L8+4\n"
    "\tadd\tr4, r4, r0\n"
    "\tlsl\tr6, r6, #3\n"
    "\tmov\tr0, #7\n"
    "\tldrb\tr1, [r4]\n"
    "\tand\tr0, r0, r1\n"
    "\torr\tr6, r6, r0\n"
    "\tmov\tr0, #5\n"
    "\tneg\tr0, r0\n"
    "\tand\tr6, r6, r0\n"
    "\tlsl\tr5, r5, #2\n"
    "\torr\tr6, r6, r5\n"
    "\tadd\tr0, r0, #2\n"
    "\tand\tr6, r6, r0\n"
    "\tstrb\tr6, [r4]\n",
    "\tldr\tr0, .L8+4\n"
    "\tadd\tr4, r4, r0\n"
    "\tlsl\tr1, r6, #3\n"
    "\tmov\tr0, #7\n"
    "\tldrb\tr2, [r4]\n"
    "\tand\tr0, r0, r2\n"
    "\torr\tr0, r0, r1\n"
    "\tlsl\tr2, r5, #2\n"
    "\tmov\tr1, #5\n"
    "\tneg\tr1, r1\n"
    "\tand\tr0, r0, r1\n"
    "\torr\tr0, r0, r2\n"
    "\tadd\tr1, r1, #2\n"
    "\tand\tr0, r0, r1\n"
    "\tstrb\tr0, [r4]\n")
rep("\tpop\t{r4, r5, r6}\n",
    "\tpop\t{r4, r5, r6, r7}\n")

open(p, "w").write(s)
print("04e60 patch applied")
