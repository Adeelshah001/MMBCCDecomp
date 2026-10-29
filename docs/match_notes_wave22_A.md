# Wave 22 Worker A — Match Notes

## Harness fix: trailing-pool extent correction

### Problem
`staging/wave21_B/addrs_sizes.txt` (and the size table generally) records the
**code size**, excluding trailing literal pools by 2–6 B. The isolated
build+diff harness extracted only the nominal size, so:
- pool loads referencing words past the nominal end were flagged
  "out-of-bounds" when they are actually in-extent;
- even a perfect C file could never verify 0-diff (the ROM extract was
  truncated before the pool).

Wave-21-B proved the principle on 0x08042ae4 (120 B code + 4 B pool = 124 B
full extent, 0-diff). This wave generalizes it harness-wide.

### fix_extents.py
`staging/wave22_A/fix_extents.py` computes the TRUE section extent per
candidate:
1. Parse all `. = 0xADDR;` slots from `mmbcc/ldscript.ld` (725 slots).
2. For each `(addr, nominal)` row: disassemble ROM
   `[addr, min(addr+nominal+128, next_slot))` as Thumb.
3. Collect `(instr_addr, target)` for `ldr rt,[pc,#imm]` / `add rt,pc,#imm`
   via objdump `@ (0xTARGET)` annotations.
