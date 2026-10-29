# Wave 8 Worker B (TAG=B) — Match Notes

Worker: Wave 8 blocked-revisits (TAG=B). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/agbcc` (main) / `old_agbcc` per brief build rule.
Harness: `/tmp/wave8_B/build.sh` (hardened v2: custom ld script to prevent
`.text.*` merging, non-empty assertions, file offset = addr - 0x08000000,
full section extent incl pools/pads).
Staging: `~/workspace/mmbcc-decomp/staging/wave8_B/` (C sources, one section
per function `.text.w8b_<addr>`). Results: `docs/wave8_B_results.tsv`.

## MATCHED (2)

### Tst_0800B2D8 @0x0800B2D8 (24B, old_agbcc, 0 diffs)
`if (((v & 143) == 128)) return 1; return 0;` where `v = gBase[4]`
(gBase = 0x02004E40 via `.set`). Compiler naturally emits ROM's
`ldr r1,[pc]` (pool->r1) + `ldrb r1,[r1,#4]` (reuse r1) + `ands r0,r1`.
No pinning or tricks needed. Verified: bin 24B, `cmp -l` 0 diffs.

### Tst_0800B2F0 @0x0800B2F0 (24B, old_agbcc, 0 diffs)
Sibling: `if (((v & 143) == 0)) return 1; return 0;`. Same idiom, 0 diffs.

## BLOCKED (with new angles tried)

### Obj_AddEntry @0x0802D7A0 (340B) — BLK-A key applied, regalloc diverges
**New angle:** Applied the BLK-A key (discovered after wave2): shared `int m3`
/ `int p3` masks across two sites each. Result: compiler emits the
`adds r0,rX,#0` copy at the FIRST use of each mask + full 32-bit `ands`
(dest r0), FIXING wave2's narrowing blocker (`u8 & ~2` → `& 253`).
**Remaining:** Register allocation diverges (300 diffs). ROM: mask in r3,
work in r7, a1->r6, a8->r8, a9->r9, prologue `sub sp,#24`. Mine: mask in r1,
work in r5, prologue `sub sp,#28` (a8 spilled). The structure (copy at first
use, 32-bit and) is correct; the allocator's choices differ. Tried pinning
(r6/r8/r9) — disrupts allocation further. Best C kept in staging.

### ObjInit_1D3C0 @0x0801D3C0 (164B) — 4 diffs (down from 81)
**New angles tried:**
1. `__asm__ volatile("" ::: "memory")` barrier between `s[10]|=1` and
   `*(s+108)=0` in if-branch: FIXES the str/strb reorder (now matches).
2. Early `int zero = 0` + two-step `p = s; p += 0x50; *(p+28) = zero` in
   else-branch: gives ROM's `movs r1,#0` hoist + `adds r0,#80` +
   `str r1,[r0,#28]` (not folded). Matches!
3. Shared `int m = -13` (BLK-A key) for s[0x41]/s[0x45]: gives
   `adds r0,r2,#0` copy at s[0x41] site. Matches!
4. Separate `u8 *p` / `u8 *q` vars prevent `adds r3,#4` reuse (ROM
   recomputes `s+0x45` from scratch).
**Remaining (4 diffs):** Else-branch prologue has `movs r1,#0` BEFORE
`movs r0,#1`; ROM has `movs r0,#1` BEFORE `movs r1,#0`. Pure scheduler
ordering heuristic; tried declaration reorder, lazy init, nested blocks —
scheduler insists on zero-first. True extent 164B (not 160; includes pool
at 0x801d460).

### Script_StepState @0x0803F480 (964B) — probe validates angle, full not attempted
**New angle probed:** Volatile-split index sum + split 0x464C as 0x4600+0x4C.
Probe result: compiler emits `adds r1,r2,r1` (sum in r1 ✓) and loads 0x464C
from pool (no `subs r1,#0x54` fold ✓). The angle WORKS for the index
computation blocker. Full 964B/24-case switch function not attempted (time).
**Note for future worker:** Use the probe pattern (`__asm__ volatile("" : "+r"(sum))`
after `sum = *b1 + sel`; `b2 = p + 0x4600; b2 += 0x4C;`) for the prologue.

### TableLookup_U16 @0x08011C58 (40B) — mask fusion persists
**New angle tried:** old_agbcc -O1 (33 diffs) vs -O2 (32 diffs); direct param
use (no u32 temps). Blocker persists: ROM does `lsls r0,r0,#24; lsrs r0,r0,#24`
then `adds r3,r0,#0` (copy to r3); compiler fuses to `lsrs r2,r0,#24` (direct
to r2). -O1 is not less aggressive for this fusion. The `adds r3,r0,#0` copy
needs the compiler to keep masked a0 in r0 while r0 is reused for a1 mask —
allocator won't do it.

### Check_0800B2B4 @0x0800B2B4 (36B) — fake-clobber doesn't fix dest
**New angle tried:** `__asm__ volatile("" : "+r"(v))` to keep r1 (base[4])
alive across both `ands`. Result: r1 IS kept alive, but compiler emits
`ands r1,r0` (dest r1) vs ROM `ands r0,r1` (dest r0). 3 diffs. The clobber
prevents r1 destruction but doesn't force the dest register. Tried `u8 m=128`
var and `w = m & v` temp — still dest r1.

### Clr20_0804B310 @0x0804B310 (36B) — nointerwork doesn't fix order
**New angle tried:** no-interwork TU (per brief: "changes scheduler behavior").
Result: 11 diffs, bin 32B (wrong size; interwork gives 36B correct). With
old_agbcc interwork: 10 diffs. Blocker: prologue order — ROM does
`lsls/lsrs r4,r1` (mask v) BEFORE `adds r3,r0,#0` (save dst); mine reverses.
The `adds r2,r3,#0` copy IS present in mine. Scheduler heuristic; nointerwork
didn't change the order. Tried `u8 bv = v` early — no effect.

### Avg_080110B0 @0x080110B0 (24B) — pin forces push, allocation off
**New angle tried:** `register s32 sum __asm__("r4")` to force `push {r4,lr}`
(was missing). Result: push present, 5 diffs remain. ROM: `ldr r2,[r0,#4]`;
`ldr r0,[r0,#0]`; `subs r3,r0,r2`; `adds r4,r2,r0`. Mine: `ldr r4,[r0,#0]`
(a in r4, not r0); `subs r0,r4,r2` (diff in r0, not r3); `adds r4,r2,r4`.
The r4 pinning causes the compiler to keep `a` in r4, breaking the ROM's
`adds r4,r2,r0` shape. s32 types give correct `asrs` (not `lsrs`).

### Bitfield_DecOrSet @0x0800DB40 (44B) — shift idiom tried
**New angle tried:** `((u32)b << 28) >> 28` instead of `b & 0xF` to get ROM's
`lsls r0,r1,#28; lsrs r1,r0,#28` (not `ands`). Result: 26 diffs (branch
structure and regalloc diverge). The shift idiom may be correct for the
`& 0xF` site, but the surrounding `ldrsb`/branch code doesn't match.

### Init_08000CA8 @0x08000CA8 (34B) — loop structure wrong
Attempted; 32 diffs, bin 56B (should be 34). ROM reuses r0 as loop counter
after `str r0,[r1,#0]`; my C with separate `int i` generates different code.
BLOCKED.

### U16_FillLoop @0x0800C8BC (46B) — whole-asm blocked by assembler
**New angle tried:** Whole-function asm (G1 pattern for shift-add-shift loops).
Result: file-scope `__asm__` with Thumb instructions rejected by assembler
(`instruction not supported in Thumb16 mode` even with `.thumb` directive).
Needs a separate `.s` file, not C. BLOCKED (assembler limitation, not C).

## BLOCKED (not attempted — time)

- FlagByte_CopyOrNeg1 @0x08010374, BitClear_StructZero @0x08010F88,
  MemCopy_U16x4 @0x0804A660, Bitfield_TableLookup @0x0800B6F4: not attempted
  due to time constraints (prioritized G1 small functions which yielded 2 matches).

## SKIPPED (per brief)

- crt0_thumb_helpers @0x080002DC: inside crt0 asm-verified range
  [0x08000000,0x0800033b]; already covered. Not attempted.

## Task_3AFFC @0x0803AFFC — no new angle attempted (low priority)

Per brief: "only attempt a GENUINELY new angle." Evaluated the two suggested
angles:
1. **Matching unmatched callees' real signatures first:** Would not help.
   The blocker is GCC's cross-case block-merging (16 similar `if ((s8)call()!=0)`
   patterns get merged across cases), not register allocation. Callee
   signatures affect call-site regalloc, not the crossjumping/merging of
   identical code blocks across switch cases.
