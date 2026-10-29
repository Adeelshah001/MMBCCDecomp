# Wave 28-D Match Notes (Worker D, bulk + blocked revisits)

Worker D, 2026-10-23. Staging: `staging/wave28_D/` (C sources, verify.sh harness).
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before starting.

Registry check: all 8 bulk targets NOT-IN-REGISTRY. 0x0801c030 and 0x08049560
IN-REGISTRY as BLOCKED (revisits, not claims). No skips.

## MATCHED (1)

### 0x0802D6E0 — MenuTick_0802D6E0 (192 B, 0 diffs) ✅

Menu state dispatch on p[1], cases 0-4, returns 3 (case 4 returns 4 via fallthrough).
**Compiler: old_agbcc** (decisive for v6→r1 allocation and overall codegen).
Staged: `staging/wave28_D/w28d_0802d6e0_final.c` (v8).

**Evidence:** `./verify.sh 0x0802d6e0 192 .text.w28d_0802d6e0 w28d_0802d6e0_v8.c old`
→ `sizes: o=1132 elf=2536 bin=192`, `rom extract: 192 bytes`, `diffs: 0`.
Clean-room recompile → linked at true ROM address with custom .ld → objcopy →
cmp vs baserom extract at file offset 0x2d6e0, exact 192 bytes, 0 diffs.
True extent 192 B confirmed (code 0x2d6e0–0x2d79e + inline pools; next func at 0x2d7a0).

**Key findings:**
- Case 1's jump-table entry (0x2d712) points into the middle of case 0's code —
  case 0 does `p[1]++` then falls through into case 1's body (Duff's-device style).
- Case 3 has NO trailing branch — it does `p[1]++` then falls through into case 4!
  (Initial assumption of `return 3` was wrong; the bytes show fallthrough.)
- **old_agbcc decisive:** main agbcc puts v6→r2 (104 diffs); old_agbcc puts v6→r1,
  matching ROM. Also fixes shift-temp and ldrh-temp allocation.
- **p-reuse idiom:** In case 4, `p = (u8 *)(u32)p[6]` emits `ldrb r4,[r4,#6]`,
  reusing p's dead register (mirrors w27c vv-reuse idiom).
- **Memory barrier for load ordering:** `__asm__ volatile("" ::: "memory")`
  between the `(v6&8)` test and the `*(u16*)(p+20)==0x1000` test forces gcc to
  emit `movs/lsls` (0x1000 materialization) BEFORE the `ldrh`, matching ROM.
  Without it, gcc hoists the ldrh above the movs/lsls.
- **u32 temp for ands dest:** `u32 m = 16; m &= t6;` gives `ands r0,r1` (dest=r0,
  matching ROM); `u8 m` gives `ands r1,r0` (dest=r1). The u32 forces the constant
  into r0 as the destination.
- **Nested scope for pool-load ordering:** In case 4, declaring `u16 m2` in a
  nested block AFTER the first `ands` forces gcc to emit `ldr r2,[pc]` (mask2)
  after the `ldrh`/`ands`, matching ROM's `ldrh r2; ands r1,r2; ldr r2; ands r1,r2`.
  Without nesting, gcc hoists the mask2 load before the ldrh.

**Name:** MenuTick_0802D6E0 (menu state machine tick; p[1]=state, p[2]/p[3]=substate,
calls Cmp_08004E0C/Set_08004E24 for state transitions).

## BLOCKED (attempted)

### 0x0801C030 — ChipState_0801C030 (214 B, 114 diffs best, was 60)

