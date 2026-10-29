# xrefs — MMBCC call graph + cross-reference database (Phase 2)

Mechanical, complete call graph over all **1703** known function starts (51 A + 1600 v2 B + 52 v2.5 B; fixed hi-reg MOV decoder)
(`func_list_v2.txt` A/B + `func_list_v2_1_addendum.txt` + `func_list_v2_2_addendum.txt`
+ `func_list_v2_3_addendum.txt` + `func_list_v2_4_addendum.txt`;
the 6 v2.1 `ALT-ENTRY, not counted` rows are excluded).

## Files

| file | contents |
|---|---|
| `xrefs.tsv` | one row per edge: `src_func\toffset\tsrc_addr\tkind\tdst_func\tdst_offset\tnote` — 15,945 rows |
| `xrefs_unresolved.tsv` | indirect `bx`/`mov pc,rX` exits that could not be resolved to a target (145) + decode anomalies |
| `xrefs_dataptrs.tsv` | whole-ROM scan: every aligned 32-bit word holding a code pointer (3,285) |
| `func_stats.tsv` | per-function instruction stats (mode, size, edge counts, loop/mem/shift tallies) |
| `btail_candidates.tsv` | `b`-to-unowned targets that forward-validate (685) — tail-call/shared-epilogue candidates for Phase 3 |
| `build_xrefs.py` | generator script (imports `gen_func_list_v2` for the ARM decoders + SHA-1 gate; carries a corrected `dec_thumb`, see below) |

## Column semantics (`xrefs.tsv`)

- `src_func` — symbol from the func lists, e.g. `sub_0804DB38` (crt0 entries keep names: `Init`, `IntrWait`, …).
- `offset` — the function's **file offset**, 6 hex digits (`04DB38`). ROM address = `0x08000000 + offset`.
- `src_addr` — file offset of the instruction/edge source, 6 hex digits.
- `kind` — one of:
  - `bl` — direct branch-and-link. Thumb BL uses the ARMv4T decode (sign-extend from bit 22, no J1/J2).
  - `bx` — resolved indirect branch/call: `bx rN` where `rN` was loaded by a dominating `ldr rN,[pc,#imm]`
    (pool bit 0 selects Thumb/ARM target), or `mov lr,pc; bx rN` mode-switching calls (noted).
  - `pool` — literal-pool reference: `ldr rD,[pc,#imm]` reading pool word at `dst_offset`.
  - `dataptr` — `ldr pc,[pc,#imm]` (none occur in any decoded body; the kind is reserved).
  - `bcond` — conditional branch; `dst_func` is filled when the target is a known start
    (otherwise the owning function with `target mid-body`, or `internal`).
  - `tailcall` — unconditional `b` to another function's start (or into its body).
- `dst_func` — target symbol, or empty when the target is not a known start.
- `dst_offset` — target file offset (6 hex); for `pool` rows this is the **pool word address**.
- `note` — free text: pool values (`[0x08030C68]=08030C6C`), `call (mov lr,pc); mode-switch`,
  `target mid-body`, `target unowned`, branch condition (`beq`), etc.

All offsets are **file offsets** (matching `func_list_v2.txt`); add `0x08000000` for ROM addresses.

## How it was built

`build_xrefs.py` decodes every function body with `gen_func_list_v2.dec_thumb` /
`dec_arm`, tracking the `ldr`-literal / `pop` register tags exactly like the Phase-1
descent, so `bx rN` / `ldr pc,[pc]` resolve through literal pools. Bodies stop at other
function starts (tail calls) but are **not** clipped to the v2 owner map, so the
v2.2 addendum bodies decode fully (decoded bodies agree with the v2 owner map on
60,394/60,394 insns). Data-pointer scan covers the whole 8 MiB ROM: every aligned
word `0x08000000 ≤ v ≤ 0x0804FFFF` whose target lands in the code region.

## Query examples

