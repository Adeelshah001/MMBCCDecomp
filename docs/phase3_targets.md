# MMBCCDecomp — Phase 3 priority target list

Date: 2026-10-20. Order for per-function matching-C iteration (PLAN.md
Phase 3). Rule: templated/SDK-like first (mechanical), then high-value
named targets, then bulk by call-graph leaves-up. A function counts as
MATCHED only when its agbcc-compiled bytes are byte-identical to the
baserom (diff-verified). Symbols from `docs/symbols_phase2.md`
(proposals); call counts from `docs/xrefs.tsv` (1703 starts).

## Wave 0 — already asm-verified (match C against known-good asm)

These 16 are byte-identical as asm; their C must reproduce the same
bytes. They calibrate the compiler flags.

| # | Address | Name | Why first |
|---|---|---|---|
| 1 | `0x0804DB24` | `CpuFastSet` | Templated `svc 0x0C; bx lr` — trivially matchable, validates flags |
| 2 | `0x0804DB28` | `CpuSet` | `svc 0x0B; bx lr` |
| 3 | `0x0804DB2C` | `LZ77UnCompVram` | `svc 0x12; bx lr` |
| 4 | `0x0804DB30` | `LZ77UnCompWram` | `svc 0x11; bx lr` |
| 5 | `0x0804DB34` | `RLUnCompVram` | `svc 0x15; bx lr` |
| 6–11 | `0x0804DB38`–`0x0804DC94` | `Sram_Memcpy`, `Sram_WaitcntInit`, `Sram_Read`, `Sram_VerifyCompare`, `Sram_VerifyWorker`, `Sram_RetryWrapper` | Small, self-contained, behaviorally understood |
| 12–16 | `0x080000C0`–`0x0800033C` | `Init`, `IntrWait`, `IrqDispatcher`, `ArmTrampoline`, `crt0_thumb_helpers` | Boot chain; mostly ARM asm — C-match where feasible |

## Wave 1 — high-value named targets (behaviorally mapped)

| # | Address | Name | Notes |
|---|---|---|---|
| 17 | `0x08000328` | `Task_Switch` | Coroutine primitive; tiny |
| 18 | `0x08000D90` | `Task_Register` | Task table `@0x030023C8` |
| 19 | `0x080004FC` | `MainLoop` | Frame driver; ~19-call dispatch — big but central |
| 20 | `0x08000AD4` | `HBlank_RasterSetup` | Raster engine arming |
| 21 | `0x08000B54/BAC/C04` | `HBlank_Raster0/1/01` | Near-twins; match one, clone |
| 22 | `0x08000C68` | `StridedCopy` | Small copy engine |
| 23 | `0x0804C6B4` | `Text_SelectBlob` | Text path entry |
| 24 | `0x0804CDE8` | `Text_OpenDialogue` | Blob parser (partially mapped) |
| 25 | `0x0804BB9C` | `ARM_SampleMulAccum` | Only non-crt0 ARM fn; true bounds `~0x4BB9C–0x4BD7C` need pinning first |
| 26 | `0x0800063C` | `HwInit_WaitCntDma` | WAITCNT/DMA3 init; small |

## Wave 2 — most-called utilities (shared code, match once, benefit many)

Top `bl` callees not yet covered above (from `xrefs.tsv`):

`sub_0800D9EC` (216), `sub_0804A378` (194), `sub_0802D7A0` (159),
`sub_08006A54` (151), `sub_0800D9FC` (121), `sub_0800D6E0` (95),
`sub_08004F18` (88), `sub_08004F80` (88), `sub_0804DCD0` (84),
`sub_0800DD2C` (84), `sub_0800DD08` (82), `sub_08006DD8` (77),
`sub_0800DD4C` (71). Identify each (likely memset/memcpy/division
helpers and hot game utilities) then match in caller-count order.

## Wave 3 — bulk (leaves-up)

Remaining B-tier in reverse-topological order (callees before
callers), using `xrefs.tsv`. Uncalled/table-only functions
(`UNCALLED`=756, `TABLE_ONLY`=557 in the build log) are callbacks and
leaf data-handlers — good mid-phase filler. The 26 v2.4 thunk-span
entries are probable alternate entries: match their host bodies first,
then decide per-entry.

## Explicitly deferred

- `02F5AC` (invalid decode — needs manual review), `030B18`
  (walker dispute), `04D088`/`04B992` (lean-real, unpromoted).
- Text codec (`BE 66 BC 00`) — Phase 4.
- Audio driver — stretch goal.
