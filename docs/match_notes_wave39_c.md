# Wave 39 Worker C — Match Notes

Worker C, Wave 39. All claims 0-diff over the full TRUE extent (from
`docs/func_list_v2.txt` next-function starts). Toolchain: `mmbcc/tools/agbcc`
and `old_agbcc`, `-O2 -mthumb-interwork` unless noted. Staging:
`staging/w39c_revisits/`. Coordinator LANDS; this worker staged only.

## Matched

### 0x08015278 — 256 B — old_agbcc + 1-byte `.s` patch — MATCHED
- Baseline W38-A V3 was 256/17 (4 sub-walls). Fixes (all in staged C except dispatch):
  - Dispatch `bhi`→`bgt` via patch (same wall as 0x0801a72c; see below).
  - Table pool into r2 / shift into r0: `base` pinned r2 + barrier, `tbp` pinned
    r0, inline `add %0, %0, %1`.
  - Addend block in ROM order: `h0` ldrh first, add chain, then an inline
    `lsl`/`asr` truncation (volatile asm = scheduling barrier, so the `h1`
    ldrsh cannot be hoisted before the truncation as gcc does for a call-arg
    `(s16)` cast); the call then passes the already-truncated value uncast.
- Intermediate: v1 9 diffs, v2 (pre-truncated `s16 add16` variable) still 9 diffs
  (gcc still truncated at call setup), v3 (inline-asm truncation) 1 diff
  (dispatch only).
- Patch: `w39c_08015278_patch.py` replaces the single `bhi` in the file with
  `bgt` (asserted exactly one occurrence). Coordinator: convert to
  `mmbcc/tools/fix_*_patch.py` per Wave 37/38 precedent (two-arg IN.s OUT.s).
- Callees (`.set` stubs at end of staged file, 9 total); c0 uses SetBit16 with
  s[44] VALUE form (ldr, not s+44) per W38-A lesson; c2 calls Sub_08017A44
  (gap callee, `.set` stub).
- Semantic note: c2's call target is a gap callee; the call itself matches
  byte-for-byte, but the callee's semantics are not verified here.

### 0x0801a72c — 240 B — old_agbcc + 1-byte `.s` patch — MATCHED
- Baseline W38-A V5 was 240/1: single byte at 0x0801a75f, ROM `bgt` (0xdc,
  signed) vs gcc `bhi` (0xd8, unsigned) for mode > 1.
