# MMBCCDecomp — Multiphase Decompilation Plan

> **DRAFT** — written 2026-10-20 before research synthesis lands. Phase
> details (counts, section layout, toolchain pins) will be finalized once
> `ANALYSIS.md` is complete. Nothing here overrides evidence in `ANALYSIS.md`.

**Primary progress metric:** functions matched / total functions.
**[CORRECTION 2026-10-20, verified by independent audit]:** structural
analysis + recursive descent + region-wide BL re-harvest + audit
(`docs/func_list_v2.txt` [fixed hi-reg MOV decoder] + v2.5 addendum)
give **51 tier-A confirmed + 1652 tier-B probable = 1703 verified
working functions** (code region 0x000000–0x04FFFF = 320 KB; byte
classes now code 62.0% / unknown 32.6%). The earlier 14,102 figure
(recomp track) was inflated by recursive descent into data regions.
Working total: **1703** (Phase 2 ✅ complete — see below).
**Secondary metric:** bytes of ROM reproduced byte-identically.

"Matched" is defined strictly: the function's compiled bytes from our C
source are byte-identical to the baserom's bytes, verified by diff. No
unverified claims.

---

## Phase 0 — Toolchain setup — ✅ COMPLETE (2026-10-20)

**Outcome:** `pret/agbcc` @ `da598c1` built + installed to
`mmbcc/tools/agbcc` (smoke-tested); `binutils-arm-none-eabi` 2.42;
`gbagfx` vendored from pokeemerald master (standalone `pret/gbagfx`
repo is gone — 404) and built; `gbafix` likewise gone from pret org —
vendored from pokeemerald and built; `Kingcom/armips` cloned but
optional (not in matching chain); `morluto/rea` evaluated →
**deferred** to targeted-RE phase.
Project skeleton at `mmbcc/`: Makefile, ldscript.ld, src/rom_header.s,
tools/finish_rom.py, rom.sha1 gate, `make check` / `make compare`.
`make` produces an 8 MiB ROM with correct header + 0x7B quirk.
**First verified slice:** crt0 (0xC0–0x33C) disassembled to
`mmbcc/asm/crt0.s`, byte-identical in the built ROM's boot region.

## Phase 1 — Disassembly bootstrap + segmentation

- **Entry:** Phase 0 exit.
- **Work:**
  - Full ARM+Thumb disassembly from entry (0x080000C0) with capstone/Ghidra.
  - Identify section boundaries: code (.text), rodata, data, and large
    compressed-asset regions; document the memory map.
  - Function boundary detection v1: prologue signatures
    (ARM `0xE92Dxxxx`, Thumb `0xB5xx`) + branch-target harvesting +
    literal-pool alignment.
  - Produce initial `asm/` layout and a linker script that reproduces ROM
    layout (a "shiftable" build — correct layout, non-matching code).
- **Exit:** Disassembly covers 100% of ROM bytes (every byte classified as
  code/data/unknown); function list v1 with counts; layout-documented
  `ldscript.txt`.
- **Measurable:** functions identified (target ≈ 14,102 to confirm);
  % bytes classified.
- **Risks:** data-in-code (literal pools, jump tables) misclassified as code;
  Thumb/ARM mode switches at unknown boundaries.

## Phase 2 — Function boundaries + symbol naming — ✅ COMPLETE (2026-10-20)

- **Entry:** Phase 1 exit.
- **Work:**
  - Promote v1 boundaries to stable symbols (`sub_08XXXXXX` → meaningful
    names as behavior is identified).
  - Build call graph + data cross-references; identify SDK/library functions
    (BIOS calls, memcpy/memset, LZ77 decompress, M4A audio, SRAM save).
  - Cross-check function count and entry addresses against the recomp
    track's 14,102-function list (sanity check only — different method).
  - Name high-value targets first: entry/boot, main loop, save/load,
    text/dialogue renderer, title-screen renderer (known glitch area).
- **Exit:** Every identified function has a stable symbol; xref database
  queryable; priority target list for Phase 3 ordered.
- **Outcome:** 1703 starts with stable `sub_08XXXXXX` symbols
  (`func_list_v2.txt` fixed-decoder + `func_list_v2_5_addendum.txt`);
  `docs/xrefs.tsv` (15,945 edges: bl/bcond/pool/tailcall/bx) +
  `docs/xrefs_dataptrs.tsv` (3,285 data pointers) +
  `docs/func_stats.tsv` queryable via `docs/xrefs_README.md`;
  19 proposed names in `docs/symbols_phase2.md` (incl. the "save API"
  → H-blank ISR correction); Phase 3 order in
  `docs/phase3_targets.md` (veneers → save → boot → named targets →
  most-called utilities → bulk leaves-up).
