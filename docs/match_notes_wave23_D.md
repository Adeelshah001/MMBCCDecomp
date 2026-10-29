# Wave 23-D Notes (Worker D, bulk leaves-up)

## Matched (21)

### Script-interpreter ASM cluster (20) — src/w23d_scriptops.c
Hand-written Thumb assembly cluster 0x0804BDE0–0x0804C03C, matched via
ASM-STAGED file-scope `__asm__` blocks. All 20 verified byte-identical in
full built ROM. See staging/wave23_D/verify_scriptops.py.

- ListWalk_0804BDE0 (0x0804BDE0, 48 B) — was BLOCKED (tst wall); cracked via ASM-STAGING
- ValidateScriptPtr_0804BE2A (0x0804BE2A, 28 B) — was BLOCKED (ROM-ptr validator); cracked
- 18 others in 0x0804BE5C–0x0804C03C range (see registry)

Key idioms:
- `mov ip,lr` / `bx ip` and `pop {r0}; bx r0` are hand-asm conventions — agbcc cannot emit these; use ASM-STAGING
- 0x0804BE28 is a documented alt-entry (not a separate function)
- Tail-calls skip prologues (`b` to 0x0804BE46/0x0804BE52, not `bl`)
- `.syntax unified` required (GAS defaults to pre-UAL divided syntax)
- `.align 1` needed for the 30 B section (GAS pads with 46c0 nop fill)
- Link ALL sections together for staging (isolated links break cross-section `bl`)
- Interior entries (0x0804BE46, 0x0804BE52): permanent absolute `.set` symbols (never defined)

### F_080378B8 (0x080378B8, 88 B + 4 pool) — src/w23d_080378b8.c
Flag-dispatch returning 0-4. Callees: ChkFlag_080247E8, TblGet_f0A, F_080247C4 (all matched).
- Pool 0x06001E68 was WRONG; correct is 0x469E (18078) — verified from ROM bytes at 0x08037910
- ChkFlag logic INVERTED: `if ((u16)ChkFlag(v) == 0) r = 3;` (ROM does bne to skip)
- cmp order: `v == *(p + 0x469E)` (not `*(p+...) == v`) for `cmp r4, r0` encoding

## Parked (with staging)

### 0x08007728 (74 B) — parked_08007728.c
Resists: compiler folds `(155<<2)` into the pool pointer; `p` gets callee-saved
reg instead of being reloaded; 622 pool-forcing hard. Needs pool-placement/
register-steering angles.

### 0x080103E0 (114 B) — parked_080103e0.c
Pool-in-the-middle: literal 0x02005160 at 0x1043C, embedded AFTER unconditional
`b.n` at 0x1043A, BEFORE L2 code at 0x10440. agbcc dumps pool in gap after
unconditional branch (wave-19 pool-control strategy). Hard to reproduce.

### 0x08010E00 (122 B) — parked_08010e00.c
Pool-in-the-middle: literal 0x020051B0 at 0x10E68, after `b.n` at 0x10E64,
before fail-path code at 0x10E6C. Same pattern as 0x080103E0.

### 0x08026184 (132 B) — parked_08026184.c
NewNode-family init (Fill_0802520C x2, Append_0802526C). Complex loop with
u16 increment idiom (`lsls #16; adds #65536; lsrs #16` for `r4++`, `asrs #16`
for signed compare). Structure mismatch — needs sibling-shape transfer from
matched NewNode init.

### 0x080263A4 (138 B) — parked_080263a4.c
Validation function (TblGet11 x2). Inverted condition: ROM does
`cmp r0,#198; bls fail` meaning fail if `(u8)(p[1]-1) <= 198`. Complex
control flow with 0=success/1=fail (inverted returns). Needs restructuring.

## In progress
- 0x08002EF4 (48 B): 34 diffs. Pool-forcing issues: 0xAA must come from pool
  (not `mov`), 0x02000819 must come from pool (not `adds #1`). Static const
  not working as expected.

## Tooling
- staging/wave23_D/w23d.sh: hardened harness. Now supports Thumb-marked stubs
  via staging/wave23_D/stubs.s (place each `.text.stub_*` at real address in
  linker script). This avoids `--defsym` veneer problem.
- Key lesson: `--defsym` creates absolute symbols → ld generates
  `__*_from_thumb` veneers. Solution: assemble stub `.s` with `.thumb_func`
  + `.globl`, place at real address via linker script.

## Remaining
81 rows in staging/wave23_D/worklist.json (after filtering matched/blocked).
74 true leaves-up (all callees matched) per wave22_layer.tsv callee analysis.
Next smallest unparked: 0x08002EF4 (30 B, in progress), 0x08002D84 (54 B,
BLOCKED callee — skip), 0x0804C630 (84 B, many unmatched callees — hard),
0x080097CC (122 B), 0x0804CB28 (126 B), 0x0804CBCC (140 B), 0x0800A6BC (142 B)...
