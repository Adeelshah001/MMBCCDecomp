# Wave 33-B Match Notes (Worker B)

Worker B, 2026-10-24. Staging: `staging/wave33_B/` (C sources, asm transcription, verify.sh, didiff.sh).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check (2026-10-24): scanned ALL 1168 rows. 0x0800cd5c appears once (row 1163, BLOCKED w32). 0x08008b08 appears once (row 1162, BLOCKED w32). No MATCHED rows — safe to claim.

## Results

| Address | Size | Status |
|---------|------|--------|
| 0x0800cd5c | 138 B | ✅ MATCHED (C, 0 diffs) — `staging/wave33_B/w33b_0800cd5c_v6.c` |
| 0x08008b08 | 176 B | ✅ MATCHED (sanctioned asm transcription, 0 diffs) — `staging/wave33_B/w33b_08008b08_asm.c` |

**Result: 2/2 MATCHED.** Staged per DO-NOT-LAND (coordinator lands).

---

## 0x0800CD5C — StateMachine_0800CD5C (138 B, 0 diffs)

True extent: 0x0800cd5c–0x0800cde6 (next func at 0x0800cde6 starts `30 b5`).

**Semantics:** State machine on `s[1]`: case 0 = init (if `s[6]==0`: `s[1]=2`, `BitCtl_520C(1)`; else `s[1]=1`; `s[3]=0`); case 1 = `NodeInitSwitch_0800D1E0(s,s+3,s+4,s+5)`, if nonzero break else `s[1]=2`; case 2 = if `s[0]!=s[7]`: shift state (`s[6]=s[0]`, `s[0]=s[7]`, `s[3]=s[2]=s[1]=0`), then `*(u16*)0x020031e0 &= 0xedff; &= 0xdbff`; else `ret=0`. Default: `ret=1`.

**Variant history:**
- v3: Changed `NodeInitSwitch` return type to `u8` → got ROM's `lsls r0,r0,#24` in case 1 (+2 bytes). Tried block-scoped pins for base/mask — **pins to r0/r2 IGNORED** (see idiom 1). 4 diffs (and-sequence regalloc).
- v4: Nested block with pins initialized at declaration — still ignored. 4 diffs.
- v5: **Breakthrough** — replaced pins with `__asm__ volatile("" : "+r"(mask))` barrier between `mask` init and `v = *p`. This pins the *load order* (mask before value) and reg coloring (mask→r0, v→r1) without pins. And-sequence now byte-identical. 2 diffs (pool sign-extension).
- v6: Changed `u16 mask` to `u32 mask` → pool word 0x0000edff (was 0xffffedff). **0 diffs.**

