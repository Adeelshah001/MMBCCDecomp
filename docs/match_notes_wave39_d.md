# Wave 39 Worker D Notes (extent targets + 23c38 C variants)

Staging: `staging/w39d_extents/` (RESULTS.md is the record; this
file is the landing companion). Coordinator owns landing, registry,
Makefile, ldscript. Baserom SHA-1 verified:
`72309736f3820470c6f372d6a05ad1f16bc5a946`, read in place only.

## 1. Extent evidence in full

### 0x08009140 — TRUE 248 B (0x08009140–0x08009238)
Func-list neighbors: `... 00909C, 009140, 009238 (MATCHED W37-A),
0092C8 ...`. Next-function prologue at 0x08009238:
`b510 push {r4, lr}`, then `ldr r1,[pc,#100]`, `ldr r0,[pc,#100]`
— a real function (its own matched source is
`mmbcc/src/w37a_08009238_MATCHED.c`, 144 B to 0x080092c8).

Disassembly summary (Thumb, force-thumb):
- `push {r4, r5, lr}`; `r5 = 0x02003670` (pool 0x91f8);
  `r4 = r5 + 4`.
- `Sub_2300(0x0830b37c, 150<<7)`; `Memset16(0x1111, *(u32*)(r5+8)
  + (200<<3), 32)`; `Memcpy16(0x0806bce0, *(u32*)(r5+8) + (204<<3),
  32)`; `Memset16(0x3333, *(u32*)(r5+8) + (208<<3), 32)`;
  `Sub_2300(0x0830b3e0, 0x46a0)`;
  `Memcpy16(0x08063fd4, *(u32*)(r5+8) + (190<<5), 192<<1)`;
  `Sub_2300(0x0830b78c, 0x5b20)`; `Sub_2300(0x0830b3cc, 0x5a40)`.
- `r = 0x0805c95c`; `Copy7bec(r,11)`, `(r+32,12)`, `(r+64,13)`,
  `r += 96`, `(r,14)`; `Copy7bec(0x0806eea0, 10)`.
- Gate: `r5 += 0x11ae` (pool 0x9230); `if ((*r5 & 248) != 16)
  Copy7bec(0x0806b560, 7)` (pool 0x9234). `pop; bx` at 0x91f4,
  pad `0000` at 0x91f6, pool 0x91f8–0x9237 (16 words, first-use
  order: 02003670, 0830b37c, 00001111, 0806bce0, 00003333,
  0830b3e0, 000046a0, 08063fd4, 0830b78c, 00005b20, 0830b3cc,
  00005a40, 0805c95c, 0806eea0, 000011ae, 0806b560).
- Why 244 is wrong: the last pool word at 0x9234 is live code
  data (referenced, passed to a call). There is no function start
  at 0x9234 and no gap: 248 B ends exactly on the 0x9238 prologue.
- Twin note: 0x08009238 is the same family (same base 0x02003670,
  same 0x11ae gate, same Copy7bec(0x0806b560, 7) call) but gates
  the whole function early, while 0x08009140 gates only the last
  call at the end. The staged 09140 file borrows the 09238
  barrier idiom (`__asm__ volatile("" : "+r"(base))` before
  `base += 0x11ae`) to keep the gate offset as a separate pool
  word plus add, not a folded 0x0200481e constant.
- Compiler: old_agbcc -O2 -mthumb-interwork, 0 diffs. Main
  agbcc: 5 diffs in the gate block only — use old_agbcc.

### 0x0803b898 — TRUE 256 B (0x0803b898–0x0803b998)
Func-list neighbors: `... 03B3A0, 03B898, 03B998 (BLOCKED Wave 6),
03C20E (via-B label inside 03B998), 03C238, 03C4C0 ...`.
Next-function prologue at 0x0803b998: `b5f0 push {r4, r5, r6,
r7, lr}`, then `mov r7, r9` — a real function start.

Disassembly summary:
- `push {r4, r5, lr}; sub sp, #4`; `r5 = arg`; `r4` is the
  stack-arg holder `e`.
- Unrolled x4: `t = (u8)MapTableVal_499AC(i)`;
  `CondRectFill(22+i, t, 2, 2*i+1, e)` with `e = 0` set after
  the FIRST Map call (not at entry) and reused via `str r4,[sp]`
  before every 5-arg call.
- `e = 2` set after the first 6a54 deref (not before the call);
  `BlitReq(*(u32*)0x08231960, 4, 1, 13, e)`,
  `(*(u32*)0x08231968, 4, 3, 13, e)`,
  `(*(u32*)0x08231970, 4, 5, 13, e)`,
  `(*(u32*)0x08231978, 4, 7, 13, e)`,
  `GatedDispatch(*(u32*)(s+32), 20, 1, 7, e)`,
  `BlitReq(*(u32*)0x08231958, 27, 1, 1, e)`.
- Tail: `dst = 0x02004ce0` (pool 0x3b990);
  `*(u16*)(dst+40) = 20`; `s += 0x4698` (pool 0x3b994);
  `b = *s`; `*(u16*)(dst+42) = (b<<4) + 8`.
- `bx` at 0x3b978, pad `0000` at 0x3b97a, pool 0x3b97c–0x3b997
  (7 words: 08231960, 08231968, 08231970, 08231978, 08231958,
  02004ce0, 00004698 — note the five 0x082319xx words are 8 apart
  in ascending order 58/60/68/70/78, used in order
  60/68/70/78/58).
