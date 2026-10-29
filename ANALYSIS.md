# MMBCCDecomp — ROM Analysis

Evidence-first findings from the user's own dump (read in place, never
copied). Baserom identity: 8,388,608 bytes,
SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946`.

> Corrections vs. initial assumptions are marked **[CORRECTION]**.
> A research agent's claim that the header checksum "validates" was
> independently re-checked 3× and found to be a script bug — the mismatch
> below is real.

---

## 1. Structural analysis (complete)

### 1.1 Header (0x000–0x0BE)

| Offset | Content |
|---|---|
| 0x000 | ARM `b` → file offset **0xC0** (`0x080000C0`) |
| 0x004–0x09F | Nintendo logo, present (bytes not reproduced here) |
| 0x0A0 | Title `BATTLECHIPGP` |
| 0x0AC | Game code `A89E` |
| 0x0B0 | Maker `08` (Capcom) |
| 0x0B2 | Fixed byte `0x96` ✓ |
| 0x0BD | **Stored `0x7B`; computed `0x94` — MISMATCH** |

**Header checksum anomaly (verified 3× independently):** the GBA complement
check over 0xA0–0xBC computes to `0x94`, but the ROM stores `0x7B`. The dump
is no-intro-verified, so this byte shipped on the physical cartridge. Real
GBA hardware only enforces the logo at boot, not this byte — which is
presumably how it shipped. **The decomp build must reproduce `0x7B` as-is**
(see PLAN.md Phase 5). A research script that reported "valid" was wrong.

Note: ROM offsets 0x04–0x1C sit inside the logo region — those words are
logo bitmap data, not real vectors. Real handlers are installed in WRAM by
the boot code.

### 1.2 Entry point + early boot

Classic public-domain GBA crt0, ARM mode at `0x080000C0`:
- `0x080000C0`: IRQ-mode stack → `0x03007DA0`; system/user stack → `0x03007FA0`
- `0x080000D8`: stores resume addr `0x080000FC` at WRAM `0x03007FFC`,
  then `bx` to Thumb entry **`0x0800033C`** (pool word `0x0800033D` @0x1B8)
- `0x080000FC–0x080001B0`: IntrWait helper — polls `REG_IE/IF` (`0x04000200`)
- `0x080001BC–~0x080002C0`: IRQ dispatcher (ARM); trampoline @`0x080002A4`
- Thumb entry `0x0800033C`: pushes `{r4,lr}`, calls ~16+ init routines
  (`0x800063C`, `0x80007D0`, `0x8000C9C`, `0x8000F1C`, `0x8001C4C`,
  `0x8001D88`, `0x80021C4`, `0x8002678`, `0x8002A04`, `0x8002CB0`,
  `0x8002D84`, `0x8002E44`, `0x8002E70`, `0x8002ED4`, `0x8002EF4`,
  `0x8002620`, `0x8004548`, `0x804A2CC`, `0x800CC24`, …),
  writes `0x0080` to `REG_DISPCNT`, returns.
- Init fn #1 (`0x800063C`) registers EWRAM base `0x03000000` into a global
  struct (likely main game context); init fn #2 (`0x80007D0`) is a
  14-word `ldm/stm` copy loop (.data/WRAM init).

### 1.3 Code/data layout

- **Executable code: file `0x000000–0x04FFFF` (320 KB)** → ROM
  `0x08000000–0x0804FFFF`. Validated by bl-target cross-check
  (55–67% of bl-pairs resolve to function starts in code; ~0% in data).
- **File `0x050000`–`0x7FFFFF` (7.7 MB) is data** (graphics/tiles/fonts,
  tables). Apparent code hits there are false positives from compressed
  graphics (verified by spot-disassembly with ARMv4T filtering).
- **No overlays.** GBA is execute-in-place; no DMA-to-RAM code staging
  found. Isolated unreferenced snippets in data zones (e.g. ~`0x08267E6`)
  are linker leftovers.

### 1.4 Function count — [CORRECTION]

- **~966 Thumb functions** per independent prologue-signature analysis;
  coordinator's own tiered bootstrap (`docs/func_list_v1.txt`,
  `docs/func_list_v1_method.md`) finds **726 strong (bl-validated) +
  392 medium (forward-coherent) = 1118 probable**, with 494 weak
  unvalidated candidates (mostly literal-pool noise).
- **Working total for planning: ~1000 functions** (range 966–1118) —
  NOT 14,102.
- The recomp track's 14,102 figure came from recursive descent into data
  regions and is inflated by false positives. The decomp's working total
  is **~1000** (Phase 1 proper — recursive descent from entry — will fix
  the exact number).
- This is very good news: the matching scope is ~15× smaller than assumed.
- ARM-mode code: only 3 functions total — 2 crt0 snippets
  (`0x080001D4`, `0x080002A4`) + 1 genuine ARM routine @`0x0804BCDC`
  (`push {r4,ip}`, uses `mul`/`ldrsb` — a math routine).

### 1.5 Compiler/toolchain fingerprint

- **No identifying strings anywhere.** Full ASCII and UTF-16LE scans found
  zero occurrences of `ARM`, `armcc`, `Nintendo`, `AGB`, `gcc`, `assert`,
  `Copyright`, `.o`/`.c` names, build strings. Only meaningful strings:
  `SRAM_V113` @`0x16E210` and `CAPCOM ALL STAFF` @`0x234F54`.
- Codegen observations (hypothesis): public-domain GBA crt0; `movs r0,r0`
  NOP padding after `bx lr`; inline literal pools; `lsls/asrs #0x18`
  sign-extension idiom. Consistent with old ARM ADS/SDT or
  agbcc-compatible GCC — **toolchain attribution remains a hypothesis**;
  retail strip removed all string evidence.