- Pure-C signed-cast variant (`(s8)s[13] > 1`) restructured the whole dispatch
  (248 B old / 252 B main), so the minimal fix is the patch: replace the FIRST
  `bhi` in the generated `.s` (the dispatch branch after the second
  `cmp r0, #1`; the file's second `bhi` already matches ROM and is left alone)
  with `bgt`. Patch script asserts the dispatch pattern.
- `.set`-at-END verified working (assembles/links fine).
- Coordinator: convert `w39c_0801a72c_patch.py` to `mmbcc/tools/fix_*_patch.py`
  as above.

### 0x08013708 — 220 B — old_agbcc, pure C + inline asm — MATCHED
- Wall (W38-A V5, 220/2): ROM loads the table pool into r1 and the shift into
  r0 (`adds r0, r0, r1`); gcc put pool in r0 / shift in r1.
- Fix (new idiom, transferred to the twin): inner block with `base` pinned r1 +
  barrier-after-pin (forces pool load first; without the barrier gcc emitted
  shift before pool load), `tbp` pinned r0, shift via `(u8 *)(p[0] * 4)`, then
  inline `add %0, %0, %1` (`"+r"(tbp)` / `"r"(base)`).
- Critical finding: gcc canonicalizes C add operand order — even `p[0]*4 +
  base` still emitted `add r0, r1, r0`, so C alone cannot express ROM's
  `add r0, r0, r1`; the inline-asm add is required.
- Intermediate: v2 (no barrier) 6 diffs, v3 (barrier, tb in r1) 6 diffs, v5
  (tbp r0) 1 diff (operand order), v6 (swapped addends) still 1 diff, v7
  (`tbp += base`) invalid (pointer += pointer), v8 (inline add) 0 diffs.
- 10 `.set` stubs at end of staged file.

### 0x0801519c — 220 B — old_agbcc, pure C + inline asm — MATCHED
- Same 2-byte pool/shift wall as twin 0x08013708 (revisited together per W38-A
  instruction); same fix applied first try → 0 diffs. Baseline W38-A V1 was
  220/2.
- 8 `.set` stubs at end of staged file.

### 0x08042b60 — 164 B — old_agbcc, pure C — MATCHED
- Main agbcc gives 4 diffs — old_agbcc is the matcher; record that.
- Baseline W38-C was 168/112 (old). Fixes:
  - `b` pinned r3 (was callee-saved r4, pushing s/ret up a register); `bt`
    pinned r1 (was r2); result s=r4, ret=r5, push `{r4, r5, lr}` matching ROM.
  - Mask constants via in-place `-=` on the strh variable (`v24 -= 55`,
    `v24 -= 2`) giving `subs` instead of mov+neg/copy+sub. (W38-C wall:
    byte-mask ANDs need subs-materialized constants 24−55=−31, −31−2=−33.)
  - `t` as block-scoped int pinned r2 (was u8 in r1 with a copy); `lsl`/`lsr`
    into r2 now matches ROM.
  - Case-1 condition inverted (`t2 != 5` path first) so gcc falls through to
    the else path and jumps forward to the t==5 block, as ROM does; pools then
    land between the else path and the t==5 block.
  - Default returns via a `retpt` label placed after `EntryMgr_Setup` (ROM's
    default branch skips Setup; plain `return ret` folded to `return 0` with a
    `mov r0, #0`).
  - Else-path tmp/z split (`tmp = s[4]; z = 0; s[7] = tmp; s[4] = t2; s[5] = z;
    s[6] = z;`) so the zero materializes into r1 between the ldrb and the
    first strb, as in ROM.
  - Mask via a u32 variable so the literal pool carries the full `0xFFFFFC3F`
    (a u16 `&=` lets gcc pool the truncated `0x0000FC3F`).
- Intermediate: v1 63 diffs (164 B, exact size), v2 (bt pin + t2 pin + inverted
  condition + default return) regressed to 168 B / 140 diffs (folded
  `return 0`), v3 (retpt label) 9 diffs, v4 (tmp/z + u32 mask) 0 diffs.
- 7 `.set` stubs at end of staged file.

### 0x08023f28 — 168 B — old_agbcc, pure C — MATCHED
- Baseline W38-C was 168/78 (adds-move wall, multi-region). Fixes:
  - First 32768 block: value pinned r1 via `v1 = 128; barrier; v1 <<= 8` (the
    barrier defeats constant folding to a pool load of -32768, which would not
    fit the extent), copy pinned r0 (`w1 = v1`) giving ROM's
    `adds r0, r1, #0`, stores from r0. (Without the barrier gcc folded
    `128; <<= 8` to a pool load and grew the binary to 172 B.)
  - Middle order: G[60]/G[61] stores, then i=0, then q62, then the hoisted zero
    — straight-line C order now matches ROM.
  - Loop variable as s8 (not u8 + `(s8)` casts): gcc then emits ROM's loop
    exactly (address into r1, increment from the extended r0, rebuild via
    lsl/lsr). The u8 form preserved i in r1 and used r0 for the address; the
    si-variable + barrier form added a copy (`add r0, r1, #0`, 172 B).
  - Tail block: pointer pinned r0, value pinned r1 via `vv = 128; barrier;
    vv <<= 8`, barrier on q before the last store defeats gcc's offset-fold
    (`strh [r0, #2]`) so the last store is `adds r0, #2; strh [r0]` like the
    others.
- Intermediate: v1 172 B (pool loads), v2 172 B (folded constants), v3 168 B /
  4 diffs (loop only), v4 (si + barrier) 172 B (extra copy), v5 (s8 loop var)
  0 diffs.
- 3 `.set` stubs at end of staged file.

### 0x08037700 — 148 B — sanctioned asm transcription — MATCHED
- Transcription format follows W38-D precedent: `.text`, `.align 2`,
  `.code 16`, `.syntax unified` (REQUIRED — without it GAS rejects `lsls`/
  `adds`/`lsrs` forms in Thumb16 mode), `.thumb_func`, `.globl`, label, code,
  then pool words in ROM order (T1 `0x0822fcb4`, `0x0000469f`, T2
  `0x0822fe34`, T3 `0x0822fe50`), `.set` stubs at end. Branch/pool offsets
  computed by GAS from labels; verified to match ROM exactly.
- C-EXHAUSTION JUSTIFICATION: W37-C attempt 2 (160 B, ~126 diffs) + W38-C pin
  experiment (val→r3, i→r2, res→r6, pp→r8; 180 B, 119 diffs, worse) + W39-C v1
  (restructure, 148 B, 73 diffs) + v2 (full pins, 156 B, 102 diffs) + v3 (block
  pins, 164 B, 144 diffs) + v4 (accumulator, 148 B, 73 diffs) + v5 (reordered
  assignments, 148 B, 60 diffs) + v6 (c pinned r1, 152 B, 106 diffs) + main-agbcc
  builds of v4/v5 (identical diffs to old_agbcc).
- Wall: structural allocator divergence — ROM packs the six loop variables into
  r1–r6 (c=r1, i=r2, val=r3, q=r4, T1=r5, res=r6) with r7 as the `*q` temp,
  while both agbcc pack them into r2–r7 (v5: c=r2, i=r3, val=r4, q=r5, T1=r6,
  res=r7) with r1 as a temp. Pinning any subset shifts the others and/or forces
  extra moves (v6's c pin moved T1 to r2 plus a copy to r7; v3's full pins
  moved p to r9 and routed the loop sum through r8).
- Semantic correction found during this work: c is a RUNNING SUM accumulator,
  not a loop-invariant constant — pre-check c = T1[0] byte + p[0x469f] byte;
  each iteration c = (u8)(T1[i] byte + p[0x469f] byte + c); the truncated sum
  is written back to c's register each iteration (ROM: `lsrs r1, r0, #24`
  after the add) and compared. The W37-C decode's "c" description was
  incomplete on this point. Also: val = (u16)Scramble() & 31 (extension via
  two-statement form, since `Scramble() & 31` lets gcc drop the extension under
  the AND mask); tail v2 is u16 (extension at SMod-arg use, late — after ptr
  computation, before T3/d computation); tail t via split (`t = T2; t += res;`)
  gives ROM's pool-first order.
