# Match notes — Wave 39, Worker B

Range: `docs/wave34_unattempted.tsv` lines 551–651 (101 lines,
`0x08014cf0` … `0x08030b1a`). Staging:
`staging/w39b_bulk/`. Harness: `staging/w39b_bulk/w39b.py`
(`build SRC ADDR SIZE {main|old|...}`; `dis ADDR SIZE`).
Triage: `staging/w39b_bulk/triage.py`, `triage.txt`,
`dis/080xxxxx.txt` per target. Baserom SHA-1 verified at session
start: `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in place
only, never copied).

## 1. Idioms learned

### 1.1 Jump-table switch via goto structure (matched: `0x0802f5ac`)

A numeric-order `switch` produced the wrong stub layout (dispatch
head put the >199 body inline; GCC emitted two 25-stubs). What
matched: group cases by code in ROM stub order (35, 36, 37, 48, 49,
50, 25, 66), each case `code = K; goto call;`, with the >199 body
(`code = 51`) placed after the stubs via gotos:

```c
int code = 0;
if (idx <= 199) goto sw;
goto big;
sw: switch (idx) { case N: code = K; goto call; ... default: goto check; }
big: code = 51;
check: if (code == 0) goto ret;
call: Sub_0802D7A0(...);
ret: return;
```

The goto structure is what places the >199 body after the stubs and
makes case stubs branch directly to the call setup (skipping the
zero-check), exactly as in ROM. Lesson: when a switch's ROM layout
has the default/out-of-range body after the stubs (not inline in
the dispatch head), restructure with gotos rather than fighting the
switch's natural layout.

### 1.2 If/else-chain dispatch reproduces switch-like dispatch exactly (0x080171c0)

ROM's mode dispatch (mode = s[13], cases 0..3) is NOT a jump table;
it is a comparison chain with a distinctive asymmetry: the first
dispatch's default branches DIRECTLY to tail (`b tail`), while the
gt-block's default goes via an intermediate block (`bne deftail;
b c3; deftail: b tail`). This is exactly what an if/else chain
emits:

```c
if (mode == 1) goto c1;
else if (mode > 1) goto gt;
else if (mode == 0) goto c0;
else goto tail;
gt:
if (mode == 2) goto c2;
else if (mode == 3) goto c3;
else goto tail;
```

The gt `else if` emits `cmp; bne deftail; b c3; deftail: b tail`
(then-part first, else-part second). A plain `switch` does NOT
reproduce this asymmetry. When ROM dispatch shows two different
default-block shapes, try an if/else chain with gotos before a
switch.

### 1.3 Pin/allocation interaction (0x080171c0)

- Pinned registers are NOT used as switch/if temps: GCC copies
  pinned → temp for tests (`add r0, r6, #0` after `ldrb r6`).
  Exception: when the pinned register is also the natural temp
  choice AND the variable is unpinned — see V3.
- Unpinned mode + pos/base pinned → mode coalesces into r6
  (`ldrb r6; cmp r6`, no copy) BUT the prologue breaks (pinned r7
  is not saved; GCC saves r8 via r6 scratch, push set loses r7).
- Mode pinned to r6 (int) + pos/base unpinned → allocation
  mode→r6, pos→r7, base→r8 AND prologue correct (`push
  {r4,r5,r6,r7,lr}; mov r7,r8; push {r7}`), because pos/base are
  ordinary callee-saved registers that GCC saves normally.
- All-unpinned → mode goes to r8 (longest-lived variable gets the
  highest callee-saved register). To get mode→r6, something must
  occupy r7/r8 — pinning mode itself (r6) does this while keeping
  the prologue correct.
- Mode must be SIGNED int (not unsigned, not u8) for the dispatch
  `bgt` (unsigned gives `bhi`) and to avoid the u8 word-check
  truncation (`lsl/lsr #24`) that a pinned u8 mode incurs (GCC does
  not track zero-extension cleanliness of pinned registers).

### 1.4 NEVER name a C variable `sp` (or any register name) when inline asm is involved

V3 named pos-update temporaries `sd, sp`; the variable named `sp`
collided with the stack-pointer register name in GCC's inline-asm
handling, and the generated `.s` literally contained `mov r2, sp`
(stack pointer!) — semantically wrong and corrupting allocation.
Renamed to `spos` in V4; the bug vanished and the prologue was
restored. Rule: never use `sp`, `lr`, `pc`, or any register name
as a C variable name in files that use inline asm.

