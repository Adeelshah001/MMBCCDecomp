# Wave 4 batch F match notes (worker, 2026-10-20)

14 huge functions (556–1550 B), all BLOCKED. 0/14 matched.

## Common structure

All 14 are "task mode-dispatch" functions sharing a template:
```
push {regs}; <save p>; <ret=0>; bl EntryMgr_Teardown (0x08004F18)
mode = p[MODE_OFF]; if (mode > N) goto epi
switch (mode) { case 0..N: ... }   // via lsls#2; ldr=table; mov pc,r0
epi: bl EntryMgr_Setup (0x08004F80); return ret
```
MODE_OFF and N vary per function. The bodies are long linear sequences of
bit ops on EWRAM (0x02004CE0, 0x02004E40, 0x02002F50, 0x02003670, 0x02004F80),
ROM table lookups (0x0822xxxx), and calls into ~30 distinct unmatched
`sub_0800xxxx` helpers. Contrary to the batch brief ("every bl-callee is
already matched"), only EntryMgr_Teardown/Setup (0x08004F18/0x08004F80) and
Text_SelectBlobIdx (0x0804A378) are matched; all others are unmatched and
were declared via `.set` absolute symbols for verification (entrymgr.c pattern).

## Root cause of BLOCKED (all 14)

Byte-matching requires reproducing agbcc -O2's exact register allocation and
basic-block/pool layout for 500–1550 B functions. The allocator's choice of
callee-saved regs for the two long-lived values (struct pointer `p` and the
`ret` accumulator) varies per function and was not reproducible from
semantically-equivalent C:

| function | ROM prologue | compiler gave |
|---|---|---|
| 0x08048400 | push {r4,r5,r6,lr}; r5=p; r6=ret=0 | push {r4..r7,lr}+r8; r7=p; r8=ret |
| 0x0803531c | push {r4,r5,r6,r7,lr}; r5=p; r7=ret=0 | (not attempted; same class) |
| 0x080367e0 | push {r4,r5,r6,lr}; r4=p; r5=ret=0 | (would match default) |
| 0x0803affc | push {r4,r5,lr}; r4=p; r5=ret=0 | (would match default) |

Three compile attempts on 0x08048400 (goto-switch, proper switch/case with
fallthrough, restructured) all failed at the prologue: the case bodies keep
too many values live (f1/f2 bit-test accumulators, pool pointers), pushing
the allocator to r7/r8. Reducing live ranges to match would require knowing
the exact original source statement order, which is not recoverable from the
binary with confidence.

Idioms that DID reproduce correctly (verified in isolation):
- `mask = 0x1f; mask = -mask;` → `movs r1,#0x1f; rsbs r1,r1,#0` (compiler
  does NOT constant-fold; matches ROM).
- `((s8)p[x] << 4) + 8` → lsls#24; asrs#24; lsls#4; adds#8 (matches ROM).
- 5-case dense switch → jump table via `lsls#2; ldr=table; mov pc,r0`
  (matches ROM dispatch shape, but table placement/pools differ).

## Per-function notes

### 0x0803531c — Task_3531C (788 B) — FULLY DECODED, 0 compile attempts
5-case switch on `p[0x46a9]`.
- Mode 0: `sub_08004E44()` (no-arg; r0/r1 hold jump-table junk at call),
  `sub_08004DFC(*(u8*)0x02004F82)`, then EWRAM 0x02004CE0 setup:
  `*(u16*)(base+0x28)=0x10; *(u16*)(base+0x2a)=0x20;`
  `*(u8*)(base+0x2c) = (1|*(base+0x2c)) & -31 & -33;`
  `*(u16*)(base+0x2c) &= 0xFC3F;` then `sub_0800800C(base,0)`,
  `sub_0800BEE0(0x40,0x80)`, `sub_08005A9C(0x17)`; falls into mode-1 tail.
- Mode 1: `sub_08035AFC(p)`, `sub_08035C5C(p)`, zero `p[0x46AA..0x46AC]`,
  `p[0x46A9]++`; gate `sub_0800B148(1,(s16)sub_08024514((u8)sub_080241F8(0x1000)),0)`;
  if nonzero `p[0x46A9]++` again.
- Mode 2: `if ((u8)sub_0800B2D8()) p[0x46A9]++`.
- Mode 3: two sub-paths on `p[0x46AC]==0`: fn-pointer from ROM table
  `0x0822EAAC[(s8)p[0x46AA]]` or `0x0822EAFC[(s8)p[0x46AB]]`; gate
  `(u8)sub_0800B368(fn,0,0,0)`; then 4× `sub_0800B448(a,b,c)` field writes
  at `p[idx*12+{0x30,0x31}]` / `p[idx*12+{0x28,0x2A}]` (or +0x120/+0x118
  variants, or the `(u8)(p[0x46AB])-4` variant at `r4=p+idx*12`).
- Mode 4: `*(u8*)(0x02004E40+0x14)|=1`; if `p[0x46AC]==*(u8*)(0x02003670+0x11AC)`:
  zero → `ret=(u8)sub_08035630(p)`; nonzero → `ret=(u8)sub_08035838(p)` +
  `sub_08035C5C(p)`; else nudge `*(0x02003670+0x11AC)` toward `p[0x46AC]` by ±1.
- Returns `ret` (r7). Calls `sub_08035630`/`sub_08035838` which lie AFTER this
  function in ROM (0x08035630 > 0x08035628 end).
- Recomp-relevant: touches EWRAM 0x02004CE0 (+0x28/+0x2A/+0x2C), 0x02004E40+0x14,
  0x02003670+0x11AC, 0x02004F80+2; ROM tables 0x0822EAAC/0x0822EAFC.

### 0x08048400 — Task_48400 (596 B) — FULLY DECODED, 3 compile attempts
5-case switch on `p[0x46A5]`. Structure mirrors 0x0803531c with different
constants:
- Mode 0: `sub_0800BEE0(0x40,0x80)`, `sub_08005A9C(0x19)`, `sub_08049560(p)`,
  EWRAM 0x02004CE0 setup with `*(u16*)(base+0x2A)=((s8)p[0x46A6]<<4)+8`,
  mask sequence, `sub_0800800C(base,0)`, `p[0x46A5]++`; falls into mode-1 tail.
- Mode 1: gate `sub_0800B148(1,(s16)sub_08024514((u8)sub_080241F8(0x1000)),4)`;
  if nonzero `p[0x46A5]++`.
- Mode 2: `if ((u8)sub_0800B2D8()) p[0x46A5]++`.
- Mode 3: `idx=(u8)(sub_08024384(0x1000)-0x32)`;
  `v=*(u32*)(((u32*)0x082344C0)[(s8)p[0x46A6]] + (idx<<2))`;
  `if ((u8)sub_0800B368(v,0,0,0)) p[0x46A5]++`.
- Mode 4: `*(0x02004E40+0x14)|=1`; `sub_08049560(p)`; bit-test ladder on
  `*(u16*)0x02002F50`/`*(u16*)0x02002F54`: r4 = 0x40/0x80/1/2 by priority
  (last match wins); the 0x40 test uses branchless
  `rsbs;asrs#31;ands` idiom for `(f2&0x40)?0x40:0`.
  - r4==2: `Text_SelectBlobIdx(0x68)`, `p[0x46A6]=6`, `ret=6`.
  - r4==1: `Text_SelectBlobIdx(0x67)`, `p[0x46A4]=1`, `p[0x46A5]=0`.
  - r4==0x40: if `(s8)p[0x46A6]>0`: `Text_SelectBlobIdx(0x66)`, `p[0x46A6]--`, `p[0x46A5]=3`.
  - r4==0x80: if `(s8)p[0x46A6]<=1`: `Text_SelectBlobIdx(0x66)`, `p[0x46A6]++`, `p[0x46A5]=3`.
- Returns `ret` (r6).
- Attempt 1 (goto-switch): compiler emitted cmp-chain, no jump table; prologue
  `f0 b5` (r4-r7). Attempt 2 (restructured): same. Attempt 3 (proper
  switch/case fallthrough): jump table OK, but prologue `f0 b5 47 46 80 b4`
  (saves r8; p→r7, ret→r8) vs ROM `70 b5 05 1c 00 26` (r5=p, r6=ret).
  Byte diff: 532/560 bytes differ; size 560 vs 596.
- Recomp-relevant: EWRAM 0x02004CE0, 0x02004E40+0x14, 0x02002F50/0x02002F54;
  ROM table 0x082344C0.

### 0x080367e0 — Task_367E0 (556 B) — structural survey only
9-case switch on `p[5]` (table at 0x08036800). Prologue `push {r4,r5,r6,lr}`;
`r4=p`, `r5=ret=0` (matches compiler default allocation — most promising
candidate for a future attempt). Mode 0 does the EWRAM 0x02004CE0 setup
variant (`*(u16*)(base+0x2A)=((s8)p[0x4698])+8`, note: no `<<4`);
calls `sub_080374B8`/`sub_08037598`/`sub_08037600` (task-local helpers),
`Text_SelectBlobIdx`, gates via `sub_0800B148`/`sub_0800B2D8`/`sub_0800B368`.

### 0x08036f34 / 0x0803719c (604/664 B) — structural survey only
17-case switches on `p[5]`. Same helper family (`sub_080374B8/0x08037598/
0x080375C8/0x08037700/0x080378B8`). 0x0803719c additionally calls
`sub_08037794`. Heavy use of `sub_0800B148/0x0800B2D8/0x0800B2F0/0x0800B308/
0x0800B368/0x0800B3F8` predicate helpers and `sub_080241F8/0x08024384/
0x08024514/0x080246A8` converters.

### 0x08037b4c (650 B) — structural survey only
7-case switch on `p[0]`. Calls `sub_0803895C`/`sub_08038AD4`,
`sub_0800B448` field writer, `Text_SelectBlobIdx`.

### 0x080385a8 (938 B) — structural survey only
11-case switch on `p[0]`. Calls `sub_08011BC8`/`sub_08011D34`,
`sub_080247E8`, `Text_SelectBlobIdx`.

### 0x0803affc (926 B) — structural survey only
16-case switch on `p[0x469D]`. Prologue `push {r4,r5,lr}` (simplest);
`r4=p`, `r5=ret=0`. Starts with `*(0x02004E40+0x14)|=1` before the switch.

### 0x0803b3a0 (1266 B) — structural survey only
12-case switch; largest function in batch. Calls `sub_0803B898`,
`sub_08040060`, `sub_08025024`, `Text_SelectBlobIdx`. Prologue saves
r4-r7 with `r4=0` initialized (third live value).

### 0x0803e144 (654 B) — DECODED (no switch)
Not a switch: bit-test prelude on `*(u16*)0x02002F50` (r4 = 0/0x40/0x80/1/2
priority ladder, same idiom as 0x08048400 mode 4), then an if-chain on r2
(0x80→0x35C, 0x40→0x2FC, else 0x3C6). Body manipulates `p[0x4699]` (counter),
`p[0x469A]`, `p[0x46B1]` (s8, clamped 1..3 via the `ble 3 / bgt 2/1` idiom),
`p[0x46B2]` (s8), using ROM table `0x082323C0` indexed by `p[0x469A]`.
Calls ONLY the matched `Text_SelectBlobIdx` (12 sites: 0x66/0x67/0x68).
Returns 0/1 in `ip` (r12); prologue saves r8 (`push {r4-r7,lr}; push {r7}`
after `mov r7,r8`). Recomp-relevant: EWRAM 0x02002F50; ROM table 0x082323C0.

### 0x08047860 (990 B) — structural survey only
6-case switch on `p[1]` (mode byte at r7+1; prologue `push {r4-r7,lr}` +
`push {r7}` saving r8, `r7=p`). 27 bl-sites; calls `sub_08047C4C`,
`sub_08046CA0/0x08046CFC/0x08046DE4/0x08046DF8`, `sub_08024FBC/0x08024FF4/
0x0802500C/0x0802508C/0x080250BC`, `sub_080242A8/0x08024434/0x080247E8`.

### 0x08047ce4 (922 B) — structural survey only
13-case switch on `p[5]` (r6+5; prologue saves r6/r7, `r6=p`). Calls
`sub_08048084`/`sub_080481FC`, BIOS `CpuFastSet`/`CpuSet` (0x0804DB24/28,
matched), `sub_08001E74`, `Text_SelectBlobIdx`.

### 0x08048658 (1550 B) — structural survey only
56-case switch (`cmp #0x37`) — the largest dispatch in the batch. Calls many
`0x0804Axxx` text-related matched/unmatched functions (`sub_0804A39C/
0x0804A3C4/0x0804A3F0/0x0804A3FC/0x0804A40C/0x0804A494/0x0804A4B0/0x0804A660/
0x0804A694/0x0804A884`), `sub_080400A8`, `sub_08028880`, `sub_08025108`.

### 0x08049ab0 (752 B) — structural survey only
16-case switch on `p[5]`. Calls `sub_08049DAC`/`sub_0804A0A4`,
`Text_SelectBlobIdx`, the standard predicate/converter helpers.

## New idioms discovered (proven in isolation)

1. **Runtime mask negation**: `u32 mask = 0x1f; mask = -mask;` compiles to
   `movs r1,#0x1f; rsbs r1,r1,#0` — agbcc does NOT constant-fold through the
   negation when the mask is subsequently used in `ands` chains. (Used in
   0x0803531c/0x080367e0/0x08048400 mode-0 EWRAM setup.)
2. **Branchless bit-presence select**: `(f2 & 0x40) ? 0x40 : 0` compiles to
   `lsls#16; lsrs#16; rsbs; asrs#31; ands` (no branch). The `(u16)` truncation
   is load-bearing for the exact encoding.
3. **(u8)(x - 0x32) << 2 as table index**: `subs#0x32; lsls#24; ...; lsrs#22`
   — write as `((u8)(v - 0x32)) << 2` with u32 accumulator.

## Recommendation for coordinator

These 14 are poor targets for further worker blind attempts: the blocker is
whole-function register allocation, which needs the original statement order.
Better approaches: (a) match the ~30 small `sub_0800xxxx` callees first —
   several are likely tiny predicates/converters, and matching them may
   clarify the callers; (b) attempt 0x080367e0 or 0x0803affc whose prologues
   (r4=p,r5=ret) match the compiler's default allocation; (c) deprioritize
   0x08048658 (56-case switch, 1550 B) until the family idioms are proven.
Note: the batch brief's "every bl-callee is already matched" is incorrect —
only 0x08004F18/0x08004F80/0x0804A378 are matched; the rest need .set
treatment (as done here) until matched.
