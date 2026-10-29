# MMBCCDecomp — Phase 2 symbol proposals (worker)

Date: 2026-10-20. All findings from disassembly of the user's ROM
(SHA-1 `72309736f3820470c6f372d6a05ad1f16bc5a946`, read in place).
`sub_08XXXXXX` is the stable primary key; proposed names are aliases only.
Nothing in `docs/func_list_v2*.txt` was renamed.

> **Headline correction:** the three "save API entries" (`sub_08000B54`,
> `sub_08000BAC`, `sub_08000C04`) are **not save functions**. They are
> H-blank raster interrupt handlers. ANALYSIS §1.6/§2.5 and
> `feeds_recomp_notes.md` §(a) mislabeled them (the pointer table they
> live in sits adjacent to the save-device table, which misled).
> They touch no SRAM, no WAITCNT, and no save primitive.

## Symbol table

| `sub_08XXXXXX` | Proposed name | Evidence (1–2 lines) | Confidence | Feeds-recomp note |
|---|---|---|---|---|
| sub_08000B54 | `HBlank_Raster0` | H-blank ISR: gates on VCOUNT≤159, calls `StridedCopy` with desc `@0x03000580`, at VCOUNT==159 clears DISPSTAT bit4 + IE bit1 (disables H-blank IRQ). No SRAM/WAITCNT/save-primitive touches. Installed `@0x03000404` (H-blank vector) by `sub_08000AD4`. | high | Recomp: H-blank timing source; safe to treat as scanline callback. NOT save-related — drop the "save API" label. |
| sub_08000BAC | `HBlank_Raster1` | Byte-identical twin of `sub_08000B54` except descriptor `@0x0300059C` (one pool word differs: `0x0300059C` vs `0x03000580`). Same VCOUNT/IRQ behavior. | high | Same as above. |
| sub_08000C04 | `HBlank_Raster01` | Same template, calls `StridedCopy` twice per scanline: desc `@0x03000580` then `@0x03000580+28`. Same VCOUNT==159 IRQ teardown. | high | Same as above. |
| sub_08000C68 | `StridedCopy` | Halfword strided copy engine: `dst=[d+4]`, `count=[d+8]` halfwords, `dst_step=([d+10]<<24)>>23`, `src_step=([d+11]<<24)>>23`, `src=[d+12]`; writes back updated src. 6 `bl` callers: `0xAE6/0xAFC` (in `sub_08000AD4`), `0xB6A` (B54), `0xBC2` (BAC), `0xC1C/0xC24` (C04). | high | Generic primitive; recomp already handles it as opaque code. |
| sub_08000AD4 | `HBlank_RasterSetup` | Runs pending strided copies immediately (descs `@0x03000580`, `+28`), then `DISPSTAT|=0x10`, `IE|=0x2`, and installs one of the three H-blank ISRs at `[0x03000404]` selected from table `@0x0816E230` by active-desc count (1→B54, 2→BAC, 3→C04). 2 `bl` callers: `0x0800090A` (in `sub_080008C0`), `0x0800095A` (in `sub_08000918`). | high | The H-blank vector install point; useful if the recomp ever needs to know when raster FX are armed. |
| sub_080004FC | `MainLoop` | Infinite loop: per-frame setup `bl`s, then VBlank wait (spins on flag bytes `@0x03000564/65` + `VCOUNT==161`), then ~19-call per-frame dispatch (`sub_0800105C`, `sub_08001C88`, `sub_080046B0`, `sub_080050F0`, `DISPCNT&=0x7FFF`, `sub_080026E4/2D20/2DCC/2E50/2E80/2EE0/21FC/08C0`, keypad poll, `sub_08000E64/D90`, `sub_080267F8`, `sub_08000E04`), `b` back to frame top. No `bl` callers — entered via task table. | high | The frame driver. Registered as task #2 at boot (`sub_08000D90(2, 0x080004FD)` from `crt0_thumb_helpers`). |
| sub_08000418 | `Task_BootSetup` | Task #1 (registered `sub_08000D90(1, 0x08000419)`): long setup sequence (`bl sub_08002F24/4A2CC/CC24/D420/D3A0/456C/45F8`, state writes), ends `bl sub_08000E80` (task switch) — one-shot, yields to main loop. | medium | Boot sequencing; not per-frame. |
| sub_08000328 | `Task_Switch` | Coroutine context switch: `mov sp,r0`, pops all regs incl. hi regs, `bx lr`. Sole `bl` caller `sub_08000E80`. | high | Task system primitive. |
| sub_08000D90 | `Task_Register` | Registers `(index, handler)` into 24-byte task table `@0x030023C8`: `[e+4]=handler`, `[e+8]=index*2560+0x03000F74`, flag bytes. Called at boot for tasks #1/#2. | med-high | Task table base `0x030023C8` now known. |
| sub_08000CA8 | `Task_TableInit` | Zeroes/inits the 2-entry task table (`[0x030023C8]`), `[0x02000800]=0`. Called once from `crt0_thumb_helpers`. | medium | — |
| sub_08000D6C | `Task_WakePending` | Iterates 2 task-table entries, calls `sub_08000E64` on entries whose flag≠1. No `bl` callers (ISR/pointer-reached). | low-med | Tentative. |
| sub_08000E80 | `Task_SwitchTo` | Marks task entry active, loads sp from task struct, `bl Task_Switch`. Called from `sub_08000418`. | medium | — |
| sub_0804BCDC | `ARM_SampleMulAccum` | **Boundary correction:** v2 entry is mid-function; true entry ≈ `0x0804BB9C` (a `ble 0x0804BC74` inside branches *before* `0x4BCDC`; `str r8,[sp]`/`ldr r8,[sp]` pairing). ARM routine: per-element `ldrsb` sampling, delta decode (`sub r1,r1,r0`), dual `mul` accumulate with `bic #0xFF0000` channel masking, `ror #8` rotate-accumulate into two 32-bit results, 4-bank strided store (`adds r5,#0x40000000` / `bcc`, top bits cleared at exit). No `bl`/`blx`/pool/table refs found — caller unknown statically. | med (mechanism high, purpose low) | Recomp: the single non-crt0 ARM path. True bounds `~0x0804BB9C–0x0804BD7C`, not `0x4BCDC`. |
| sub_0800063C | `HwInit_WaitCntDma` | See §1.2 correction below. | med-high | WAITCNT value `0x45B7` now pinned; DMA3 arming idiom documented. |
| sub_0804C6B4 | `Text_SelectBlob` | Indexes 8-byte text directory `@0x08106DD0` (`r0=(idx&0xFFFF)*8`), loads blob pointer, `bl sub_0804CDE8`. 2 `bl` callers: `sub_08002FC4`, `sub_0800303C`. | medium | Text-bank access path (see text section). |
| sub_0804CDE8 | `Text_OpenDialogue` | Dialogue-box state machine: parses blob header (`[+0]`=window count, `[+2]/[+3]` flags incl. `0x80` gate, `[+4]` word, per-window dwords at `+8`), builds 80-byte window structs, calls `sub_0804C288`/`sub_0804CBCC` per window. | medium | Codec foothold: blob layout partially mapped. |
| sub_0804C288 | `Text_UpdateWindows` | Walks window linked list (`[r4+#52]`=next), flag-gated, dispatches per-window draw via `sub_0804C278`. | low-med | — |
| sub_0804C278 | `Text_DrawWindow` | Per-window draw helper (6 `bl` callers incl. `sub_0804C02E`, `sub_0804C288`, `sub_0804C2FC`). | low | Glyph rendering likely below this. |
| sub_08002300 | `LoadBgAssets` | Table-driven BG asset loader: per entry LZ77UnCompVram / CpuFastSet / RLUnCompVram → VRAM. 15 `bl` callers incl. `sub_080021FC` (called from `MainLoop`). | med-high | Scene BG pipeline; title screen loads through here. |
| sub_0800695C | `Tilemap_DecodeBlit` | Tilemap RLE-ish decode using tables `@0x080733A6` (match) / `@0x080733B2` (tile data) in the `0x73000` cluster, then `bl sub_08006AD8` (copy out). Callers: `sub_080068F0`, `sub_08006928`. | medium | Shared tilemap engine (title + scenes). |
| sub_08008460 | `Tilemap_DecodeBlit2` | Second tilemap decode/blit variant, same `@0x080733A6/B2` tables, calls `sub_080083F8`. Caller: `sub_0800B420`. | low-med | — |