4. Keep only refs whose **instruction** is inside `[addr, nominal_end)` —
   loads past nominal_end belong to the next function (lesson: 0x08004998's
   window caught the next function's pools at 0x08004a3c/0x08004a94).
5. Fixpoint phantom elimination: drop refs whose instruction address is
   itself a pool target (pool words misdisassembled as `ldr`; lesson:
   0x08041890's mid-function pool words at 0x080418e4/0x08041910/0x08041950
   disassemble as phantom `ldr r5,[pc]` → 0x08041a08/0x08041a34/0x08041b44).
6. TRUE extent = `max(nominal_end, max_target + 4)`; targets `>= next_slot`
   are flagged EXTERNAL (absolute `.set` data, not this section).

### Results
- 131 wave-21-B rows scanned: **56 EXTEND** (true > nominal, deltas +4..+50),
  75 OK, 0 OVERSHOOT, 0 EXTERNAL_FAR.
- Outputs: `staging/wave22_A/corrected_addrs_sizes.txt` (harness input),
  `staging/wave22_A/extent_report.tsv` (full per-row analysis).
- Key corrections: 0x08011e20 112→120, 0x08016e84 114→120, 0x08016efc
  116→120, 0x0800e440/0x0800e748 118→128, 0x080097cc 122→148,
  0x08026184 126→132, 0x08004998 102→108, 0x08042ae4 120→124 (confirms
  wave-21-B).

### w22a.sh (hardened harness)
`staging/wave22_A/w22a.sh <addr> <cfile> [main|old|noiw]` — like w21b.sh but:
- reads TRUE extents from `corrected_addrs_sizes.txt`;
- non-empty assertions at every step (.i/.s/.o/.elf/.bin/rom extract);
- requires `binlen == true_extent` (exact byte count);
- neighbor check: true end must not cross the next ldscript slot;
- reports MATCHED only on 0 diffs over the full extent.

## Matched (1)

| Address | Name | Size | Compiler | Notes |
|---------|------|------|----------|-------|
| 0x08011e20 | Node_PopAndInit_11E20 | 120 (112+8 pool) | main | Sibling of w16b_08017000; sub_08004424(*(u32*)0x02005270); bit-ops at +35; node[9]=c; node[5]=**(0x08223cc0+c*4); *(0x02005020+b*4)=node |

Full-build verified 0-diff; landed per hygiene (`.set` stripped for
globally-defined `sub_08004424`; pools are raw hex constants).
Registry appended.

## New idioms

### Pinned-barrier for pool loads (0x08011e20)
`__asm__ volatile("" : "+r" (tbl));` after `tbl = (u32 *)0x08223cc0;`
forces the literal pool load to materialize BEFORE the following
`strb`/`lsls`, matching ROM's hoisted load schedule. Without it the
scheduler sinks the load to first use (10 diffs).

### Array-index idiom steers pool-load registers (0x08011e20)
`*(u32 *)tbl[c]` puts the table pointer in r1 and the shifted index in
r0 (`lsls r0; adds r0,r0,r1`); the explicit `(tbl + (c<<2))` form puts the
table in r0 and index in r1. When ROM shows tbl→r1/index→r0, use the
array-index form.

### Tied-opaque pool anti-folding (0x0800e440, attempted)
`__asm__ volatile("" : "=r" (S) : "0" ((u8 *)0x02005130));` makes S an
opaque register value, defeating constant folding of `S+37`/`S+24` into
spurious pool words (0x02005155, 0x02005148). From wave-16-D notes.

## Blocked / Parked (with precise diffs)

### 0x08016e84 (114→120) / 0x08016efc (116→120) — PARKED: high-reg allocation
Twin 5/6-param setup functions. Callees all matched (IncU8_12,
SetField120_U16Pair, SetBytes_08011F68). ROM allocates b→r4/c→r5/d→r6
(low callee-saved), a→r8/e→r9, sl→sl(a+124), no spill, no r7.
- Natural codegen: 112 B, b→r5/c→r6/d→r9/e→sl/slp→r7 (wrong regs).
- Pinning b,c,d→r4,r5,r6 causes `add sp,#-4` spill (too many live vars).
- `ldrsh` pair: ROM does `movs r3,#0; ldrsh r1,[r0,r3]; movs r3,#2;
  ldrsh r2,[r0,r3]` (indexed, sign-extended). Natural gives `ldrh`
  (compiler proves u16-param conversion needs only zero-extend).
- Needs: allocation without spill + forced ldrsh. Possible angles:
  old_agbcc (tried: 108 B, different alloc), or restructure to reduce
  live ranges.

### 0x0800e440 (118→128) / 0x0800e748 (118→128) — PARKED: pool placement
State machines on S[21] (S=(u8*)0x02005130). Callees all matched
(ChipInit_0801709C, Byte12_Gt1_080170c4, SetByte20_Clear21to23_02005130,
ListIterate_D568 — note real name, not the _0800D568 alias).
- Mid-function pools 0x02005130 ×2 (not CSE'd across branches); trailing
  pools 0x02005270/0x020053c0.
- Blocker 1: `S[37]`/`S[24]` fold to constant pools (0x02005155,
  0x02005148) when S is a constant; tied-opaque fixes folding but…
- Blocker 2: …the tied-opaque asm perturbs pool placement — pool lands
  mid-function (0x800e45c) instead of after the initial branch block
  (0x800e454), breaking branch offsets.
- Needs: anti-folding that doesn't disturb the "pool after first
  unconditional jump" placement. Possible: `.short` nop pool barrier,
  or accept two-pool structure via separate opaque vars per block.

### 0x080097cc (122→148) — NOT ATTEMPTED (complex)
Complex address math: 6 pools (0x06010000/0x081720b4/0x081720cc/
0x06010020/0x06010400/0x06010420), bit manipulations, 4× Memcpy16 calls.
True extent 148 B confirmed. Needs full re-derivation.

### 0x08026184 (126→132) — NOT ATTEMPTED (complex)
Loop copy function; pool 0x00000e82 at 0x08026204 (2 B past end).
Callees 0x0802520c/0x0802526c are UNMATCHED (not in registry).
Needs callee matching first.

### 0x08020b60 (158, OK) — ATTEMPTED, 10 B short
Struct init with 3 in-bounds pools. Best: 148 B (10 B short).
- Fixed: double-OR anti-folding (`b=2|b; b=1|b` for `|=3`).
- Remaining: compiler pushes {r4,r5,lr} vs ROM {r4,lr}; r5 holds
  constant 1 reused for `(S+72)[0]=1` (ROM does fresh `movs r0,#1`).
  Needs CSE-break on the constant 1.

## Files
- `staging/wave22_A/fix_extents.py` — extent correction harness
- `staging/wave22_A/corrected_addrs_sizes.txt` — 131 rows, true extents
- `staging/wave22_A/extent_report.tsv` — per-row analysis
- `staging/wave22_A/w22a.sh` — hardened build+diff harness
- `staging/wave22_A/w22a_dis.sh` — disassembly with true extents
- `mmbcc/src/w22a_08011e20.c` — landed match
