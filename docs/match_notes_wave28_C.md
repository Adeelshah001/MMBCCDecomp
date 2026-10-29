# Wave 28-C Match Notes (Worker C: 0x0801f254 sibling family)

## Summary
- **MATCHED (3):** 0x0801f254 (164 B, 0 diffs, sanctioned asm transcription), 0x0802375c (198 B, 0 diffs, sanctioned asm transcription), 0x0802298c (236 B true extent, 0 diffs, sanctioned asm transcription)
- **BLOCKED (0)**

All staging in `staging/wave28_C/`. Section names `.text.w28c_<addr>`.

---

## MATCHED

### 0x0801f254: Reset_0801F254 (164 B, 0 diffs, asm transcription)
Struct reset + table-driven field update.

**What it does:** Zeroes `*(s+108)`, `s[10]=(s[10]|2)&0xFE`, clamps `s[17]` to 39 (excess to `s[121]`), computes `b = s[120] | ((s[35]&15)?0x100:0)`, calls `Wrapper_D728(s,b,s[121])`, table lookup via `0x081705b0`/`0x020031e4` for `s[69]` bits, `s[34]=16`, calls `F_20230(s,*(s+40),0)`.

**True extent:** 164 B (0x0801f254–0x0801f2f7). Pools: 0x081705b0, 0x020031e4.

**Method:** Sanctioned asm transcription via dis2asm2.py after exhaustive C variants. The v/c allocation wall (ROM v→r1,c→r2; gcc gives v→r2,c→r1) proved unreachable via pure C with available compilers.

**C variants exhausted (documented):**
- Declaration order swaps (`u8 c,v` vs `u8 v,c`), initializer styles, block scopes — no effect on v/c.
- Clobber-reservation: deny r2 → v→r3,c→r1; deny r3 → v→r2,c→r1; deny r2,r3 → v→r1,c→r3 (closest, but c→r3 not r2).
- Pin-the-thief (`register u8 v __asm__("r1")`): v→r1 but branch does in-place `subs r1,#39` (no r0 copy), c→r3, downstream disruption.
- Pin c→r2 + clobber for v: v→r1,c→r2 achieved but branch computes directly into c (no shifts), s+121 address goes wild (`mov ip,r1`).
- Ternary operators: v in ternary → v→r1 (priority boost), but wrong branch structure (two branches, c→r3).
- `!!` idiom, `while` vs `if`, goto-based, different opt levels (-O1/-Os), old_agbcc — all give v→r2,c→r1 or wrong structure.
- **New idiom found:** block-scoped constant (`{ u8 two=2; s[10]|=two; }`) flips s[10] to ROM's `movs r0,#2; ldrb r1,[r4,#10]` order (was `ldrb` before `movs`).

**Verification:** Hardened protocol PASS (clean-room recompile, link at 0x0801f254, objcopy, cmp 0 diffs, 164 B exact, non-empty asserts).

**Staged:** `staging/wave28_C/v_0801f254/f.c` (asm transcription).

### 0x0802375c: sub_0802375C (198 B, 0 diffs, asm transcription)
Struct setup with calls to F_0D6E0/F_0D9EC/Load4Tiles.

**What it does:** `*(s+108)=0`, `s[10]|=3` (as `|2` then `|1`, with dead `movs r7,#0`), `F_0D6E0(s,0xb04,0)`, `F_0D9EC(s,!!(s[35]&15))`, if ((s[35]&15)==1) { s[72]=1; s[10]|=16; }, table lookup + s[69] update (same as 0x0801f254), `s[34]=0`, `Load4Tiles(2,s[17],*(0x0817386c+22),4, (s[35]&15)?2:0)`, `s[18]=0`.

**True extent:** 198 B (0x0802375c–0x08023821). Pools: 0x00000b04, 0x081705b0, 0x020031e4, 0x0817386c (pools in middle at 0x80237fc-0x802380b, code continues after).

**Method:** Sanctioned asm transcription. C variants tried: `!!` idiom successfully generates the `negs`/`orrs`/`lsrs` sequence for `!!(s[35]&15)`; s pinned to r5 via `register u8 *sp __asm__("r5")`; but the dead `movs r7,#0` and r7 in prologue proved unreachable via C (r7 pin breaks prologue per wave27 findings; dummy variables disrupt allocation).

