# Function list v2 — methodology

**Artifacts:** `func_list_v2.txt` (1696 rows: 51 A + 1600 B + 45 D —
fixed hi-reg MOV decoder, see §v2.5),
`func_list_v2_1_addendum.txt` (+37 B, historical),
`func_list_v2_2_addendum.txt` (+7 B, historical),
`func_list_v2_3_addendum.txt` (+8 B, historical),
`func_list_v2_4_addendum.txt` (+32 B, historical),
`func_list_v2_5_addendum.txt` (+52 B consolidated novel),
`byteclass.tsv`, `gen_func_list_v2.py` (the generator)
**Date:** 2026-10-20 · **Status:** Phase 1 proper — recursive descent from
entry, replacing the v1 prologue-scan bootstrap. Counts independently
audited; hi-reg MOV decoder fixed and artifacts regenerated (§v2.5);
Phase 2 sweep ongoing.

## Result

| Tier | Count | Meaning |
|---|---|---|
| A | 51 | Reached by recursive descent from entry (confirmed) |
| B | 1652 | Unreached but forward-disassembles cleanly (probable): 1600 v2 (fixed) + 52 v2.5 |
| D | 45 | Demoted entries (pool noise / mid-function / invalid) |
| **A+B** | **1703** | **verified working function count** |

Byte classification after the fix (full `0x000000–0x04FFFF` coverage):
**code 62.0% · pool 5.4% · data 0.1% · unknown 32.6%** (was
39.0/3.7/0.1/57.2 — the decoder fix recovered most of the unknown).

v1→v2 transitions: A→A 49, A→B 640, A→D 37 · B→A 1, B→B 384, B→D 7 ·
C→B 466, C→D 27 · plus 1 descent-only A (not in v1: `sub_0804BE10`).

Byte classification of file `0x000000–0x04FFFF` (320 KB, full coverage,
no gaps/overlaps): **code 39.0% · pool 3.7% · data 0.1% · unknown 57.2%**.

## Algorithm

ARMv4T-exact recursive descent (hand-written decoders; capstone was
available but not strict enough for ARMv4T validity). Baserom is read in
place under a SHA-1 gate (`72309736…bc5a946`); never copied or modified.

1. **Seeds** (6): ARM `@0xC0` (Init), `@0xFC` (IntrWait), `@0x1BC`
   (IrqDispatcher), `@0x2A4` (ArmTrampoline); Thumb `@0x2DC`
   (crt0_thumb_helpers), `@0x33C` (Thumb entry).
2. **Control flow:** conditional branches enqueue the target and continue
   fallthrough; unconditional `b` ends fallthrough (target still queued);
   `bl` (Thumb and ARM) queues the target as a new function seed and
   continues; terminators are `bx lr` / `mov pc,lr` / `pop {…,pc}` /
   self-branch (Thumb) and `bx lr` / `mov pc,lr` / `ldm {…,pc}` (ARM).
3. **bx resolution:** `bx rN` consults a path-carried register map fed by
   `ldr rN,[pc,#imm]` (tag `pool`: pool word bit0 selects Thumb/ARM
   target, ROM→file address converted) and by `pop {…,rN}` (tag `pop`:
   return-via-popped-register is a plain terminator). Registers are
   invalidated on overwrite (write-set computed per instruction; `swi`
   clobbers r0–r3). Unresolvable `bx` (callback argument, IRQ trampoline)
   ends the path as an indirect exit. `mov lr,pc; bx rN` is treated as a
   mode-switching **call**: the target becomes a seed *and* fallthrough
   continues (this recovers the crt0 `b 0xC0` reboot stub at `0xF0`).
   `ldr pc,[pc,#imm]` table jumps mark their target as code.
4. **Function assignment:** starts = seeds ∪ bl-targets ∪ bx/ldr-pc
   targets. Bodies are reachability walks that stop at other starts
   (tail calls) — including on fallthrough, so the dispatcher does not
   absorb the `ArmTrampoline` at `0x2A4`.
5. **Literal pools:** any word referenced by `ldr [pc,#imm]` is `pool`
   (Thumb: `((pc+4)&~3)+imm`; ARM: `pc+8±imm`). In `byteclass.tsv`,
   code wins on pool/code overlap (718 bytes, interior pools).
6. **v1 re-check:** reached ⇒ A. Unreached ⇒ bounded recursive-descent
   `fwd_check` over unowned bytes: every path must end in a terminator
   (or a resolved/unresolvable indirect exit), with no invalid,
   Thumb-2-only, or coprocessor encodings, no region escape, no stepping
   into owned/pool bytes or another v1 entry ⇒ B; else D. One extra pass
   follows `bl`/`bx` targets out of confirmed B functions (78 added as
   `via-B`, single fixpoint).

## Key corrections vs v1

- **Thumb BL decode:** v1 sign-extended the offset from bit 23
  (`off -= 1<<24`); ARMv4T sign-extends from bit 22 (`off -= 1<<23`).
  v1's harvest therefore missed *all* backward `bl`s (targets landed
  out of region and were filtered). Descent here uses the correct decode.
