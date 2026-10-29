#!/usr/bin/env python3
"""Wave 49 Worker C -- PROPOSED (NOT sanctioned) .s patch for the
0x08041fbc / 0x080420d0 / 0x080421e4 triple (each 276 B).

Raw C (old_agbcc -O2 -mthumb-interwork, v12 files in this dir) builds
276 B with exactly 10 differing bytes at 4 sites, IDENTICAL for all
three functions (verified: same relative offsets, same byte values).
One patch script serves all three .s files: their .s text is identical
except the function name and the mode-1 table .word
(0x08232b1c / 0x08232b34 / 0x08232b4c).

EQUIVALENCE PROOF, site by site, from built + ROM disassembly
(offsets are function-relative; entry state identical -- prologue is
byte-exact -- and all code between sites is byte-exact, so patched
state converges to ROM state at every site by induction; no value,
address, branch target, flag result, or instruction count differs):

Site A -- mode-1 table window, +138..+141 (W47 sanctioned class:
order-swap; here a PURE reorder, no rename).
  OLD: lsl r0,#24 / lsr r0,#22 / ldr r1,[pc] / add r0,r0,r1
  NEW: lsl r0,#24 / ldr r1,[pc] / lsr r0,#22 / add r0,r0,r1
  (1) ldr writes only r1, lsr writes only r0; neither touches
  memory; the ldr address is PC-relative and both positions target
  the SAME pool word (built ldr at +0x8c [pc,#16] -> 0xa0; patched
  ldr at +0x8a [pc,#20] -> 0xa0; pool word = mode-1 table base).
  (2) Flags: lsr sets flags in both orders; ldr touches no flags;
  the following add does not read flags, so final flags are the
  lsr result in both versions. (3) The add and the following
  ldr r0,[r0] are byte-identical in both versions. This is the same
  window the Wave 47 coordinator sanctioned for the 44630/4472c
  twins (there with a rename; here reorder-only, strictly narrower).

Site B -- case-2 increment-load temp, +175/+176 (W42 class:
register-field rename r0 -> r2).
  OLD: ldr r0,[pc] / add r1,r4,r0
  NEW: ldr r2,[pc] / add r1,r4,r2
  (1) Both ldrs target the same pool word 0x46ad (built +0xae
  [pc,#4] -> 0xb4; ROM +0xae [pc,#4] -> 0xb4), so r1 = s+0x46ad
  identically. (2) The temp is dead after the add in both versions:
  built r0 is overwritten by the shared body's ldrb r0,[r1] before
  any read; ROM r2 is never read on the case-2 path (b body, then
  b ret; the next r2 use anywhere is case 4's mov r2,#0, an
  overwrite). (3) Entry state identical (r4 = s; r0 = tested value,
  dead after the beq). (4) add result, flags, and all downstream
  bytes identical.

Site C -- case-3 increment-load temp, +195/+196 (W42 class:
register-field rename r2 -> r0).
  OLD: ldr r2,[pc] / add r1,r4,r2
  NEW: ldr r0,[pc] / add r1,r4,r0
  (1) Same pool word 0x46ad (built +0xc2 [pc,#12] -> 0xd0; ROM
  +0xc2 [pc,#12] -> 0xd0); r1 identical. (2) Temp dead after the
  add in both versions: built r2 never read on this path (body uses
  r1/r0 only; next r2 use is case 4's mov r2,#0 overwrite); ROM r0
  overwritten by the body's ldrb r0,[r1] before any read. (3) The
  shared test block is entered from case 1 (b .L20) and case 3
  (fallthrough) in both versions with r0 = tested value, dead after
  the beq -- so r0 is free for the load in both entries. (4) add
  result and flags identical.

Site D -- case-4 first-load temp, +223/+224 (W42 class:
register-field rename r0 -> r2).
  OLD: ldr r0,[pc] / add r1,r4,r0
  NEW: ldr r2,[pc] / add r1,r4,r2
  (1) Same pool word 0x46ac (built +0xde [pc,#40] -> 0x108; ROM
  +0xde [pc,#40] -> 0x108); r1 identical. (2) Temp dead after the
  add in both versions: built r0 overwritten by the immediately
  following mov r0,#10 before any read; ROM r2 overwritten by the
  immediately following mov r2,#0 before any read. (3) The rest of
  case 4 (second load, stores, ldrsb pair, call) is byte-identical.

No pool word changes; no call argument changes; no branch retargets
(no branch instruction sits in any window); instruction count
unchanged at every site (1:1 swaps). The patch does NOT extend to
any other function: it is scoped to these three .s files, whose raw
C already matches everywhere else.

STATUS: PROPOSED by Worker C, Wave 49. Sanction decision belongs to
the Wave 49 coordinator (not claimed as pure C, not landed).
Dress rehearsal (this dir): apply to each v12 .s, assemble, link
with -Ttext at the function address, objcopy, compare vs baserom
extent -> 0 diffs for all three (see RESULTS.md).
"""
import sys

inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()

PATCHES = [
    # Site A: mode-1 window reorder (anchored on the TblGetByte_24384 call + subs)
    ("\tbl\tTblGetByte_24384\n\tsub\tr0, r0, #50\n\tlsl\tr0, r0, #24\n\tlsr\tr0, r0, #22\n\tldr\tr1, .L25\n\tadd\tr0, r0, r1\n",
     "\tbl\tTblGetByte_24384\n\tsub\tr0, r0, #50\n\tlsl\tr0, r0, #24\n\tldr\tr1, .L25\n\tlsr\tr0, r0, #22\n\tadd\tr0, r0, r1\n"),
    # Site B: case-2 load temp r0 -> r2 (anchored on Check_B308 call)
    ("\tbl\tCheck_B308\n\tlsl\tr0, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L6\t@cond_branch\n\tldr\tr0, .L27\n\tadd\tr1, r4, r0\n",
     "\tbl\tCheck_B308\n\tlsl\tr0, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L6\t@cond_branch\n\tldr\tr2, .L27\n\tadd\tr1, r4, r2\n"),
    # Site C: case-3 load temp r2 -> r0 (anchored on CheckAndSet_B2B4 + .L20)
    ("\tbl\tCheckAndSet_B2B4\n.L20:\n\tlsl\tr0, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L6\t@cond_branch\n\tldr\tr2, .L29\n\tadd\tr1, r4, r2\n",
     "\tbl\tCheckAndSet_B2B4\n.L20:\n\tlsl\tr0, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L6\t@cond_branch\n\tldr\tr0, .L29\n\tadd\tr1, r4, r0\n"),
    # Site D: case-4 first-load temp r0 -> r2 (anchored on Tst_0800B2F0 call)
    ("\tbl\tTst_0800B2F0\n\tlsl\tr0, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L6\t@cond_branch\n\tldr\tr0, .L31\n\tadd\tr1, r4, r0\n",
     "\tbl\tTst_0800B2F0\n\tlsl\tr0, r0, #24\n\tcmp\tr0, #0\n\tbeq\t.L6\t@cond_branch\n\tldr\tr2, .L31\n\tadd\tr1, r4, r2\n"),
]

for i, (old, new) in enumerate(PATCHES):
    assert text.count(old) == 1, f"patch {i}: OLD block count != 1: {text.count(old)}"
    assert new not in text, f"patch {i}: NEW block already present (double-patch?)"
    text = text.replace(old, new)

open(outp, "w").write(text)
print("patched: 4 sites applied (mode-1 reorder + 3 register-field renames)")