- V5 (best C, 60 diffs, kept as reference in `staging/w39c_revisits/work/
  t_37700_v5.c`) is instruction-identical to ROM except for the register
  shift, plus two tail differences: v2 extension timing (v5 early after call,
  ROM late after ptr) and `*t` load vs `b*4` order (v5 does b*4 first into r1
  then `*t` into r4; ROM loads `*t` into r1 first then b*4 into r4).
- `.set` symbols: `Scramble_400A8 = 0x080400a8`, `SMod_0804DDA0 = 0x0804dda0`.

### 0x0800c964 — 172 B — sanctioned asm transcription — MATCHED
- Transcription format as 0x08037700 (`.syntax unified` REQUIRED). Pool words
  in ROM order: `0x081731e0`, `0x08741784`, `0x0817344c`, `0x087493b0`,
  `0x02004f40`. Verified 0 diffs via `verify_asm_0c964.py` (as + ld script +
  objcopy + cmp).
- C-EXHAUSTION JUSTIFICATION: W37-C decode + W38-C staged file (172 B, 143
  diffs) + W39-C v1 (statement-order rewrite, 176 B, 150 diffs) + v2 (sp/e
  pins, 188 B, 156 diffs) + v3 (e pin only, 188 B, 149 diffs) + v4 (block e04,
  180 B, 137 diffs) + v5 (z pin r4, 180 B, 133 diffs) + v6 (F 2nd param int,
  eoff/e04/tv vars, dst[3], h2 var, 176 B, 136 diffs) + v7 (barriers, e3 var,
  h2 pin r5, 172 B, 77 diffs) + v8 (eoff/e0/e1/p54/zidx pins, 168 B, 130 diffs)
  + v9 (taddr vars + e1 asm load, 168 B, 130 diffs) + v10 (v7 + e1 asm + p54
  pin, 172 B, 76 diffs — best C). Ten W39-C variants covering: plain rewrite,
  function/block pins, barriers, intermediate variables, inline asm loads,
  two-statement forms, taddr variables. Remaining gaps are allocator choices
  (temp/pool register selection, reassociation folding of `e04 + (tv + base)`
  into `(e04 + base) + tv`) that C cannot express.
