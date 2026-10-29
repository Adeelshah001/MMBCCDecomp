# Function list v1 — methodology

**Artifact:** `func_list_v1.txt` (1612 rows: file offset, tier, mode)
**Generator:** `gen_func_list_v1.py` (documents the exact filters)
**Date:** 2026-10-20 · **Status:** bootstrap only — Phase 1 proper
(recursive descent from entry) will promote/demote entries.

## Method

1. **Prologue scan** over code region `0x000000–0x04FFFF`:
   - Thumb: halfword `0xB500–0xB5FF` with LR or r4+ in the register list
     (`(h & 0xFF00) == 0xB500 && (h & 0x5100)`).
   - ARM: `stmdb sp!, {...}` with LR or r4+ (`(w & 0xFFFF0000) == 0xE92D0000`).
   - Result: 1399 Thumb + 3 ARM candidates (includes literal-pool noise —
     pools live inline in the code region).
2. **BL-target harvest** (ARMv4T encodings — the original Thumb BL has no
   J1/J2 bits; an early version of this script wrongly used the Thumb-2
   decode and found 0 targets):
   - Thumb `BL`: `0xF000–0xF7FF` / `0xF800–0xFFFF` halfword pairs,
     offset = sign24(imm10:imm11:0), target = PC+4+offset.
   - ARM `BL`: `0xEBxxxxxx`.
   - Result: 733 targets inside the code region.
3. **Tiering:**
   - **A (726, strong):** bl-validated push prologues (515) + 5 known
     entries (crt0/IRQ/Thumb entry) + 206 bl-targeted non-push functions
     (leaf functions like `ldr;strb;bx lr`, `sub sp,#imm` prologues such
     as init fn #1 @0x63C) that forward-disassemble to a return.
     Caveat: a handful of A entries may be mid-function false targets
     from pool words that decode as BL — recursive descent will resolve.
   - **B (392, medium):** push candidates never BL-targeted but
     forward-coherent (reach `bx lr` / `pop {..,pc}` without hitting
     Thumb-2-only or coprocessor encodings).
   - **C (494, weak):** remaining push candidates — likely mostly
     literal-pool false positives, plus some real unreferenced functions
     (callbacks, table-driven init).

## Cross-check

An independent agent using prologue-signature + ARMv4T-validated
disassembly counted **~966** functions. Our probable-real count
(A+B = **1118**) brackets it; both methods agree the true total is
**~950–1100**, i.e. ~15× smaller than the recomp track's 14,102
(recursive descent into data regions).

## Working total for planning

**~1000 functions** (range 966–1118). Phase 1 proper (recursive descent
from `0x080000C0`, following all branches, classifying pools) will fix
the exact number.
