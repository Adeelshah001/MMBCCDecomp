# MMBCCDecomp → Recomp-track feed notes

Cross-track findings with value for the sibling **static-recompilation**
track (same ROM, different technique). Structure/metadata only — no
copyrighted content. Evidence pointers refer to `ANALYSIS.md`.

> Naming status at write time: `mmbcc/asm/savedrv.s` (sibling worker) did
> not exist yet, so save-driver functions use `sub_08XXXXXX` placeholders.
> When `savedrv.s` lands, its names supersede these.

---

## (a) Stable symbol table — real names so far

**Boot chain (`mmbcc/asm/crt0.s`, asm-verified byte-identical):**

| ROM address | Symbol | Role |
|---|---|---|
| `0x080000C0` | `Init` | ARM; sets IRQ stack `0x03007DA0`, sys stack `0x03007FA0`, stores resume addr `0x080000FC` @`0x03007FFC`, `bx` to Thumb entry |
| `0x080000FC` | `IntrWait` | ARM; polls `REG_IE/IF` (`0x04000200`) |
| `0x080001BC` | `IrqDispatcher` | ARM IRQ dispatcher |
| `0x080002A4` | `ArmTrampoline` | ARM trampoline |
| `0x0800033C` | `crt0_thumb_helpers` | Thumb entry; calls ~16+ init routines, writes `0x0080` to `REG_DISPCNT`, returns |

**BIOS veneer table @`0x0804DB24`** (five `svc N; bx lr` wrappers, 4 B
each — templated, match first):

| ROM address | SWI # | BIOS function |
|---|---|---|
| `0x0804DB24` | 0x0C | CpuFastSet |
| `0x0804DB28` | 0x0B | CpuSet |
| `0x0804DB2C` | 0x12 | LZ77UnCompVram |
| `0x0804DB30` | 0x11 | LZ77UnCompWram |
| `0x0804DB34` | 0x15 | RLUnCompVram |

**Save-driver primitives @`0x0804DB38–0x0804DC94`** (names pending
`sibling savedrv.s`; placeholder symbols + roles):

| ROM address | Placeholder | Role (ANALYSIS §2.5) |
|---|---|---|
| `0x0804DB38` | `sub_0804DB38` | memcpy |
| `0x0804DB5C` | `sub_0804DB5C` | WAITCNT (`0x04000204`) `|= 3` + dispatch |
| `0x0804DBC0` | `sub_0804DBC0` | SRAM→RAM copy |
| `0x0804DC00` | `sub_0804DC00` | verify-compare |
| `0x0804DC30` | `sub_0804DC30` | verify worker |
| `0x0804DC94` | `sub_0804DC94` | 3×-retry wrapper (end address not yet pinned) |