- CORRECTION to W37-C decode (important for landing and for F_0800DF8C's own
  future decomp): F_0800DF8C takes **6 args**, not 5. ROM's call passes
  r0=addr, r1=b (extended early), r2=1, r3=`a` (Sub's 2nd parameter, kept in r3
  across the addr computation), [sp]=32, [sp+4]=(u8)(h>>3). `a` is F's 4th
  arg, NOT unused. This explains the sub sp, #8 frame (2 stack args) and why
  r3 is never clobbered before the call. The 5-arg call in the old staged C
  (32 in r3, e5 on [sp]) was wrong.
- Other ROM-order facts confirmed during the rewrite (useful if F_0800DF8C or
  this function is ever re-derived in C): b is extended early (prologue,
  `lsls`/`lsrs` r1) before e computation; e is in r5, s in r6, z (0) in r4
  (kept from s[52] to the final strh stores); s[52] address is computed BEFORE
  the `movs r4, #0` (address adds, then mov, then store); s[54]'s address is
  computed AFTER the RHS (into r3) and REUSED for the later signed load
  (`movs r1, #0; ldrsb r1, [r3, r1]`); h is reloaded for the final `> 159`
  check (into r5, e dead) — the F call intervenes, so a named h variable kept
  across the call is wrong; the G-call e[3] load is a single `ldrsb` shared
  by the condition and the argument (a separate pre-check load + reload is
  wrong); the final store is `str [r0, #12]` with pool `0x02004f40` (NOT a
  folded pool `0x02004f4c` with offset 0 — use `dst[3]` form in C).
