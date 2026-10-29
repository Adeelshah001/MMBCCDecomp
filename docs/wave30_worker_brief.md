# Wave 30 Worker Brief (read FIRST)

You are a Wave 30 worker for the MMBCC matching-decomp project at
~/workspace/mmbcc-decomp/. Baserom (user's own legal dump, READ-ONLY):
~/workspace/megaman-bcc-recomp/rom/Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba
SHA-1 must be 72309736f3820470c6f372d6a05ad1f16bc5a946 — verify before starting.

## Hard verification protocol (no exceptions)
1. Every match claim: clean-room recompile (exact compiler + flags) → link at the
   TRUE ROM address with a custom .ld (explicit SECTIONS — `--section-start`
   alone FAILS: ld merges .text.*) → objcopy → `cmp` vs baserom extract at
   file offset (addr − 0x08000000), exact byte counts, full extents incl. pools.
2. Non-empty assertions at every step (.o, .elf, .bin, rom extract all non-empty).
3. Neighbor check: byte-diff the function before/after in the built ROM.
4. **Check docs/match_status.tsv BEFORE any claim** — duplicates get reverted.
   Registry is append-only (REVERTED rows for retractions).
5. MATCHED = 0 diffs verified by build+diff. Near-matches are UNMATCHED.
6. **DO-NOT-LAND rule:** stage your matched C in `staging/wave30_X/` — only the
   coordinator lands into mmbcc/src/ after independent verification.
7. Toolchain: agbcc @da598c1 + old_agbcc variant; arm-none-eabi binutils 2.42
   (exact GAS 2.42 match; reinstall from ~/workspace/mmbcc-decomp/tools/host/
   .deb if vanished). Makefile sed needs `$$` escaping.

## Idiom catalog (Wave 0–29; full notes in docs/)
volatile VCOUNT re-reads, write-posting (void) reads, (baseReg -= const)
anti-folding, asm volatile barriers, extern-absolute-symbol idiom, tail-pad
idiom, absolute-base-to-local, two-statement base, no-interwork pop{pc}
epilogues, SUBALIGN, BYTE() fragments, GAS 2.42 .set ordering, runtime mask
negation, branchless bit-select, old_agbcc dispatcher shape, intra-function
bl as long branch, combiner dest-register rule, old_agbcc for instruction
order, split-adds anti-folding, pinning + inline-asm scratch regs,
sign-extension forcing, double-OR constant-first, opaque register copy,
literal-0 vs named-zero, goto-beq, ((u32)v<<22)>>28, agbcc jump-table
layout, pinned register __asm__ idx + opaque asm, opaque OR-constants,
ordered materialization via single asm, memory barrier vs combiner fold,
opaque ldrb init, tied-opaque pool loads, volatile-asm prologue sequencing,
cross-register shift asm, goto dual-bhi, int sxr=xr signed-copy, explicit
u8 *tbl forces pool ldr before lsrs, int v=*(u16*)p → ldrh+bgt, goto
decision-trees, barrier-before-copy, dummy asm inputs for ordering,
volatile mvn/neg vs fusion, late empty-asm copy barrier, int lo = 0x30
variable-constant, old_agbcc branched-leaf bx lr, s16-param HI-normalized,
pure-u32 address arithmetic, pool-load hoisting fix, CSE beats temp, pinned
COPY registers force in-place allocation, volatile u16 forces per-access
stack traffic, divided-syntax inline asm forces operand order, non-empty
asm shift templates, pinned constant in loop defeating LICM, r7-pin
miscompile fix, u16 increment idiom, widened int temps, pinned-r0 zero vs
CSE, late pool materialization, (u32)(s8) temp, int-decl callee, goto-ladder,
opaque adds copy, c24-unpin idiom, t30-reuse mask idiom, deferred-zero
variable, explicit-q ordering, jump-terminated cross-jumping, u8 z=0
zero-materialization ordering, FIXALIGN1, goto store6 tail-sharing, two-step
ldrh, goto-to-late-label idiom, never pin r7 (context-dependent),
sibling-shape transfer, no-arg prototype for arg-ignoring thunks, shift-first
u8 increment, pool-control strategy, pinned-constant + empty-asm scheduling
barrier, non-void-no-return → pop {r1} epilogue, split-shift interleave via
dual barriers, scoped register-denial, early-zero materialization,
index-as-pointer adds ordering, pinned-barrier for pool loads, u32 pin to
pushed callee-saved reg is safe (r7 only miscompile), volatile forces
redundant loads, dead-register reuse via pin + reassign, natural u8 temp,
pin-one-forces-another, mid-function pool via .short nop, pinned base
prevents folding, divided-syntax add ordering, clobber-reservation,
trailing-pool extent correction, kill-and-reload, explicit u16 increment,
tied-asm copy preservation, int mask var, verify pools from bytes, sub-word
u8 pins NOT honored (use u32), pre-UAL add/asr, opaque empty-asm barriers,
array-index steers registers, interwork-epilogue check, separate result
vars, (216<<1) materialization, ASM-STAGED __asm__ blocks, try old_agbcc
before fighting 2-reg allocator rotation, single-expression v=(*p&m)|k for
load order, Makefile sed for scheduler-resistant movs/str splits,
extern-array pool-ordering, pool-loaded 0xAA via absolute-symbol trick, gcc
loop-hoist fixed by sed, 6 rect-fill idioms, inline-asm prologue idiom,
r7-pin + clobber-reservation coexist, inline-asm ldrsb, two-half s8 switch,
u8 *pa = a first-local, live-range extension spills, naked-asm idiom for
prologue save-set class, natural ldrsh from C works for s16 v = tbl[i],
bl-target discipline for multiply-instantiated functions,
((u32)s[35]<<28)>>28 shift-mask idiom, split-&= anti-fold, split pool-load
statement, opaque +r barrier forces runtime negs, sanctioned asm
transcription (dis2asm2.py — only after C variants exhausted; rebase branch
targets to ROM addresses), "m"-constraint dummy forces stack slot with zero
emitted instructions, explicit u32 stk[N] frame array, pin-the-thief idiom,
do NOT clobber a pinned reg, real indirect call pinned to r1 emits
bl _call_via_r1 naturally, volatile-store DSE defeat (zero bytes), int t
(not u8) gives ROM's signed ble, memory-barrier pins constant-materialization,
p-reuse reuses dead parameter register, block-scoped constant flips
movs-before-ldrb order, !!(x) → negs/orrs/lsrs#31, GAS 2.42 Thumb-16 adds
mnemonic quirk, int-vs-u8 clamp signedness rule, size-mismatch invalidates
diff counts, u32 temp forces ands dest=r0, nested scope orders pool loads,
s32 laundering for asm outputs, zero-fill section padding via file-scope
__asm__(".section NAME\n.align 2, 0\n.previous"), in-place ldrb via pinned
r0, adds operand order follows source order, block-scoped pins safe for
r1/r2/r5/r6, remeasure true extent before assuming bloat, signed variable
defeats AND-folding, memory barrier defeats CSE merging, real-copy asm
"movs %0,%1" (empty-template "=r" is a miscompile), ldrsb asm needs "=l"
(old_agbcc puts "=r" in sl), s16 scnt in-place sign-extend defeats &
0x1FFFFF folding, pinned ip, fake "+r" clobber defeats loop-invariant hoist,
kill+reassign forces pool reloads, opaque barrier defeats the
(x<<24)!=(y<<24)→x!=y fold, volatile u8 forces stack slot + byte reload,
anti-merge barrier (empty volatile asm, zero bytes), explicit goto for
branch direction, two-step EWRAM load, m-constraint forces stack slot for
unused out-params.

## Key rules
- Isolated-link stubs need `.global` before `.thumb_func`+`.set`; nm hygiene
  must confirm GLOBAL (A/T), not just present.
- Never reorder ldscript without rebuilding and re-verifying.
- Leave alone: Vec2_CopyMirrored (permanent), Sram_VerifyCompare, MainLoop,
  ChipSlot_Tick, B3 (second-vintage, parked).
- Never delete staging. Workspace workdirs only, not /tmp.
- Your final report: verified matched list (with diff evidence), new idioms,
  blockers with precise diffs, staging paths, what's next.
