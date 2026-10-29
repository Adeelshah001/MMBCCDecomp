# Wave 30-B Notes: 0x0803643c (WalkBits_0803643C) — Worker B

## Target
0x0803643c, true extent 444 B (0x0803643c–0x080365f8), trailing pool 0x0200BCE8 @ 0x080365f4.

## Result
**DECISION: Sanctioned asm transcription (dis2asm2.py).**
- 8 serious C variants attempted, best at 351 diffs; allocation wall holds.
- Transcription verified: **444 B, 0 diffs, byte-match** (clean-room: cpp → agbcc → as → ld at 0x0803643c → objcopy → cmp vs baserom extract).
- Staged: `staging/wave30_B/w30b_0803643c.c` (section `.text.w30b_0803643c_asm`).
- DO-NOT-LAND: coordinator lands after independent verification.
- Registry: 0x0803643c remains BLOCKED (revisit) — transcription staged, not landed.

## C Variants Attempted (all documented)

| Variant | Size | Diffs | Hypothesis | Outcome |
|---------|------|-------|------------|---------|
| v15 (w29a baseline) | 444 | 399 | Starting point (2× mov r8,r8 NOPs + patch) | Allocation diverges throughout |
| b1 | 440 | 374 | Prologue restructure: av→r6 pin, a24→r8 assigned late, decl order mirrors ROM | Prologue largely matches; best structural base |
| b2 | 460 | 356 | Heavy early pins (b3t→r3, a24t→r2, sh→r5, b3→ip) | Pin bloat (sub sp,#12), r9v→sl spill |
| b3 | 440 | 388 | b1 + explicit frame (sv/sp4 swap) + b3t late-park | Allocator thrash, worse |
| b4 | 416 | 376 | Block-scoped pins (tbl→r6, cnt→r5, sa→r7) | Pins honored but global coloring shifted |
| b5 | 420 | 352 | **Control-flow fixes** (sect2→slinc, inner2 fall-through) + section reorder | Best C; exposed r7 pin conflict (miscompile) |
| b6 | 432 | 351 | b5 + r3var→r3 pin | Pin thrash, [sp,#8] spill |
| b7 | 440 | 365 | Byte-access idiom (`((u8*)&a24)[3]`) for mov+shift pattern | a24 forced to stack, disaster |

## Key Findings

### Control-flow corrections (b5)
Two bugs in all prior C versions vs ROM:
1. sect2 `(r4&0xC0)==0` → **slinc** (ROM 0x36538 `beq 0x365a0`), not done2.
2. inner2 fall-through → **slinc** (ROM falls through to 0x365a0), not done2.
Also: section entry order is r4-check → tbl reload → sa recompute → r2=r3 → cnt=0 → off=0 (ROM 0x364ca-0x364d4).

### The allocation wall
~15 interdependent register decisions. Light pins (b1/b5) achieve good structure but wrong temp choices. Heavy pins (b2/b4/b6) cause cascading/thrashing: spills (`sub sp,#12`), variables pushed to sl/ip, [sp,#8] spills. Each fix regresses another area (whack-a-mole). Stuck at ~350 diffs across 8 variants.

Specific unreachable patterns:
- ROM `mov r1,r8; asrs r7,r1,#24` (sa recompute) vs gcc's folded `asrs r7,r8,#24`.
- tbl in r6 at section entries but r2 at initial load.
- r6 repurposing (av→tbl→(u8)r2), r5 repurposing (sh→cnt).
- b3 parked to ip LATE (after test computation), not at load.

### New idioms
1. **Block-scoped low-reg pins are honored** (b4): `register u8 *tbl __asm__("r6")` in a block gives `ldr r6,[pc]`. But they perturb global coloring unpredictably.
2. **Pin pressure threshold**: >3 pins causes spill cascade (b2: sub sp,#12; b6: [sp,#8] spill).
3. **Byte-access on pinned regs forces stack**: `((u8*)&a24)[3]` with a24 pinned r8 spills a24 to stack (b7).
4. **Conflicting pins miscompile silently**: r3var (plain, allocated r7) + sa7 (pinned r7) — gcc merged them, wrong semantics (b5).

## Transcription Verification
- Tool: `staging/wave30_B/dis2asm2.py` (copy of wave28_D version).
- Preprocessing needed: objdump bare-hex targets → 0x-prefixed; strip `<symbol>` suffixes; `cdp` pool pseudo-insns → `.word 0x0822eed8`.
- Build: `cpp -I mmbcc/include w30b_0803643c.c` → `agbcc -O2 -mthumb-interwork` → `as -mthumb -mcpu=arm7tdmi` → `ld -T` at 0x0803643c → `objcopy -O binary -j .text.w30b_0803643c_asm`.
- Result: 444 B, `cmp` vs baserom extract (file offset 0x3643c): **0 diffs**.
- External symbol: `SelBlob_Ret = 0x0800303c` (via `.set`; `bl` PC-relative offset correct at link address).
- Pools preserved: 0x0200BCE8 (×3), 0x0822EED8 (×2), `movs r0,r0` pads (×2).

## Files Staged (staging/wave30_B/)
- `w30b_0803643c.c` — **sanctioned transcription, VERIFIED 0-diff** (section `.text.w30b_0803643c_asm`)
- `v30b_b1.c` … `v30b_b7.c` — C variant intermediates (b5 best at 352 diffs)
- `v29a_v15.c` — w29a baseline (copied)
- `func_0803643c.bin` — ROM extract reference (444 B)
- `build.sh` — build+diff harness (compile → patch → as → ld → cmp)
- `w27b_0803643c_patch.py` — u16 0x10000 site patch (copied from wave27_B)
- `dis2asm2.py`, `func_dis_0x.txt` — transcription tooling
- `_f.bin` — verified 444 B build output (0 diffs)

## Registry
Checked docs/match_status.tsv: 0x0803643c is BLOCKED (revisit). No duplicate claim. No registry update (transcription staged, not landed — coordinator decides).

## Recommendation to Coordinator
Land `staging/wave30_B/w30b_0803643c.c` as `mmbcc/src/w30b_0803643c.c` (or per naming convention) after independent verification. The C wall is proven across 8 variants; transcription is the sanctioned path per precedents (w27a_08006ad8, w28a_080224e4, w28c_0801f254). Function behavior: walks 4-byte-entry table at 0x0822EED8 from index `a`, tests bits of `g_0200bce8[3]`; sets bit 0x40 of `g_0200bce8[4]` when found index differs from saved byte; calls `SelBlob_Ret(0x66)` if `c != 0`; returns final index or 0xFF. Name: `WalkBits_0803643C` (from behavior).