**vv-reuse idiom CONFIRMED:** Reassigning `vv = sp[19]` in case 1 emits
`ldrb r4,[r5,#19]`, reusing r4 (vv's dead register), matching ROM exactly.
This is the idiom from w27c, now verified working.

**Remaining walls:**
1. **Prologue r6:** ROM pushes `{r4,r5,r6,lr}`; mine pushes `{r4,r5,lr}`.
   r6 is used ONLY for the ldrsh index (`movs r6,#0; ldrsh r3,[r3,r6]`).
   Pinning z→r6 (`register int z __asm__("r6")`) backfires — vv (which should be
   r4) gets allocated to r6 instead, breaking the prologue differently.
2. **ldrsh index:** ROM uses r6 as zero-index (`movs r6,#0; ldrsh r3,[r3,r6]`
   twice). The `z` variable won't go to r6 naturally. Needs a way to force
   r6 without pinning (which breaks vv).
3. **Pool order:** ROM does `ldr r0,[pc]` (pool→r0) then `ldrb r4,[r5,#19]`
   then `adds r0,r4,r0`. Mine does pool→r1. The `__asm__ volatile("" : "+r"(p1))`
   forces the pool load first, but it goes to r1 not r0.
4. **adds operand order:** ROM `adds r0,r4,r0` vs mine `adds r0,r0,r4`
   (2-byte encoding difference).

Staged: `staging/wave28_D/w28d_0801c030_v3.c` (vv-reuse working, 114 diffs at
208 B; w27c v4 had 60 diffs at 216 B — my version regressed on size).

### 0x08049560 — GfxSetup_08049560 (280 B, 44 diffs best, was 235)

**DSE-defeating idiom FOUND:** `*(volatile u16 *)&local = 0;` (volatile-qualified
STORE, not volatile variable) defeats gcc's Dead Store Elimination and preserves
both `strh` instructions with ZERO extra bytes (unlike `volatile u16 local` which
adds 48 B, or the `"r"` asm which adds 2 B for `mov r0,#0`).

With the volatile store, the prologue matches ROM:
```
movs r1,#0; add r0,sp,#4; strh r1,[r0]  (local = 0) ✓
ldr r1,[pc]; add r0,sp,#4; strh r1,[r0]  (local = pool) ✓ (regs differ slightly)
```

**Remaining walls:**
1. **48-byte bloat:** Even with the surgical volatile store (not volatile variable),
   the function compiles to 328 B vs ROM's 280 B. The extra 48 B are NOT in the
   prologue (which matches). Likely the volatile store affects alias analysis
   throughout the function, preventing optimizations. Needs investigation.
2. **Register swap in prologue:** ROM `movs r1,#0; add r0,sp,#4` vs mine
   `add r1,sp,#4; movs r0,#0` (with plain volatile store). The `u16 zero = 0`
   variable fixes the order but adds a new local that perturbs allocation.
3. **Missing `adds r1,r0,#0` copy:** ROM does `ldr r0,[pc]; adds r1,r0,#0`
   (pool→r0, copy to r1). Mine does `ldr r1,[pc]` directly. The copy is elusive.

Staged: `staging/wave28_D/w28d_08049560_v5.c` (44 diffs, 328 B).

**New idiom:** Volatile-qualified store `*(volatile u16 *)&p = v;` defeats DSE
with zero bytes overhead (vs 48 B for volatile variable, 2 B for `"r"` asm).

## BLOCKED (triaged, not attempted in depth)

### 0x08002A1C — sub_08002A1C (210 B)
Complex DMA setup loop (16 iterations). High register pressure (r6,r7,r8,r9 all
used). Contains `ldrsb` (needs inline asm per brief). Two similar code paths
(0x2a54 and 0x2a9c) with different pool constants. Calls CpuSet (0x804db28).
Requires significant effort.

### 0x080046B0 — sub_080046B0 (238 B)
Complex gfx, CpuFastSet, high-reg pressure. Triaged only.

### 0x0803AC4C — sub_0803AC4C (238 B)
Multiple branches. Triaged only.

### 0x0801E77C — sub_0801E77C (254 B)
Switch on p[14], stack args. Triaged only.

### 0x080096BC — sub_080096BC (260 B)
Tile-copy loop, 5 params, uses r8/r9/sl, calls 0x8000758. Triaged only.

### 0x08006FE8 — sub_08006FE8 (264 B)
6 params, GetPtr family. Triaged only.

### 0x08024A30 — sub_08024A30 (268 B)
11 callees. Triaged only.

## New idioms discovered

1. **Volatile-store DSE defeat:** `*(volatile u16 *)&local = 0;` preserves a
   dead store with zero bytes overhead. (vs `volatile` variable: +48 B;
   vs `"r"` asm: +2 B for input materialization).
2. **old_agbcc for allocation:** On 0x0802d6e0, old_agbcc gave correct v6→r1
   allocation vs main agbcc's v6→r2. Always try old_agbcc, even when main
   is close (confirms w27c finding on 0x0801b0dc).
3. **Memory barrier for load ordering:** `__asm__ volatile("" ::: "memory")`
   forces gcc to emit constant materialization before a load, defeating the
   scheduler's load-hoisting.
4. **u32 temp for ands dest:** `u32 m = 16; m &= t6;` gives `ands r0,r1`;
   `u8 m` gives `ands r1,r0`. Use u32 to force dest=r0.
5. **Nested scope for pool ordering:** Declaring a mask variable in a nested
   block after its first use forces the pool load to emit after, matching
   ROM's load-use-load pattern.
6. **p-reuse for dead parameter:** `p = (u8 *)(u32)p[6]` reuses p's register
   (r4) for a new value when p is dead, emitting `ldrb r4,[r4,#6]`.

## Tooling
- `staging/wave28_D/verify.sh` — hardened harness (adapted from w27d).
- `staging/wave28_D/w28d_0802d6e0_final.c` — MATCHED source (0 diffs).
- `staging/wave28_D/w28d_0801c030_v3.c`, `w28d_08049560_v5.c` — best blocked attempts.
- `staging/wave28_D/rom_*.bin` — ROM extracts for disassembly.
- `staging/wave28_D/exp*.c`, `dse_test*.c` — experiments (kept for reference).

## Summary for coordinator
- **MATCHED:** 0x0802D6E0 (MenuTick_0802D6E0, 192 B, old_agbcc, 0 diffs).
  Staged at `staging/wave28_D/w28d_0802d6e0_final.c`.
  Needs registry claim + landing.
- **BLOCKED:** 0x0801C030 (vv-reuse works, needs r6 prologue + ldrsh index work),
  0x08049560 (DSE defeated via volatile store, needs 48 B bloat investigation).
- **TRIAGED:** 7 bulk targets (0x08002a1c, 0x080046b0, 0x0803ac4c, 0x0801e77c,
  0x080096bc, 0x08006fe8, 0x08024a30) — not attempted in depth due to time.
- **Progress:** 1/10 bulk matched, 2/2 revisits attempted with new idioms.
