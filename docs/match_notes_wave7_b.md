# Wave 7 Worker B — Match Notes (2026-10-20)

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/old_agbcc`.
Verification: hardened protocol (non-empty assertions, file offset =
addr - 0x08000000, full 564 B extent incl. literal pools, `cmp -l` clean).
Scratch: `/tmp/wave7_b/`. Result: **1 MATCHED, 0 BLOCKED.**

## MATCHED

### Task_367E0 @ 0x080367e0 (564 B) — MATCHED (0 diffs, old_agbcc)

**Formulation**: `/tmp/wave7_b/Task_367E0_080367e0_MATCHED.c`

9-mode task state machine on `p[5]`, returns `u32` in r0 (`ret` in r5).
Prologue `push {r4,r5,r6,lr}; r4=p; r5=ret=0; bl EntryMgr_Teardown`;
9-entry jump table; epilogue `bl EntryMgr_Setup; r0=r5; pop; bx`.

Mode summary:
- 0: EWRAM 0x02004CE0 setup (`*(u16*)(+0x28)=16`,
  `*(u16*)(+0x2a)=(s8)p[0x4698]+8`, `*q=(1|*q)&-31&-33` with `q=base+44`,
  `*(u16*)(+0x2c)&=0xFFFFFC3F`), `sub_0800800C(base,0)`, `p[5]++`,
  fallthrough to mode 1.
- 1: `sub_0800B148(1, gByteTbl_0822FCA4[p[0x469f]], 4)` → shared gate.
- 2: `(s8)sub_0800B2D8()` gate; flag ladder on `p[0x469f]` (0/1/2) testing
  `p[0x17]` bits 1/2/4; else `p[5]=7`.
- 3/5/7: `ftbl = 0x082300A4/0x082300B0/0x08230098` → shared fn-dispatch
  (`sub_0800B368(ftbl[p[0x469f]],0,0,0)` → shared gate). Case 7 falls
  through into the shared dispatch (its `ldr r1` is the first insn).
- 4: `gEwram_02004E40[0x14]|=1`; `(u8)sub_08037600(p)` → 1:
  `Text_SelectBlobIdx(103)`, `p[0x4699]=p[0x4698]+2`, `p[5]=0`;
  → 2: `Text_SelectBlobIdx(104)` → `p[5]++`; else epi.
- 6: `gEwram_02004E40[0x14]|=1`; if `(s8)sub_0800B308()` or
  `(*(u16*)(0x02002F50+4)&2)` then `ret=1`.
- 8: `(s8)sub_0800B308()` gate; `p[0x17]` |= 1/2/4 by `p[0x469f]` (0/1/2);
  `p[0x4699]=1`, `p[5]=0`.

**Corrections to prior notes**: mode 0/1 byte-table index is `p[0x469f]`
(not `p[0x4699]`; pool at 0x080368b4 is `0x0000469F`); table base is
`0x0822FCA4` (not `0x2208A4FC`); mask pool is `0xFFFFFC3F` (not `0xFC3F`).

**Idioms used** (new ones marked *):
- *`(call() << 24)` for `(s8)` test*: `m = sub_0800B2D8() << 24` with
  `m` pinned to r0 gives `bl; lsls r0,r0,#24` with NO `adds` copy
  (direct `(s8)call()` copies to r1/r5).
- *Split shared gate*: `check_r0` (does the `lsls/cmp/beq`) vs `inc_p5`
  (`p[5]++; b epi`). Mode-2 rungs and case-4 L2 branch DIRECTLY to
  `inc_p5` (0x080369aa), skipping the re-test — ROM's `bne` targets the
  `ldrb`, not the `lsls`.
- *Block-scope r0 pin + call-result assignment*: `register u32 m
  __asm__("r0"); m = call() << 24;` keeps the value in r0. (A barrier-only
  pin across a call is ignored — the var MUST be assigned from the call.)
- *Opaque `movs` for const-before-load*: `__asm__ volatile("movs %0, #1"
  : "=l"(m))` with `m` pinned to r0, then pinned temp load, gives ROM's
  `movs r0,#1; ldrb rT,[r4,#23]; ands r0,rT` order.
- *u32-mask anti-fold*: `*(u16*)p &= 0xFFFFFC3F` folds to `0xFC3F`;
  use `u32 w = *p16; w &= 0xfffffc3f; *p16 = w;` to force the full pool word.
- *Barrier defeats const-prop on pinned var*: `register u32 off
  __asm__("r1") = 0x4698; __asm__ volatile("" : "+l"(off));` stops the
  compiler propagating `0x4698` and ignoring the pin (gives `ldr r1,=`).
- *addr/off double pin*: `{ register u32 addr __asm__("r0"); register
  u32 off __asm__("r1") = C; addr = (u32)p + off; ... }` forces
  `ldr r1,=C; adds r0,r4,r1` (mode-2 f-load, mode-4 L1).
- `g[0x14]|=1` with r6 temp: opaque `movs r1,#1` + `register u8 t
  __asm__("r6")` gives `ldr r0,=base; movs r1,#1; ldrb r6,[r0,#20];
  orrs r1,r6; strb r1,[r0,#20]`.
- `beq`-dispatch for 2-case inner switch: `if (sv == 1) goto L1; if
  (sv == 2) goto L2; goto epi;` (NOT `!=`/`bne` form).
- Local copy defeats pool-word folding: `u8 *b250 = gEwram_02002F50;`
  then `*(u16*)(b250+4)` keeps `ldr r1,=0x02002F50; ldrh r1,[r1,#4]`
  (direct `g+4` folds to `0x02002F54`).

**Pin-conflict lesson**: multiple `register __asm__("r0")` vars in one
function interfere unpredictably (r0 gets reserved function-wide; only
the pinned var may use it within its block). Keep r0 pins minimal,
block-scoped, and never barrier-only across calls.

## Files for coordinator

- `/tmp/wave7_b/Task_367E0_080367e0_MATCHED.c` — 0 diffs (old_agbcc)
- `/tmp/wave7_b/verify.sh` — hardened verification harness
- `docs/wave7_b_results.tsv` — summary table

**Landing notes**:
- old_agbcc, section `.text.w7b_080367e0`, links at 0x080367e0.
- Uses inline asm (`movs`, `ldr` via pins) and `register __asm__` pinning
  throughout; keep in its own section/file.
- `.set` absolute symbols for 5 data + 11 unmatched callees (see file
  tail); matched callees use real names (EntryMgr_Teardown/Setup,
  Task_37598, Text_SelectBlobIdx).
- Test-link stubs: `/tmp/wave7_b/stubs.s` (matched externs only).