2. **`__attribute__((optimize))`:** agbcc is gcc 2.95-based; it does not honor
   `__attribute__((optimize))` (introduced in gcc 4.x). No effect.
Recorded as BLOCKED without new attempt; wave7_a's 7 angles remain the state
of the art.

## Idioms / observations for the catalog

1. **Shared-mask copy pattern:** When an `int mask = -K` is used at two sites,
   old_agbcc emits `adds rD,rM,#0` (copy) at the FIRST site and uses the mask
   reg directly at the LAST site (to avoid destroying the live mask). This is
   the BLK-A key generalized (Obj_AddEntry, ObjInit_1D3C0 s[0x41]).
2. **Early zero hoist:** `int zero = 0;` declared at block start gets hoisted
   by the scheduler to just before its use, interleaved with surrounding code
   (ObjInit_1D3C0 else-branch: `movs r1,#0` before `ldrb`). Useful for matching
   ROM's interleaved materialization.
3. **Two-step address anti-fold:** `u8 *p = s; p += 0x50; *(u32*)(p+28) = 0;`
   defeats the `s+0x6c` fold, giving ROM's `adds r0,#80; str r1,[r0,#28]`.
4. **Separate pointer vars anti-CSE:** Using `u8 *p` and `u8 *q` for `s+0x41`
   and `s+0x45` prevents the compiler from optimizing to `adds r3,#4` (ROM
   recomputes from scratch).
5. **Pinning side effects:** `register ... __asm__("r4")` forces the push but
   perturbs the allocation of related values (Avg_080110B0: `a` goes to r4).
6. **Fake-clobber limitation:** `__asm__("" : "+r"(v))` keeps a value live but
   does not control the dest register of subsequent ops (Check_0800B2B4).
