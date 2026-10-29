# Wave 29-C Match Notes (Worker C)

Worker C, 2026-10-23. Staging: `staging/wave29_C/` (C sources, v29.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: 0x08002A1C NOT-IN-REGISTRY. 0x080046B0 NOT-IN-REGISTRY.
0x08049560 IN-REGISTRY as BLOCKED (revisit, not a new claim). No skips.

## MATCHED (2)

### 0x08049560 — GfxSetup_08049560 (328 B, 0 diffs) ✅

**Compiler: main agbcc.** Staged: `staging/wave29_C/c_08049560_v8.c`.

**True extent correction:** Wave 28 measured 280 B and reported "48 B bloat".
The ROM pool runs 0x8049678–0x80496A8 (12 entries = 48 B). True extent is
**328 B** (278 code + 2 pad + 48 pool), not 280. The "bloat" was the pool.
Verify with SIZE=328.

**Evidence:** `./v29.sh 0x08049560 328 .text.w29c_08049560 c_08049560_v8.c main
"F_080247C4=0x080247C4" "Gfx_BlitRequest=0x08006A54" "GatedDispatch=0x08006DD8"`
→ `sizes: o=1292 elf=2272 bin=328`, `rom extract: 328 bytes`, `diffs: 0`.
Re-ran → deterministic 0 diffs. Bl targets decoded from ROM: 9× 0x08006A54,
3× 0x08006DD8, 1× 0x080247C4 — match stubs.

**Key findings:**
- **Prologue via two volatile stores + real-copy asm:** `u16 zero = 0;` then
  `*(volatile u16 *)&local = zero;` gives `movs r1,#0; add r0,sp,#4; strh r1,[r0]`.
  Then `v = 0xFFFF8000;` + `__asm__ volatile("movs %0,%1" : "=r"(w) : "r"(v));`
  + `*(volatile u16 *)&local = w;` gives `ldr r0,[pc]; adds r1,r0,#0`
  (`movs r1,r0` assembles to 0x1C01 in divided syntax!); `add r0,sp,#4; strh r1,[r0]`.
  The `"=r"(w) : "r"(v)` with EMPTY template is a miscompile (gcc trusts the
  template to do the copy); must use a real template. GAS 2.42 rejects
  `adds r1,r0,#0` in divided syntax but accepts `movs r1,r0` → same bytes.
- **p2 pointer in r5:** `u16 *p2 = (u16 *)(p + (222 << 2));` then `*p2` dereferenced
  twice (not value-kept) → `adds r5,r6,r1` once, `ldrh r0,[r5]` / `ldrh r1,[r5]`
  reloads. Matches ROM's address-in-r5 pattern.
- **ew[20]/ew[21] indexed stores** kill the `adds r1,#2` merge; pool gets
  0x02004CE0 (not folded 0x02004D08).

### 0x08002A1C — sub_08002A1C (224 B, 0 diffs) ✅

**Compiler: old_agbcc** (decisive: main gives 200 B/104+ diffs; old gives 224 B).
Staged: `staging/wave29_C/c_08002a1c_v17.c`.

**True extent:** 224 B (0x08002A1C–0x08002AFC): code + 2 pad + 16 B mid-pool
(0x8002A8C: 0x02003090, 0x1FF, 0x03002420, 0x1FFFFF) + code + 2 pad + 12 B end pool
(0x8002AF0: 0x3FF, 0x03002420, 0x1FFFFF). Mid-pool placed after main path's `b.n`.

**Evidence:** `./v29.sh 0x08002A1C 224 .text.w29c_08002a1c c_08002a1c_v17.c old
"CpuSet=0x0804DB28"` → `sizes: o=1060 elf=3340 bin=224`, `diffs: 0`.
Deterministic. Bl target 0x0804DB28 decoded from ROM (2× in this function).

**Key findings:**
- **s16 scnt variable:** `s16 scnt = (s16)cnt;` gives in-place `lsls r3,r3,#16;
  asrs r3,r3,#16` in r3, reused for BOTH `muls r0,r3` AND `ands r2,r3` (mode).
  Using `cnt & 0x1FFFFF` directly folds (gcc knows u16 range); the signed
  scnt defeats folding.
- **ldrsb idiom:** `__asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]"
  : "=l"(sb) : "r"(e));` — must use `"=l"` (old_agbcc puts `"=r"` in sl!).
- **Pinned ip:** `register u32 *ip __asm__("ip")` gives `ldr r0,[r6,#8];
  mov ip,r0` then `add r0,ip`. Without pin, gcc avoids the spill.
- **Memory barrier for prologue order:** `__asm__ volatile("" ::: "memory")`
  between `e1 = ...` and `e2 = e1` prevents CSE merging (was computing e2 first).
- **`i[flag]` → `*(u8 *)(i + flag)`:** With flag as u32, `i + flag` gives
  `mov r0,r8; add r0,r9` (ROM order); `flag[i]` gives `mov r0,r9; add r0,r8`.
- **`(sb << 1) + tv` (int, not pointer):** gives `adds r1,r1,r0` (accumulate
  into sb's reg); pointer version gives `adds r0,r0,r1`.

## BLOCKED (attempted)

### 0x080046B0 — sub_080046B0 (244 B true extent, 232 B best)

Complex sprite-DMA linked-list walker. Best: `staging/wave29_C/c_080046b0_v8.c`
(main agbcc, 232 B, ~344 diff lines).

**Progress:**
- Prologue `ldr r0,[pc] (0x02003250); movs r1,#129; lsls r1,r1,#3; adds r0,r0,r1;
  ldr r5,[r0]` achieved via `Tbl8 *tbl` + `+r` barrier + `&tbl[129]` (defeats folding).
- node→r5 via `register Node *node __asm__("r5")` pin.
- do-while structure (not while) eliminates duplicate null check.

**Remaining walls:**
1. **r8v setup order:** ROM does `movs r2,#128; lsls r2,r2,#8; mov r8,r2` FIRST,
   then r7v/r9v. Mine does r7v/r9v first. Scheduler reorders; barrier didn't help.
   (6 bytes)
2. **12 bytes short:** Bin 232 vs 244. Likely in alt-path manual copy loops
   (ldm/stm generation) or pool layout differences.
3. **Structural:** 344 diff lines; vram_base (r6) allocation, bit-manipulation
   scheduling, and CpuFastSet arg setup all differ.

**Recommendation:** Needs a ground-up rewrite mirroring ROM's exact instruction
schedule, or sanctioned asm transcription after more C attempts.

## New idioms discovered

1. **True-extent remeasure:** Wave 28's "48 B bloat" on 0x08049560 was the pool.
   Always verify pool extent from ROM bytes before assuming bloat.
2. **Real-copy asm template:** `"=r"(w) : "r"(v)` with empty template is a
   MISCOMPILE (gcc trusts template). Use `"movs %0,%1"` for a 2-byte reg copy.
   In divided syntax, `movs r1,r0` assembles to 0x1C01 (`adds r1,r0,#0` bytes).
3. **Signed variable defeats AND-folding:** `s16 scnt = (s16)cnt;` then
   `scnt & 0x1FFFFF` emits real `ands`; `cnt & 0x1FFFFF` with u16 cnt folds.
4. **Memory barrier defeats CSE merging:** `__asm__ volatile("" ::: "memory")`
   between `e1 = ...; e2 = e1;` prevents gcc from computing e2 first.
5. **`i + flag` vs `flag + i`:** With u32 flag, `*(u8 *)(i + flag)` gives
   `mov r0,r8; add r0,r9`; `flag[i]` gives `mov r0,r9; add r0,r8`.
6. **Integer vs pointer addition:** `(sb << 1) + tv` (ints) gives
   `adds r1,r1,r0`; `(u8 *)tv + (sb << 1)` (pointer) gives `adds r0,r0,r1`.
7. **`"=l"` constraint for old_agbcc:** old_agbcc allocates `"=r"` asm outputs
   to high regs (sl); use `"=l"` for Thumb1-restricted instructions.

## Tooling
- `staging/wave29_C/v29.sh` — verify harness (adapted from wave28_D).
- `staging/wave29_C/c_08049560_v8.c` — MATCHED (0x08049560, main, 0 diffs).
- `staging/wave29_C/c_08002a1c_v17.c` — MATCHED (0x08002A1C, old, 0 diffs).
- `staging/wave29_C/c_080046b0_v8.c` — best blocked attempt (0x080046B0).
- `staging/wave29_C/final_08049560.{bin,s}`, `final_08002a1c.{bin,s}` — evidence.
- `staging/wave29_C/exp_prologue.c`, `c_08002a1c_v*.c` (v1-v17), `c_080046b0_v*.c`
  (v1-v9) — iteration history.

## Summary for coordinator
- **MATCHED:** 0x08049560 (GfxSetup_08049560, 328 B, main agbcc, 0 diffs).
  Staged at `staging/wave29_C/c_08049560_v8.c`. **Registry currently BLOCKED —
  needs update to MATCHED.**
- **MATCHED:** 0x08002A1C (sub_08002A1C, 224 B, old_agbcc, 0 diffs).
  Staged at `staging/wave29_C/c_08002a1c_v17.c`. **Not in registry — needs claim.**
- **BLOCKED:** 0x080046B0 (v8 best, 232/244 B, prologue order + 12 B shortfall).
- **Progress:** 2/3 targets matched.
