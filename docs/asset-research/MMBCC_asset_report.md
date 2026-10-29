# MMBCC (Mega Man Battle Chip Challenge, USA, GBA) — ROM Asset Analysis Report

**Date:** 2026-10-20 · **Analyst:** subagent (data/asset analyst)
**ROM:** `Mega_Man_-_Battle_Chip_Challenge__USA__0_8r4i.gba` — 8,388,608 bytes, SHA1 `72309736f3820470c6f372d6a05ad1f16bc5a946` (verified before analysis)
**Header:** title `BATTLECHIPGP`, game code `A89E`, maker `08` (Capcom)
**Compliance:** ROM opened read-only in place, never copied; no graphics/audio/text content extracted (aggregate statistics only); `~/workspace/megaman-bcc-recomp/` untouched; scratch in `/tmp`.
**Method:** Python 3.12 + capstone 5.0.7. GBA BIOS decompressors (LZ77 v10/v11, Huffman 4/8-bit, RLE 8/16-bit) re-implemented from GBATEK semantics and validated by synthetic round-trip encode→decode. "Valid" = decodes to exactly the header's stated size with no source overrun and no invalid back-reference. Size sanity bound is strict `8 < size < 4 MiB` per the task.

---

## 1. Compression map

### 1a. LZ77 type 0x10 (v10) — the workhorse format
| Stage | Count |
|---|---|
| Header candidates (`0x10` + sane size) | 27,943 |
| Clean decodes (raw) | 837 |
| After strict `size > 8` (441 trivial 8-byte false positives removed — any `10 08 00 00` + 9 bytes "decodes") | 396 |
| After overlap filter (drop blocks fully inside another's compressed span) | **318** |

- Compressed footprint: **974,862 bytes (11.6% of ROM)** → 3,185,848 bytes decompressed (avg ratio 3.27).
- Size distribution (filtered 318): 9–64 B: 298 · 65–256 B: 2 · 257 B–1 K: 9 · 1–4 K: 2 · 16–64 K: 6 · >1 M: 1.
- Caveat: many tiny blocks have ratio < 1.0 (output smaller than input); the high-confidence set is the ~15 blocks >1 KB with ratio ≥ 1.5.

### 1b. LZ77 type 0x11 (v11, vram-safe)
| Stage | Count |
|---|---|
| Header candidates | 210,306 |
| Clean decodes (raw) | 1,189 |
| **v11-exclusive** (does NOT also decode as v10; 25/26 use the v11 extended-length form) | 26 raw → **20** filtered |

- The raw 1,189 is inflated (v11's long-match form is permissive); the 20 v11-exclusive blocks are the reliable set: 260,733 bytes → 1,121,634 bytes.
- Notable: `0x051E8E` (1.12 MB dec, 258 KB comp, 15,165 extended matches) + three ~70 KB blocks at `0x051F00`/`0x051F1C`/`0x0523D4`.

### 1c. Huffman 0x20 / 0x28 — INCONCLUSIVE, likely absent
- 0x20: 19,240 candidates → 19 "clean"; 0x28: 9,505 → 1 "clean". **All produce degenerate output** (entropy ≈ 0, single repeated value) → validator false positives, not real Huffman blocks. No reliable Huffman data identified.

### 1d. RLE 0x30 — INCONCLUSIVE, likely minimal
- RLE8: 11,183 candidates → 514 clean; RLE16: 6,335 → 204 clean. After `comp < dec`: 44 / 17 — but 40/16 are multi-MB decodes totaling >120 MB from an 8 MB ROM (impossible; overlapping false positives — RLE decode-cleanliness alone cannot validate). No reliable RLE blocks identified.

### 1e. Totals & top 30
- **Reliable compressed total: 338 blocks, 1,235,595 bytes (14.7% of ROM) → 4,307,482 bytes decompressed.**
- Combined top 30 (offset, type, decompressed, compressed):

```
0x01A7E14 v10  dec= 2949640 (2.81 MB) comp= 843551 ratio=3.50
0x0051E8E v11  dec= 1118722 (1.07 MB) comp= 258266 ratio=4.33
0x07A5D54 v10  dec=   38080           comp=  20067 ratio=1.90
0x079C88C v10  dec=   37888           comp=  19889 ratio=1.90
0x0797E88 v10  dec=   37120           comp=  18819 ratio=1.97
0x07AF400 v10  dec=   36864           comp=  18913 ratio=1.95
0x07AAC38 v10  dec=   36416           comp=  18248 ratio=2.00
0x07A16C0 v10  dec=   35328           comp=  17937 ratio=1.97
0x01937B7 v11  dec=    1377           comp=   1346 ratio=1.02
0x0193357 v10  dec=    1361           comp=   1507 ratio=0.90
0x018F997 v10  dec=    1136           comp=   1257 ratio=0.90
0x0189017 v10  dec=     703           comp=    780 ratio=0.90
... (then 18 more blocks, 703 B down to 63 B; full list in /tmp/lz77_results.json)
```
- The six ~35–38 KB v10 blocks clustered at `0x797E88`–`0x7A5D54` are likely a sprite/graphic set. The 2.9 MB block at `0x1A7E14` contains 7× repeated 256 KB chunks — real repeated asset or decoder-periodic false positive (flagged for validation).

---

## 2. Text encoding

- **No plain ASCII** outside the header: 26,700 byte-runs ≥8 chars in `0x20`–`0x7E` are random noise (only 580 contain spaces; samples are ascending byte sequences like `pqrstuvwxyz{|`, not language). **No Shift-JIS** (lead/trail pair rate ≈ 0.00–0.03 in decompressed data).
- **Dialogue is NOT in BIOS LZ77 blocks**: 38 "text-like" 0x10 blocks (by entropy/alphabet heuristics) profile as graphics (76% of bytes are `0x00`/`0xFF`/`0xFE`).
- **The text bank (high confidence):** 13 pointer tables at file `0x165C00`–`0x16D630` → **98 variable-length blobs** (110–1120 B, avg ~301 B) in `0x165584`–`0x16D45F`.
  - Every blob begins with the 4-byte magic **`BE 66 BC 00`** (106 occurrences ROM-wide, **all** confined to `0x165000`–`0x16E000`); 81/98 end with byte `0xB1`.
  - Content: entropy 6.30, 250/256 distinct bytes — not plain text; single-byte XOR vs BIOS headers fails. Tag-like bytes (`BC/BB/BD/BE/BF`) shared with the save-device table suggest a **common Capcom serialization/bytecode format**.
- **Most plausible:** custom Capcom container (`BE 66 BC 00` magic) holding compressed text or a text+control bytecode. Not BIOS LZ77/Huffman/RLE, not ASCII/SJIS. Codec unidentified (no public documentation found). Font data not positively located — required next step.

---

## 3. Graphics inventory (aggregate only)

- **Tile data (raw):** 331 × 4 KB windows (3 < entropy < 7.6, 32-byte-tile repetition > 0.15) → **~1.36 MB**. Strongest: `0x389000` (rep 0.71), `0x387000`, `0x5BF000`, `0x4CD000`. Byte histogram dominated by `0x00` (30.7%) and repeated-nibble bytes (`0x11`,`0x22`,… — solid 4bpp tiles).
- **Palettes:** 3,134 candidate runs (272 KB) of ≥16 u16 with bit15 clear — **inflated by code false positives** (uniform per-MB distribution); true count likely 1–2 orders of magnitude lower. Needs per-asset validation (hypothesis).
- **Tilemaps:** 384 × 2 KB candidate windows. **High-confidence cluster: `0x73000`–`0x7E000` (~44 KB, 22 consecutive windows, ent ≈ 4.0, ~130–150 distinct u16)** — BG-map bank. Secondary: `0x7F000`–`0x81000`, `0x55800`–`0x56000`.

---

## 4. Audio

- **No M4A/MP2K ("Sappy") engine signatures.** `CAPCOM ALL STAFF` (1× credit string) is the only meaningful hit; `M4A`/`IPCM` matches are byte-coincidences in binary data (verified by context).
- **Sequence data (high confidence):** table cluster `0x3A8DA8`–`0x3A95B8` (4–9 pointers each) → targets show `(note, duration)`-like pairs with `0xFF`/`0xFE` delimiters and inline pointers — MIDI-like song tracks at ~`0x3A8D00`–`0x3A9600`.
- **Verdict:** custom **Capcom-proprietary sound driver** (hypothesis; consistent with Capcom GBA titles and the absence of Nintendo MP2K markers). Driver init/voice data not yet located.

---

## 5. Save hooks (SRAM_V113)

SRAM base is built **arithmetically** — `movs rX,#0xE0; lsls rX,rX,#20` → `0x0E000000`. Literal-pool and ARM-immediate searches were exhaustively ruled out (58 unaligned `0x0E000000` values in 3–5 MB are data coincidences with zero code references).

**Address-computation sites** (Thumb; `addr = 0x0E000000 + (index << 13)`, 8 KB banks):
- `0x08001DB8` (file `0x1DB8`; compute at `0x1DDA`, calls `0x804DB5C`), `0x08001E30` (`0x1E42`), `0x08001F1C` (`0x1F5A`, stores to `[r4+0x10]`), `0x08002070` (`0x20AA`, stores to `[r5+0x10]`).

**Driver primitives** (Thumb):
- `0x0804DB38` (file `0x4DB38`): raw `ldrb`/`strb` copy loop.
- `0x0804DB5C` (`0x4DB5C`): sets **WAITCNT `0x04000204` |= 3** (SRAM timing), dispatches via function pointer.
- `0x0804DBC0` (`0x4DBC0`): SRAM→RAM byte copy with WAITCNT setup.
- `0x0804DC00` (`0x4DC00`): byte compare loop (verify; returns mismatch address or 0).
- `0x0804DC30` (`0x4DC30`): larger verify worker (0xC0 stack buffer).
- `0x0804DC94` (`0x4DC94`): **retry wrapper** — copy + verify, up to 3 attempts.

**Save-device table** (file `0x16E148`–`0x16E230`): entries → 12-byte device structs at `0x08106C18`–`0x08106C60`. **SRAM_V113 entry** at file `0x16E208` (name inline `"SRAM_V113"`), driver table `[0x0804DB39, 0x0804DB5D, 0x0804DC01, 0x0804DC31]` → the four primitives above. Save API entries (table at `0x16E230`): `0x08000B54`, `0x08000BAC`, `0x08000C04` (validate a halfword against `0x9F`; exact roles unconfirmed — hypothesis: init/read/write).

---

## 6. Scripts
All in `/tmp` (scratch, kept for the record):
- `/tmp/lz77_scan.py` → `/tmp/lz77_results.json` (full compression scan; note: JSON `valid_raw`/`valid_filtered` use the loose `size ≥ 8` bound — §1 figures above apply the strict `size > 8` + v11-exclusive refinement)
- `/tmp/text_analysis.py`, `/tmp/text_deep.py` (encoding screens, decompressed-block profiling)
- `/tmp/gfx_analysis.py` → `/tmp/gfx_full.log` (tile/palette/tilemap candidates)
- `/tmp/audio_scan.py` (engine signatures, song-table hunt)
- `/tmp/sram_scan.py` (superseded SRAM literal finder; the movs/lsls finding replaced it)

## 7. Open questions / next steps
1. Identify the `BE 66 BC 00` codec (trace the text-bank accessor to the decompressor).
2. Locate font data (1bpp blocks near the text bank) — prerequisite for any text RE.
3. Validate the 2.9 MB block at `0x1A7E14` and the RLE candidates (decode-only validation is insufficient for RLE).
4. Confirm Capcom sound-driver init and instrument data.
5. Tighten palette detection with a code-exclusion pre-filter.
