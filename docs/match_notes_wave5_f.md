# Wave 5 Batch F-Retry Match Notes (worker, 2026-10-20)

0/14 MATCHED. Deep attempt on Task_367E0 (69% bytes match); others not attempted.

## Task_367E0 @ 0x080367e0 (564 B) — BLOCKED, 389/564 match

Closest formulation: /tmp/wave5_f/t_367e0.c, compiled with old_agbcc.
Built size EXACT (564 bytes). Prologue, jump-table dispatch, and all 9
mode block sizes match ROM exactly.

### What matches
- Prologue: `push {r4,r5,r6,lr}; r4=p; r5=ret=0; bl EntryMgr_Teardown` ✓
- Dispatch: `ldrb r0,[r4,#5]; cmp #8; bls; b default; lsls#2; ldr r1,[pc,#4];
  adds; ldr; mov pc,r0` with inline jump table ✓
- Mode 0 (100 B): EWRAM setup, mask negation, (s8)+8, fallthrough to mode 1 ✓
  (size exact; minor reg diffs)
- Mode 1 (48 B): `bl sub_0800B148; b shared_gate` — shared gate via goto ✓
  (size exact; registers match after pinning tbl to r0)
- Mode 2 (72 B): gate + flag ladder with `beq #set7` + fallthrough ✓
  (size exact; uses goto pattern for shared set7)
- Mode 3/5/7 (8/8/2 B): `ldr r1,=table; b shared` / fallthrough ✓
  (shared fn-dispatch tail via goto; tbl naturally in r1)
- Mode 4 (80 B): `|=1`, inner switch on (u8)sub_08037600(p) ✓ (size exact)
- Mode 6 (44 B): `|=1`, `||` with `(u16)[2]` ✓ (size exact)
- Mode 8 (88 B): three ifs with `|=`, p[0x4699]=1, p[5]=0 ✓ (size exact)
- Epilogue: `bl EntryMgr_Setup; adds r0,r5,#0; pop; bx` ✓

### Remaining diffs (175/564 bytes)
Primarily register allocation permutations that don't affect semantics:
1. **Mode 0 `v = 1 | *q`**: ROM `movs r2,#1; ldrb r1,[r3]` vs mine
   `movs r1,#1; ldrb r2,[r3]` — v ends up in r2 in both; cosmetic swap
   of temporary registers.
2. **Mode 4/6 `g[0x14] |= 1`**: ROM `ldr r0,=base; movs r1,#1; ldrb r6,[r0,#0x14]`
   vs mine `ldr r1,=base; movs r0,#1; ldrb r2,[r1,#0x14]` — r0/r1 swap for
   base/const, r6 vs r2 for mem temp. The `tbl`/`r` live values at function
   scope affect allocation.
3. **Mode 2 ladder**: `ldrb r3,[r4,#0x17]` (mine) vs `ldrb r2,[r4,#0x17]` (ROM)
   for flag temps; `cmp r2,#2` vs `cmp r1,#2`.
4. **Shared gate**: mine hoists `strb r0,[r4,#5]` to epilogue (`b #0x08036a06`)
   vs ROM's inline `strb; b` — tail-merge difference.
5. Pool word ordering differences (consequence of above).

### Key techniques that worked
1. **Declare `base` after calls**: `u8 *base` must not be live across the
   `bl` calls, else compiler keeps it in callee-saved reg and p/ret get
   pushed to r6/r7. Declare after the calls.
2. **Register pinning for table**: `register u8 *tbl __asm__("r0")` forces
   the table base into r0, matching ROM's `ldr r0,=tbl` in mode 1.
   (Unpinned `u32 *tbl` naturally goes to r1 for the shared fn-dispatch.)
3. **Goto for shared tails**: Explicit `goto` to a shared label reproduces
   ROM's cross-jumping layout:
   - Modes 3/5/7: `tbl = CONST; goto fn_dispatch;` with `fn_dispatch:`
     label placed after case 7, before case 8.
   - Mode 1 + fn-dispatch: `r = CALL(...); goto check_r0;` with `check_r0:`
     label doing `if ((u8)r != 0) p[5]++;`.
   - Mode 2: `if (cond) goto m2_set7;` pattern for the `beq #set7` +
     fallthrough structure (NOT `else if` chain which gives `bne`).
4. **old_agbcc for scheduling**: old_agbcc emits `movs` before `ldrb`/`ldrh`
   where main agbcc does the reverse (mode 0 `v=1|*q`, mode 4/6 `|=1`,
   `&=0xfffffc3f` mask load).

### Why BLOCKED
The remaining 175 bytes are register allocation permutations (r0/r1, r1/r2,
r2/r6 swaps) that depend on subtle live-range interactions between the
function-scope `r`/`tbl` variables and the mode bodies. Fixing them requires
either (a) extensive trial-and-error with variable declaration ordering,
or (b) more register pinning which risks interfering with other parts.
The structure, size, and semantics are correct; only the register names differ.