- **BIOS-call veneer table @`0x0804DB24`:** five `svc N; bx lr` wrappers —
  `CpuFastSet` (0x0C), `CpuSet` (0x0B), `LZ77UnCompVram` (0x12),
  `LZ77UnCompWram` (0x11), `RLUnCompVram` (0x15). Confirms runtime
  LZ77/RL decompression of assets.

### 1.6 Save hooks — RESOLVED (see §2.5)

- `SRAM_V113` descriptor table @`0x16E1D0–0x16E220` (16-byte records).
- Asset analysis mapped the full driver: SRAM base built arithmetically
  (`movs rX,#0xE0; lsls rX,rX,#20` — no literal pools, hence missed by
  the structural scan); 4 addr-compute sites (`0x08001DB8`,
  `0x08001E30`, `0x08001F1C`, `0x08002070`); 6 primitives at
  `0x0804DB38`–`0x0804DC94` (memcpy, WAITCNT dispatch, SRAM→RAM,
  verify-compare, verify worker, 3× retry); device table
  `0x16E148`–`0x16E230` with SRAM_V113 entry @`0x16E208`; API entries
  `0x08000B54`, `0x08000BAC`, `0x08000C04`. Details in §2.5.

### 1.7 Anti-tamper / multiboot

- **Not a multiboot binary** (verified: no `swi 0x25` in code regions).
- No static evidence of ROM checksums (`swi 0x0D` absent; no xrefs to
  header/logo region). Runtime checks can't be excluded without tracing.

---

## 2. Compression map + asset inventory (complete)

Full report + scripts preserved at `docs/asset-research/`
(`MMBCC_asset_report.md`, `lz77_results.json`, scan scripts).
Aggregate metadata only — no asset content extracted.

### 2.1 Compression map (real-decode validated)

| Type | Reliable blocks | ROM bytes | Decompressed |
|---|---|---|---|
| LZ77 v10 (`0x10`) | 318 | 974,862 (11.6%) | 3.19 MB |
| LZ77 v11 (`0x11`) | 20 | 260,733 | 1.12 MB |
| **Total** | **338** | **1,235,595 (14.7%)** | **4.31 MB** |

(27,943 raw v10 candidates collapsed to 318 after clean-decode +
strict-size + overlap filtering; v11 validated separately as many
candidates also decode as v10. Huffman 0x20/0x28: validator false
positives only, likely absent. RLE 0x30: validators too permissive,
likely minimal usage.)