### 1.5 Barrier idiom for sign-extension preservation (0x080171c0 case-2 pos update)

ROM's pos update keeps explicit sign-extensions:
`lsls/asrs` pairs for `(s16)d<<8` and `(s16)pos`. GCC folds these
away unless the temporaries are separated by an empty volatile-asm
barrier on BOTH:

```c
sd = (s16)d << 8;
spos = (s16)pos;
__asm__ volatile("" : "+r"(sd), "+r"(spos));
pos = (u16)(spos + sd);
```

This reproduces ROM's `lsl/asrs` pairs exactly. Same barrier
pattern works for the case-1 threshold (a `v` local + barrier
inside the then-arm breaks GCC's cross-jumping that otherwise
merges the two threshold comparisons into a shared block).

### 1.6 Short-typed ternary dance (0x080171c0 step — MATCHED pattern)

ROM's step ternary (`st==0 → 1`) has the distinctive form:
`lsls #16; movs r1,#1; cmp; beq keep; lsrs r1; lsls/asrs; adds`
(false value materialized FIRST, then conditionally overwritten by
the shifted true value). This is produced when BOTH the value and
the result are `short`:

```c
short st = (short)(tt - cur) >> 1;
short st2 = st ? st : 1;
```

With `int st` / `short st2`, GCC emits a branchy form instead
(`cmp; beq; lsl; lsr; b; mov; lsl; asr; add`). Rule: for a
ternary whose ROM form shows the mov-first + shifted-extract
pattern, make both operands short, not just the result.

### 1.7 C89 declaration-before-statement rule (agbcc)

agbcc (GCC 2.9, default C89) rejects declarations after statements
in a block. When converting an initialized declaration
(`u16 d = ...;`) to a separate assignment (`u16 d; d = ...;`),
every later declaration in the same block (`u32 gw`, `int sd,
spos`) must be hoisted above the first statement, or the build
fails with "syntax error before ...". This bit twice during V7.

### 1.8 Copy forwarding defeats deliberate copies

Declaring `u8 *o = other;` at Path-B entry and calling
`Byte12_Gt1(o)` does NOT materialize the `adds r1, r4, #0` copy
ROM has: GCC forwards `o` to `other` (single `adds r0, r4, #0`
at the call site). A copy that is used only once, with the source
unchanged, will be forwarded away. Forcing such a copy to survive
needs a use that blocks forwarding (not yet found for this case).

### 1.9 Separate assignments do not change codegen (old_agbcc)

Converting initializers to separate assignments (`u16 d; d = ...;`,
`int cur, tgt, d; cur = ...; tgt = ...; d = ...;`) produced
byte-identical codegen to the initializer forms (V7 = V6). Do not
expect declaration/assignment style alone to fix allocation
differences with this compiler.

## 2. Per-function notes

### 2.1 `0x0802f5ac` — MATCHED (896 B, old_agbcc)

See RESULTS.md. Signature:
`void Sub_0802F5AC(u8 *s, u8 a, u8 b, u16 c, u8 idx, u8 d)`.
Prologue `push {r4,r5,r6,lr}; sub sp,#24`. Dispatch: `idx > 199 →
code 51`; else 190-entry jump table (pool base `0x0802f5e8`),
cases 1..190 → codes {25, 35, 36, 37, 48, 49, 50, 66}; idx 0 /
191..199 → code 0 → no call. Tail: if code != 0, call
`Sub_0802D7A0(s, a, b, 0, 2, 0, c, c, code, d)` (10 args).
Full case→code map: `staging/w39b_bulk/work/f5ac_cases.txt`.
Staged: `w39b_0802f5ac.c` (+ `_A.c`/`_B.c`/`_C.c` variants).
Callee `.set` at END of staged file: `Sub_0802D7A0, 0x0802d7a0`
— but the build-global name is `Obj_AddEntry`, so the coordinator
must adjudicate (keep as local alias vs rename) at landing.
Semantic re-check: C matches ROM on all paths; no doubt beyond
the callee's own (previously matched) semantics.

### 2.2 `0x080171c0` — BLOCKED (claim extent 508 B; TSV 532 B)

Full decode (verified against `dis/080171c0.txt`):