- `.set` symbols: `F_0800DF8C = 0x0800df8c`, `G_0800C22C = 0x0800c22c`
  (both flagged "check" in W37-C notes; the 6-arg signature above constrains
  F_0800DF8C's own decomp).

## Blocked

### 0x0801e890 — 172 B — 52 diffs (main agbcc) — BLOCKED
- W38-C baseline re-confirmed (staged file builds 176 B, 52 diffs main / 124
  old). W39-C attempts: v1 (fresh ROM-order rewrite, 168 B, 144 diffs), v2
  (tp variable, 168 B, 138 diffs), v3 (W38-C file + direct Setup/IncUse via
  `base[s[16]*3]` expressions, 172 B, 130 diffs — WORSE). The direct-Setup
  angle from W38-C's "next angle" note is DISPROVEN: W38-C's idx/off/e/sv
  structure (52 diffs) beats direct expressions (130 diffs).
- Remaining 52 diffs by region (main agbcc): first block s[9] load register
  (2 B), s[10] region (5 B), Setup call region (21 B — largest), Setup args
  (2 B), IncUse region (3 B), clamp u16-load region (5 B), s[69]/s[34] regions
  (14 B). Next: targeted fixes to the Setup region and s[69] region of the
  W38-C file; do NOT use W39-C v3. If C stalls, transcription is sanctioned
  (this is a revisit target) but was not attempted — the 52-diff C baseline
  is still live.
- Pools (LE, confirmed): `0x082243d8`, `0x08226aec`, `0x081705b0`,
  `0x020031e4`. Callees: ChipSlot_Setup `0x0800d6e0` (MATCHED),
  ChipSlot_IncUse `0x0800d9ec` (MATCHED), F_0801E93C `0x0801e93c` (MATCHED).
  Pad: 2 bytes (`0x0000`) at 0x0801e92a before the pools.
- Semantic note: the clamp (`v = byte & 3; if (v > 3) v = 3;`) is redundant
  (byte & 3 is always ≤ 3) — ROM still emits the cmp/ble/movs, so the C must
  keep the clamp (W38-C's barrier-on-w pattern does this). s[69] =
  (s[69] & -13) | (v << 2) (2-bit field in bits 2–3).

## Skipped

- 0x0801aa70, 0x0801cd50, 0x0801ebf0, 0x08017a44, 0x0801b98c, 0x080111b4,
  0x0804db28 — all already MATCHED in `docs/match_status.tsv`; registry check
  (TSV grep + ldscript overlap check) done for every target before any claim.
- Note: W38-A's bulk RESULTS.md said of 0x08017b6c and 0x0802129c that they are
  "unlisted gap callees — flag for coordinator; do not claim them" in the bulk
  context. The Wave 39 task explicitly lists them as targets, so they were
  treated as targets to attempt (with that caveat noted for the coordinator).

## Unattempted

- 0x08017b6c (404 B): leaf function (no bl calls), push {r4, r5, lr}. Pool
  loads at 0x08017b8c/0x08017c18/0x08017c1c/0x08017c9c/0x08017ca0/0x08017cdc.
  Not disassembled in full; needs dedicated effort (400+ B).
- 0x0802129c (400 B): leaf function (no bl calls), push {r4, r5, r6, r7, lr} +
  push {r7}. Pool loads at 0x080212c4/0x0802131c/0x08021348/0x080213a0/
  0x080213b8/0x08021428. Not disassembled in full; needs dedicated effort.

## Idioms used / confirmed in Wave 39 (for future workers)

- Pin-activation + barrier-after-pin: a pinned variable's pool load (or
  computation) must be forced to its pinned register BEFORE dependent code, or
  gcc emits the dependent code first (13708/1519c/15278 pool-shift walls).
- gcc canonicalizes C add operand order: `p[0]*4 + base` still emits
  `add r0, r1, r0`; when ROM has `add r0, r0, r1`, an inline-asm add is
  required (13708/1519c/15278).
- Volatile-asm truncation as scheduling barrier: an inline `lsl`/`asr` pair
  prevents gcc from hoisting a later load before the truncation (15278 h1
  wall); a call-arg `(s16)` cast does NOT prevent the hoist.
- Barrier defeats constant folding: `v = 128; barrier; v <<= 8` prevents gcc
  from folding to a pool load of -32768 (23f28 32768 wall).
- s8 loop variable (not u8 + casts) reproduces ROM's loop exactly when gcc
  otherwise preserves the index in a different register (23f28).
- In-place `-=` on a strh variable materializes mask constants via `subs`
  (42b60: 24−55=−31, −31−2=−33); mov+neg is 2 bytes longer per constant.
- u32 mask variable so the pool carries the full `0xFFFFFC3F` (42b60); a u16
  `&=` lets gcc pool the truncated `0x0000FC3F`.
- `retpt` label after a call to defeat gcc folding `return ret` to
  `return 0` with a `mov r0, #0` (42b60 default-return wall).
- `dst[3]` form for a store with immediate offset: `*(u32 *)(BASE + 12)` lets
  gcc fold BASE+12 into the pool word; `dst[3]` (dst = (u32 *)BASE) emits
  pool BASE + `str [r0, #12]` (0c964 store wall).
- Single-load condition+argument: `s8 e3 = e[3]; if (e3 >= 0) G((u16)e3);`
  shares one `ldrsb`; writing the condition and the argument as separate
  `(s8)e[3]` expressions emits a pre-check load plus a reload (0c964 G-call
  wall).
- A named variable kept across a call is WRONG when ROM reloads after the
  call (0c964 h wall): use inline loads at each site; the intervening call
  forces the reload.
- F-call 6th-arg / stack-arg detection: if ROM's call uses [sp] AND [sp+4]
  but not r3, r3 holds a passed-through argument (0c964: `a` is F's 4th arg).
  Count stack slots (sub sp, #8 = 2 stack args) to determine the arity.
- Transcription `.syntax unified` is REQUIRED for GAS to accept `lsls`/
  `adds`/`lsrs` Thumb16 forms (37700, 0c964).
- Direct-expression table indexing is NOT always better: for 0x0801e890,
  W38-C's idx/off/e/sv variable structure (52 diffs) beats direct
  `base[s[16]*3]` expressions (130 diffs) — the variable structure matches
  ROM's register flow better.