Largest blocks: `0x1A7E14` (v10, 2.95 MB dec — needs validation, 7×
repeated chunks), `0x51E8E` (v11, 1.12 MB dec, 15,165 extended matches),
six ~35–38 KB v10 blocks at `0x797E88`–`0x7A5D54`. Distribution is
heavy-tailed: 298 tiny blocks (9–64 B), a handful of large ones.

### 2.2 Text encoding — bank located, codec unknown

- **No ASCII** outside the header; **no Shift-JIS**; dialogue is **not**
  inside LZ77 blocks (38 "text-like" blocks profile as graphics).
- **Text bank found:** 13 pointer tables at file `0x165C00`–`0x16D630`
  → **98 variable-length blobs** (110–1120 B, avg ~301 B).
- Every blob starts with magic **`BE 66 BC 00`** (106 occurrences, all
  confined to `0x165000`–`0x16E000`); 81/98 end with `0xB1`.
- Content entropy 6.30 — not plain text, not single-XOR; **most plausible:
  custom Capcom container (compressed text or text+control bytecode).**
- Codec unidentified; font glyph data not located. **This is the hardest
  single Phase 4 sub-task** (cf. PLAN.md).

### 2.3 Graphics (aggregate)

- Tiles: ~1.36 MB (331×4 KB windows; top concentration `0x389000`).
- Palettes: 3,134 raw candidates (272 KB) but heavily inflated by code
  false positives — true count likely 10–100× lower.
- Tilemaps: 384 windows; high-confidence cluster **`0x73000`–`0x7E000`
  (~44 KB)**.

### 2.4 Audio — proprietary driver

- **No M4A/MP2K/Sappy signatures** (hits were byte-coincidences).
- MIDI-like (note, duration) sequence data with `0xFF`/`0xFE`
  delimiters at `0x3A8DA8`–`0x3A95B8`.
- **Verdict: Capcom-proprietary sound driver** (hypothesis). Audio
  pipeline is a Phase 4 unknown.

### 2.5 Save hooks — fully mapped (fills §1.6 gap)

- SRAM base is built **arithmetically** (`movs rX,#0xE0; lsls rX,rX,#20`)
  — no literal pools, which is why the structural scan missed it.
- **4 address-compute sites:** `0x08001DB8`, `0x08001E30`, `0x08001F1C`,
  `0x08002070` (addr = `0x0E000000 + (index<<13)`).
- **6 driver primitives** (adjacent to the BIOS veneer table @`0x0804DB24`):
  `0x0804DB38` (memcpy), `0x0804DB5C` (WAITCNT `0x04000204`|=3 +
  dispatch), `0x0804DBC0` (SRAM→RAM copy), `0x0804DC00` (verify-compare),
  `0x0804DC30` (verify worker), `0x0804DC94` (3× retry wrapper).
- Save-device table at file `0x16E148`–`0x16E230`; **SRAM_V113 entry**
  at `0x16E208` with driver table
  `[0x0804DB39, 0x0804DB5D, 0x0804DC01, 0x0804DC31]` (Thumb addresses).
- Save API entries: `0x08000B54`, `0x08000BAC`, `0x08000C04`.
- All in the code region — cross-check against `docs/func_list_v1.txt`
  tiers in Phase 2.

## 3. Toolchain research (complete)

### 3.1 Sources

| Tool | Source | State |
|---|---|---|
| `agbcc` | `pret/agbcc` @ `da598c1` (active; commits through 2026-10-18) | ✅ cloned to `tools/agbcc`, **built** (`./build.sh` exit 0), smoke-tested |
| `gbagfx` | **standalone `pret/gbagfx` is GONE (404)** — removed from the pret org | ✅ vendored copy from `pret/pokeemerald` master `tools/gbagfx` → `tools/gbagfx` (canonical current practice: vendored per-project) |
| `armips` | `pret/armips` also gone (404) | ✅ `Kingcom/armips` @ `62adab4` cloned — **optional**, NOT part of the matching build chain (ROM-hacking tool, not a decomp tool) |

