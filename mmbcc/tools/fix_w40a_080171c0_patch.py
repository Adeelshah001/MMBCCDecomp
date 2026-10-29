#!/usr/bin/env python3
"""W40-A patch for 0x080171c0 (old_agbcc build of w40a_080171c0.c).
Usage: w40a_080171c0_patch.py IN.s OUT.s
Three regions, all verified against ROM bytes (LE pool words N/A here):
(a) case-2 sc&3 sum temp: ROM keeps the sum in a fresh r1 and truncates
    into r4 (ands r1,r0; adds r1,r4,r1; lsls r1; lsrs r4); gcc adds into
    r4 in place. Same instruction count (5).
(b) case-2 d-ternary: ROM's shifted form (lsls; negs; shared lsrs join);
    gcc emits neg-then-truncate + copy. Same instruction count (9).
(d) Path-B follow copies: ROM loads cur/tgt into r0/r1, subs d into r3,
    then copies cur->r4, tgt->r2 (other dead after tgt load); gcc loads
    directly into r3/r2. Adds 2 instructions (4 bytes) -- this is the
    504->508 size gap. Step block cur register renamed r3->r4 to match.
(c) Path-B entry copy (adds r1,r4 / adds r0,r1) already matches in the claim C.
"""
import sys

def rep(s, old, new, name):
    assert old in s, f"patch region {name} not found"
    assert s.count(old) == 1, f"patch region {name} not unique"
    return s.replace(old, new)

def main():
    src = open(sys.argv[1]).read()
    # (a)
    src = rep(src,
        "\tmov\tr1, #3\n\tand\tr0, r0, r1\n\tadd\tr4, r4, r0\n"
        "\tlsl\tr4, r4, #16\n\tlsr\tr4, r4, #16\n",
        "\tmov\tr1, #3\n\tand\tr1, r1, r0\n\tadd\tr1, r4, r1\n"
        "\tlsl\tr1, r1, #16\n\tlsr\tr4, r1, #16\n", "a")
    # (b)
    src = rep(src,
        "\tand\tr1, r1, r6\n\tcmp\tr1, #0\n\tbne\t.L33\t@cond_branch\n"
        "\tneg\tr0, r4\n\tlsl\tr0, r0, #16\n\tlsr\tr0, r0, #16\n\tb\t.L34\n"
        ".L33:\n\tadd\tr0, r4, #0\n.L34:\n\tadd\tr4, r0, #0\n",
        "\tand\tr1, r1, r6\n\tcmp\tr1, #0\n\tbne\t.L33\t@cond_branch\n"
        "\tlsl\tr0, r4, #16\n\tneg\tr0, r0\n\tb\t.L34\n"
        ".L33:\n\tlsl\tr0, r4, #16\n.L34:\n\tlsr\tr0, r0, #16\n\tadd\tr4, r0, #0\n", "b")
    # (d) follow loads + d + copies
    src = rep(src,
        ".L39:\n\tldr\tr3, [r5, #80]\n\tldr\tr2, [r4, #80]\n"
        "\tsub\tr1, r3, r2\n\tcmp\tr1, #0\n\tblt\t.L40\t@cond_branch\n"
        "\tmov\tr0, #128\n\tlsl\tr0, r0, #1\n\tcmp\tr1, r0\n",
        ".L39:\n\tldr\tr0, [r5, #80]\n\tldr\tr1, [r4, #80]\n"
        "\tsub\tr3, r0, r1\n\tadd\tr4, r0, #0\n\tadd\tr2, r1, #0\n"
        "\tcmp\tr3, #0\n\tblt\t.L40\t@cond_branch\n"
        "\tmov\tr0, #128\n\tlsl\tr0, r0, #1\n\tcmp\tr3, r0\n", "d1")
    # (d) tgt-cur check
    src = rep(src,
        ".L40:\n\tsub\tr1, r2, r3\n",
        ".L40:\n\tsub\tr1, r2, r4\n", "d2")
    # (d) step block cur register
    src = rep(src,
        "\tsub\tr0, r0, r3\n",
        "\tsub\tr0, r0, r4\n", "d3")
    src = rep(src,
        "\tadd\tr0, r3, r0\n\tstr\tr0, [r5, #80]\n",
        "\tadd\tr0, r4, r0\n\tstr\tr0, [r5, #80]\n", "d4")
    open(sys.argv[2], "w").write(src)

if __name__ == "__main__":
    main()
