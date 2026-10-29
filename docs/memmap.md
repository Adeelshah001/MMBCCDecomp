# MMBCCDecomp — Memory Map

Phase 1 exit document. All claims trace to `ANALYSIS.md` (sections cited
as "§N.N"); hypotheses are labeled **HYP**. No claims here are "matched"
(this is a planning document, not a verification claim).

Baserom: SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946`, 8,388,608 bytes
(8 MiB). On GBA ROM the game occupies `0x08000000–0x087FFFFF`.
**File offset = ROM address − `0x08000000`.**

> `docs/func_list_v2.txt` (sibling worker) did not exist at write time;
> boundary evidence below uses `docs/func_list_v1.txt` + `ANALYSIS.md`.

---

## (a) GBA address space, as used by this game

| Range | Region | Use in this game | Evidence |
|---|---|---|---|
| `0x02000000–0x0203FFFF` | EWRAM (256 KB) | Main work RAM. Boot init fn #1 (`@0x0800063C`) registers a base pointer into a global struct — ANALYSIS §1.2 writes it as "EWRAM base `0x03000000`", but `0x03000000` is the IWRAM base, so the phrasing is ambiguous (value stored vs. register target — see (c)) | ANALYSIS §1.2 |
| `0x03000000–0x03007FFF` | IWRAM (32 KB) | Real IRQ handlers installed here by boot code (header vectors 0x04–0x1C are logo bitmap, not handlers); stacks: IRQ → `0x03007DA0`, system/user → `0x03007FA0`; resume addr stored @`0x03007FFC` | ANALYSIS §1.1, §1.2 |
| `0x04000000–0x040003FE` | I/O registers | `REG_DISPCNT` @`0x04000000` (boot writes `0x0080`); `REG_IE/REG_IF` @`0x04000200` (IntrWait + IRQ dispatcher poll); `WAITCNT` @`0x04000204` (save driver ORs in `0x3`) | ANALYSIS §1.2, §2.5 |
| `0x08000000–0x087FFFFF` | ROM (8 MiB used of 32 MiB window) | Entire game; execute-in-place | ANALYSIS §1.3 |
| `0x0E000000–0x0E00FFFF` | SRAM (64 KB window) | Save storage. Base built arithmetically (`movs rX,#0xE0; lsls rX,rX,#20`); slot address = `0x0E000000 + (index << 13)` → 8 KB slots (`0x2000`) | ANALYSIS §2.5 |

No overlays: GBA executes in place; no DMA-to-RAM code staging was found
(ANALYSIS §1.3).

---

## (b) ROM file-offset map

All offsets below are **file offsets** (subtract from `0x08000000` to get
the ROM address used in ANALYSIS). Sizes in bytes unless noted.