**CORRECTION 2026-10-20 — the "save API" label is dead:** `0x08000B54`,
`0x08000BAC`, `0x08000C04` are **H-blank raster interrupt handlers**
(`HBlank_Raster0/1/01`), NOT save/load functions. They gate on
VCOUNT≤159, call the strided-copy helper @`0x08000C68`, and tear down
the H-blank IRQ at VCOUNT==159; they touch no SRAM/WAITCNT/save
primitive. Reached only via the pointer table @`0x0816E230` (adjacent
to the save-device table — that's what misled ANALYSIS §1.6/§2.5).
If the recomp has save-shim notes referencing B54/BAC/C04, remove them.
The real save/load entry points are still unidentified; the save path
remains the 6 primitives @`0x0804DB38`–`0x0804DC94`. Full detail:
`docs/symbols_phase2.md`.

**Function-count correction (recomp-track impact):** the decomp's
independently verified analysis finds **1703 probable functions**
(51 confirmed + 1652 probable; docs/func_list_v2.txt [fixed hi-reg MOV
decoder] + v2.5 addendum), not 14,102. The 14,102 figure came from
recursive descent into data regions — false positives from compressed
graphics. If the recomp is carrying per-function metadata for 14,102
entries, ~88% of them are likely data misclassified as code
(ANALYSIS §1.4, `docs/func_list_v2_method.md`).

---

## (b) Save-system behavior summary (for the recompiler)

- **SRAM base construction:** built arithmetically —
  `movs rX, #0xE0; lsls rX, rX, #20` → `0x0E000000`. No literal pools,
  so signature scans for a `0x0E000000` pool word miss it.
- **Slot addressing:** `addr = 0x0E000000 + (index << 13)` — 8 KB
  (`0x2000`) slots. 4 addr-compute sites: `0x08001DB8`, `0x08001E30`,
  `0x08001F1C`, `0x08002070`.
- **WAITCNT handling:** the driver ORs `0x3` into `WAITCNT`
  (`0x04000204`) before SRAM access (sub_0804DB5C). A recompiler's SRAM
  shim must tolerate/ignore this; it's timing config, not data.
- **Retry semantics:** verify-compare (`sub_0804DC00`) + verify worker
  (`sub_0804DC30`) under a **3×-retry wrapper** (`sub_0804DC94`).
  Save failure = 3 failed verify cycles, not one.
- **Device table:** file `0x16E148–0x16E230`; `SRAM_V113` descriptor
  @`0x16E1D0–0x16E220` (16-byte records); entry @`0x16E208` with driver
  table `[0x0804DB39, 0x0804DB5D, 0x0804DC01, 0x0804DC31]` — **Thumb
  addresses (LSB set)**; strip the LSB before using as code pointers.
- **API entries:** `0x08000B54`, `0x08000BAC`, `0x08000C04` — the game's
  own save/load call sites funnel through these.
- **Implication for the recomp:** SRAM emulation only needs
  read/write/verify at `0x0E000000 + (index<<13)` granularity; the
  WAITCNT poke and retry loop are the only timing/behavioral subtleties.

---

## (c) Text-codec status — STILL UNKNOWN

- Text bank: file `0x165C00–0x16D630` (31,280 B); 13 pointer tables →
  **98 variable-length blobs** (110–1120 B, avg ~301 B).
- Every blob starts with magic **`BE 66 BC 00`** (106 occurrences, all
  confined to file `0x165000–0x16E000`); 81/98 end with `0xB1`.
- Content entropy **6.30** — not plain text, not single-XOR. Most
  plausible: **custom Capcom container** (compressed text or
  text+control bytecode) — **hypothesis**.
- Codec unidentified; font glyph data not located. Hardest single
  Phase 4 sub-task (ANALYSIS §2.2). **No action for the recomp track
  unless it wants dialogue text.**
- Also relevant: no ASCII outside the header, no Shift-JIS anywhere,
  dialogue is NOT inside LZ77 blocks (38 "text-like" blocks profile as
  graphics).

---

## (d) Other reusable findings

- **BIOS SWI numbers used:** 0x0B (CpuSet), 0x0C (CpuFastSet), 0x11
  (LZ77UnCompWram), 0x12 (LZ77UnCompVram), 0x15 (RLUnCompVram). No
  `swi 0x25` (not multiboot), no `swi 0x0D` (no static ROM-checksum
  evidence) — ANALYSIS §1.5, §1.7.
- **Header quirk byte:** file `0xBD` stores `0x7B`; the GBA complement
  check over `0xA0–0xBC` computes `0x94`. Verified 3× independently
  (an earlier "valid" report was a script bug). The dump is no-intro
  verified — this byte shipped on the physical cartridge. Real hardware
  only enforces the logo at boot. **Any tool that rewrites the header
  (gbafix et al.) must preserve `0x7B`** — the decomp build applies it
  in a post-link step (`tools/finish_rom.py`).
- **ARM math routine @`0x0804BCDC`:** the only genuine ARM-mode game
  function (`push {r4,ip}`, uses `mul`/`ldrsb`). A recompiler's ARM
  backend needs exactly one non-crt0 ARM path for this game.
- **Init fn #2 @`0x080007D0`:** 14-word `ldm`/`stm` copy loop = the
  `.data`→WRAM initializer. Its src/dst/len operands pin the RAM-side
  `.data` extent (currently TO-REFINE — see `docs/memmap.md` §(c)).
- **Compression inventory (asset pipeline, not recomp-critical):**
  338 validated LZ77 blocks (318 v10 + 20 v11), 1,235,595 ROM bytes
  (14.7%) → 4.31 MB decompressed; largest `0x1A7E14` (v10, ~2.95 MB
  dec — needs validation), `0x51E8E` (v11, 1.12 MB dec); full list in
  `docs/asset-research/lz77_results.json`.
- **Audio:** proprietary Capcom driver (**hypothesis** — no M4A/MP2K
  signatures); MIDI-like sequences @`0x3A8DA8–0x3A95B8` with
  `0xFF`/`0xFE` delimiters. Audio pipeline is a stretch goal here;
  recomp track's fast-forward-audio wishlist item is unaffected by this.
- **Title-screen glitch area (recomp wishlist context):** decomp
  priority list includes the title-screen renderer as a target
  (ANALYSIS "Priority target list" #6) — future symbol/behavior notes
  will flow back through this feed.

## 2026-10-20 — Phase 2 naming results (from `docs/symbols_phase2.md`)

- **"Save API" label is dead** (see correction above): B54/BAC/C04 are
  H-blank raster ISRs. Real save/load entry points still unidentified.
- **H-blank raster engine mapped:** `HBlank_RasterSetup`@`0x08000AD4`
  installs `HBlank_Raster0/1/01`@`0x08000B54/BAC/C04` at the H-blank
  vector `[0x03000404]`; per-scanline `StridedCopy`@`0x08000C68`
  (descs `@0x03000580/+28`); teardown at VCOUNT==159. A recompiler can
  treat the ISR as an opaque per-scanline callback.
- **Main loop:** `sub_080004FC` — VBlank wait (flags `@0x03000564/65`,
  VCOUNT==161) + ~19-call dispatch. No C-style `main()`; frames driven
  by coroutine task table @`0x030023C8` (`Task_Switch`@`0x08000328`,
  `Task_Register`@`0x08000D90`).
- **ARM backend:** exactly one non-crt0 ARM routine, true bounds
  ~`0x0804BB9C`–`0x0804BD7C` (v2's `sub_0804BCDC` is a mid-function
  label). Fixed-point mul + signed-byte sampling.
- **Title pipeline (partial):** `LoadBgAssets`@`0x08002300` (15
  callers) + `Tilemap_DecodeBlit`@`0x0800695C`; title-scene init not
  yet isolated — the title glitch is not yet attributable to one
  function.
- **Text foothold:** directory @`0x08106DD0` → `Text_SelectBlob`
  (`0x0804C6B4`) → `Text_OpenDialogue` (`0x0804CDE8`, blob layout
  partially mapped). The `BE 66 BC 00` codec itself is still unknown.

## 2026-10-20 — Phase 3: H-blank engine C-matched (4/4)

- **Self-disarming ISR:** at VCOUNT==159 the raster ISRs clear
  DISPSTAT bit 4 and IE bit 1 — the effect disables its own H-blank
  IRQ on the last visible scanline. Model as a per-scanline callback
  active only for VCOUNT 0–159.
- **Setup primes immediately:** `HBlank_RasterSetup` runs the pending
  `StridedCopy`(s) synchronously, then sets DISPSTAT|=0x10 / IE|=0x2
  and installs the vector at `[0x03000404]`. Vector selection:
  sel=1->Raster0, 2->Raster1, 3->Raster01, 0->not armed.
- **Descriptors are stateful:** `desc[3]` primed from `desc[0]` at
  setup; `StridedCopy` advances the src word per scanline —
  0x03000580/0x0300059C carry frame-progress state.
- **Raster0's slot (index 1) is never selected by this setup**
  (sel in {2,3} when arming) — possibly installed from another path
  or vestigial; flag if the recomp ever sees vector 0x08000B55
  installed from elsewhere.
- Matched sources: `mmbcc/src/hblank.c` (4 functions, byte-identical).

## 2026-10-20 — Phase 3: MainLoop fully mapped (C-match blocked, behavior mapped)

- **Frame pacing:** spin on `IWRAM[0x03000564] < [0x03000565]`, then
  `VCOUNT==161`, then clear `[0x03000564]` — model as "wait for VBlank".
- Per frame: `u16@0x02022ED2` toggles 0/1, `u16@0x02002ED0` cleared;
  `DISPCNT &= 0xFF7F` (OBJWIN off).
- 20-call dispatch, all no-arg except `sub_08000E64(1)`,
  `Task_Register(1, 0x08000419)`, `sub_080267F8(0x020070F0)`,
  `sub_08000E04(arg,1)`; no `bl` callers (task-table entry).
- **Keypad combo on EWRAM @0x02002F50/54** (bits 0,1 + bits 2,3, with
  `[r5,#4]` second read) re-registers task #1 — likely debug/reset;
  guarded by `*(u8*)0x02002F80==0` and `!(((u16*)0x02002EE0)[1]&1)`.
- Full structural notes: `docs/match_notes_mainloop.md`.

## 2026-10-20 — Phase 3: text directory + blob layout refined (SelectBlob matched)

- **Directory entries are NOT (blob_ptr, 0):** word[1]'s low halfword
  is a live index into 12-byte structs at 0x08106D7C
  (`sub = *(u16*)(entry+4)`, `cfgWord = *(u32*)(0x08106D7C + sub*12)`).
- The 5 functions at 0x0804C6B4/6E0/72C/780/7B4 share an identical
  10-insn prologue — likely one macro/inline in the original source.
- **Blob header:** [+0] u8 window count; [+2] u8 vs cfg[9] high-water
  (unsigned bhi); [+3] u8 bit7 gates sub_0804CBCC(blob[3]); [+4] u32 ->
  cfg[48]; [+8] u32 per-window dwords.
- **Window structs** 80 B at cfg[44]: per-window init writes
  [+0]=192 (u8), [+32]=i, [+64]=blob[8+i*4]; second loop covers
  i in [blob_count, cfg[8]) writing [+0]=0.
- **cfg struct:** [+52] magic guard 0x68736D53 (inc/restore/verify);
  [+11] u8 gate; [+28/+32]=150, [+30]=256, [+34/+36]=0, [+4]=0,
  [+0]=blob, [+12]=0. Full map: docs/match_notes_text.md.
- Matched source: mmbcc/src/text.c (Text_SelectBlob, old_agbcc).

## 2026-10-20 — Phase 3: task system + HW init matched

- **Task stacks:** each task gets a 2560-byte IWRAM stack at
  `0x03000FA0 + index*2560`, just below the task table @0x030023C8 —
  exact stack extents for the recomp's task-table shim. Entry:
  24 bytes (u8,u8,u16, handler, stack, +12 pad); flags [e+0]=2.
- **HwInit concrete state:** DMA3 double-arm (sp->IWRAM 8064 words,
  then sp->EWRAM 256KB, both VBlank-timed; superseded before first
  VBlank); two zeroed EWRAM halfwords [0x02002ED2]/[0x02002ED0].
- **StridedCopy semantics** (structurally confirmed, C blocked on
  regalloc): steps are (s8)step_byte*2, recomputed per iteration;
  u16 count with wraparound decrement; updated src written back to
  the descriptor.
- Matched sources: mmbcc/src/task_register.c, mmbcc/src/hwinit.c.

## 2026-10-20 — Phase 3: save primitives C-matched (behavioral gold)

- **`Sram_WaitcntInit`/`Sram_VerifyWorker` execute from IWRAM:** they
  copy the *following* function's machine code (36 B / 48 B, length
  derived as `(u32)NextFn - (u32)CurFn`) into an IWRAM stack buffer
  and call it there — the SRAM timing window runs from fast RAM.
  A recompiler must preserve this (the timing-sensitive code cannot
  run from ROM/Flash wait-states in the model).
- The old asm's `bl 0x0804DCD8` was agbcc's `_call_via_r3`
  (ARMv4T has no `blx`); 8 `_call_via_rN` thunks live at
  0x0804DCCC–0x0804DCEC in the original link.
- `Sram_RetryWrapper` = read -> verify, up to 3 attempts, returns
  the verify result. `Sram_Read` signature is (src, dst, len).
- Matched sources: mmbcc/src/bios.c, mmbcc/src/sram.c,
  mmbcc/asm/thunks.s (all byte-identical).

## 2026-10-20 — Wave 2: Vec2 mirror helpers (worker B, verified)

- `Vec2_SetMirrored`@0x0800DD2C and `Vec2_AddMirrored`@0x0800DD4C
  matched in C (mmbcc/src/vec2.c). The three-function family
  (`sub_0800DD08/2C/4C`, 84/82/71 bl-callers) works on game-object
  structs: **flag byte at struct offset +35, bit 7 = horizontal mirror**;
  **s32 X/Y vector at +80/+84**. Set/Add variants are byte-identical;
  the Copy variant is functionally understood but blocked on a
  register-allocation diff.
- Recomp-relevant: the +35 flip-flag / +80 vector layout is a stable
  struct fact the recomp track can use when naming object fields.

## 2026-10-20 — Wave 2: EntryMgr setup/teardown + GatedDispatch (worker D, verified)

- `EntryMgr_Teardown`@0x08004F18 / `EntryMgr_Setup`@0x08004F80 matched
  in C (mmbcc/src/entrymgr.c). 3-entry manager at **0x02003670**
  (entries at +44/+0x264/+0x49C, mode flag byte at +0x11AE, generation
  counter at [base]); byte at 0x02005028 cleared on teardown; Setup
  bumps the counter. The pair is always called together — useful for
  naming the manager in the recomp track.
- `GatedDispatch`@0x08006DD8 matched (mmbcc/src/gateddispatch.c):
  returns 0 while `*(u8*)(0x02004830+0x265)` set, else forwards to
  `sub_08006E6C` — 77 callers, mostly from table-driven dispatcher
  `sub_080285C4`.

## 2026-10-20 — Wave 2: Text_SelectBlobIdx + Gfx_BlitRequest (worker C, verified)

- `Text_SelectBlobIdx`@0x0804A378 matched (mmbcc/src/text_idx.c):
  `s16 f(u16 idx) { return sub_0800303C(idx); }` — entry into the
  text-blob-select path; 194 callers.
- `Gfx_BlitRequest`@0x08006A54 matched (mmbcc/src/gfx.c, name
  tentative): gated forwarder to `sub_08006AD8`, gated on
  `*(u8*)0x02004A95`; 151 callers, mostly graphics-path.
- `sub_0802D7A0` (proposed `Obj_AddEntry`) understood but blocked:
  appends a 16-byte entry to a work buffer (`work[work[5]*16+420..435]`,
  count at `work[5]`); 159 callers.

## 2026-10-20 — Wave 2: ChipSlot helpers (worker A, verified)

- `ChipSlot_IncUse`@0x0800D9EC / `ChipSlot_Setup`@0x0800D6E0 matched
  in C (mmbcc/src/chipslot.c). Battle-chip slot bookkeeping: IncUse
  calls `sub_08004258(s+0x70, idx)` (216 callers — hottest utility in
  the ROM); Setup calls `sub_0800D800(s, 0, b, c, 0)`.
- `sub_0800D9FC` (proposed `ChipSlot_Tick`, 121 callers) mapped but
  blocked: per-slot state update touching an EWRAM pair array at
  0x02005030 with a relative-offset table walk.

## 2026-10-20 — Wave 3 batch 3 (15 leaf functions matched)

- `0x02005130`: EWRAM global struct (tentative `g_02005130`, u8-based)
  with s8 field at +0x0A and u16 field at +0x12. Both accessors have
  zero bl-callers — invoked via function pointers or dead code.
- `0x0200BD10`: two adjacent u16 globals zeroed together (callers
  sub_08000418, sub_080267F8 — latter near the text-init cluster).
- `0x0200CE08`: function-pointer global taking one u32 arg, invoked via
  `_call_via_r1` (caller sub_0804C2FC) — a callback slot.
- `0x080174xx` struct family: counter bytes at 0x11/0x12, s16[4] (two
  pairs) at 0x78. Members matched: GetU8_12, IncU8_11 (increment-then-
  explicit-reload), GetS16_78_3. Siblings in batches 1/4/5.
- `0x08002FC4` (Text_SelectBlobU16): u16-truncating wrapper on the
  text-bank path (Text_SelectBlob@0x0804C6B4), 4 call sites.
- `0x08021290` (Wrap_ChipSlotTick): forwarder to wave-2's blocked
  ChipSlot_Tick candidate, zero bl-callers — likely called indirectly.
- `0x080057FC` (NoopStub): empty stub, sole caller EntryMgr_HookA.

## 2026-10-20 — Wave 3 bulk (batches A/B/D/E discoveries)

- **Script bytecode interpreter (~0x0804BE10):** `bx ip` dispatch loop;
  engine state at r1 (+0x02 u8 call depth, +0x40 u32 script ptr, +0x44
  u32 return-stack[3]); gosub/return opcodes at 0x0804BE70/0x0804BE8C;
  every script pointer validated against ROM window
  0x08105CC8–0x01FFFFFF (bad pointer → opcode 0, not a crash). The
  recomp must preserve this validation.
- **EWRAM map (tentative):** 0x02005130 (u16 +12/+14/+16/+18, s8 +0x0A),
  0x02005160 (+68/+72 bytes, +0x46 u16), 0x020051B0 (+20 flag byte,
  set/reader pair), 0x02005230 (+8 u32), 0x02005260 (triple u32),
  0x02007090 (+18 u16), 0x020070F0 (+7 byte), 0x0200BD20 (+128 u16,
  +130 byte), 0x0200081C (intrusive linked-list head, node +12 → +20).
- **ROM tables:** 0x0822740C (16-byte entries: u16 +6, u8 +11, ~249
  entries — chip/character data), 0x0820B6A4 (u32 table, u16 index),
  0x0822D69C (code-pointer table, 0x080Fxxxx entries — dispatch/vector).
- **ARM code exists** at 0x0804B974 (`add r2,r3,r0,lsl r1; add r0,r3,#0;
  bx lr`) — the recomp must handle this ARM fragment.
- **0x080174xx object/sprite attribute block:** u8 +16 (bit-test), +17
  (hot status byte, 49 callers), counters +0x11/+0x12, u16 pair +120,
  s16 pairs +0x78–0x7E (position-like). Relevant to title-screen work.
- **Text windows** dispatch per-window draw via fn-ptr at [struct+44]
  through the TailCallR3 (`bx r3`) trampoline.
- **SRAM/libgcc region 0x0804DD90–0x0804DE6E** is a non-interwork TU
  (`pop {pc}` epilogues, `mov pc,lr` stub) — hand-written or foreign
  compiler; recomp should preserve exact behavior.
- **Struct-init family** at sub_08005434: InitTriple_03090 +
  StoreTwoHalves_030BC + SetField204_04164 back-to-back (ROM-pointer
  field 0x0816E2CC → {0,0,0x08000400,0x20001000,...}).
- **REG_MOSAIC (0x0400004C)** is written from an EWRAM mirror at
  0x02003240 (CopyMosaicReg@0x08002EE0).
- **Task mode-dispatchers (Wave 4 batch F, 14 fns 0x0803531C–0x08049AB0):**
  EntryMgr_Teardown → mode byte → jump-table switch → EntryMgr_Setup.
  Dispatch INDIRECTLY via ROM fn-pointer tables 0x0822EAAC / 0x0822EAFC /
  0x082300A4 (indexed by (s8) struct fields) — indirect dispatch the
  static recomp must resolve through these tables, not bl edges.
  EWRAM touched: 0x02004CE0 (+0x28/+0x2A/+0x2C 16-bit regs),
  0x02004E40+0x14 (flag byte ORed 1), 0x02002F50/+4 (bit-test flags),
  0x02003670+0x11AC (counter nudged ±1 toward p[0x46AC]), 0x02004F80+2.
  0x0803E144 is the odd one: calls only Text_SelectBlobIdx, returns
  0/1 in ip (not a switch).
- **Indirect dispatchers (Wave 4 batch I, 62 matched):** the game
  dispatches per-index handlers via ROM fn-pointer tables
  `tbl[s[off]](s)` through `bl _call_via_r1` — ~35 tables mapped
  (dense 0x08226xx cluster = one subsystem's state handlers). Entity
  array at *(0x02007090+0x14), 144-B stride, index byte at +0x1B0.
  EWRAM vectors at 0x0200CD80/0x0200CE0C. CpuFastSet_Vram copies
  ROM→VRAM with src bank from flag nibble at 0x020031E4. Script
  dispatcher uses `tbl[*b->ptr++]` (table 0x08105F70).
- **Battle-scene dispatcher (Wave 4 batch J):** sub_080298FC
  (0x080298FC–0x0802C7B2) is a giant switch dispatcher that uses
  intra-function `bl` as LONG BRANCH (>2 KB targets, out of Thumb `b`
  range) to a single `bx r1` epilogue — a recomp must treat these as
  gotos, not calls. Object list: List_UnlinkPushHead@0x080044F4
  unlinks from doubly-linked list, pushes onto global head at
  *(0x0200081C), bumps u16 count. Obj_SetFromTableA/B/C
  (0x08011E98/0x08017084/0x08020F58): *(u32*)(obj+12)=4,
  *(u32*)(obj+20)=table[obj[9]]->val10, tables
  0x08223CC0/0x082243D8/0x08226EF0.
- **DMA helpers (Wave 4 batch H):** Memcpy16@0x08000758 (16-bit
  memcpy, CpuFastSet bulk for 32B+ chunks, CpuSet for tails; masks
  length with & 0x1FFFFF), Memset16@0x080006DC (fill variant, bit 24).
  Copy8_28D0@0x080028D0 copies 8 B to WRAM 0x03002420+(b<<5) — likely
  sprite/OAM/tile buffer with 32-byte strides. TableLookup_11C80:
  32-byte entries at 0x0817A9C4, valid for 0 < idx < 0x4867.
- **Task manager (Wave 4 batch G):** TaskMgr_Update@0x08000CD4
  iterates 3 entries (0x18 B each) at IWRAM 0x030023C8 (+0 u8 state,
  +1 u8 flag, +2 u16 countdown, +4/+8 u32 args); decrements counters
  (state=2 at zero), calls Task_Register when flagged, then
  sub_080002dc(entry, arg1, arg2, 0x02000800); repeats while
  *(u32*)0x030023C4 != 0. VCOUNT handler touches IWRAM 0x03000400
  block (+0x15c fn-ptr callback via _call_via_r0, +0x160 counter,
  +0x166 compare byte, +0x167 flag) and writes DISPSTAT high byte.
  Object initializers share ROM table 0x081705b0 + EWRAM table
  0x020031e4 indexed by (u16>>4)<<1, byte &3 clamped to 3.
- **Mode handlers (Wave 4 batch K):** task-init pattern = zero
  `p[1..5]` + `p[0x4698..0x46B7]`, `sub_0804A2DC(n)`, Teardown/Setup.
  Mode switches gated on poll fns; `gEwram_02004E40[0x14] |= 1` at
  handler entry; `Text_SelectBlobIdx(0x67/0x68/0x78)` for UI text;
  `*(u32*)(p+0x18/0x1C)` bitflags; `*(u16*)0x020031E0` bitmask
  cleared `&= 0xEDFF &= 0xDBFF`. ROM fn-ptr tables 0x082300D4/
  0x082300E0/0x0822FF4C/0x0822FF58.
- **VCOUNT/raster bookkeeping (Wave 5):** HBlank_VCountUpdate@0x08000978
  (IWRAM 0x03000400 block, now fully mapped): [0x15C]=fn-ptr callback
  (invoked via _call_via_r0 when vcount==[0x166]), [0x160]=u32 counter
  (incremented when vcount==0), [0x166]=u8 compare value (also written
  to REG_VCOUNT 0x04000005 when vcount < [0x166], else 0),
  [0x167]=flag byte (bit 1 set/cleared/XORed with 2 across the update).
- **Strided copy engine (Wave 5):** StridedCopy@0x08000C68 — descriptor
  {u16 unk0, u16 unk2, u32 dst, u16 count, u8 dst_step, u8 src_step,
  u32 src}; copies count halfwords with per-side byte steps scaled
  ×2 ((s8)step*2); writes back updated src. Used by the H-blank
  raster path (HBlank_Raster01 calls it per scanline).
- **Task mode handler (Wave 5):** Task_366A8@0x080366A8 — switch on
  p[2]: case 0 calls sub_08004DFC(1) then p[2]++; case 1 does
  Teardown, polls sub_08004E0C(0) as signed byte, and if zero sets
  p[1]=2, p[2]=p[3]=v (sign-extended), then Setup. (Note: earlier
  wave4_k notes had the branch inverted; ROM skips the body on
  nonzero.)
- **Count correction (Wave 5):** 1676 → 1674 — Frag_0803D9EC and
  sub_0803C20E proven interior labels (fallthrough entry, zero
  incoming edges), not functions. Recomp call-graph consumers should
  drop these two addresses.
- **Dispatch tables (Wave 5 H1):** TableCall_BB78@0x0800BB78 —
  indirect call via ROM tables 0x081731A0 (fn ptrs) + 0x0817313C (s8
  index), guarded by *(s16*)(s+0x14) != -1. ListIterate_D568@0x0800D568
  — linked-list traversal (InitLinkedNode setup; node +4=next,
  +0x14=fn ptr; sentinel s+0x14). TableDispatch_9380@0x08009380 —
  6-entry 0x34-stride loop over EWRAM 0x02004CE0, dispatch via ROM
  table 0x0817212C indexed by (v>>6)&0xf.
- **Task handlers (Wave 5 G2):** Task_360C4@0x080360C4 — 5-case p[3]
  switch polling sub_0800B148/B2D8/B320/B308/B2B4/B2F0, ROM table
  0x0822EB44. Task_40798/45200/4529C — 7x Gfx_BlitRequest blit lists
  from ROM pointer tables 0x082325E4 / 0x08232C04 (arg1 0x2f vs 1 =
  mode). Task_4C8EC (blocked): script magic 0x68736D53 at
  *(0x03007FF0), EWRAM script ctx 0x0200CD80.
- **Object initializers (Wave 5 G1):** ObjInit_207EC@0x080207EC /
  ObjInit_22EBC@0x08022EBC — `*(s+108)=0`, `s[10]` bitflags,
  ChipSlot_Setup/IncUse, `s[0x45]` bits 2-3 = clamped idx,
  `s[0x22]`/`s[0x41]` config. Type IDs 0x411a/0x401b/0x501/0x255.
  ROM table 0x08227174 (u16, 6 B/entry, indexed by s[17]).
- **Task handlers (Wave 5 H2):** sub_0804dcd0 (unmatched) is a
  mode-availability poll used by 5 task fns; ROM tables 0x0822ea80,
  0x0823010c, 0x08230da8, 0x08231764, 0x0822eb6c. Task mode offsets
  0x4698/0x4699/0x469c, 0x46a4–0x46af, 0x46b7. SramInit_496A8@0x080496a8
  — SRAM init via CpuFastSet/CpuSet primitives.
- **F-retry correction:** Task_367E0's jump-table base is 0x08036800
  (not 0x080367FC); mode 8 body at 0x080369bc.

## 2026-10-20 — Wave 6 BLK-A + L1 (recomp-relevant)

- **ObjInit family key cracked** (`sub_08017D50`@0x08017D50): the shared
  idx pattern used by ~15 ObjInit-family functions is now understood
  (pinned idx register + opaque `ands` sequence). Expect the rest of
  the ObjInit family to fall next.
- **Struct-init family progress**: `sub_08003154`/`sub_08003298` show
  the family's constant-materialization habits (opaque OR-constants,
  fresh negations) — useful for reading other struct-init code.
- **Task_38AD4**@0x08038AD4: bit-test priority ladder on EWRAM
  `0x02002F50` driving `Text_SelectBlobIdx(0x66/0x67/0x68)` dialogue
  selection, then EWRAM `0x02004CE0` setup (`*(+0x28)=0x14`,
  `*(+0x2A)=(p[0x4698]<<4)+8`). New named EWRAM region `0x02004CE0`
  (also referenced by batch-F findings).
- **Correction**: a ROM pool word previously assumed to be `0x800` is
  actually the pointer `0x0800330d` — a reminder that pool constants
  must be read from raw bytes, not assumed.
- **Tooling note**: `docs/xrefs.tsv` undercounts callees for the big
  task dispatchers (0x08036A14 etc.) — they call unmatched helpers
  invisible to the leaves-up layer computation.

## 2026-10-20 — Wave 6 BLK-B behavior feeds (2 newly matched)

- **sub_080230A0** @ 0x080230A0: small utility operating on a table at
  0x081705B0 and EWRAM 0x02004E40. Computes `s32 v = 3 & tbl[idx]`
  (signed, clamped to >3 via `ble` branch), then calls
  ChipSlot_Setup(s, 0x3715, 0) and ChipSlot_IncUse(s, 0) — i.e. it sets
  up a chip slot with param 0x3715. Looks like a chip-slot
  initializer/validator helper. For the recomp: the `adds r0,r1,#0`
  redundant move is timing-neutral.
- **Task_37440** @ 0x08037440: 120-byte task-mode dispatcher with unusual
  prologue (r5=p, r4=mode). Flow: EntryMgr_Teardown() -> sets a flag at
  EWRAM+0x14 (|=1) -> dispatches on p[5]: case 0 calls sub_0800B368 via
  jump table at ROM 0x082300E0; case 1 calls sub_0800B308 and writes
  p[0x4699]=mode. So this is a task transition handler that tears down
  the entry manager, flags a state byte, and re-dispatches by mode
  through a function-pointer table. The JT at 0x082300E0 and the
  p[0x4699] mode field are new stable addresses for the recomp's task
  model. sub_0800B308/sub_0800B368 (unmatched) are the next high-value
  targets — they sit behind this dispatcher.

## 2026-10-20 — Wave 6 L4 behavior feeds (29 newly matched)

- **Ent_TblInit family (x11)**: 11 near-identical 50B entity
  initializers at 0x08021000/0x080217e0/0x08022920/0x0801d36c/0x08021df8/
  0x0802054c/0x08023034/0x08021528/0x0801f1e8/0x08022644/0x080236f0,
  differing only in table addresses. Shape: `t1 = tblA + s[9]`
  (entry select), `*(s+12) = 1`, `*(s+20) = *(entry+4)`,
  `tblB[s[16]](s)` (per-type init callback), then dispatch via a
  0x08226xxx jump table. For the recomp: this is the entity spawn/init
  path — the `tblB[s[16]]` callback table and the 0x08226xxx dispatch
  tables are the type system. 11 instances suggest 11 entity archetypes
  or spawn contexts.
- **ObjInit family (x11)**: object initializers pairing
  ChipSlot_Setup(s, param, flag) + ChipSlot_IncUse(s, idx) with an
  idx clamp (`tblbyte & 3`) and `s[0x45] = (s[0x45] & -13) | (idx<<2)`
  bit-field packing, plus per-variant field stores (s[0x22], 0x600/8
  pairs, Vec2_AddMirrored offsets, Text_SelectBlobIdx calls). The
  `s[0x45]` bit-field (2 bits at position 2, mask -13) looks like an
  object subtype/orientation field. 0x08016dac uses a
  `tbl[0x08223CF0][s[13]](s)` dispatch prologue — another function
  table to preserve.
- **HwSetup_0804CCB8**: hardware setup via double-indirect through
  `*(u32**)0x03007FF0`, early-return guard, REG bit-test/set,
  `strh 0x400` x2, `CpuSet(zero, p+0x350, 0x05000318)`. IWRAM vector at
  0x03007FF0 is a hardware-config indirection the recomp must preserve.
- **Tick_08028244**: `s[1]` 0/1 state machine with `s[6]++` tick
  counter; calls InitRec8_267B4(0x020070F0, 9) when `s[6] > 180` or a
  flag is set. 180-tick (3-second) timer pattern.
- **Lists_0800E204**: iterates two object lists at `*(0x02005270)` and
  `*(0x020053C0)` via ListIterate_D568 — two more global list heads.
- **Get_0802503C**: returns a field from entity array 0x02007090+24.

## 2026-10-20 — Wave 6 L3 behavior feeds (15 newly matched)

- **ObjInit x11 more**: 11 additional ChipSlot-paired object
  initializers (0x080186F4/0x0801B3AC/0x08022320/0x08020D54/0x080223E4/
  0x08022E14/0x0801ABE4/0x0801D658/0x0801D828/0x0801F930/0x08019090).
  Combined with L4's 11, the ObjInit family now stands at 22 matched
  instances — a large, regular family the recomp can treat
  parametrically (Setup param, IncUse idx, s[0x45] bit-field, s[0x22]).
- **Sram_VerifySlot** @ 0x08001DB8: SRAM slot verification routine
  (112B). Pairs with the Wave 3 save primitives; the recomp's save
  path now has a verified slot-check.
- **Gfx_Blit3** @ 0x08042EC0: triple Gfx_BlitRequest call sequence
  using tables at 0x08232D5C/0x08232D70, base 0x08232D50, offset
  0x46AA, and byte at 0x08232BA4. Blit coordinates derived from
  `gBase_08232D50[4]+1` / `[5]+1,3,5`. Another VRAM blit helper for
  the recomp's graphics path.
- **Mem1_AllocInit** @ 0x0804CD70: memory-allocator init (106B);
  **Task_3AF98** @ 0x0803AF98: 100B task handler. Both extend the
  task/memory map.

## 2026-10-21 — Wave 9 batch B: Script_StepState behavior feed

- **Script_StepState @0x0803F480 (964B, MATCHED):** the script bytecode
  stepper. Called with `(ptr, 0)` from @0x0803d3a4 and `(ptr, 1)` from
  @0x0803d4dc (pointer passed in r7 at both sites).
- State layout around the struct pointer `p`: `p[0x46A0]` is an inner
  index byte, `p[0x464C + p[0x46A0] + sel]` an outer index byte, and
  `q = p + 0x46A4` a 256-byte step table. `v = q[outer]` selects one of
  22 handled opcodes (0,2,4,…,26,30,32,34,36,38,40,44,46).
- Each handled opcode writes a step count into `q[outer]`: 16 (v=0,2),
  18 (4,6), 20 (8,10), 22 (12,14), 24 (16,18), 26 (20,22), 28 (24,26),
  38 (30,32), 40 (34,36), 42 (38,40), 48 (44,46). Odd v, v=28, v=42,
  and v>46 are no-ops for the store.
- After the switch, `q[p[0x464C + p[0x46A0] + flag]]++` always runs,
  with `flag = (sel == 0)`. The recomp must preserve the exact
  double-indirect indexing and the unconditional trailing increment.

## Wave 10 (2026-10-21)

- **sub_0800B368 (new, MATCHED):** gate controller for the 0x02004E40 state block — if `(base[4]&128)!=0`: clears base[0..3], sets base[5]=3, stores arg at base+32, calls the B520/B4E4/B4C8 init chain, returns 1; else base[5]=1, returns 0. One of Task_3AFFC's callees; stable named symbol the recomp can reference.
- **sub_0800BEE0 RE decode (correction):** bitfield ops act on base **0x02004F40** (NOT 0x0200404f as W8 notes said), offsets +9/+10, using movs+negs for -7/-9. Call sites observed: `(0x40,0x80)` and `(0x40,0x00)`.
- **Task_3AFFC callees RE'd:** sub_080241F8 (`u8 (u16)` — switch on `a>>12`; cases call sub_08025A08/sub_08026554 or do table lookups; default 200) and sub_08024384 (near-twin, default 50, call site `sub_08024384(0x1000)-50`); sub_0800B148 (`u8 (u8,u16,u8)` — 340B bitfield state machine on 0x02004E40, call site `(1,(s16)w,4)`).
- **Division block fully mapped + transcribed (all byte-identical):** DupThunks @0x0804DCEC (7 hi-reg bx thunks r8–lr, NOT r0–r6 duplicates), SDiv_0804DD08 / SMod_0804DDA0 / UDiv_0804DE70 / UMod_0804DEE8 — the game's software division routines (__divsi3/__modsi3/__udivsi3/__umodsi3 equivalents, 4-bit alignment + 4-unrolled subtract/OR). The recomp must preserve their exact semantics including the divide-by-zero guard paths (beq → DivZeroStub_4DEDE).
- **Obj_AddEntry @0x0802D7A0 (340B, transcribed):** 10-param object entry — semantics: early check uses the 9th param (a8), 4th param is u8, sets `*p|=1` at struct+424. Global register home assignment (work→r7, a1→r6, a7→sl, a8→r8, a9→r9) documented for reference.
- **ComputeFields @0x0804CFD4 (MATCHED):** field computation with the `t = x & 4` test-before-save pattern; pool reload behavior of `pp[0]` documented.
- **BitCtl_520C (MATCHED):** bit control at gEwram_02003670+0x11AE with hword init at gEwram_020031f0 — true extent 92B.
- **Rank_49934 / PairBonus_2D460 / Clamp_26720 / S8TableLookup_0C248 / TableByte_16FAC / EwramLookup_26D94 / Xor_23CE4:** small stable named symbols with verified behavior (rank map, pair bonus checks, clamp ladder, s8 table lookup via gTbl_0817313C, ROM table 0x082240B8 lookups, XOR-fold).

## Wave 11 feed (2026-10-22)

- **Task_3AFFC path callees resolved:** `GetByte1_26554`@0x08026554 `u8 (void *ctx, s16 idx)` — 28B table entries at `*(ctx+4)`, returns `entry[1]`, 0 if idx>127 or entry[25]==0 (called from sub_080241F8 case 2 as `sub_08026554(0x020070A8, a & 0xFFF)`); `GetByte0_265B0`@0x080265B0 `u8 (void *ctx, s16 idx)` — returns `entry[0]`, **49** if invalid (sub_08024384 case 2); `GetPtr14_265D0`@0x080265D0 `u8 *(void *ctx, s16 idx)` — returns `&entry[14]`, NULL if invalid. Use these signatures for the recomp's 3AFFC-equivalent dispatch.
- **3AFFC corrections:** true extent 928B, returns u32 (not u8); sub_0800B148's 2nd param is s16 (not u16) — explains `asrs`; mode 9: `p[0x469c] = g8`; mode 15: `*q = 6`; mode 14: `B368(0x0823190C)`.
- **sub_0803FACC → DecisionTree_3FACC:** accepted set `{0x1030, 0x3030, 0x2030, 0x4030} ∪ [0x30, 0x36]` — note 0x2030 (prior note said 0x3020, wrong).
- Misc stable symbols: `Poke_4AC88` (pool 0x0200BD20 pokes), `Memset_11C14` (dual memset at 0x02005260), `Decode_23B88` (u16 decode loop), `Init_1E74` (guarded init at 0x02002F80), `F_4BDC0` (list unlink), `F_23D10` (checksum), `F_25490` (byte swap).

## Wave 13 feed (2026-10-22)

- **Task_3AFFC callees MATCHED (stable symbols for the recomp):** `SyncObjFlagBits_BEE0`@0x0800BEE0 — flag-bit setter on object base 0x02004F40: early-return if `*(u16*)(base+20)==a`, else `*(u16*)(base+6)=a` + bit ops on base[9]/base[10] keyed on b (128 / >128 / else); `TblGetByte_241F8`@0x080241F8 — u8 lookup dispatched on `a>>12` (case 1/2 → table entry getters, case 3 → ROM table 0x082298F0, case 4 → `*(0x020070CC+1)`, default 200); `TblGetByte_24384`@0x08024384 — near-twin (default 50). All three byte-identical.
- **New stable symbols:** `ChipSlot_InitEntry`@0x08046CA0 (chip-slot struct+array init pattern), `DispCntRestore_Dma3`@0x08002D20 (DISPCNT save/mask/merge/restore + DMA3 SAD=0x020031E4/DAD=0x04000008), `PalDmaInit_02678`@0x08002678 (palette DMA via 0x03002420 → 0x05000000), `DrawText_048B4`@0x080048B4 (string-to-tilemap: `dst=**(u16**)0x02003250 + (x+y*32)`, tile = `(c>0x9F?0x2E0:0x3A0)+c`).
- **sub_0800B148 CFG (still blocked, for reference):** bitfield state machine for task dispatch — checks `(base[4]&15)`, `(base[4]&128)`, decision tree on `(base[21]&15)` vs param a, two `base[21]` write sites; calls 0x0800B470 (s16), 0x08007EEC (conditional), 0x0800B6F4.
- **B3 @0x080244B0 (blocked):** likely second-vintage function — allocation matches old_agbcc naturally (pinned-copy trick was harmful here); only its scheduler differs. If the recomp reimplements it, plain C suffices.

## Wave 15 feed (2026-10-22)

- **GuardedListInit family (10 functions, 0x0800E400–0x0800E950, all MATCHED):** flag-guarded list init template — sets `*(u16*)0x02005130+24 = 1`, checks `(s8)IsZero_02005160_*(...)==1`, clears + calls SetByte20(0), then ListIterate_D568 on `*(u8**)0x02005270` and `*(u8**)0x020053C0`. Members differ only in checker function. Reusable pattern for the recomp's list init.
- **New stable symbols:** `TaskScan_08000D6C` (3-slot task scan), `Task_ActivateSlot`@0x08000DC0 (task-slot init), `TblStride_24818`, `Tbl_ClearEntries`@0x08011170, `ChipInit_0801C3FC/0801C540` (chip init wrappers), `IdxLookup_080246FC` (range-checked table lookup), `CondCopy_0800EAF4`, `FlagStore_0800EB70`, `CopyBytes_0800EAC4`.
- **B148 @0x0800B148 (still blocked, 191 diffs):** R1 memcheck b16 copy + R2 t21 in-place angles solved; residual is prologue save-set + regalloc. **Task_3AFFC @0x0803AFFC (still blocked, 288 diffs):** mid-switch tail_c label fix placed shared tail correctly; modes 0–9 at 91%.
- **Build hygiene fix:** orphan section merge bug fixed (wave13_B.o's duplicate section was corrupting ROM region 0x08024432+; now discarded).

## Wave 16-D feed (2026-10-22)

**6 blocked-revisit matches landed:** ResetStateBlock_3618c (zeroes 8B state + init call seq), ObjSlotInit_05FC0 (32B slot init), ObjInit_21E64 (object init, old_agbcc), TblLookup_0804C7B4 (table lookup w/ ClearSignBit call), RecInit_08027C84 (record init), F_0802FD68 (p[3] state machine).

**New stable symbols for recomp cross-track:** ChipSlot_Setup/ChipSlot_IncUse callees confirmed in ObjInit_21E64; ClearSignBit_0804C5F4 called from TblLookup; InitRec8_267B4 + LoadCallClear_4A328 sequence in RecInit.

**Idioms:** tied-opaque pool anti-folding, volatile-barrier shift/pool interleave, divided-syntax adds ordering, opaque zero vs r5 zero-CSE.

## Wave 16 feed (2026-10-22, COMPLETE)

**+33 matches (623/1674 total):** 15 leaves-up (B: Node_PopAndInit twins, Dispatch_24434, Sub_1AB34, Fill/Buf ops), 12 leaves-up (C: 7 ChipInit variants, TwoTblOps, CondSet7, ChipFlagSet, StateMachine), 6 blocked revisits (D).

**B148 breakthrough:** prologue save-set solved — explicit register variables excluded from GCC 2.9 save-set computation (unpin to fix). 191→95 diffs.

**New symbols for recomp:** ChipSlot_Setup/IncUse patterns confirmed across 7 ChipInit variants; Vec2_AddMirrored, Text_SelectBlobIdx, Wrapper_D770/D728 call sequences; TblLookup_25730, GetRomTableU16, Buf_RemoveAt_25290, Append_0802526C buffer ops.

**Idioms:** r7-pin miscompile, u16 increment, double-OR constant-first, pinned-r0 zero, late pool materialization, goto-ladder, opaque adds copy, tied-opaque pools.

## Wave 17 (2026-10-22) — coordinator additions

- **sub_0800B148 MATCHED:** EWRAM `gEwram_02004E40` state update — takes (u8 a, u16 b, u8 c), returns 1 if full update runs, 0 on early exit. Manipulates bits in base[30]/[31]/[21]/[19]/[5]; calls B470/7EEC/B6F4. Key Task_3AFFC-path callee now fully matched.
- **Task_3AFFC tail-sharing decoded:** case 3 sets up (r0=9, r1=&p[0x469c], r2=0) → shared `strb r0,[r1,#0]` at 0x803B33C; case 13 sets up (r0=7) → fallthrough. r2=0 caller-provided for later p[0x469d]=0.
- **ChipInit family (10):** Node_PopAndInit wrappers with variant params (0,1,b,3), (0,1,c,6), etc.; u16*(n+120) stores.
- **Search_080112FC (248 B):** table search routine; **TableWalk_080113F4 (194 B):** table walker.
- **StateMachine family (13 C1):** 64B/92B state machines with p[2]/p[3] store variants.

## Wave 18 (2026-10-23) — coordinator additions

- **+27 matches (687/1674 total):** A: Task_3AFFC 351→70 diffs (still blocked; `goto store6` tail-sharing, deferred-zero case 9, two-step ldrh — remaining: modes 2/4 interleave, case-9 g8 in r2, case-13 branch layout); B: 17 leaves-up (TblWalkInit/Ret, TaskInit ×3, 8 NodeInit wrappers, Loop3, etc.); C: 2 blocked revisits (StateMachine 0x0800e6d0, F_0803AED0); D: 8 bulk (AllChipCopiesValid_08049704 + 7 NewNode_* wrappers).
- **NewNode_* family (7):** thin Node_PopAndInit wrappers — (0,1,0,17), (0,0,a,11), (0,1,0,12), (0,1,b,17), (0,0,0,17), (0,0,0,11), (0,1,c,16)+Vec2_SetMirrored. Battle object node allocation entry points; param patterns (type/id/variant) useful for recomp object-system RE.
- **AllChipCopiesValid_08049704 (124 B, old_agbcc):** validates chip copies via table at 0x082344D6 + AddTableEntry_082344CC; EWRAM base 0x020070F0.
- **Idioms:** u8 z=0 zero-materialization ordering, FIXALIGN1 (`.align 2,0`→`.align 1,0` for sub-4B-multiple fns), linked-at-address verification, deferred-zero variable, explicit-q ordering, jump-terminated cross-jumping, c24-unpin, t30-reuse mask.

## Wave 20 feed (2026-10-23)

- **Task_3AFFC structural findings** (staging/wave20_A/w20a_best4.c): case-9 g8 copy semantics (live-range forces r2 copy; case 3 keeps g8 in r0 — the live-range difference is the driver); modes 2/4 table-init does `(u8*)t + (u32)tbl` index-as-pointer adds; 0x469d pool load shared across case 14/store6 with contextual allocator preferences.
- **Slot family** (0x0801e14c/0x080173d4/0x0801787c): table lookups via pool **0x082243D8** (corrects wave-15 typo 0x082243D4); SlotCopy/SlotClear/TblSlotInit shapes.
- **BuildList_08021D10** (0x08021d10): list building with prev→r4 / i→r5 allocation; node layout with mid-function pool.
- **Setup_08005F44** (0x08005f44): u32 mask negation pattern; **ChkFlag_080247E8**: flag-check with mid-function pool.
- **Twin setups** 0x0800EB30/0x0800EC3C: Setup_0800FFF4/0801009C + SetByte20(4)/(11) — differ only in immediate.
- All new symbols are stable, named, byte-verified — usable as reference for the recomp track.

## Wave 21 (2026-10-23) — behavior discoveries for the recomp track

- **Task_3AFFC @0x0803AFFC MATCHED (928/932 B):** the big task state machine is now fully named C. 22-case jump-table dispatch on mode; true footprint 932 B (926 code + 2 pad + pool word 0x469d at +0x3A0). Modes include entry-manager teardown/setup cycles, g8 register handling, deferred-zero patterns. This is likely the battle-scene master task — its mode table maps directly to scene phases the recomp's interpreter must preserve.
- **DrawObj_080439D8 @0x080439D8:** draw-object routine; object index from `p[0x46A9]>>4 + p[0x46A9]`; 184 B + 12 B pool. Relevant to the recomp's renderer if it re-implements object drawing.
- **Sram_08001E30 @0x08001E30:** SRAM routine — pins base `0xE0<<20` (= 0x0E000000) in r5 across calls; pairs with the Wave-3 save primitives. Save-path address construction confirmed arithmetically (no literal pools).
- **F_08043630 @0x08043630:** flag/count helper with `CountNonzeroStride`-style u32 counter; 3-pool function.
- **New generalizable idiom — clobber-reservation:** `__asm__ volatile("" : : "r"(x) : "r2")` denies a register to the allocator without pinning a variable (pinning poisons global allocation). Reusable anywhere the original compiler's register choice must be forced.
- **sub_08047CC0 extent correction:** true extent is 36 B (32 code + 4-byte pool), not 32 B — the pool word `0x46B4` at 0x47CE0 belongs to it.

## Wave 22 (2026-10-23) — behavior discoveries for the recomp track

- **Harness deliverable:** staging/wave22_A/corrected_addrs_sizes.txt — 56 function extents corrected (+4…+50 B) to include trailing literal pools. Any recomp-side tooling that sizes functions from the old table should use the corrected one.
- **Node_PopAndInit_11E20 @0x08011e20:** sibling of w16b_08017000 — node pop-and-init family now has two verified members.
- **Setup twins @0x0800ECF8/0x0800ED20:** Setup_08010270/08010308 wrappers storing 14/15 to byte 0x20 of 0x02005130 on success — differ only in the immediate.
- **F_0802493C @0x0802493c:** index validator chaining CheckPair_258D8 → GetStride4Byte20 → Clear20_Set21_FF → Sub_254E0.
- **Registry rename:** the live symbol at 0x080254e0 is **Sub_254E0** (w17d); the older F_080254E0 name is superseded — recomp references should use Sub_254E0.
- **0x08016D2C pool correction:** pool constant is **0x020031E4** from ROM bytes (disassembly misdecodes it).
- **New stable symbols:** DrawObj_080405D8 (draw-object, 180+12 pool), Entry_TryActivate_08010F34, ChipState_Tick_0800E3A0, Sram_TryInitSlot_08001EBC, F_08011A78, sub_08016D2C — all byte-verified, usable as reference.

## Wave 23 (2026-10-23) — behavior discoveries for the recomp track

- **sub_08002E80 @0x08002e80:** DispCnt shadow save/restore — saves p[1..3] through the 0x02003230 table into 0x04000040/44/48 (display registers); pairs with DispCntRestore_Dma3.
- **sub_08002CB0 @0x08002cb0:** DMA3 setup — `*p=(*p&0xFFF8)|0x1300` ((u16*)0x020031E0), q=(vu32*)0x040000D4 with q[0]=&spv(0), q[1]=p+4, q[2]=0x8500000E; p[2..5]=0xC008/0x4205/0x4406/0x4807; calls DispCntRestore_Dma3. Documents the display-DMA3 handshake exactly.
- **Script-interpreter op cluster @0x0804BDE0–0x0804C03C (20 functions):** the script VM's op implementations — ListWalk_0804BDE0, ValidateScriptPtr_0804BE2A (ROM-ptr validator), Script_Dispatch, Script_PopPtr, Script_CountLoop, 9× ScriptOp_Store* (validated stores into script state fields s[10..29] with s[0] flag bits), Script_LoadEntry3, Script_WriteWinIn (validated byte → *(0x04000060+op)), DispatchCounter. Directly useful for the recomp's script-interpreter RE (Path B).
- **F_080378B8 @0x080378b8:** flag-dispatch returning 0–4; pool is 0x469E.
- **Rect-fill family sizes (behavior-relevant):** sub_08006AD8 is a 768 B tilemap rect-fill engine (flag-limit validation, u16 tile copy loop with 0x8000-break, W|Y fill) — render-path reference. Family: 0x08007134 (480 B, calls 0x08006AD8), 0x080065BC (416 B), 0x08006374 (420 B, calls 0x080065BC 2×).
- **Compiler note for recomp tooling:** agbcc cannot emit `tst` in Thumb mode (ARM-only combine) — any recompiler-side pattern matching that assumes `tst` from C sources is wrong; the original hand-asm used it in the script VM.

## Wave 24 (2026-10-23) — recomp-relevant findings
- **InitRec28_4AF20 @0x0804AF20:** zeroes a 28-byte record, fills p[8]=TblGetByte_24384(a), p[10]=TblGetByte_24384(c), p[12]=Sub200_08024514(b), p[14]=Sub200_08024514(d), p[20]=a, p[22]=c.
- **SetAA_Clr2_08002EF4 @0x08002EF4:** calls F_0804C630, writes (u16)0xAA to *(u32*)0x02003244, clears *(u8*)0x02000818/0x02000819. Recomp note: a pool-loaded 0xAA cannot come from a C constant (compiler folds it) — the original used an address expression; equivalent behavior is just "store 0xAA".
- **Ewram4830_StateReset_0800A6BC / ChipState_Tick_0800E748 / ChipList_Setup_0800E224:** chip-state machine functions now named; useful symbols for the recomp's battle-chip logic.
- **Rect-fill engine @0x08006AD8:** confirmed 768 B tilemap rect-fill; prologue does param spill + selective hi-reg allocation — recomp can ignore the exact register choices.

## Wave 25 (2026-10-23) — recomp-relevant findings (partial: worker C landed)

- **ShiftPairCfg family (6 functions, all call ShiftPair_Copy_800C):** @0x0803F844, @0x08046810, @0x08045914, @0x0804A1F0, @0x0803AD48, @0x08041890. Each is a two-half switch on (s8)p[off] (cases 1/3): case 1 configures an EWRAM struct (base addresses incl. 0x02004D48, 0x02004DB0, 0x02004DE4) then calls ShiftPair_Copy_800C(base, idx); case 3 clears bit 1. Useful stable symbols for the recomp's sprite/pair-copy config paths.

- **HexFormat_08004998 @0x08004998:** hex-formats a u32 into a 16-byte stack buffer, calls DrawText_048B4(buf,b,c). Useful for the recomp's number-rendering path.
- **Task_Clock_08026740 @0x08026740:** clock task; S[16] seconds, S[17] minutes, S[18]/S[19] hours-ish state at EWRAM struct; calls F_EF8 + Task_ActivateSlot. Corrected control flow: S[18]=0 is inside if(S[19]!=99).

- **FlagPairDispatch_08045838 @0x08045838:** two-stage flag dispatch on p[0x46B0]/p[0x46B1] — value 1 programs EWRAM structs (bases 0x02004D48/0x02004D7C) then calls ShiftPair_Copy_800C; value 3 clears bit 1. Stable symbol for the recomp's sprite-config paths.
- **Rect-fill engine @0x08006AD8 (still unmatched):** prologue fully decoded via new inline-asm-prologue idiom; function is a tilemap rect-fill with ctx/b/c/d/e/pa params. When matched, will name the graphics blit family.

## 2026-10-23 — Wave 26 decomp feed
- New stable symbols: Tbl_SwapAndUpdate_080259A4 (0x080259A4, swaps *(p+20+b*4) / *(p+20+c*4), StoreIdx2_25638 calls), ChipState_F_0800E440 (0x0800E440, chip-state machine; calls Byte12_Gt1_080170C4), ChipState_Advance_0801BF10 (0x0801BF10, state dispatch on s[13] via 0x08226884 table), EntryState_08042C04 (0x08042C04, EntryMgr teardown/setup switch), ObjInit_08016EFC (0x08016EFC, 6-param object init), NodeInitSwitch_0800D1E0 (0x0800D1E0, 4-pointer switch state machine; calls NodeInit_0802260C).
- Note for recomp: several identical copies of tiny helpers exist (Byte12_Gt1 at 0x08011F68/0x080170C4/0x0801CDD8/0x0801D34C/0x0801F1D8/0x08022634) — callers are pinned to specific copies; don't merge them when lifting to recomp.
- Rect-fill engine (0x08006AD8, 768 B tilemap rect-fill): corrected semantics — mode else-branch, hs reuses rd, m1/m2 computed inside loop1, loop1/loop2 reachability structure; full decode in staging/wave26_A/w26a_08006ad8_v20.c.

## 2026-10-23 — Wave 27 decomp feed
- **Rect-fill graphics family MATCHED (all four):** TilemapRectFill_6AD8 (0x08006AD8, 768 B — tilemap rectangle fill with ctx/b/c/d/e/pa params), RectFill_7134 (0x08007134, 480 B), FillRect_65BC (0x080065BC, 416 B), FillRect_6374 (0x08006374, 420 B — calls 65BC twice). These are the game's tilemap/VRAM rectangle-fill primitives — prime candidates for the recomp's graphics pipeline (batch/accumulate their semantics rather than lifting the register-level code).
- **Dispatch_080482D8 (0x080482D8, 168 B):** state machine with indirect dispatch via _call_via_r1; case 0 calls Call4E60_4E44 + PalModeSet_4DFC(g_02004F80[2]). Stable symbol for the recomp's dispatch paths.
- Note: the rect-fill sources are asm transcriptions (compiler-impossible register allocation), so the C semantics are approximate — the full ROM decode in staging/wave26_A/w26a_08006ad8_v20.c is the better semantic reference for the recomp.
- **BlendCopy twins MATCHED (0x080224E4, 0x08021B3C, 206 B):** 15-bit color blender — copies a 15-bit pixel run through a two-half blend switch on (s8)p[off] (cases 1/3), then calls Memcpy16. Prime recomp graphics-pipeline candidate (the game's color-blend primitive). Note: sources are sanctioned asm transcriptions (C-unavoidable reload allocation); semantic reference is worker A's vC best-C (staging/wave28_A/w28a_080224e4_best_C_vC.c) plus the blend switch structure.
- **Reset_0801F254 family (0x0801F254 164 B, 0x0802375C 198 B, 0x0802298C 236 B):** chip/battle-object reset family — zeroes s[27] (108), clears bit 1 of s[10], with s16-boolean conversion `negs/orrs/lsrs #31` idiom on s[17]. asm transcriptions; semantics: init/reset of battle object structs.
- **ChipSetup_0801B0DC (0x0801B0DC, 220 B):** switch on s[17] (cases 0-2), calls ChipSlot_Setup/ChipSlot_IncUse/Wrapper_D770/Text_SelectBlobIdx. Stable chip-setup symbol for recomp.
- **MenuTick_0802D6E0 (0x0802D6E0, 192 B):** menu state machine tick — switch on p[1] with fallthroughs (0→1, 3→4), calls Cmp_08004E0C/Set_08004E24. Menu-loop symbol for recomp UI work.
- Idiom for the recomp's build: GAS 2.42 rejects `adds` mnemonic in Thumb-16 — use `add` (identical 0x1c08 encoding).

## Wave 29 (2026-10-24) — decomp → recomp feeds
- **ChipState_0801C030** (0x0801C030): chip-state dispatch on s[13] with ChipInit_0801B98C calls; true extent 216 B (was recorded 214).
- **GfxSetup_08049560** (0x08049560): graphics setup calling Gfx_BlitRequest (9×), GatedDispatch (3×), F_080247C4 — prime recomp graphics-pipeline candidate; true extent 328 B (incl 48 B pool).
- **sub_08002A1C** (0x08002A1C): 224 B incl mid-pool; calls CpuSet (0x0804DB28).
- 0x0803643c tail fully decoded: `(sp4<<24) != (r6<<24)` compare with r8 stash; r6 repurposed mid-function.

## Wave 30 (2026-10-24) — decomp → recomp feeds
- **Task_SelectBlobIdx_0803AC4C** (0x0803AC4C, 252 B): Text_SelectBlobIdx 0x66/0x67/0x68 dispatch on EWRAM 0x02002F50 bit-tests (bits 32/16/1/2), sibling of Task_38AD4; writes *(u16*)(0x2004CE0+40/42) display params. Stable text-select symbol for recomp.
- **WalkBits_0803643C** (0x0803643C, 444 B): bit-walker over ROM table 0x0822EED8 with (sp4<<24)!=(r6<<24) u32 tail compare; calls SelBlob_Ret(0x66). asm transcription (C-unreachable allocation).
- **SpriteTileUpload_080046B0** (0x080046B0, 244 B): walks sprite-node linked list at *(u32**)0x02003250[129]; for nodes with f6 & 0x8000, DMA-uploads 8×8 tile graphics to a VRAM page selected by (*(u16*)0x020031E4 & 12) via CpuFastSet or manual ldm/stm with v<<2 pixel scaling. Prime recomp graphics-pipeline candidate (the sprite tile-upload primitive).
- **ChipFxTick_0801C428** (0x0801C428, 280 B): chip FX state machine; calls SetBit16/MaxAssign_17 (0x080174A4/0x08017478 copies) and ChipInit_0801B98C. Stable symbol for recomp chip-FX work.
- Compiler insight for the recomp's build: gcc's thumb_reorg/find_barrier() dumps the constant pool at the first BARRIER after the first constant load — predicts ROM mid-pool + end-pool layouts; useful when hand-placing pools in recomp asm shims.

## Wave 31 (2026-10-24)
- ChipFxTick2_0801E77C: chip-FX state machine (p[14] states 0-3, 60-tick timer at p+120, per-type table 0x020051C8 + p[16]*12), sibling of ChipFxTick_0801C428 — useful for the recomp's FX emulation mapping.
- TileList_Upload_080096BC (BLOCKED, 272 B): tile-list-to-VRAM upload — dual 32 B Memcpy16 blits via tables 0x081720B4/0x081720CC, `(t&0xE00)==0x200` skip, `(t&0x8000)` break — prime recomp graphics-pipeline candidate once transcribed.
- CondRectFill family (8 wrappers): flag-gated wrappers around RectFill_7134/FillRect_65BC/FillRect_6374/TilemapRectFill_6AD8 — the game's conditional tilemap-fill API surface.
- Init_08000CA8: writes 0x030023C8 region + 0x02000800 + byte-stores at 24-byte stride — early-init memory setup, relevant to recomp boot-state emulation.

## Wave 32 (2026-10-24) — +4 matched (823/1674)

New stable named symbols for the recomp's Path B:
- **TileList_Upload_080096BC** (272 B): uploads a u16 tile list to VRAM at 0x06010000 + ((base+(y<<5)+x)<<5); per tile `t&0x8000` = break, `(t&0xE00)!=0x200` → two 32 B Memcpy16 blits (src from table at 0x081720CC, dst vram and vram+0x400); tail = default tile from *(u16**)0x081720B4. Registers: r8=seq, r9=(s8)n bound, sl=(u8)n, r5=vram cursor, r6=list cursor, r7=s16 i.
- **TblPairSwap_080249B8** (120 B): two-index pair check + swap-and-update dispatch; sibling of F_0802493C. `if (a>29||b>29) return 1; q=*(p+20)+(*(u8*)(*(p+20)+432))*144; if (CheckPair_258D8(q,a)||CheckPair_258D8(q,b)) Tbl_SwapAndUpdate_080259A4(q,a,b); return 0.`
- **Lookup_02D574** (52 B): branch-chain lookup (2→4, 3→1, 4→3, 1→2, else 255).
- **ChipDispatch_08024A30** (268 B): 3-param chip dispatch via 7 matched callees (CheckPair_258D8, F_0802493C, GetBoundedByte_08025478, DecByte_080254b4, SetSlot_IfLE29, GetStride4Byte20, Sub_254E0); `q = base + byte*144` recomputed 4×; returns 0/1/5.

Idiom note: pool-const pin must initialize at declaration (`register u32 poolr __asm__("r1") = 0xFFFF0000u;`) — broke the W24-D r7/r8 catch-22 (c lands in r7 naturally). Pure-C alternative for HexFormat_08004998 staged (could drop its python patch).

## 2026-10-24 — Wave 33 (for recomp Path B)
- `PatternRowsBlit_08006FE8` (264 B): pattern-row blit to VRAM via GetPtr_08008610 + SetIfXZero — graphics pipeline primitive.
- `StateMachine_0800CD5C` (138 B): state machine on s[1] (init → NodeInitSwitch → compare/update masks).
- `DrawChipRects_08008B08` (176 B): 12-iteration loop calling RectFill_7134 (chip-rect renderer).
- `ChipInit_080221CC` (196 B): straight-line chip init (clears s+108, sets bits, ChipSlot_Setup/IncUse, BlendCopy).
- `Sram_VerifyCompare` now byte-identical in src/sram.c — the save driver's compare primitive is fully matched.
- `HexFormat_08004998` now pure C (no python patch) — cleaner reference for the text/hex formatting path.
- 9 tiny wrappers matched (bulk leaves-up).

## Wave 34 (2026-10-24)
- `BoundsCheck_08042A64` (100 B): bounds-check helper using EWRAM base 0x02007036 and table 0x0000ac11; s8 table lookups via ldrsb, two-phase (b,c) range validation. Twin at 0x080459F8.
- `sub_08007678` (176 B): branch on c!=0 selecting a u32 from table 0x08170e7c indexed via 0x08172074, then calls FillRect_6374 (rect-fill primitive) — graphics pipeline candidate.
- `sub_08035E5C` (84 B): p+0x4699 s8-indexed dispatch into table 0x0822EB6C, calls sub_0804DCD0.
- 51 bulk leaves-up matched (28–56 B): mostly worker-call wrappers, table lookups, bit manipulation. Func_list gaps found: 0x0800c5a4/0x0800cbdc are real 20 B functions missing from func_list.
- Idiom for recomp: old_agbcc (not main agbcc) is the correct compiler for ChipSlot_Tick-class code with heavy r7 usage — if recompiling similar code, expect r7-heavy register allocation.

## Wave 35 (2026-10-24) — ChipSlot_Tick closed; 9 blocked revisits; 24 bulk
- **ChipSlot_Tick @0x0800D9FC (324 B)** — the per-slot state-update tick, now fully matched (old_agbcc + H-first reorder patch). Recomp relevance: slot-tick semantics fully decoded across W34–W35 (regions D–J, pair/key handling, store1/store2).
- **Sub_0804C288 (68 B)** — tst-wall function now matched via .s patch; the inline-asm tst experiment proved gcc 2.95 cannot share the epilogue (no asm-goto) — patch-in-place is the mechanism for tst walls.
- **Rect-fill/bulk family growth:** 22 more bulk leaves-up (table lookups, flag dispatches, gated increments) + 2 func_list gaps (0x0800c5a4/0x0800cbdc, 20 B decrement-and-mask leaves).
- **New named symbols for the recomp:** Sub_0800B3F8/Sub_0800B420 (worker-call twins), Sub_08022E88, Sub_0802D488, Sub_0804B350, Sub_08027D18, Sub_080267C0, Sub_0804C780, Sub_0804C288, Sub_0804C820, Sub_0804990C, Sub_0801B630, plus 22 bulk symbols (see match_status.tsv wave 35 rows).
- **Caution carried forward:** verify pools from ROM bytes in little-endian (two LE misreads caught this wave: 0x0871c8a4, 0x03002440); trailing-pad false matches (verify sections exact, not short-window 0-diff); local .sets are safe to keep (W34 precedent) but .globl+.set temporaries must be removed when the real symbol lands (wave3_b.c ChipSlot_Tick stub).
- **Wave 36 reconciliation (2026-10-24):** +27 matched (1060/1677). New named symbols: Lookup_0800cb70, Wrap_0800ec7c, Step_08010d84, Check_08028970, Sub_0800B448, Sub_0800C878, Sub_0802366C, Sub_08017670, Sub_080256E0, Sub_080050F0, Sub_080129F8, Sub_0800288C, Sub_0800EDB0, Sub_080112CC, Sub_08007798, Sub_0801DD48, Sub_08021C2C, Sub_08024C40, Sub_0804AFD0, Sub_0804380C, plus 7 restored Step/Check/Lookup symbols. 0x08030ad4 pinned as a 12,276 B dispatcher (needs its own project, not a single-wave attempt). Gap candidates for the recomp's function map: 0x08007f24 (24 B bit-4 setter), 0x0801e970 (32 B).

## Wave 37 (2026-10-24) — Worker C bulk + extent corrections; C2 running
- **Sub_0804CB28 (164 B)** — HW register setup on u32 keys: table lookup at 0x08105e3c, SDiv chain (1584/p16, 0x91d1b*p16+5000/10000, 0x1000000/v), writes to 0x04000102/0x04000100, spin on 0x04000006 ==159 then !=159. Recomp relevance: the sound/HW init sequence is now byte-decoded (SDiv_0804DD08 is the shared divider primitive).
- **Sub_0804CBCC (152 B)** — magic-guarded key-mask handler (magic 0x68736d53 bump/restore, bit tests, strided clear, 0xB00000 P update); pairs with 4CB28 as the HW key path.
- **Move-task family growth:** Sub_080185A8/0x08018474/0x0801986c (init tasks, ChipSlot_Setup 542/544), Sub_080192DC/0x08018510/0x0801A220/0x0801AC58/0x0801AD60/0x08017DC4/0x0801A344 (move-task steps, ChipInit 67/68/84/93/102/119) — the 1ac58-family dispatch/mode semantics are now well mapped for the recomp's task model.
- **Jump-table state machines:** Sub_0804713C (B148/B2D8/B320/B308/B2B4/B2F0) and Sub_08021144 (4713c family, 5-entry table) — dispatch patterns the recomp can mirror.
- **Extent corrections for the recomp's function map:** 0x0801757c is 132 B (not 164) with an unregistered 32 B function at 0x08017600; 0x080231d0 is 148 B (not 168) with an unregistered 20 B function at 0x08023264. Both gaps assigned to Worker C2.
- **New named symbols for the recomp:** Sub_08042D80, Sub_08016C94, Sub_080185A8, Sub_080192DC, Sub_08018510, Sub_0801986C, Sub_08038488, Sub_0804CBCC, Sub_08005434, Sub_08009EDC, Sub_08018474, Sub_0801A220, Sub_0801AC58, Sub_0802D5D4, Sub_0804713C, Sub_0801AD60, Sub_0801757C, Sub_0801EC44, Sub_0804CB28, Sub_08017DC4, Sub_0801E028, Sub_08021144, Sub_080231D0, Sub_0801A344 (see match_status.tsv wave 37 rows).

## Wave 37 C2 (2026-10-24) — 12 more bulk; move-task family nearly complete
- **Move-task family (1ac58):** Sub_0801969C/0x080197BC (twin), Sub_08017ED8/0x08018640/0x08019400 (twins), Sub_08019AAC/0x08019BDC/0x08019E7C/0x0801A5F0 — the ChipInit/TestBit16/GetField17 dispatch family is now mapped across ~20 members, a reusable template for the recomp's task-step code.
- **Sub_08042E14 (172 B)** — blit-request sequence (Gfx_BlitRequest + CondTilemapRectFill) with inline-asm ldrsb per call (agbcc never emits ldrsb from C — the recomp's blit paths need the same treatment).
- **Sub_08017984 (160 B) + Sub_08017A24 (32 B gap leaf)** — task step + leaf; the TSV 192 B window wrongly merged them, another extent-correction lesson for the recomp's function map.
- **New named symbols for the recomp:** Sub_08042E14, Sub_0801969C, Sub_080197BC, Sub_08017ED8, Sub_08018640, Sub_08019400, Sub_08019AAC, Sub_08019BDC, Sub_08019E7C, Sub_0801A5F0, Sub_08017984, Sub_08017A24 (see match_status.tsv wave 37 rows).
- **New idioms for the recomp:** barrier-forced pool-first load; address-in-register pin + index-first addition (adds r0,r0,r1 vs adds r0,r1,r0); split address-computation from deref (store-before-deref order); shared IncUse block via r1-pinned arg; stepwise-orr; ip (r12) for s is a compiler-version idiom — do NOT pin to r12 in Thumb (bloats code), treat ip-functions as patch/transcription candidates.
- **F_08030AD4 giant dispatcher (12,276 B, Wave 38)** — the game's central dispatch table (255-entry jump table, 94 distinct handlers, 162 → default latch) is now fully mapped and byte-matched; prime recomp target for the dispatch/VM layer. Shared epilogue at 0x08033ab2 (bx r1); trailing pool word 0x02005168.
- **Gap leaves 0x08017600 (32 B) + 0x08023264 (20 B)** — small struct-field helpers; the function map keeps growing in the gaps between TSV windows (check neighbors before trusting TSV sizes).
- **Wave 38 idiom correction for the recomp:** agbcc DOES emit ldrsb from C in some patterns (3 of 4 gates in 0x080234c8) — the "never emits ldrsb" rule is narrowed, not absolute. nm-hygiene rule: only UPPERCASE (A/T) symbols are linkable globals; lowercase 'a'/'t' are locals that do not resolve cross-object references.
- **Wave 38-B transcriptions (0x0800adc8/0x080361e8/0x0800c268)** — a state machine, a global-struct state machine, and a 5-level fixed-point affine/tile fill, all byte-matched; the affine fill's loop-nest decode (X/Z/Y/W/U levels, SDiv at every Z tail check) is directly reusable for the recomp's graphics code.

## Wave 38-A (2026-10-24) — 14 bulk matches; SetMirrored/1823c families mapped
- **SetMirrored family (6 members):** Sub_08012F4C/0x08013528/0x080139FC (216 B) + Sub_08013AD4/0x08014078 (220 B) + Sub_0801572C (236 B, goto-dispatch twin) — chip-state setters built on Vec2_SetMirrored + SetBit16 + Check119_Minus3_Le1 + GetField17_U8 + ChipSlot_IncUse; the goto skeleton transfers across all 6 (the recomp's chip-state code has a reusable template).
- **1823c family (4 members):** Sub_0801823C (212 B) + Sub_08018FB8 (216 B, int return) + Sub_0801A484 (228 B, unsigned nibble) + Sub_0801B728 (244 B) — task-step functions around Vec2_AddMirrored/CopyMirrored + ChipInit + IncUse; the pinned-r3 + barrier idiom for dead out[1] loads recurs.
- **17a94 family (2 members):** Sub_08017A94 (216 B, init-task 18474 family, trailing .hword 0 pad) + Sub_0802106C (216 B variant, NO file-scope pad — pool .align supplies it) — init-task Setup-arg-via-inline-asm pattern.
- **Caller-side pointer idiom (confirmed):** SetBit16's real callee takes a POINTER (s[16] |= 1<<bit), but bulk callers load the pointer FROM s+44 (ldr) rather than passing s+44 itself (adds) — i.e. the struct field at +44 IS a pointer to the bitfield struct. Same VALUE-from-s[44] pattern for ChipInit/GetField/1aa70/1cd50/Dec 5th/6th args. The recomp's struct model should treat s+44 as a pointer field, not an inline sub-struct.
- **Unlisted gap callees flagged for the function map:** 0x0801aa70, 0x0801cd50, 0x0801ebf0, 0x08017a44, 0x0801b98c, 0x080111b4, 0x0804db28, 0x08017b6c, 0x0802129c (0x080110e0 already MATCHED) — called by bulk functions but absent from the func list; the map still has gaps.
- **Build lesson for the recomp track:** full rebuilds must use serial make (make -j1) — parallel make dropped targets after make clean in this wave.
