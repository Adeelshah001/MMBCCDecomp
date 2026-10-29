# Wave 35 Coordinator Notes — 2026-10-24

## Headline
930 / 1674 C-matched (+37), 13 ASM, 943 byte-identical total. Full regression: 921 sections, 862 clean, 57 accepted 2B c046 tail artifacts, 2 pre-existing dirty (mainloop, text_open). Zero regressions.

## Landed (37, all independently re-verified 0-diff from clean-room builds AND in-built-ROM extraction)
- B (9): 0x0800b3f8, 0x0800b420, 0x08022e88, 0x0802d488, 0x0804b350 (old), 0x08027d18 (48 B true), 0x080267c0, 0x0804c780, 0x0804c288 (+ fix_0804c288.py patch).
- D (3): 0x0804c820, 0x0804990c, 0x0801b630.
- A/coordinator (1): 0x0800d9fc ChipSlot_Tick (324 B, old + fix_0800d9fc.py H-first reorder patch).
- C (24): 0x0800c5a4, 0x0800cbdc (func_list gaps), 0x08026dbc, 0x080375c8, 0x08000e28, 0x08006e30, 0x080079f0, 0x0800c748 (56 B true), 0x0800c8f0 (56 B true), 0x0800ee98, 0x08004dbc, 0x08022f48, 0x0804cecc, 0x0801112c, 0x0801d89c, 0x080275b4, 0x08002d84, 0x080047a4, 0x0800741c, 0x0800b320, 0x0801f9a4, 0x0802756c, 0x08027cb4, 0x080110e0.

## Coordinator actions / catches
- ChipSlot_Tick: sanctioned targeted 10-byte patch on v29 (32 C variants + micro-tests exhausted for the H-first group; gcc sink-to-compare-site invariant across source order, operator form, compiler version). Verified 0 diffs / exact 324 B section from clean rebuild.
- Landing fix: removed temporary `.globl ChipSlot_Tick .set` in src/wave3_b.c (its own comment directed removal on match; otherwise duplicate-symbol).
- D .set hygiene: stripped same-name .sets (Vec2_AddMirrored, ChipInit_080178A8, MaxAssign_17, FlagBit_Set_11D68); renamed Worker_0804C5F4 -> ClearSignBit_0804C5F4; kept .set for BLOCKED Vec2_CopyMirrored. All other worker local .sets kept per W34 precedent (no .globl anywhere — byte-safe).
- ChipSlot_Tick section renamed .text.v8 -> .text.w35a_0800d9fc; 2 unmatched-callee .sets added (sub_080042B8, sub_0800244C); Wrap_08002904 resolves to real MATCHED symbol.
- Registry: append-only; 930 distinct active MATCHED (936 MATCHED rows - 6 historical reverted duplicates: 0x08011e20, 0x08042a64, 0x0801e14c, 0x080173d4, 0x0801787c, 0x0801e77c). Zero new duplicates. BLOCKED rows 305 (+20). INTERIOR 30 (+1: 0x08023b2a, host 0x08023aec).
- Toolchain: binutils vanished twice during the wave; reinstalled from persistent .deb (dpkg lock waited out, not forced).

## Open items for parent decision
1. **Function-count denominator:** Worker C's v2.8 addendum adds 2 matched functions (0x0800c5a4/0x0800cbdc) -> 1674 -> 1676 if accepted. Headline kept at 930/1674 pending parent convention call; with addendum it is 930/1676.
2. **0x08027d48 leaf:** 4-byte leaf (ldrb r0,[r0,#2]; bx lr) identified by Worker B at 0x08027d48, missing from func_list, NOT matched. Recommend a gap row (would make 1677 with the v2.8 addendum).
3. **0x08030ad4 true extent:** TSV says 68 B but code runs past it (sub sp,#80 dispatcher, no epilogue at offset 66+). Needs next-function-in-address-order determination before assignment.

## Parked / next (Wave 36 candidates)
- Bulk lines 109-250 (142 lines) from docs/wave34_unattempted.tsv.
- Near-miss closers: 0x0802fbf0 (4 diffs), 0x080272e0 (7 diffs), 0x0802873c (1 diff), 0x08001c08 (2 diffs).
- 0x0801a9ac twin family orr-order wall (4 diffs x3: 0x0801a9ac/0x0801b8d0/0x0801cc94).
- 0x0800b448 (28 diffs, bb fusion; W15-D barrier v4 lost with /tmp, needs re-derivation).
- Blocked revisits with Wave-35 idioms (statement-split pool-fold defeat, goto label order, split shift, loop-top zero -> r6, main-vs-old lr-push rule).