```bash
D=~/workspace/mmbcc-decomp/docs
# all callers of the CpuSet veneer
awk -F'\t' '$4=="bl" && $5=="sub_0804DB28"' $D/xrefs.tsv
# every literal-pool word read by one function, with values
awk -F'\t' '$1=="sub_08030B18" && $4=="pool"' $D/xrefs.tsv
# most-called functions (bl + tailcall + mode-switch bx)
awk -F'\t' '$4=="bl"||$4=="tailcall"||($4=="bx"&&/mode-switch/) {c[$5]++} END{for(k in c) print c[k],k}' \
  $D/xrefs.tsv | sort -rn | head -20
# unresolved indirect branches in a function (switch dispatch / callbacks)
awk -F'\t' '$1=="sub_08000300"' $D/xrefs_unresolved.tsv
# data tables pointing at a function (callback/state tables)
awk -F'\t' '$5=="sub_08017D50" && $7=="data"' $D/xrefs_dataptrs.tsv
# jump-table-like runs: consecutive code-pointer words
awk -F'\t' 'NR>1{print $1}' $D/xrefs_dataptrs.tsv | python3 -c "
import sys
offs=sorted(int(l.strip(),16) for l in sys.stdin); run=[offs[0]]
for o in offs[1:]:
    if o==run[-1]+4: run.append(o)
    else:
        if len(run)>=8: print('%08X len=%d'%(run[0],len(run)))
        run=[o]"
```

## Known caveats (for Phase 3)

0. **Decoder bug found and fixed locally.** `gen_func_list_v2.dec_thumb` has the
   hi-register `MOV` Rs/Rd high bits **swapped** (it maps bit7→Rs-high,
   bit6→Rd-high; the ARMv4T encoding is bit6→Rs-high, bit7→Rd-high — verified
   against `arm-none-eabi-as`: `mov pc,r0`=0x4687, `mov r7,r8`=0x4647,
   `mov pc,r8`=0x46C7). Effects: (a) real `mov pc,r0` switch-dispatch jumps
   decoded as `fall` — bodies chained through jump tables into case handlers
   (e.g. `sub_08030B18` was 2,707 insns / 9,814 B / 295 bl, now 153 / 334 / 11);
   (b) real `mov r7,r8`-style moves decoded as `bx r0` — false indirect exits
   truncating ~120 functions. `build_xrefs.py` carries a corrected `dec_thumb`
   (all outputs below use it); the upstream fix belongs in `gen_func_list_v2.py`
   (2-line change), which also affects `func_list_v2.txt`/`byteclass.tsv` bodies.
   Casualty found: `sub_0802FDA0` (55 insns, 7 bls, 1 caller) validates cleanly
   with the fixed decoder but was rejected by the buggy `validate_target`
   (fell through the misdecoded dispatch into the table → invalid at 02FE18).
1. **Jump tables now terminate bodies correctly.** Switch dispatch idiom:
   `lsls r0,r0,#2; ldr r1,[pc,#imm]; adds r0,r0,r1; ldr r0,[r0]; mov pc,r0`
   with a self-referential table (`entry[0]` = table base + 4). Tables at
   `030C68` (256 entries), `04868C` (57), `04754C` (27), `04D8D8` (19),
   `036F5C`/`0371C4` (18 each), `02FF8C` (25), `02FE18` (9), `033AEC`,
   `03B030`, `03DAC8`, `03453C`, plus ~110 smaller embedded tables
   (`xrefs_dataptrs.tsv`, `class_at_word=pool` runs inside bodies).
2. **Register-indirect call trampoline @`04DCD0`.** 14-entry table
   `bx r1; nop; bx r2; nop; …` — the compiler's `blx` substitute on ARMv4T.
   91 `bl` sites: 83 → `04DCD0` (call via r1), 4 → `04DCD4` (r2), 4 → `04DCD8` (r3).
   These are indirect calls; the callee must be recovered by dataflow on r1/r2/r3.
3. **144 `bx-indirect` exits** (`xrefs_unresolved.tsv`): genuine `mov pc,rX` switch
   dispatches (register holds table-loaded target), `bx rN` on untracked
   registers (callbacks, IRQ trampoline). Not resolvable statically.
   Additionally `btail_candidates.tsv` lists 685 `b`-to-unowned targets that
   forward-validate — probable tail-called shared subroutines/epilogues
   (e.g. 9 `b` paths into `0173AA` from `sub_080171C0`). Note: 26 of these
   were promoted to starts by the v2.4 addendum (thunk-span `02BCE2`–`02C71E`
   range); the remaining ~660 stay candidates for Phase 3.
4. **745 functions have no direct `bl`/`tailcall` caller.** 540 of them are referenced
   from data tables (`xrefs_dataptrs.tsv`, non-pool class); many of the rest are
   reached only via the r1-trampoline or are case handlers behind jump tables.
   `IntrWait` / `IrqDispatcher` are vector-called (ROM header).
5. Only **one** pool-resolved `bx` in all 1,689 functions
   (`Init@0000EC`: `mov lr,pc; bx rN` → `sub_0800033C`, ARM→Thumb mode switch).
   No `ldr pc,[pc]` occurs in any decoded body (the `dataptr` kind is reserved).