- **Measurable:** 19 named + 16 asm-verified with real names / 1703;
  mean ~9.4 edges per function.
- **Risks (acknowledged):** 26 v2.4 thunk-span entries are probable
  alternate entries (flagged); 65 four-byte indirect stubs are weak-B;
  `.data`/`.bss` RAM boundaries still TO-REFINE (copy loop
  @`0x080007D0` analysis carried to Phase 3).

## Phase 3 — Matching C iteration

- **Entry:** Phase 2 exit.
- **Work:**
  - Per function: write C, compile with agbcc (`-O2`, era flags from
    fingerprint analysis), diff against baserom bytes, iterate until
    byte-identical (register allocation, struct layout, and instruction
    scheduling are the usual battlegrounds).
  - Order: SDK/libc-like functions first (they're templated), then
    high-value targets (boot, main loop, save, text renderer), then bulk.
  - Track per-function status: `UNMATCHED → ASM → C-WIP → MATCHED`.
  - AI-assisted drafting allowed (m2c-style); human/agent verification is
    the byte-diff, which is mechanical.
- **Exit:** All functions MATCHED (bytes identical in full-ROM build).
- **Measurable:** functions matched / total — the headline number.
  Target slices: first 10, first 100, 25%, 50%, 75%, 100%.
- **Risks:** THE bottleneck — some functions need exact struct/union
  layouts or inline-asm; a few may resist for weeks. Non-matching
  "equivalent" C is acceptable only as a documented interim with the
  function marked UNMATCHED.

## Phase 4 — Asset pipeline

- **Entry:** Text encoding cracked (or run in parallel with Phase 3).
- **Work:**
  - Graphics: convert tiles/palettes/tilemaps with gbagfx-style tooling;
    repo stores PNG + `.inc`/palette sources, not binary blobs.
    Starting points from analysis: ~1.36 MB tiles (top `0x389000`),
    tilemap cluster `0x73000`–`0x7E000` (~44 KB).
  - Compression: 338 validated LZ77 blocks (v10: 318, v11: 20),
    1.24 MB → 4.31 MB decompressed; rebuild via gbagfx LZ support in
    the build system. Largest: `0x1A7E14` (2.95 MB dec — validate the
    7× repeated chunks), `0x51E8E` (v11, 1.12 MB dec).
  - Text: decode the `BE 66 BC 00` container (blobs @`0x165C00`–
    `0x16E000`, 98 blobs via 13 pointer tables); store scripts as text
    with an encoder that reproduces original bytes. **Hardest Phase 4
    sub-task — codec unidentified.**
  - Audio: proprietary Capcom driver (no M4A) — sequences at
    `0x3A8DA8`–`0x3A95B8`; engine RE is a stretch goal.
- **Exit:** Zero unexplained binary blobs in repo; every asset builds from
  source and round-trips byte-identical.
- **Measurable:** assets converted / total (blocks, tilesets, text banks).
- **Risks:** custom text encoding may be the hardest single sub-task;
  audio engine is a custom Capcom driver (stretch goal).

## Phase 5 — Verification to byte-identical build

- **Entry:** Phase 3 exit (all functions matched) + Phase 4 exit.
- **Work:**
  - Clean-checkout full build → SHA-1 compare against
    `72309736f3820470c6f372d6a05ad1f16bc5a946`.
  - Reproduce quirks byte-for-byte (e.g., the header checksum byte at
    0xBD, currently `0x7B` vs computed `0x94` — see ANALYSIS.md).
  - Document build reproducibility (pinned toolchain SHAs, no timestamps).
- **Exit:** `make` on a clean checkout yields SHA-1-identical ROM. **Done.**
- **Measurable:** 1/1 (binary) — plus a CI-style check script.

---

## Cross-cutting rules

1. Baserom never enters the repo; SHA-1 gate only.
2. No copyrighted asset content in reports — structure/metadata only.
3. "Matched" always means byte-verified. Estimates are labeled as such.
4. Continuous work: each run advances the headline metric or removes a
   named blocker, and updates `PROGRESS.md`.