- Signature: `void Sub_080171C0(u8 *s)`. Prologue `push
  {r4,r5,r6,r7,lr}; mov r7,r8; push {r7}` (r8 saved and used);
  epilogue `pop {r3}; mov r8,r3; pop {r4,r5,r6,r7}; pop {r0};
  bx r0`. Entry: `other = *(u32 *)(s+40)` (r4). If `other == 0`
  → Path A (mode machine); else → Path B. Shared tail:
  `ChipSlot_Tick(s)` (`0x0800d9fc`, Wave 35), then return.
- Path A: `mode = s[13]` (r6). Dispatch chain per §1.2 above.
  Default (mode >3 or falling through) → tail.
  - Case 0 (`0x080171ec`): `s[13]=1; *(int*)(s+88)=512;
    *(int*)(s+96)=96;` then FALLS THROUGH into case 1 (no break).
  - Case 1 (`0x080171fa`): `*(int*)(s+80) -= *(int*)(s+88);
    *(int*)(s+88) += *(int*)(s+96); if (*(int*)(s+88) > 3072)
    *(int*)(s+88) = 3072;` then threshold: flag =
    `gEwram_02003670[0x11ae] & 4` (global `0x02003670`, byte
    offset `0x11ae`; pool words NOT folded — source is array
    indexing on the global symbol). If flag: advance iff
    `s[80] <= 0x77ff`, else tail. If !flag: advance iff `s[80]
    <= 0x6fff`, else tail. (Two separate cmp sites — NOT a
    value-ternary; nested-if / duplicated-comparison codegen.)
    Then `*(int*)(s+80) = flag ? 0x7800 : 0x7000` (codegen:
    false value `0xe0<<7` first, `cmp flag,0; beq store;` true
    value `0xf0<<7`, then store — same idiom as Wave 7-C
    `wave7_c_old.c` line 51). Then `s[13]++; s[18]=60; goto
    tail`.
  - Case 2 (`0x0801726c`): `cnt = s[18]` (kept in BOTH r2 for
    comparisons and r3 for the decrement). If `cnt <= 51`, skip
    to the decrement part. If `cnt > 51`: `base = 0x02003670`
    (r8, hi reg, kept across the AbsScale call); `pos =
    (base[0x11ae] & 4) ? 0x7800 : 0x7000` (r7). If `cnt != 52`:
    `fx = (cnt-52) << 15`; `half = (u16)(fx >> 16)` via LOGICAL
    shift (fx unsigned); `sc = AbsScale_52A0(fx)` (`0x080052a0`,
    BLOCKED — call via `.set`, keep at landing);
    `d = half + (sc & 3)` (u16, truncated); `gw = *(u32 *)base`;
    if `gw & 1`: `d = 0`; else `d = (gw & mode) ? d :
    (u16)(-d)` (see §2.4 for the exact ROM codegen form);
    `pos = (u16)((s16)pos + ((s16)d << 8))` (codegen:
    `lsls/asrs` pairs — see §1.5); `*(int*)(s+80) = (s16)pos`.
    Decrement part (`0x080172ec`): `--s[18]` (no-call path uses
    r3 from entry with NO reload; call path RELOADS s[18] into
    r3 at `0x080172e4` before the pos store, because r3 is
    caller-saved and the call clobbers it); if new `s[18] != 0`
    (via `lsls #24; cmp #0` — the u8 `--x != 0` idiom) → tail;
    else `s[13]++; *(int*)(s+88)=512; *(int*)(s+96)=96; goto
    tail`.
  - Case 3 (`0x08017308`): `*(int*)(s+80) -= *(int*)(s+88);
    *(int*)(s+88) += *(int*)(s+96); if (*(int*)(s+80) <
    -20480)` (pool `0xffffb000`): `{ *(u32*)(s+12) = 2;
    *(u32*)(s+20) = Tbl[s[9]][2]; }` where Tbl base pool is
    `0x082243d8` (table of pointers, stride 4, field word at
    +8). Codegen order: row ADDRESS computed before the s[12]
    store, pointer loads after it. Then `goto tail`.
