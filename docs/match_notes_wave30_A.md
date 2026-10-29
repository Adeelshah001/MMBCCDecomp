# Wave 30-A Match Notes (Worker A, 2026-10-24)

Worker A, target 0x0803AC4C. Staging: `staging/wave30_A/` (C sources, verify.sh harness with PYFIX support, fix_0803ac4c.py).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: 0x0803ac4c NOT in docs/match_status.tsv (no existing claim; was BLOCKED per wave-29 notes, now revisited).

## MATCHED (staged, DO-NOT-LAND — coordinator lands)

### 0x0803AC4C — Task_SelectBlobIdx_0803AC4C (252 B) — 0 diffs

**Build recipe:** old_agbcc + PYFIX post-processing (`staging/wave30_A/fix_0803ac4c.py`).
**Staged:** `staging/wave30_A/w30a_0803ac4c_matched.c` (C), `staging/wave30_A/fix_0803ac4c.py` (asm post-processor).
**Verification:** clean-room rebuild → link at 0x0803AC4C → objcopy → cmp vs baserom: **0 diffs over 252 B**, reproducible across clean rebuilds.

**Why old_agbcc:** Its register allocator matches ROM's choices where main agbcc does not:
- B32: `ldr r5` (0x469b) + `adds r1,r4,r5` (main: r1/r0)
- B16: `adds r1,r4,r7` / `adds r0,r4,r7` + `subs r0,r1,r0` (main: r0/r1 swapped)
- B16 `t` → r5, matching ROM

**C structure (from wave-29 v4, refined):**
- B32: `a = p[0x469b]` (immediate) + `register u32 o2 __asm__("r7") = 0x4698` (pinned) for pb. The r7 pin defeats old_agbcc's `subs r5,#3` CSE-fold (0x4698 = 0x469b-3), forcing a separate `ldr r7` pool load.
- B16: `register u32 off __asm__("r7")` (pinned) → `ldr r7; adds r1,r4,r7; subs r7,#3; adds r0,r4,r7`, ROM-exact.
- Tail: clobber-only `__asm__ volatile("" ::: "r2")` between g[20]/g[21] kills old_agbcc's `subs r2,#2` fold (0x4698 = 0x469a-2), forcing a separate `ldr` pool load. (Clobber-only, no inputs → does NOT recolor p, unlike volatile-input asms.)
- Anti-merge barrier `__asm__ volatile("")` (wave-29) preserved.

**Post-processing (fix_0803ac4c.py):** Python script rewriting the .s before assembling. All changes are semantically neutral (register renaming + callee-saved save/restore):
1. `push {r4,r5,r6,lr}` → `push {r4,r5,r6,r7,lr}`; `pop {r4,r5,r6}` → `pop {r4,r5,r6,r7}`. The r7 pins mark r7 "fixed" so gcc uses it without saving; the original compiler saved it. Function has no stack frame, so this is a no-op semantically. REQUIRED for ABI correctness (r7 is callee-saved).
2. B32 o1: `ldr r0,=0x469b` + `add r1,r4,r0` → `ldr r5` + `add r1,r4,r5`. (old_agbcc picks r0; ROM uses r5. r5 is free — pushed and not yet used.)
3. B16 q: `ldr r2,=0x469a` + `add r3,r4,r2` → `ldr r0` + `add r3,r4,r0`. (The B32 o2 pin perturbs global allocation, shifting q from r0 to r2.)
4. Tail oB: `ldr r2,=0x4698` + `add r0,r4,r2` → `ldr r5` + `add r0,r4,r5`. (r5 is free — `t` is dead after B16.)

The script matches on pool VALUES (0x469b/0x469a/0x4698) + following-instruction context, not line numbers or labels, so it's robust to minor C changes.

**New idioms discovered:**
1. **Pin + post-process for fixed regs:** When a register pin (e.g., r7) is required for allocation but prevents gcc from emitting save/restore, post-process the .s to add the register to push/pop. Semantically safe iff the function has no stack-frame dependency on the push width (verify: no sp-relative addressing).
2. **Clobber-only asm (no inputs) is allocation-safe:** `__asm__ volatile("" ::: "r2")` kills a register's value (defeating CSE folds) WITHOUT the global recoloring caused by volatile-input asms. Use this instead of `"+r"` taints when possible.
3. **Volatile-input asms recolor p:** Any `__asm__ volatile("" : "+r"(x))` or `("" : : "r"(x) : ...)` causes old_agbcc (and main) to move `p` from r4 to r5 (callee-saved preference across compiler barriers). Avoid; use pins or clobber-only asms instead.
4. **r5 pin is poison (old_agbcc):** `register u32 x __asm__("r5")` is ignored/buggy — the allocator puts the pinned variable in r0 and bumps `p` to r5. Never pin r5. (r7 pins work; r1/r2/r5/r6 block-scoped pins were previously reported safe, but r5 is NOT safe in old_agbcc.)
5. **Pin perturbation:** A pin in an early block (B32 o2→r7) can shift register choices in later blocks (B16 q: r0→r2; tail: fold→ldr r2). When this happens, fix the later blocks via post-processing rather than fighting the allocator.

**Behavioral name:** `Task_SelectBlobIdx_0803AC4C` — dispatches Text_SelectBlobIdx(0x66/0x67/0x68) based on EWRAM 0x02002F50 bit-tests, managing a blob-index counter at p[0x469a] via table 0x08231790, with EWRAM 0x02004CE0 setup. Sibling of Task_38AD4 (0x08038AD4).

## For the coordinator (landing)

To land this, the project Makefile needs:
- A per-file rule compiling `src/w30a_0803ac4c.c` (or renamed) with **old_agbcc** (precedent: w23a_08002e80.c uses OLDAGBCC).
- A post-processing step applying `fix_0803ac4c.py` (or equivalent sed) to the .s before assembling. Precedent: "main agbcc + custom pool sed" for BuildList_08021D10; "gcc loop-hoist fixed by sed".
- ldscript slot at 0x0803AC4C (252 B / 0xFC).

The .s rewriting is deterministic and verified. The C + script produce byte-identical output to the baserom.

## Tooling issues
- **binutils PATH outage:** `/usr/bin/arm-none-eabi-*` vanished mid-session; reinstalled via `sudo dpkg -i ~/workspace/mmbcc-decomp/tools/host/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb` (worked first try).
- I accidentally broke `staging/wave29_D/verify.sh` line 18 with a stray sed early in the session; restored it to the original (`cpp -I $PRJ/mmbcc/include $D/$C -o $D/_v.i`). Verified the file is back to original via grep.

## Summary for coordinator
- **MATCHED (staged):** 0x0803AC4C (252 B, 0 diffs) — old_agbcc + Python asm post-processing. Staged at `staging/wave30_A/w30a_0803ac4c_matched.c` + `staging/wave30_A/fix_0803ac4c.py`. DO-NOT-LAND: needs coordinator review and Makefile integration (old_agbcc rule + post-processing step).
- **Progress:** 1/1 targets matched. Wave-29's 18-diff BLOCKED is now closed.
