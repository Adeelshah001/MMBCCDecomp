# Wave 6 Batch L4 — Match Notes

34 functions (18–98 B), all bl-callees matched. 29 MATCHED (all old_agbcc), 5 BLOCKED.
Worker: verification harness hardened per 2026-10-20 correction (explicit non-empty
assertions on .o/.elf/.bin/rom.bin; file offset = addr − 0x08000000; byte-count-exact
compare). All 29 MATCHED re-verified with hardened harness (code + pool bytes).

## New idioms

### Struct-offset defeats constant pool folding (Tick_08028244 @ 0x08028244)
`*(u16 *)(0x02002F50 + 4)` folds the +4 into the pool (emits pool 0x02002F54 +
`ldrh r1,[r1,#0]`), but ROM pools the unfolded 0x02002F50 with `ldrh r1,[r1,#4]`.
Wrapping the access in a struct — `struct { u8 pad[4]; u16 flg; } *st; st->flg` —
prevents the fold: pool stays 0x02002F50, offset survives as `[r1,#4]`. 0 diffs.

### Goto state machine for 0/1/else dispatch (Tick_08028244)
ROM checks `v==0 → L0`, `v==1 → L1`, else return — with L0 falling through into L1.
Natural C `if (v > 1) return; if (v == 0) {...}` produces `cmp #1; bhi` + `cmp #0; bne`,
a different branch shape. Explicit `if (v == 0) goto zero; if (v == 1) goto one;
return;` reproduces the ROM exactly.

### `s[i]++` forces a reload; `s[i] = v + 1` folds when v is known (Tick_08028244)
In the `v==0` arm, ROM does `ldrb r0,[r1,#1]; adds r0,#1; strb r0,[r1,#1]`
(reload + increment). Writing `s[1] = v + 1` lets the compiler fold to
`movs r0,#1; strb` since v is provably 0. `s[1]++` keeps the reload.

### Delay pool-variable declaration to its use block (Tick_08028244, ObjInit_08016DAC)
A pool-backed pointer declared at function top gets its `ldr [pc]` hoisted above
branches. Declaring/using it inside the block where ROM loads it (e.g. after the
`bhi`) places the load correctly. Related: in ObjInit_08016DAC the dispatch table
is loaded first because it is *used* first — pool-load order follows first use.

### u8 `b + 0x10` arithmetic shape (Wrap_08002904 @ 0x08002904)
`Copy8_28D0(s, a, b + 0x10)` compiles to the shift-add-shift idiom:
`lsls r2,r2,#24; movs r3,#128; lsls r3,r3,#21; adds r2,r2,r3; lsrs r2,r2,#24`
— i.e. `(b<<24 + 0x10000000)>>24`. The compiler materializes 0x10000000 as
`128<<21`, not `16<<24`. No special handling needed; plain C matches.

### Direct-call dispatcher `tbl[s[13]](s)` (ObjInit_08016DAC @ 0x08016dac)
`((void (*)(u8 *))tbl[s[13]])(s)` with old_agbcc emits the wave4_i dispatcher shape
(`ldrb/lsls #2/adds/ldr`, target in r1, `bl _call_via_r1`) with the index in r2.
Table base comes from the pool; no masking on the index.

### Unsolved: mask-into-r0 bit-test (LoopSet_0804C8A4 @ 0x0804c8a4, BLOCKED)
ROM: `movs r7,#128; ldrb r1,[r4]; adds r0,r7,#0; ands r0,r1` (mask copied to r0,
AND with v). All C formulations tried (`(v & m1)`, `(m1 & v)`, `int t = m1 & v`,
nested ifs, gotos) produce `adds r0,r1,#0; ands r0,r7` (v copied to r0) or merge
the two tests into `(v & 192) == 192`. The allocator prefers v-in-r0; flipping it
needs a new trick. Loop structure, call, and stores all match — pure regalloc.

### Unsolved: keep base register across calls (Sram_08001E30 @ 0x08001e30, BLOCKED)
ROM holds `a` in r6 and materialized `0xE0000000` in r5 across two
Sram_RetryWrapper calls. Natural C puts `a` in r5 and recomputes the base per
call. Needs register-pressure engineering.

### Note: 0x0803B998 BLOCKED — callee not a function
`bl 0x0803C20E` targets an INTERIOR address (fallthrough from 0x0803C20A per
match_status.tsv), violating the batch premise "all bl-callees matched". Also
uses r8/r9 as scratch and a `mov pc,r0` jump table — needs dedicated RE, out of
batch scope.

## Carried-forward idioms (applied successfully)
- `__asm__("movs %0,%1")` + `register int c __asm__("r0")` for the `&3` clamp:
  GAS encodes `movs r0,rX` as `adds r0,rX,#0` (ObjInit family).
- Scoped `u32 zero = 0;` after `p -= 0x23` for early `movs r1,#0` scheduling.
- `sh = idx << 2` (new var) vs `idx <<= 2` selects live-range/allocation.
- Opaque `__asm__` to break zero-CSE when two `=0` stores must use different regs.
- `.set` absolute symbols need `.globl`; `.set` lines at file end (GAS 2.42).
- Inter-function `0000` gap vs GAS `c046` fill: only the function's byte extent
  (plus its own pools) must match; trailing fill is harness artifact.