- Path B (`0x08017338`, other != 0): `if (s[18] != 0) {
  s[18]--; goto tail; }`. Else if `(u8)Byte12_Gt1_080170c4(other)`
  (codegen: `bl; lsls r0,#24; cmp r0,#0; beq skip` — the
  (u8)-truncation-tested-against-zero idiom; Byte12_Gt1 returns
  0/1 for `s[12] > 1`, matched Wave 7 in `wave7_g2_old.c`
  lines 348–357) then the same table block as case 3. Then
  follow logic (`0x08017364`): `cur = *(int*)(s+80); tgt =
  *(int*)(other+80); d = cur - tgt;` (ROM register flow: loads
  into r0/r1, `subs r3,r0,r1` for d, then copies `adds r4,r0`
  (cur) and `adds r2,r1` (tgt) — cur in r4 reusing other's dead
  register, tgt in r2). If `d >= 0`: if `d <= 256` → snap, else
  → step (codegen: `cmp d,256; ble snap; b step`). Else (d < 0,
  block at `0x08017380` after the Tbl pool word at
  `0x0801737c`): `if (tgt - cur > 256)` → step, else snap
  (codegen: `subs r1,r2,r4; movs r0,#128; lsls #1 (256);
  cmp r1,r0; bgt step;` then snap). Snap (`0x0801738a`):
  `*(int*)(s+80) = tgt; goto tail`. Step (`0x0801738e`):
  `st = (short)((short)tgt - cur) >> 1` (codegen: `lsls/asrs`
  pairs + `lsls #16; asrs #17`); then `st2 = st ? st : 1` with
  ROM's shifted test/extract dance (see §1.6 — the `st==0 → 1`
  is dead in practice for |diff| > 256 but the compiler emits
  it from source — keep it); `*(int*)(s+80) = cur + st2;
  goto tail`.