- **v1's C tier was not mostly noise.** 454/455 C→B promotions return via
  `pop {rX}; bx rX` (or `mov pc,lr`), which v1's linear scan did not
  recognise as terminators — it only accepted `bx lr` / `pop {…,pc}`.
  The `pop`+`bx` return idiom is pervasive in this binary (thunks,
  callbacks). Spot checks (e.g. save-API entries `0xB54/0xBAC/0xC04`,
  all v1-C) show healthy function bodies (p50 ≈ 124 bytes).
- **`mov pc,lr` is a return** (previously fell through, inflating bodies).
  Conditional self-branch (`bne .` spin-wait in the IRQ dispatcher) falls
  through correctly; only unconditional `b .` is a halt.

## Anomalies / coordinator decisions

1. **887 of 1605 functions are called** (bl/bx target); 717 B functions
   are uncalled — presumably callbacks/table-driven (B is defined as
   "probable" for exactly this), but some could be noise. They are spread
   across all banks with healthy sizes (p50 ≈ 108 B); only 58 are ≤24 B
   thunks.
2. **22× `B_calls_mid_function`:** 9 B functions `bl` to `0x4DDA0`,
   which sits inside A-function `sub_0804DD9C` (plus 2 similar cases at
   `0x4151E`, `0x4427C`). `0x4DDA0` looks like a real alternate entry
   (`movs r3,#1…` after the previous function's `mov pc,lr` return).
   Kept merged per the no-split rule; splitting is a judgment call.
3. **44× `B_target_failed`:** mostly (40×) `bl` targets overlapping pool
   words — likely `bl` to veneers coinciding with pools, or bogus edges.
   Not promoted; logged.
4. **310× `B_target_demoted`:** B functions calling already-demoted v1
   entries (expected; no action).
5. **`bx_indirect` (3):** `@0x2AC` (IRQ trampoline, expected —
   handlers live in WRAM), `@0x4BE24` (`bx r12`), `@0x4DCD0` (bx veneer).
6. **57.2% of the region is `unknown`.** Within this methodology only
   v1 entries + descent-reachable code can be classified; uncalled,
   non-push-prologue functions missed by v1's scan would hide here.
   A whole-region ARMv4T-validated sweep (beyond v1's push signatures)
   could shrink this in a later pass.
7. **0 tail-call-merge candidates** by the `b`-to-push-prologue heuristic.

## v2.2/v2.3 verification audit (coordinator, 2026-10-20)

Independent audit of the v2+v2.1 count, per the user's "verify before
claiming" rule. Three audit workers + coordinator's own re-derivation.

**BL decode: PROVEN correct.** Re-derived from ARM ARM first principles
(Thumb BL = `11110 S imm10` / `11111 imm11`; offset = SignExtend_23
(S:imm10:imm11:0), sign bit = bit 22; target = A+4+offset). Independent
decoder agrees with the generator on **all 7,936 BL sites, 0 mismatches**.
The v1 bug (`off -= 1<<24`, sign from bit 23) provably missed 100% of
backward BLs (5,081/5,081 landed out-of-region).

**Counts: EXACT.** Generator re-run reproduces `func_list_v2.txt` and
`byteclass.tsv` byte-for-byte. A=51, B=1554, D=71 (the "72" was a grep
artifact matching the header comment; "87" was this doc's stale cell —
fixed above). v1→v2 transition matrix re-verified exact. All 43
addendum rows distinct from v2; all caller-count claims verified
(146 for `03385E`, 41 for `004E0C`).

**Stale numbers in this doc corrected** (doc → true, from generator
output): via-B "78" → **64**; pool/code conflicts "718 bytes" →
**574**; `B_calls_mid_function` "22×" → **2**; `B_target_failed`
"44×" → **40**; `B_target_demoted` "310×" → **168**; `bx_indirect`
"(3)" → **5**.

**New finding — 7 wrongful D-demotions → v2.2 (+7 B).** A correct-decode
region-wide BL scan (1,095 distinct in-region targets: 1,013 ∈ v2,
43 ∈ v2.1 addendum, 39 novel) showed the v2.1 re-harvest was incomplete:
it skipped v2 D entries. 7 D entries are real functions:
- `overlaps_pool` misfire ×4 (`004E60`, `004F80`, `004FEC`, `00B520`):
  traced exemplar `004F80` — fwd_check demoted it because linear decode
  reached its OWN inline pool word `004FD4` (already in `all_pools` via
  another path). 70 genuine BL callers in classified bodies, push
  prologue — unambiguously real.
- `bx_pool_not_code` ×1 (`02142C`): bx target was a misclassified pool
  word; 1 genuine caller + prologue.
- `contains_v1_*` ×2 (`04DE70`, `04DEE8`): over-strict containment vs
  neighbours `04DEDE`/`04DF9E`; 3/6 genuine callers — probable
  alternate entries (flagged for Phase 2).
See `func_list_v2_2_addendum.txt` for per-entry evidence.

**Known undercount region (NOT in the 1649):** a thunk/veneer cluster
spanning ~`029AC4`–`02C70C` (~100 instances of the `381c 4946 5246
089b` + `BL` call idiom) is real code missed by v1's prologue scan and
v2's descent. Exact function count there needs the Phase 2
unknown-region sweep. True total is therefore **≥1649**; the old
1642–1900 honest range stands, now floored at 1649.

**Remaining caveats:** B tier is "probable" by construction (uncalled B
functions could include noise — tier-promotion spot-checks pending);
57.2% of bytes remain `unknown`; "function count" counts starts and
shared tails double-count shared bytes (1,844 B across bodies).

### v2.3: 1B auditor's D-tier census (+8 B)

The 1B auditor walked all 71 D entries with pool-check disabled and
found **7 more wrongful demotions** (uncalled but clean, genuine
returns, 118–494 B bodies, killed by phantom pools): `014944`,
`014B54`, `014EB8`, `015278`, `0420D0`, `0422F8`, `015378` — plus
**1 missed entry point** `04DDA0` (13 callers, real code, owned by
nothing, byteclass unknown). Root causes confirmed and sharpened:
(1) **order-dependent pool poisoning** — v1 entries processed in
offset order; early confirmations register pools that kill later
entries (`004C10` → kills `004E60`/`004F80`/`004FEC`/`004E0C`; reverse
the order and verdicts flip); (2) **self-pool fallthrough** —
fwd_check consults only the global pool set. Also verified:
C→B promotions 399/466 with genuine terminators (doc's "454/455"
overstated); B-tier p50=50 (not 108), ≤24 B = 476 (not 58);
65 four-byte indirect stubs flagged (weak tail, 4 pool-referenced).
See `func_list_v2_3_addendum.txt`. **Verified total now 1657.**

### v2.4: Phase 2 unknown-region sweep (+32 B)

The sweep worker's region-wide correct-decode BL scan (1,095 distinct
in-region targets) + own recursive descent of the `029AC4`–`02C70C`
thunk span found 32 more entries, all coordinator-verified distinct
(no overlap with v2/v2.1/v2.2/v2.3; none are 1B-confirmed-correct
demotions; caller counts corroborated by independent scan):
- 26 `contains_v1_*` D→B: BL-targeted starts in the thunk span (1–31
  genuine callers each, validate_target clean, most call known v2
  functions). Accepted with the alternate-entry caveat (cf. v2.2
  04DE70/04DEE8): several are probable alternate entries into shared
  thunk bodies — entry points regardless, flagged for Phase 3.
- 1 other D→B: `033962` (1 caller, calls known `04AD00`, tail-branches
  to known `033AB2`).
- 6 pointer-table discoveries (`00A18`, `044F4`, `11E98`, `17084`,
  `20F58`, `4C4FC`): bx-lr-terminated bodies referenced from multiple
  function-pointer table runs.
- Key correction: the 100× `381c 4946 5246 089b` idiom instances are
  NOT starts (zero BL/data-pointer targets; fallthrough-reached
  interior code; no terminators) — an inline call-helper pattern.
See `func_list_v2_4_addendum.txt`. **Verified total now 1689**
(A=51, B=1638, D=30).

### v2.5: hi-reg MOV decoder fix — canonical recount (coordinator)

The xref worker found a real decoder bug in `gen_func_list_v2.py`:
hi-register MOV had Rs/Rd high bits swapped (bit7→Rs, bit6→Rd;
correct is bit6→Rs, bit7→Rd — verified against assembler encodings).
Impact on real ROM bytes: **298** `mov r7,rX` sites misdecoded as
`bx rY` (false indirect exits truncating functions) and **256**
`mov pc,r0` switch-dispatch jumps misdecoded as `mov r7,r8` (bodies
chained through jump tables). Fixed (2 lines), generator re-run,
artifacts byte-regenerated:
- v2: **A=51, B=1600, D=45** (was 51/1554/71). `sub_0802FDA0`
  (previously flagged missing) now found. No entries removed.
- The fix absorbed 20 of v2.1's 37, 5 of v2.2's 7, 7 of v2.3's 8
  directly into v2 (incl. the `overlaps_pool` wrongful demotions
  `004E60/004F80/004FEC/00B520/02142C` — now A/B natively).
- The 52 still-novel entries consolidated into
  `func_list_v2_5_addendum.txt` (17 ex-v2.1 + 2 ex-v2.2 [`04DE70`,
  `04DEE8`] + 1 ex-v2.3 [`04DDA0`] + 32 ex-v2.4), original evidence
  preserved. v2.1–v2.4 kept as historical records.
- Byte classification: **code 62.0% / pool 5.4% / data 0.1% /
  unknown 32.6%** (unknown down from 57.2%).
- **Verified working count: A=51, B=1652, D=45 → 1703 total.**
  Old `/tmp/v2backup/` holds the pre-fix artifacts.

## Seed list

`0xC0/R, 0xFC/R, 0x1BC/R, 0x2A4/R, 0x2DC/T, 0x33C/T`
(file offsets; R=ARM, T=Thumb). The genuine ARM routine `@0x4BCDC` was
discovered via `bx` resolution (not seeded).
