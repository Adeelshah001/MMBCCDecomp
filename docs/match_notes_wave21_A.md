# Wave 21 Worker A notes — Task_3AFFC @ 0x0803AFFC (2026-10-23)

## Task_3AFFC @ 0x0803AFFC: MATCHED, 0 diffs (was 4), 932 B section, old_agbcc

Best source: `mmbcc/src/w21a_0803affc.c` (integrated; staging probes in
`staging/wave21_A/probes/w21_p0{1..7}.c`). Harness:
`staging/wave21_A/build_3affc_w21.sh` (wave20 harness, T=wave21_A).

### Result: 4 → 0 diffs (MATCHED)

The last 4 bytes — two mirrored contextual register preferences for the same
0x469d pool load — are solved by the **clobber-reservation idiom** (new,
generalizable). Built-ROM region 0x0803AFFC–0x0803B39F byte-identical to
baserom (932/932); neighbor sections intact (before identical; after is the
still-unmatched function at 0x0803B3A0, zero-filled, no overlap).

### The clobber-reservation idiom

Problem: case 14 wants `ldr r0` (ours had `ldr r2`); store6 wants `ldr r2`
(ours had `ldr r0`). Explicit register-variable pinning poisons global
allocation (W20: +8 B, 74 diffs — abandoned per standing evidence).

Solution: instead of pinning a register variable, deny the unwanted
register(s) with a volatile asm **clobber**, keeping the constant pseudo live
across the asm so the allocator must avoid the clobbered reg(s). Zero emitted
bytes, no pinned live range, no global perturbation:

```c
/* case 14: deny r2 -> allocator picks r0 */
u32 off = 0x469d;
__asm__ volatile ("" : : "r" (off) : "r2");
q = p + off;
__asm__ volatile ("" : : "r" (off));   /* keep off live past the add... */
v = *q;                                /* ...then die before the byte load */
*q = v + 1;

/* store6: deny r0 AND r1 -> allocator picks r2 */
off6 = 0x469d;
__asm__ volatile ("" : : "r" (off6) : "r0", "r1");
q6 = p + off6;
__asm__ volatile ("" : : "r" (off6));
*q6 = 6;
```

Why the second asm: with only the first, the `off` pseudo dies at the address
add and the allocator **coalesces** the add dest into its register
(`add r0,r4,r0` instead of `add r1,r4,r0`), cascading into wrong downstream
regs and losing the shared-`strb` tail-merge (p01: 77 diffs). Keeping `off`
live past the add (second asm use) kills the coalescing; it then dies before
the `ldrb`/`strb` so those reuse r0/r1 normally and the `.L54: strb r0,[r1]`
tail-sharing survives.

Why clobber beats pinning: a clobber creates no pseudo and no live range —
it only removes reg(s) from consideration for pseudos live across that exact
insn. The effect is surgical; the rest of the function is untouched
(verified: only the 4 target bytes changed vs W20 best).

Data points:
- p01 (case14, clobber "r2" only, `p[off]++`): load steered to r0 ✓ but
  coalescing broke downstream → 77 diffs.
- p02 (store6, clobber "r0" only): allocator's next preference is r1
  (`ldr r1`), not r2 → 4 diffs (wrong 2).
- p04 (case14 + liveness-extension): **0 diffs** (case 14 solved).
- p05 (store6, braces around label): 848 B — goto-into-block confuses old
  GCC (same failure mode as W20's `u8 v = 6` probe). Fixed by declaring the
  temps at function scope, no braces.
- p06 (store6, deny r0+r1, single asm): `ldr r2` ✓ but coalesced
  (`add r2,r4,r2`) → 924 B.
- p07 (both fixes): **928/928 zero-diff** on the harness window; pool word
  at +0x3A0 verified separately → MATCHED.

### Size note

The harness's "928 B" is the compare window. The true ROM footprint is
**932 B**: 926 code + 2 pad + 4 pool word (0x469d at +0x3A0, referenced by
store6's `ldr r2,[pc,#20]`; next function starts at +0x3A4). The section is
already exactly 932 B — **no FIXALIGN1 needed** (verified: section size
0x3A4, bytes 0x0803AFFC–0x0803B39F identical).

### Integration

- `mmbcc/src/w21a_0803affc.c` (section `.text.w21a_0803affc`)
- `mmbcc/Makefile`: SRCS_C += src/w21a_0803affc.c; per-file old_agbcc rule
  (no FIXALIGN1 sed)
- `mmbcc/ldscript.ld`: `. = 0x0803AFFC; .text.w21a_0803affc : {
  build/w21a_0803affc.o (.text.w21a_0803affc); }`
- `docs/match_status.tsv`: MATCHED row appended (6th row for 0x0803affc)
- Clean full rebuild → link OK → built-ROM region diff 932/932 identical;
  neighbor check OK.

### Drive-by fix (pre-existing, blocking the build)

`src/w21c_08043630.c` (Wave 21-C) failed to link: `undefined reference to
sub_08005A9C`. Root cause: the `.set` in `src/wave7_b.c` is a **LOCAL**
absolute symbol (invisible outside wave7_b.o), and `src/wave4_f.c` (which has
the `.globl` version) is not in SRCS_C. The file's comment ("no .set here")
was wrong. Fix: added a file-local `__asm__(".set sub_08005A9C,
0x08005A9C")` to w21c_08043630.c. Zero code change; link now succeeds.
Coordinator may want to confirm with the Wave 21-C worker.

### Recommendations

1. The clobber-reservation idiom generalizes: to deny register R at a point,
   birth the pseudo before `asm volatile("" : : "r"(pseudo) : "R", ...)` and
   keep it live across. Deny the registers you do NOT want (not the one you
   want). Add the second liveness asm if dest coalescing appears.
2. The "928 B" in earlier notes is the harness window; true size is 932 B.
   Future workers: compare the full section including trailing pool.
3. `make -j` can race the link before all objects build (rom_header.o);
   serial `make` after is fine.