- Callee/global names for the staged file (coordinator `.set`
  audit — ALL of these are build globals except as noted, so
  STRIP the `.set` lines for build globals at landing and KEEP
  only non-globals; for standalone verification all five are
  needed in the staged file):
  - `Byte12_Gt1_080170c4` → `0x080170c4` (MATCHED, build
    global — strip).
  - `ChipSlot_Tick` → `0x0800d9fc` (MATCHED Wave 35 — strip).
  - `Sub_080052A0` (AbsScale) → `0x080052a0` (BLOCKED, not in
    build under this name — but `AbsScale_52A0` IS a build
    absolute symbol (from `w37d_0801ffbc`'s `.globl
    AbsScale_52A0` + `.set`); adjudicate keep-vs-rename at
    landing).
  - `gEwram_02003670` → `0x02003670` (build global — strip).
  - `Tbl_082243D8` → `0x082243d8` (build global absolute
    symbol; also `PtrTbl_082243D8` / `gTbl_082243D8` aliases
    exist — strip; precedents: `register u32 *tbl
    __asm__("r1") = (u32 *)0x082243d8;` in `w35c_0801d89c` /
    `w36b_0801a9f8`, and `.set Tbl_082243D8` in
    `w36a_0801e93c`).
- GAP FUNCTION (coordinator action): `0x080173bc`, 24 B (20 B
  code + 4 B pool), NOT in func_list: `ldr r2,[pc,#16]` → pool
  `0x082243d8`; `s[12]=4` (word); `s[20] = Tbl[s[9]][4]`
  (word at +16); `bx lr` at `0x080173ce`; pool word
  `0x082243d8` at `0x080173d0`. Needs a gap row for a future
  claim. The `0x080171c0` claim extent (508 B) EXCLUDES this
  function and its pool; the tiny-function pool word is OUTSIDE
  the 508 B extent and must NOT be reproduced by the claim.
- Iteration history (files `w39b_080171c0_v1.c` … `_v7.c`,
  `w39b_080171c0_best.c` = V6):
  - V1 (old): 476 B, 382 diffs. Mode→r8, pos→r6, base→r7;
    case-1 threshold as value-ternary (shared cmp); step folded
    via CSE.
  - V2 (old): 504 B. Mode pinned r6; threshold nested-if;
    s[18] direct; tbl+row split; pos barriers; step split;
    d-ternary per-arm casts. Problems: dispatch copy (pin
    artifact); mode truncation in word check; d-ternary
    neg-form; step branchy; follow direct homes.
  - V3 (old): 500 B. Mode unpinned, pos pinned r7, base pinned
    r8 → dispatch EXACT (`ldrb r6; cmp r6` chain) and threshold
    EXACT (v + barrier). BUT prologue broke (r7 not saved,
    scratch via r6) AND the `sp`-name collision (§1.4)
    corrupted the pos update (`mov r2, sp`).
  - V4 (old): 508 B, 436 diff bytes. `sp` → `spos`, pos
    unpinned, base pinned r8 → prologue restored, size exact.
    Allocation rotated to mode→r7, pos→r6, base→r8 (dispatch
    copy returns).
  - V5 (old): 508 B, 391 diff bytes. All-unpinned (base pin
    removed) → mode→r8 (V1-style). Step short st/st2 added
    (§1.6) — step now matches except cur register.
  - V6 (old): 504 B, 142 diff bytes. If/else-chain dispatch
    (§1.2) + mode pinned r6 as SIGNED int + all V5 fixes.
    Dispatch exact, threshold exact, step exact (except cur
    reg), tail/epilogue exact, case-2 entry/dec exact, table
    blocks exact.
  - V7 (old): 504 B, 142 diff bytes, byte-identical codegen to
    V6 (separate assignments + Path-B `o` copy both neutralized
    — see §1.8, §1.9).
- Remaining diffs (V6/V7 vs ROM, by region):
  - Case-2 `sc & 3` sum temp: ROM `movs r1,#3; ands r1,r0;
    adds r1,r4,r1; lsls r1,#16; lsrs r4,r1,#16` (fresh r1 temp,
    truncate into r4). Mine: `mov r1,#3; and r0,r0,r1;
    add r4,r4,r0; lsl r4,#16; lsr r4,#16` (reuse r0/r4).
    Size-neutral; separate-assignment source shape does not
    change it.
  - Case-2 d-ternary: ROM (§2.4 below). Mine: `and r1,r1,r6;
    cmp; bne true; neg r0,r4; lsl; lsr; b join; true: add r0,r4;
    join: add r4,r0`. Size-neutral vs ROM (both 18 B including
    the condition).
  - Path-B entry copy: ROM `adds r1,r4,#0` at `0x08017338`
    before the s[18] check, then `adds r0,r1,#0` at the Byte12
    call. Mine has neither (single `adds r0,r4,#0` at the call).
    2 bytes.
  - Follow cur/tgt copies: ROM loads into temps r0/r1,
    `subs r3`, then `adds r4,r0; adds r2,r1` (cur→r4 reusing
    other's dead register, tgt→r2). Mine loads directly into
    homes r3/r2, no copies. 4 bytes.
  - Net: ROM longer by 6 (copies) but the build is only 4 short,
    so one further +2-byte surplus region in mine remains
    unlocated (offset cascades mask it — the byte-diff runs
    after the first deficit are dominated by branch/pool offset
    bytes, not instruction differences).

### 2.3 Open question: the d-ternary shifted form (§2.4)

ROM's case-2 d-ternary (`0x080172c4`–`0x080172d4`):

```text
172c4: ands r1, r6        (gw & mode; r1 = gw, r6 = mode)
172c6: cmp r1, #0
172c8: bne 172d0           (true arm)
172ca: lsls r0, r4, #16   (false arm: shift d)
172cc: negs r0, r0        (false arm: negate SHIFTED value)
172ce: b 172d2             (join)
172d0: lsls r0, r4, #16   (true arm: shift d)
172d2: lsrs r0, r0, #16   (join: truncate)
172d4: adds r4, r0, #0    (d = result)
```

Both arms shift d; the false arm negates the shifted value; the
join truncates once (shared `lsrs`). This is GCC's HImode
(narrow) ternary expansion: arms computed in shifted form, join
shifts back. Isolated experiments (`work/dtern.c`, functions f1–f5:
plain ternary, both-arms-cast, if/return, if/else-assign) with
BOTH old_agbcc and main agbcc all yield the SImode form instead
(`and; cmp; bne true; neg; lsl; lsr; b join; true: add; join`) —
false arm neg-then-shift, true arm plain copy, per-arm truncation.
No tested source form yields ROM's shifted form. Hypotheses not
yet tested: a different agbcc version than both bundled ones; a
macro or GNU extension that forces HImode ternary typing; a
construct where the ternary's result feeds directly into a shifted
context without an intermediate assignment to d. The coordinator
may want to try other compiler versions or a construct search for
this fragment; it is the single most instructive open item from
this wave (a matching fragment would also confirm the pattern for
other narrow ternaries in the codebase).

### 2.4 Semantic doubt carried forward (0x080171c0)

The AbsScale fragment: `fx = (cnt-52)<<15` is a fixed-point
argument; `half = fx>>16` is `(cnt-52)/2` for in-range values;
`d = half + (AbsScale(fx) & 3)` looks like a rounding/fractional
adjustment, but AbsScale's exact semantics are unknown (it is
BLOCKED, not matched) — a byte-match would confirm the call
sequence, not AbsScale's meaning. Also the step's `st==0 → 1` is
dead in practice for |diff| > 256 but is emitted from source.

### 2.5 `0x08015ac4` — UNATTEMPTED, partial decode (starting point)

560 B, SetMirrored family, jump-table switch on s[14] (cases 0..6;
`cmp #6; bls table; b tail` at `0x08015ce2`). Prologue `push
{r4,r5,r6,lr}; sub sp,#12`; `p = s + 124` (r6). Shared tails:
`0x08015c96` (mode++ then tail) and `0x08015ce2` (tail: Tick).
Cases seen: case with `SetMirrored(s,?,0)` + `IncUse(s,0)` →
`0x08015c96`; a case doing `s[44]` loads + `0x08017474`
calls + bit-set (`v=(v&15)|64` at a `s[124]+?` byte) +
`s[33]=10` + `IncUse(s,3)` + mode++ → `0x08015bac`;
`Check119(s)` (`0x08011f50`) + `0x08017474` + `0x0801d070`
call with stack args (0,0) + `ldrh [r6,#8]` + `s[124+7]`
check vs 2 → `IncUse(s,7)` + `s[14]=4`, else `IncUse(s,0)`
→ `0x08015c96`; a case with `0x08017478` + `DecIfNonZero`
(`0x08017464`) + `s[44]=0` + `SetMirrored` + `IncUse(s,0)` +
`s[124+4]=0` + `SetBytes(s,0)` (`0x08011f68`) → tail;
a case with `s[33]=60`, `s[18]=40`, `Sub_0801EE14`
(`0x0801ee14`, stack arg 0, s[35] nibble) → `0x08015c96`;
`DecIfNonZero`-adjacent `s[18]--` + `IncUse(s,2)` +
`Text_SelectBlobIdx(127)` (`0x0804a378`) → `0x08015c96`;
a case with `s[10] & 254` + `SetBytes`-family work. Full
disassembly: `dis/08015ac4.txt` (246 lines). Next worker: decode
cases from the jump table (pool at `0x08015ae0`), write a switch
with shared `mode++`/tail labels, and expect cross-jumping of
identical `IncUse` + `s[14]++` tails (as in the W38 template).

### 2.6 `0x0802d928` — UNATTEMPTED, partial decode (starting point)

464 B, 5 bls / 4 distinct callees (`0x0802d574`, `0x0802daf8`,
`0x0803facc`, `0x0803fd68`). Hi-reg heavy prologue: `push
{r4,r5,r6,r7,lr}; mov r7,r9; mov r6,r8; push {r6,r7}`;
args: r0 = u16 (→ r8, sign-extended via `lsl/lsr #16`), r1 = u16
(→ r5, via `lsl/lsr #16`), r2 = u16 (→ r9). First call
`0x0803fd68` (result u8 → r6 via `lsl/lsr #24`); then a sparse
switch on r5 with a binary-search comparison tree (constants
seen: `144<<5` = 4608, `138<<6` = 8832, `157<<5` = 5024,
`148<<5` = 4736, `233<<2` = 932, `202<<6` = 12928, plus pool
constants at `0x0802d980`/`0x0802d99c`/`0x0802d9d8`/`0x0802d9dc`
/`0x0802da00`/`0x0802da14`) with shared target blocks
(`0x0802da18`, `0x0802da1c`, `0x0802da40`, `0x0802da8c`,
`0x0802da92`, `0x0802da98`, `0x0802daa6`, `0x0802dac0`,
`0x0802dace`, `0x0802dadc`, `0x0802dae8`, `0x0802dab2`).
Result register r7 (set to 0/1/5 in seen fragments). Full
disassembly: `dis/0802d928.txt`. Next worker: identify the
switch value set and the per-case r7 assignments + shared tails
before writing C; expect GCC's sparse-switch binary-search tree,
not a jump table.

## 3. Triage / family notes for the next wave

- SetMirrored family (shared callees `0x0800d9ec` IncUse,
  `0x0800d9fc` Tick, `0x0800dd2c` SetMirrored, `0x08011f50`
  Check119, `0x08011f68` SetBytes, `0x08017464` DecIfNonZero,
  `0x08017474`, `0x08017478`, `0x080174a4` SetBit16,
  `0x0804a378` Text_SelectBlobIdx): `0x08015ac4` (560 B,
  §2.5), `0x08016400` (656 B), `0x08015cf4` (668 B),
  `0x08016690` (760 B), `0x08016988` (780 B), `0x080160d4`
  (812 B). Cracking one should template the rest (W38's
  216–244 B versions are the pattern: mode dispatch,
  SetMirrored/IncUse/Check119/SetBit16/DecIfNonZero/SetBytes/
  Tick calls, goto-shared tails). Also `0x08014cf0` (456 B),
  `0x08019fb8` (484 B), `0x08023824` (600 B), `0x0801fa68`
  (616 B), `0x0801e4cc` (688 B) share parts of this callee set.
- 0x08045xxx family (shared callees `0x08006a54`,
  `0x080070f0`, `0x08007324`, `0x0800741c`, `0x080245e0`,
  `0x08024634`, `0x08024648`, `0x08024818`, `0x08024848`):
  `0x08045c54` (460 B), `0x08045a5c` (504 B), `0x08043430`
  (512 B), `0x08044298` (520 B), `0x08044fb8` (584 B).
- 0x0802cxxx family (shared callees `0x0802c7b4`,
  `0x0802d7a0`, `0x0802fc28`, `0x080400a8`, `0x0804dee8`):
  `0x0802cb0c` (472 B), `0x0802cce4` (488 B), `0x0802d184`
  (604 B), `0x0802f92c` (632 B), `0x0802cecc` (696 B),
  `0x0802c7dc` (816 B).
- Low-callee candidates (most tractable after the families):
  `0x08001800` (740 B, 1 bl: `0x080017a0`),
  `0x0804d1e8` (1100 B, 2 distinct bls: `0x0804d130`,
  `0x0804d180`), `0x0800105c` (932 B, 2 distinct: `0x080016c0`,
  `0x08001754`), `0x080088c4` (580 B, 2 distinct: `0x080062b4`,
  matched `0x08008b08`), `0x08049dac` (760 B, 2 distinct:
  `0x0804a0a4`, `0x0804a378`), `0x08028ce4` (776 B, 2
  distinct: `0x08028fec`, `0x0804a378`).
- `0x0804a8ac` (460 B) and `0x0804a694` (496 B) are twins
  (same bl set `0x08001400`, `0x080014f8`, `0x0804ad4c`;
  each has an early `pop {r5,pc}` / `bx lr` terminator shortly
  after entry — needs care, possibly early-exit paths, not yet
  investigated).
- `0x0800a150` (1244 B) and `0x0800a754` (1308 B) have `bx lr`
  near the end of their windows.
- The two huge entries (`0x0803ca7c` 3952 B, `0x080298fc`
  9190 B) are genuine func_list starts whose TSV size equals
  the next-start distance, but no host/interior determination
  has been made — do NOT claim either as a single leaf without
  that verification.

## 4. Landing notes for the coordinator

- `0x0802f5ac`: staged `w39b_0802f5ac.c`, 896 B, old_agbcc.
  `.set` callee `Sub_0802D7A0` vs build global `Obj_AddEntry`
  — adjudicate at landing. Intended section: new `.text`
  section at `0x0802f5ac`. No section attribute in the staged
  file (per brief).
- `0x080171c0`: NOT landed (blocked). If a future worker
  matches it: claim extent 508 B (NOT 532 B); add a gap row for
  `0x080173bc` (24 B); strip `.set` lines for build globals
  (`Byte12_Gt1_080170c4`, `ChipSlot_Tick`, `gEwram_02003670`,
  `Tbl_082243D8`); adjudicate `Sub_080052A0` vs build symbol
  `AbsScale_52A0`.
- `0x08030b1a`: SKIP — interior of matched `0x08030ad4`.
- Staging dir `staging/w39b_bulk/` must be preserved until the
  coordinator verifies (per brief — do not clean up early).
  Variants, triage, disassemblies, and the harness all live there.
- No files outside `staging/w39b_bulk/` and this notes file
  were edited by this worker. No registry/Makefile/ldscript/
  PROGRESS edits. No chat messages sent. No ROM bytes copied
  anywhere (disassembly excerpts only, in notes and staging).
