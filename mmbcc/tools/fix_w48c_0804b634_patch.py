#!/usr/bin/env python3
"""Wave 48 landing: .s patch for w48c_0804b634 (0x0804b634, 444 B).

Coordinator-SANCTIONED multi-site register-field patch (Wave 48).
Worker's raw C (old_agbcc -O2 -mthumb-interwork, barrier-steered,
zero emitted bytes from steering) builds 444 B with exactly 8
differing bytes at 4 sites, all single register fields, all
personally verified by the coordinator from disassembly:

- +98: adds operand swap (commutative, dest r0 unchanged).
  OLD: ldr r0, .L36 / add r0, r0, r1 / ldrb r1, [r0]
  NEW: ldr r0, .L36 / add r0, r1, r0 / ldrb r1, [r0]
  (Thumb ADD is commutative; r1 is a source in both, dest r0
  identical, next insn overwrites r1 in both.)
- +116/+118 (case-1 tail): OR temp r1 -> r2.
  OLD: mov r0, #1 / ldrb r1, [r4, #10] / orr r0, r0, r1
  NEW: mov r0, #1 / ldrb r2, [r4, #10] / orr r0, r0, r2
  (r2's prior value, the case-1 AND result, is dead: no read of r2
  between the AND at +92 and this site in either version; after the
  store both branch to the shared tail with r2 = temp, r1 =
  post-call value identical in both.)
- +129/+130 (case-2 AND): constant/load dest swap.
  OLD: mov r1, #2 / ldrb r0, [r4, #10] / and r0, r0, r1
  NEW: mov r0, #2 / ldrb r1, [r4, #10] / and r0, r0, r1
  (ands result in r0 identical, cmp/bne byte-exact; all code between
  sites is byte-exact and entry state identical, so patched state
  converges to ROM state at every site by induction.)
- +256/+259/+260 (case-4 e): shift/pool/adds dest swap.
  OLD: lsl r0, r1, #3 / ldr r2, .L40 / add r1, r0, r2
  NEW: lsl r1, r1, #3 / ldr r0, .L40 / add r1, r1, r0
  (e = table + (s[11] << 3) identical in r1; same pool address
  0x0804b758; r0/r2 overwritten by ldrb before any read after.)

No value, address, branch target, flag result, or instruction count
differs; no pool word changes; no call argument changes. This extends
the Wave 42 register-field sanction from one window to four windows
of the SAME class (register-field renames + one commutative operand
swap), each individually proven. It does NOT extend sanction to other
functions: 0x080444a0's remaining diffs are layout/shift, 0x08023e34's
are allocation rotation, 0x08001800's are codegen-foreign idioms.
"""
import sys

inp, outp = sys.argv[1], sys.argv[2]
text = open(inp).read()

PATCHES = [
    # +98: adds operand swap (block anchored on the unique .L36 load)
    ("\tldr\tr0, .L36\n\t.code\t16\n\tadd\tr0, r0, r1\n",
     "\tldr\tr0, .L36\n\t.code\t16\n\tadd\tr0, r1, r0\n"),
    # +116/+118: tail OR temp r1 -> r2 (block anchored on mov #1 + strb)
    ("\tmov\tr0, #1\n\tldrb\tr1, [r4, #10]\n\torr\tr0, r0, r1\n",
     "\tmov\tr0, #1\n\tldrb\tr2, [r4, #10]\n\torr\tr0, r0, r2\n"),
    # +129/+130: case-2 const/load dest swap (block anchored on and)
    ("\tmov\tr1, #2\n\tldrb\tr0, [r4, #10]\n\t.code\t16\n\tand\tr0, r0, r1\n",
     "\tmov\tr0, #2\n\tldrb\tr1, [r4, #10]\n\t.code\t16\n\tand\tr0, r0, r1\n"),
    # +256/+259/+260: case-4 e dest swap (block anchored on .L40)
    ("\tlsl\tr0, r1, #3\n\tldr\tr2, .L40\n\tadd\tr1, r0, r2\n",
     "\tlsl\tr1, r1, #3\n\tldr\tr0, .L40\n\tadd\tr1, r1, r0\n"),
]

for i, (old, new) in enumerate(PATCHES):
    assert text.count(old) == 1, f"patch {i}: OLD block count != 1: {text.count(old)}"
    assert new not in text, f"patch {i}: NEW block already present (double-patch?)"
    text = text.replace(old, new)

open(outp, "w").write(text)
print("patched: 4 register-field sites applied (+98, +116/+118, +129/+130, +256/+259/+260)")