- Why 2464 is wrong: 0x0803c238 − 0x0803b898 = 2464, but the span
  contains the 0x0803b998 prologue, the 0x0803b978 `bx lr`
  terminator, and the 0x0803c20e interior label. A 2464 B
  "function" would swallow at least one other function whole.
  The byteclass range `03B898-03B979 code` corroborates the
  code end at 0x3b979 (bx + pad).
- Compiler: old_agbcc -O2 -mthumb-interwork, 0 diffs. Main
  agbcc: 2 diffs in the tail only — use old_agbcc.
- Variant history (for the record): v1 (unpinned, `e = 0` at
  entry, `e = 2` before first 6a54 call) gave 33 diffs, both
  compilers — the diffs were exactly the s/e register swap
  (s in r4, e in r5 vs ROM s in r5, e in r4) plus the two
  assignment placements. v2 pinned s->r5 / e->r4 and split the
  first call of each group into a temp: 5 diffs (old; first
  block's `mov r4,#0` scheduled before the u8 truncation's
  lsl/lsr). v3 changed the Map-result temp from `int` (+ cast)
  to `u8` (truncation at assignment, before `e = 0`): 0 diffs.
  The staged file is v3 (renamed to `w39d_0803b898.c`).

### 0x08023c38 — 172 B, no extent dispute
Next function 0x08023ce4 MATCHED (Xor_23CE4, W10-L, ldscript
slot). Full decode is in RESULTS.md's blocked notes and in the
v4 `.s` discussion below.

## 2. Per-function notes for the coordinator

### 0x08009140 (`staging/w39d_extents/w39d_08009140.c`)
- Intended section `.text.w39d_08009140`. No section attribute
  in the staged file.
- `.set` lines (END of file): Sub_08002300, Memset16, Memcpy16,
  Sub_08007BEC. Strip Memcpy16 at landing (build global
  `Memcpy16` at 0x08000758, uppercase T — confirm with `nm`,
  never `head -1`). Keep the other three; Sub_08007BEC is an
  alias, not the build name `Copy_08007BEC`.
- The `p = base + 4` / `*(u32 *)(p + 4)` form reproduces ROM's
  repeated `ldr r1, [r4, #4]` loads (no hoisting: r4/r5 are the
  only callee-saved registers used, so the value cannot survive
  the calls in a register).

### 0x0803b898 (`staging/w39d_extents/w39d_0803b898.c`)
- Intended section `.text.w39d_0803b898`. No section attribute
  in the staged file.
- `.set` lines (END of file): Sub_0800499AC, Sub_080073D4,
  Sub_08006A54, Sub_08006DD8. All four targets are MATCHED in
  the build under DIFFERENT names (MapTableVal_499AC,
  CondRectFill_080073D4, Gfx_BlitRequest, GatedDispatch), so the
  aliases should not collide — but verify with the full-nm
  UPPERCASE check before landing (Wave 38 nm-case trap: a
  lowercase-'a' local does not resolve, and `head -1` hides
  second lines).
- The 5-arg declarations are load-bearing: ROM passes a 5th
  stack argument (`e`) to CondRectFill even though its MATCHED
  source declares 4 params (the callee ignores it). Landing the
  file with a 4-arg declaration would drop the `sub sp, #4`
  frame and break the match. Do not "fix" the arity.
- Register pins (`s` -> r5, `e` -> r4) are function-wide pins;
  they are what ROM uses, not a workaround to remove.

### 0x08023c38 (BLOCKED — no candidate staged)
- Files: `staging/w39d_extents/attempts_23c38/v0_baseline.c`
  (W37-C2 verbatim), `v1_s16.c`, `v2_pins.c`, `v3_shiftpin.c`,
  `v4_recompute.c`, `v5_unsigned.c`. Best: v4, old_agbcc -O2
  -mthumb-interwork, 172 B, 101 diffs over the full extent
  (v3 with -O1 ties at 172 B / 101 diffs with a different diff
  distribution). No `w39d_08023c38.c` exists on purpose.
- ROM allocation to beat: sl=shift, r5=bit, r9=bit copy,
  r6=byte, r4=i (plain), r8=i<<16, r7=dst+i, dst->[sp],
  src->[sp+4], sub sp,#8. Tail + epilogue already match in v4
  except `sub sp,#4` vs `#8`.
- What did NOT work: pinning everything (v2: loop restructured,
  176 B, 146 diffs); recomputing `sh & 7` in the second part
  (v4: recomputes inline, no r9 copy); unsigned sh/bit/byte
  (v5: 111 diffs). Flag variants tried: -O1/-Os/no-interwork
  for v1/v3 (see RESULTS.md).
- No asm transcription was staged or attempted for this
  function, per the brief (not sanctioned yet).

## 3. Idioms used / confirmed
- Next-prologue extent determination (never a self-measured
  window): 09140 via 09238's `b510` prologue + live last pool
  word; 3b898 via 3b998's `b5f0` prologue + `bx` + pool.
- Pool-word-as-evidence: a disputed tail word that is referenced
  by a `ldr [pc]` and passed to a call is code data, not pad.
- 09238-twin barrier idiom (`volatile "+r"` before `+=`) for
  the 09140 gate offset.
- Register pin + split-temp placement (3b898): pin s->r5 /
  e->r4; put the `e` assignments AFTER the first deref/call of
  each group by splitting that call's first argument into a
  temp; make the Map-result temp `u8` so truncation precedes
  the `e = 0` store.
- s16 counter idiom (23c38 v1/v3/v4): `s16 i` in a `for` loop
  reproduces ROM's `(i+1)<<16` / `lsr` / `asr` / `cmp <=13`
  tail; the loop is NOT hoisted in these variants (bit/byte
  recomputed per iteration), contrary to the W37-C2 report for
  their int-counter version.