### Callers of the three ex-"save API" entries (for the record)

None via `bl`. All three are reached **only** through the pointer table at
file `0x16E230` (ROM `0x0816E230`): `[0x08000B55, 0x08000BAD, 0x08000C05]`
(Thumb, LSB set). `sub_08000AD4` selects one by active-descriptor count and
stores it at `[0x03000404]` = the H-blank IRQ vector (crt0 dispatcher maps
IF-bit1 → table+4).

## Feeds-recomp

1. **"Save API" label is dead.** `sub_08000B54/BAC/C04` are H-blank raster
   ISRs, not save/load. The actual save path remains the 6 primitives at
   `0x0804DB38–0x0804DC94` (unchanged). If the recomp has save-shim notes
   referencing B54/BAC/C04, remove them.
2. **H-blank raster engine is now mapped** (`HBlank_RasterSetup` /
   `HBlank_Raster0/1/01` / `StridedCopy`, descs `@0x03000580/+28`,
   vector `@0x03000404`, teardown at VCOUNT==159). If the recomp's PPU
   ever needs to know when the game arms scanline effects, this is the
   place. Behaviorally it's a per-scanline callback — a recompiler can
   treat the ISR as opaque.
3. **Main loop identified: `sub_080004FC`.** Frame = VBlank wait
   (flags `@0x03000564/65`, `VCOUNT==161`) + 19-call dispatch. The boot
   chain (`Init` → `crt0_thumb_helpers`) returns into `b Init` spin —
   there is no C-style `main()`; frames are driven by `MainLoop` as
   task #2 via the coroutine task table (`@0x030023C8`,
   `Task_Switch`@`0x08000328`).