| File offset | Size | ROM addr | Contents | Evidence |
|---|---|---|---|---|
| `0x000000–0x0000BE` | 191 | `0x08000000` | Cartridge header: ARM `b` → `0xC0`; Nintendo logo (0x04–0x9F); title `BATTLECHIPGP`; game code `A89E`; maker `08` (Capcom); fixed `0x96` ✓; checksum byte @`0xBD` stores **`0x7B`** vs computed `0x94` (factory quirk — shipped on the physical cart) | ANALYSIS §1.1 |
| `0x0000C0–0x00033C` | 705 | `0x080000C0` | Boot chain (5 functions, asm-verified): `Init` @C0 (stacks), `IntrWait` @FC (polls `REG_IE/IF`), `IrqDispatcher` @1BC, `ArmTrampoline` @2A4, Thumb entry `crt0_thumb_helpers` @33C (calls ~16+ init routines, writes `0x0080` to `REG_DISPCNT`) | ANALYSIS §1.2 |
| `0x00033C–0x04FFFF` | 326,980 | `0x0800033C` | Game code, almost entirely Thumb. Includes: init routines called from Thumb entry (e.g. fn #1 @`0x63C`, fn #2 @`0x7D0`); save API entries @`0xB54`, `0xBAC`, `0xC04`; SRAM addr-compute sites @`0x1DB8`, `0x1E30`, `0x1F1C`, `0x2070`; ARM math routine @`0x4BCDC` (1 of only 3 ARM functions); BIOS veneer table @`0x4DB24`; save primitives @`0x4DB38–0x4DC94` | ANALYSIS §1.2–1.4, §2.5 |
| `0x04DB24–0x04DB37` | 20 | `0x0804DB24` | 5 BIOS-call veneers, 4 B each: `svc N; bx lr` — CpuFastSet (0x0C), CpuSet (0x0B), LZ77UnCompVram (0x12), LZ77UnCompWram (0x11), RLUnCompVram (0x15). Confirms runtime LZ77/RL asset decompression | ANALYSIS §1.5 |
| `0x04DB38–0x04DC94` | 349+ | `0x0804DB38` | 6 save-driver primitives: memcpy @DB38, WAITCNT dispatch @DB5C, SRAM→RAM copy @DBC0, verify-compare @DC00, verify worker @DC30, 3×-retry wrapper @DC94 (extends slightly past 0xDC94; end not yet pinned) | ANALYSIS §2.5 |
| `0x050000–0x7FFFFF` | 7,864,320 | `0x08050000` | Data zone (7.7 MB): graphics/tiles/fonts/tables. Apparent code hits here are compressed-graphics false positives (spot-verified with ARMv4T filtering). Isolated unreferenced snippets (e.g. ~`0x8267E6`) are linker leftovers | ANALYSIS §1.3 |
| `0x073000–0x07E000` | 44,032 | `0x08073000` | High-confidence tilemap cluster | ANALYSIS §2.3 |
| `0x165C00–0x16D630` | 31,280 | `0x08165C00` | Text bank: 13 pointer tables → 98 variable-length blobs (110–1120 B, avg ~301 B), magic `BE 66 BC 00`, 81/98 end with `0xB1`, content entropy 6.30. Codec unknown — **hardest Phase 4 sub-task** | ANALYSIS §2.2 |
| `0x16E148–0x16E230` | 232 | `0x0816E148` | Save-device table; `SRAM_V113` descriptor @`0x16E1D0–0x16E220` (16-byte records); `SRAM_V113` entry @`0x16E208` with driver table `[0x0804DB39, 0x0804DB5D, 0x0804DC01, 0x0804DC31]` (Thumb addresses, LSB set) | ANALYSIS §1.6, §2.5 |
| `0x16E210` | — | `0x0816E210` | ASCII string `SRAM_V113` (one of only two meaningful strings in ROM) | ANALYSIS §1.5 |
| `0x1A7E14` | large | `0x081A7E14` | Largest LZ77 v10 block (~2.95 MB decompressed — needs validation; 7× repeated chunks) | ANALYSIS §2.1 |
| `0x234F54` | — | `0x08234F54` | ASCII string `CAPCOM ALL STAFF` | ANALYSIS §1.5 |
| `0x389000` (area) | ~1.36 MB total | `0x08389000` | Top concentration of tile data (331×4 KB tile windows across ROM) | ANALYSIS §2.3 |
| `0x3A8DA8–0x3A95B8` | 2,064 | `0x083A8DA8` | MIDI-like audio sequence data (`0xFF`/`0xFE` delimiters); proprietary Capcom driver (**HYP** — no M4A/MP2K signatures) | ANALYSIS §2.4 |
| `0x51E8E` | large | `0x08051E8E` | Largest LZ77 v11 block (1.12 MB decompressed, 15,165 extended matches) | ANALYSIS §2.1 |
| `0x797E88–0x7A5D54` | ~35–38 KB ×6 | `0x08797E88` | Six large LZ77 v10 blocks | ANALYSIS §2.1 |

Aggregate compression: 338 validated LZ77 blocks (318 v10 + 20 v11),
1,235,595 ROM bytes (14.7%) → 4.31 MB decompressed. Full block list in
`docs/asset-research/lz77_results.json`. (ANALYSIS §2.1)

---

## (c) Observed section boundaries

**On GBA ROM, all executable code lives in one logical `.text`:**
`0x08000000–0x0804FFFF` (file `0x000000–0x04FFFF`, 320 KB). Validated by
bl-target cross-check: 55–67% of bl-pairs resolve to function starts
inside this region, ~0% outside (ANALYSIS §1.3). The current linker
script places everything in a single `.text` (see `docs/ldscript.txt`).

**Literal pools are inline** in the code region — not a separate section
(ANALYSIS §1.4: prologue scan hits include literal-pool noise).

**`.data` → WRAM copy:** init fn #2 @`0x080007D0` is a 14-word
`ldm`/`stm` copy loop (**HYP**: `.data`/WRAM init). The matching
`.rodata`/`.data` **RAM-side** boundaries are **TO-REFINE**:

| Unknown | What would settle it |
|---|---|
| RAM-side `.data` VMA + length | Read the copy loop @`0x080007D0`: its source pointer, destination pointer, and word/byte count operands. The `ldm`/`stm` register lists and loop count give exact `src → dst : len`. |
| `.rodata` vs `.text` boundary inside the 320 KB | Pools are inline, so on-ROM there is no separate `.rodata` — but if the original link had one, its RAM references (if any) or pool-cluster analysis during Phase 1 recursive descent will decide. |
| `.bss` VMA + length | Find the zero-init loop (the init-routine list in §1.2, ~16+ calls from `0x0800033C`, has not been individually mapped yet — the zero loop is likely one of them). |
| EWRAM vs IWRAM global placement | Phase 2 data-xref work: which globals live at `0x0200xxxx` vs `0x0300xxxx`. |

Related open question: ANALYSIS §1.2 says init fn #1 (`0x0800063C`)
"registers EWRAM base `0x03000000`" — `0x03000000` is the **IWRAM** base
address, so either the register target is an IWRAM-resident global
struct (and "EWRAM base" refers to a *value* stored there, not the
register target) or the note is imprecise. Resolve by disassembling
`0x0800063C` and checking the literal/pool word it stores.

---

## (d) Unknown / gap regions (explicit)

1. **Code-region data pockets:** literal pools and jump tables are
   interleaved with code inside `0x000000–0x04FFFF`; exact code/data
   interleaving is unmapped. Phase 1 proper (recursive descent from
   `0x080000C0`) must classify every byte.
2. **Save-primitive tail:** the 3×-retry wrapper @`0x0804DC94` extends
   past `0x0804DC94`; its end address is unpinned (sibling save-driver
   worker is producing `mmbcc/asm/savedrv.s`).
3. **Data-zone layout:** `0x050000–0x7FFFFF` is 7.7 MB of mostly
   unclassified data — asset regions (tiles, tilemaps, text bank, audio
   sequences, LZ77 blocks) are located per §2, but boundaries between
   them are not drawn. Jump-table-free code is not expected there.
4. **The 7×-repeated-chunk block @`0x1A7E14`:** largest LZ77 v10 block
   (2.95 MB decompressed) flagged as needing validation.
5. **Text container codec:** `BE 66 BC 00` blobs (entropy 6.30) —
   encoding/compression unidentified; font glyph data not located
   (ANALYSIS §2.2). No bearing on code layout, but blocks Phase 4 text
   pipeline.
6. **Audio driver:** proprietary Capcom (**HYP**); engine code location
   within `0x08000000–0x0804FFFF` unidentified (ANALYSIS §2.4).
7. **Runtime anti-tamper:** no static evidence of ROM checksums
   (`swi 0x0D` absent, no xrefs to header/logo region), but runtime
   checks can't be excluded without tracing (ANALYSIS §1.7).
8. **`.bss`/`.data` RAM extents:** see (c) — the blocker list.

> Compiler/toolchain attribution (old ARM ADS/SDT vs agbcc-compatible
> GCC) remains a hypothesis (ANALYSIS §1.5) — retail strip removed all
> string evidence. It does not affect the memory map.