## Other 13 targets — not attempted

- **Task_3531C** (788 B): prologue wants r5=p,r7=ret; compiler gives r4/r5.
  Semantics decoded in wave4_f notes. Needs regalloc breakthrough.
- **Task_36F34** (604 B), **Task_3719C** (664 B): prologue r5=p (no ret init),
  17-case switches. Non-standard allocation suggests extra live value.
- **Task_37B4C** (650 B): 7-case switch on p[0]. No prologue data.
- **Task_385A8** (938 B): 11-case switch on p[0]. No prologue data.
- **Task_3AFFC** (926 B): prologue r4=p,r5=ret MATCHES compiler default
  (push {r4,r5,lr} — simplest!). 16-case switch. Best candidate for next
  attempt after 367E0.
- **Task_3B3A0** (1266 B): 12-case, largest after 48658. Deprioritize.
- **Task_3E144** (654 B): NO switch (if-chain on bit-test), prologue saves r8.
  Different template; separate effort.
- **Task_47860** (990 B): 6-case switch, prologue saves r8.
- **Task_47CE4** (922 B): 13-case switch.
- **Task_48400** (596 B): prologue wants r5=p,r6=ret. Wave4_f tried 3x.
  Needs regalloc breakthrough.
- **Task_48658** (1550 B): 56-case switch. Deprioritized per wave4_f.
- **Task_49AB0** (752 B): 16-case switch.

## New generalizable idioms

1. **Jump-table base literal**: GCC emits `ldr r1,[pc,#4]` loading the table
   base from a literal word that contains the table's own address (first
   entry). The table follows immediately. To match, the C switch must be
   dense and the case bodies must match in size (else table shifts).

2. **Mode-0 fallthrough**: `case 0: ...; p[5]++; /* fallthrough */ case 1:`
   preserves the fallthrough in the binary. The compiler does not insert
   a branch.

3. **Shared dispatch tail via goto**: When ROM shows `ldr r1,=const; b shared`
   for multiple cases, use explicit `goto` to a shared label. The label
   placement in the source controls the code layout. The shared code must
   use the variable (e.g., `tbl`) so the compiler keeps it in a register
   across the goto.

4. **Register pinning for specific allocation**: `register T *v __asm__("rN")`
   forces a variable into a specific register. Use sparingly; function-scope
   pinning reserves the register for the whole function and can interfere
   with other code. Prefer block-scope pinning.

5. **old_agbcc scheduling**: For `v = 1 | *mem`, `g |= 1`, and mask loads,
   old_agbcc emits `movs` (const materialization) BEFORE the `ldrb`/`ldrh`,
   matching ROM. Main agbcc often does the load first. Try old_agbcc when
   the ROM has movs-before-load.

6. **Goto vs else-if for flag ladders**: To get ROM's `beq #target` +
   fallthrough (instead of `bne #next`), use separate `if (cond) goto target;`
   statements, not `if/else if` chains. The `&&` in `if (a && b)` gives
   `bne`; separate ifs with goto give `beq`.

7. **Call result via goto**: To share a `if ((u8)r0 != 0) p[5]++;` tail between
   a call in one case and a call in shared code, assign the result to a
   `u32 r` variable and `goto` a shared `check_r0:` label. The compiler keeps
   `r` in r0 (the return register) across the goto.

## Recomp-relevant findings (Task_367E0 decoded)

- EWRAM 0x02004CE0 (+0x28/+0x2a/+0x2c): object graphics setup; +0x2a =
  (s8)p[0x4698]+8 (Y position); +0x2c bit 0 set, bits 4/5 cleared, bits 6-7
  masked with 0xFC3F.
- EWRAM 0x02004F80[2]: argument to sub_08004DFC in mode 0.
- EWRAM 0x02004E40[0x14]: global flag bit 0 set in modes 4/6.
- EWRAM 0x02002F50[4] bit 1: polled in mode 6.
- ROM tables: 0x0822FCA4 (u8 table indexed by p[0x469F] for mode 1 gate),
  0x082300A4/0x082300B0/0x08230098 (u32 fn-pointer tables for modes 3/5/7).
- p[0x469F]: mode sub-selector; p[0x17]: bit flags; p[0x4698]/p[0x4699]:
  counters; p[5]: main mode byte.
- Helpers: sub_08004E44, sub_08004DFC, sub_0800BEE0(0x41,0x80),
  sub_08005A9C(6), sub_080374B8(p), sub_08037598(p), sub_0800800C(base,0),
  sub_0800B148, sub_0800B2D8, sub_0800B368, sub_08037600(p), sub_0800B308.