4. **ARM backend note:** exactly one non-crt0 ARM routine, true bounds
   `~0x0804BB9C–0x0804BD7C` (v2's `sub_0804BCDC` is a mid-function
   label). Fixed-point `mul` + signed-byte sampling + 4-bank output.
5. **Title-screen pipeline (partial):** BG assets load through
   `LoadBgAssets` (`sub_08002300`, LZ77/CpuFastSet/RL → VRAM,
   15 callers) and tilemaps decode through `Tilemap_DecodeBlit`
   (`sub_0800695C`, tables `@0x080733A6/0x080733B2`). The
   title-screen-**specific** init (which scene calls these for the
   title) is not yet isolated — needs game-state tracing (Phase 3).
   The known title glitch is therefore not yet attributable to a
   single function from the decomp side.
6. **Text engine foothold (hardest Phase 4 sub-task, code side):**
   text directory at ROM `0x08106DD0` (file `0x106DD0`), 8-byte
   entries `(blob_ptr, 0)` — 16 live blob pointers (indices 1, 3–17;
   rest point at default `0x08107320`) → `Text_SelectBlob`
   (`sub_0804C6B4`) → `Text_OpenDialogue` (`sub_0804CDE8`, blob
   header layout partially mapped) → `Text_UpdateWindows`
   (`sub_0804C288`) → `Text_DrawWindow` (`sub_0804C278`).
   No code references the `BE 66 BC 00` magic directly; blobs are
   reached via this directory, not via the `0x165C00` pointer tables
   (those are referenced from data-region tables only).

## Correction: ANALYSIS §1.2 (`sub_0800063C`)

**The note is wrong.** Disassembly of `sub_0800063C` (pools verified
from raw words):

| # | Target register | Value stored |
|---|---|---|
| 1 | `WAITCNT` (`0x04000204`) | `0x45B7` (halfword write) |
| 2 | `DMA3SAD` (`0x040000D4`) | `sp` |
| 3 | `DMA3DAD` (`0x040000D8`) | `0x03000000` |
| 4 | `DMA3CNT` (`0x040000DC`) | `0x85001F80` (32-bit, VBlank-timed, 8064 words) |
| 5 | `DMA3SAD` | `sp` (re-armed, supersedes #2–4) |
| 6 | `DMA3DAD` | `0x02000000` |
| 7 | `DMA3CNT` | `0x85010000` (32-bit, VBlank-timed, 65536 words = 256 KB) |
| 8 | EWRAM `[0x02002ED2]`, `[0x02002ED0]` | `0` (halfwords) |

Corrected reading: `0x03000000` **is** the IWRAM base (the note's
"EWRAM base" label is wrong), and it is stored to the **DMA3
destination-address register**, not "registered into a global struct".
The EWRAM base `0x02000000` appears separately as the second DMA3
destination. There is no struct registration in this function at all.
Same `SAD=sp` DMA3 idiom recurs in `sub_080021C4`
(`sp`→VRAM `0x06000000`, 96 KB) and other DMA3 users
(`sub_08002620/26E4/2D20/2D84/2DCC/5130`) — the boot arming is
superseded before the first VBlank; exact intent of the
stack-sourced fill is unclear (flagged unknown, not assumed).

## Open / low-confidence items (honest unknowns)

- ARM `sub_0804BCDC` (`ARM_SampleMulAccum`): exact purpose (audio
  vs graphics DSP) and caller unknown — no static refs.
- Title-screen-specific init: pipeline found, scene selection not.
- `Text_DrawWindow` and below (glyph rasterization): not yet traced.
- Boot DMA3 `sp`-source idiom intent: unknown.