**Walls solved:**
1. W31 fold wall (`0xedff & 0xdbff` → `0xc9ff`): solved by mask-first formulation (`m &= v` instead of `v &= m`) — no fold possible.
2. Scheduling wall (movs r0,#0 before strbs, ldr r2 after): solved in v2, preserved.
3. Case-1 `lsls`: solved by `u8` return type.
4. And-sequence regalloc (mask in r0 before value in r1): solved by barrier-pinned load order.
5. Pool sign-extension: solved by u32.

---

## 0x08008B08 — DrawChipRects_08008B08 (176 B, 0 diffs via transcription)

True extent: 0x08008b08–0x08008bb8 (ends `bx r0`; 176 B).

**Semantics:** 12-iteration loop (s16 i, 0–11). Each iteration: check `*(u8*)(0x02004830+0x265)`, return if set. `ctx = 0x02004830+24`. `x = *(u16*)(p+4+2*i)`. `y = tbl0[2*i+24*kind] + (s8)p[0]`, `z = tbl1[2*i+24*kind] + (s8)p[1]` (tbl0=0x08172020, tbl1=0x08172021). `w = (mask&1) ? 0 : 16`. Call `RectFill_7134(ctx, x, y, z, w)` (w stack-passed). `mask >>= 1`.

**ROM register map (decoded):** p→r9, kind→r10, mask→r8, ctx→r12, i→r3 (kept as i<<16 in body), flag→r6, x→r7, y→r2, z→r4, k→r1. Prologue saves r8/r9/r10 via r5/r6/r7 (top-down per gcc thumb.c).

**Variant history (C attempts):**
- v13: Hi-reg pins (p→r9, kind→"r10", mask→r8, ctx→"sl"). **DISCOVERED: agbcc "r10" and "sl" both map to reg 10 — collision!** kind ended up in reg10, ctx too. 167 diffs.
- v14: Fixed pins (kind→"sl"=r10, ctx→"ip"=r12). Pins honored. Prologue close but body regalloc off (i→r2, flag→r0, x→r5). 163 diffs.
- v15: Tried pinning i→r3, flag→r6, x→r7 with dummy memory inits — dummies not eliminated, bloat to 192B. 158 diffs.
- v16: Hi pins only, `w = (mask&1) ? flag : 16` to keep flag live. Body still off. 162 diffs.
- v17: Added `i2 = i<<1` CSE — didn't trigger in-place shift. 163 diffs.
- v18: **Pin activation breakthrough** — `__asm__ volatile("" : "=r"(i), "=r"(flag), "=r"(x))` activates pins. Got in-place shift (`lsl r0,r3,#16; asr r0,r0,#15`) and x→r7, flag→r6! But double-computation clobbered i. 160 diffs.
- v19: v18 + i2 — CSE worked but gcc put i2 in r3, destroying i. 163 diffs.
- v20: Minimal temps, w=flag — pins conflicted (w→r6 clobbered flag, k→r3 clobbered i). 162 diffs.

**Decision:** After 8 C variants (20 total incl. w32), allocator walls (in-place shift + i/r3, flag/r6, x/r7 simultaneous coloring) proved intractable. **Sanctioned asm transcription** via hand-crafted GAS block (dis2asm2-style), verified 0-diff.

**Transcription:** `staging/wave33_B/w33b_08008b08_asm.c` — full 176B function with mid-function pool (4 words at 0x8b78) as `.word` directives, branch labels, `bl RectFill_7134` via `.set`. Verified: clean-room recompile → link at 0x08008b08 → objcopy → cmp vs baserom at file offset 0x8b08, 176 bytes, **0 diffs**.

---

## New Idioms Discovered

1. **agbcc register name mapping (CRITICAL):** In agbcc's `REGISTER_NAMES`, reg 10 is named `"sl"`, reg 11 `"fp"`, reg 12 `"ip"`. The names `"r10"`, `"r11"`, `"r12"` are NOT primary — `__asm__("r10")` and `__asm__("sl")` BOTH map to reg 10 (collision!). For physical r12 (objdump's "r12"), use `__asm__("ip")`. For r10, use `__asm__("sl")`.
2. **Pin activation via empty asm:** `__asm__ volatile("" : "=r"(var));` activates a register pin that would otherwise be ignored. Emits zero code (just `.code 16` directive). Essential for pins with constant initializers.
3. **Pin initializer rule:** Pins with memory-load initializers (`= p[0]`) are honored; pins with constant (`= 0`) or arg (`= q`) initializers are IGNORED (unless activated via idiom 2).
4. **Barrier-pinned load order:** `__asm__ volatile("" : "+r"(mask));` between a constant initializer and its use forces the scheduler to keep the load before subsequent loads, and influences reg coloring (mask→r0). Used in cd5c v5 to get mask-before-value order without pins.
5. **u32 for pool constants:** A `u16` variable initialized to `0xedff` got its pool word sign-extended to `0xffffedff`. Declaring as `u32` keeps `0x0000edff`.
6. **Mask-first and-sequence:** `m &= v` (not `v &= m`) puts the mask in r0 and value in r1, matching ROM's `ands r0, r1` with mask loaded first.
7. **Prologue algorithm (from gcc thumb.c):** Hi-reg saves use top-down temp selection — `for (regno=7..0)` paired with hi regs `for (next_hi_reg=12..8)`. To get ROM's `mov r7,r10; mov r6,r9; mov r5,r8; push {r5,r6,r7}`, need live lo regs = {r4,r5,r6,r7} and live hi regs = {r8,r9,r10}.

## For Coordinator

- **Staging:** `staging/wave33_B/`:
  - `w33b_0800cd5c_v6.c` — MATCHED C source (138 B, 0 diffs). Section: `.text.w33b_0800cd5c_v6`.
  - `w33b_08008b08_asm.c` — MATCHED asm transcription (176 B, 0 diffs). Section: `.text.w33b_08008b08_asm`.
  - `verify.sh`, `didiff.sh` — harnesses (adapted from wave32_D).
  - Intermediate C attempts v13–v20 (BLOCKED, for reference).
- **Registry:** Both addresses appear once each as BLOCKED (rows 1162, 1163). Coordinator to append MATCHED rows (or REVERTED+BLOCKED→MATCHED per convention).
- **Landing notes:**
  - cd5c: Pure C, main agbcc, no python patch. `NodeInitSwitch_0800D1E0` prototype changed to `u8` return (for `lsls`); `BitCtl_520C` bl to 0x0800520c via `.set`.
  - 8b08: Asm transcription. `bl RectFill_7134` via `.set 0x08007134` (7134 currently BLOCKED; linker will resolve when matched). Mid-function pool included as `.word`.
- **Names:** StateMachine_0800CD5C, DrawChipRects_08008B08.

## Progress Bar

Wave 33-B: 2/2 targets matched (100%). Worker-B contribution: +2 matched (1 C, 1 asm-transcribed).
