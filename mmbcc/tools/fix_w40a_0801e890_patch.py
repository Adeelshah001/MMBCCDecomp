#!/usr/bin/env python3
"""W40-A patch for 0x0801e890 (old_agbcc build of w40a_0801e890.c).
Usage: w40a_0801e890_patch.py IN.s OUT.s
Four small regions, all verified against ROM bytes:
(sv) case setup: ROM computes 1024 into r3 then copies to r1
    (movs r3,#128; lsls r3,#3; adds r1,r3); gcc puts 1024 in r1
    directly. Inserts the copy (+2 bytes) -- this is the 170->172
    size gap; the following pool alignment then matches ROM.
(off1) setup off-add operand order: ROM adds r0,r0,r1; gcc (with the
    off pin lineage) emits adds r0,r1,r0. Same size.
(off2/idx) IncUse block: ROM reloads s[16] into r1 and adds
    r0,r0,r1; gcc loads into r2 and adds r0,r2,r0. Same size.
(pool) clamp table pool: ROM loads 0x020031e4 into r1; gcc loads
    into r3. Same size.
Everything else in the o3s build already matches ROM instruction
for instruction (first block, s[10], s[69], s[34], tail).
"""
import sys

def rep(s, old, new, name):
    assert old in s, f"patch region {name} not found"
    assert s.count(old) == 1, f"patch region {name} not unique"
    return s.replace(old, new)

def main():
    src = open(sys.argv[1]).read()
    src = rep(src,
        "\tldrb\tr1, [r6, #16]\n\tlsl\tr0, r1, #1\n\tadd\tr0, r1, r0\n",
        "\tldrb\tr1, [r6, #16]\n\tlsl\tr0, r1, #1\n\tadd\tr0, r0, r1\n", "off1")
    src = rep(src,
        "\tmov\tr1, #128\n\tlsl\tr1, r1, #3\n",
        "\tmov\tr3, #128\n\tlsl\tr3, r3, #3\n\tadd\tr1, r3, #0\n", "sv")
    src = rep(src,
        "\tldrb\tr2, [r6, #16]\n\tlsl\tr0, r2, #1\n\tadd\tr0, r2, r0\n",
        "\tldrb\tr1, [r6, #16]\n\tlsl\tr0, r1, #1\n\tadd\tr0, r0, r1\n", "off2")
    src = rep(src,
        "\tldr\tr3, .L4+12\n\tadd\tr0, r0, r3\n",
        "\tldr\tr1, .L4+12\n\tadd\tr0, r0, r1\n", "pool")
    open(sys.argv[2], "w").write(src)

if __name__ == "__main__":
    main()