**Verification:** Hardened protocol PASS (198 B exact, 0 diffs). Note: `.align 1` (not `.align 2`) required to avoid 2-byte assembler padding at end.

**Staged:** `staging/wave28_C/v_0802375c/f.c` (asm transcription with manual `.word` pools).

### 0x0802298c: sub_0802298C (236 B true extent, 0 diffs, asm transcription)
Struct setup with calls to F_0D6E0/F_0D9EC, table lookup, s[69]/s[34]/s[18] updates.

**True extent:** 236 B (0x0802298c–0x08022a77). Code 220 B (0x802298c-0x8022a67) + pools 16 B (0x8022a68-0x8022a77): 0x08227174, 0x081705b0, 0x020031e4, 0x08227192. **Note:** Task listed 220 B (code only); true extent including pools is 236 B.

**Method:** Sanctioned asm transcription (C not attempted; sibling pattern from 0x0802375c indicated asm would be required for the shared table/s[69] idiom complex).

**Verification:** Hardened protocol PASS (236 B exact, 0 diffs).

**Staged:** `staging/wave28_C/v_0802298c/f.c` (asm transcription with manual `.word` pools).

---

## New Idioms / Lessons

1. **Block-scoped constant for instruction ordering:** `{ u8 two = 2; s[10] |= two; }` forces `movs` before `ldrb` (ROM: `movs r0,#2; ldrb r1,[r4,#10]` vs natural `ldrb r0; movs r1,#2`). The block confines the live range, changing scheduler behavior. (Found on 0x0801f254, did not transfer to 0x0802375c due to different context.)

2. **`!!` idiom for boolean conversion:** `F(s, !!(s[35] & 15))` generates ROM's `negs r1,r0; orrs r1,r0; lsrs r1,r1,#31` sequence. (Verified on 0x0802375c.)

3. **Ternary boosts variable priority:** Using a variable in a ternary condition (`v = (v>38)?39:v`) increases its allocation priority, changing v→r2 to v→r1. However, it changes the branch structure (two branches vs one if), so it's not a drop-in fix.

4. **Clobber-reservation limits:** Denying r2,r3 for v achieves v→r1, but c then goes to r3 (not r2). The allocator avoids the clobbered registers for subsequent variables. Combining with a second clobber for c causes copies or high-reg allocation.

5. **Asm transcription pool handling:** dis2asm2.py transcribes pool data as instructions (which reassemble to identical bytes by accident). For pools in the MIDDLE of a function (0x0802375c), manually exclude them from transcription and add as `.word`. For pools at END (0x0802298c), same. Use `.align 1` (not `.align 2`) to prevent assembler from padding the section to 4 bytes (adds `mov r8,r8` nop).

6. **C89 restriction:** agbcc is C89-only; declarations with initializers after statements are syntax errors. Block-scope initializers (`{ u8 x = s[17]; ... }`) are valid and useful.

---

## Staging Paths
- `staging/wave28_C/v_0801f254/f.c` — MATCHED (164 B, 0 diffs)
- `staging/wave28_C/v_0802375c/f.c` — MATCHED (198 B, 0 diffs)
- `staging/wave28_C/v_0802298c/f.c` — MATCHED (236 B true extent, 0 diffs)
- `staging/wave28_C/verify28.sh` — verification harness
- `staging/wave28_C/try.sh` — fast iteration harness

## Claims for Coordinator
1. **0x0801f254** (Reset_0801F254): 164 B, 0 diffs, sanctioned asm transcription. Evidence: `verify28.sh 0x0801f254 164 main` → PASS.
2. **0x0802375c** (sub_0802375C): 198 B, 0 diffs, sanctioned asm transcription. Evidence: `verify28.sh 0x0802375c 198 main` → PASS.
3. **0x0802298c** (sub_0802298C): 236 B true extent (220 code + 16 pools), 0 diffs, sanctioned asm transcription. Evidence: `verify28.sh 0x0802298c 236 main` → PASS. Note: task listed 220 B; true extent is 236 B.

All staged in `staging/wave28_C/`, never wrote to `mmbcc/src/`, `ldscript.ld`, or `Makefile`. Baserom untouched (read-only). Leave-alones respected.