Build prerequisites installed: `binutils-arm-none-eabi` (2.42, via apt).
`agbcc` produces: `agbcc`, `old_agbcc` (pre-patched variant, some functions
only match with it), `agbcc_arm` (cc1 proper), `libgcc.a`, `libc.a`.
Smoke test: `int add(int a,int b){return a+b+1;}` → authentic
`gcc 2.9-arm-000512` Thumb asm, assembled cleanly.

Fork assessment: stay on `pret/agbcc` (not stale). Fallbacks if upstream
breaks: `laqieer/agbcc` (host-build fixes), `macabeus/agbcc` (WASM/niche).

### 3.2 Canonical pret GBA project skeleton (from pokeemerald master)

- `Makefile`: ROM header vars (`TITLE`, `GAME_CODE`, `MAKER_CODE`,
  `REVISION`), `COMPARE ?= 0` → `make compare` runs `sha1sum -c rom.sha1`.
- Toolchain: `arm-none-eabi-{as,ld,objcopy,objdump}` + agbcc;
  `ld_script.ld` with **explicit per-object ordering** (that's what makes
  the link byte-identical); `ENTRY(Start)`.
- `rom.sha1`: `<sha1>  <file>.gba` — byte-identity gate.
- `tools/` vendored per project: `agbcc` (via `install.sh`), `gbafix`,
  `gbagfx`, `preproc`, `scaninc`, `ramscrgen`, … built by `make tools`.
- `sym_ewram.txt` / `sym_bss.txt`, `charmap.txt`, `asmdiff.sh`,
  `libagbsyscall/`, `include/gba/` (old `pret/agb` headers now vendored
  in-tree — no separate shared-headers repo).
- Bring-up recipe: copy skeleton → set header vars from ROM →
  `rom.sha1` ← baserom hash → install agbcc → disassemble into `asm/` →
  decompile to `src/` one function at a time → `make compare` until match.

### 3.3 morluto/rea evaluation — DEFERRED

`morluto/rea` v6.7.0 ("Reverse Engineer Anything"): an MCP server + CLI +
agent skill pack fronting RE tools with an Evidence/provenance model —
**not a decompiler**. Relevant MCP tools: `analyze_function`,
`annotate-native-function` (rename), `inspect-native-instruction`,
`xrefs`, `search`, `build-call-path`, `resolve-native-call-targets`,
`compare-functions` (diff compiled fn vs reference — maps directly to
match verification). Engines: Ghidra (needs local install), Hopper, IDA,
JEB, Rizin, Cutter, objdump, GDB. Binary Ninja not supported.

**Recommendation: DEFER to the targeted-RE / function-matching phase.**
Adopting now would spend effort on Ghidra install + GBA raw-binary
validation before a project exists to use it in. The toolchain
(agbcc/gbagfx/skeleton) was the critical path and is done. Re-evaluate
when per-function matching work begins; `compare-functions` is the
highest-value hook.

---

## Priority target list for Phase 2/3 (from §1–§2)

1. Boot chain: `0x080000C0` → `0x0800033C` → init routines
   (esp. `0x800063C` context registration, `0x80007D0` WRAM init)
   — **boot portion (0xC0–0x33C) already asm-verified**
2. IRQ dispatcher `0x080001BC` + IntrWait `0x080000FC` — **asm-verified**
3. BIOS veneer table `0x0804DB24` (5 wrappers — templated, match first)
   + adjacent save driver `0x0804DB38`–`0x0804DC94` (6 primitives,
   fully mapped in §2.5 — high-value, small, self-contained)
4. ARM math routine `0x0804BCDC`
5. Text container codec (`BE 66 BC 00` blobs @`0x165C00`–`0x16E000`) —
   the critical unknown for Phase 4; dialogue renderer follows it
6. Title-screen renderer (known glitch area from recomp track)
7. Audio driver (proprietary; sequences @`0x3A8DA8`–`0x3A95B8`)
