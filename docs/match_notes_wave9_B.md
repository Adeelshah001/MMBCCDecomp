# Wave 9 Worker B (TAG=B) — Match Notes

Worker: Wave 9 Script_StepState full-function (TAG=B). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/old_agbcc` per brief build rule
(cpp → old_agbcc -O2 -mthumb-interwork → as).
Harness: `staging/wave9_B/build1.sh` (hardened: custom ld script to prevent
`.text.*` merging, non-empty assertions on .o/.elf/.bin/ROM-extract,
file offset = addr − 0x08000000, full 964B section extent incl pools).
Staging: `~/workspace/mmbcc-decomp/staging/wave9_B/` (kept; never deleted
before verification). Results: `docs/wave9_B_results.tsv`.
Toolchain outage: parent reported binutils restored mid-session
(/tmp/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb cached);
this worker's toolchain never actually broke — `which` + old_agbcc
smoke test passed at session start and after the notice.

## MATCHED (1)

### Script_StepState @0x0803F480 (964B, old_agbcc, 0 diffs)

Full 964-byte script bytecode stepper, 22-case switch (values
0,2,4,…,26,30,32,34,36,38,40,44,46; odds + 28,42 + >46 → default).
Landed: `mmbcc/src/wave9_b_old.c`, section `.text.w9b_0803f480`,
ldscript slot `0x0803f480`, Makefile `wave9_b_old.o` old_agbcc rule.
Full-build `mmbcc.gba` section extract byte-identical to baserom.

Semantics (from behavior):
```c
void Script_StepState(u8 *p, u8 sel)   // callers: (ptr,0) @0x0803d3a4, (ptr,1) @0x0803d4dc
{
    u8 *q = p + 0x46A4;
    int flag = (sel == 0);             // 1 if sel==0 else 0
    u8 v = q[p[0x464C + p[0x46A0] + sel]];
    switch (v) {
    case 0:  /* ... */ q[p[0x464C + p[0x46A0] + sel]] = 16; break;
    case 2:  /* ... */ q[p[0x464C + p[0x46A0] + sel]] = 16; break;
    /* ... pairs (4,6)->18, (8,10)->20, (12,14)->22, (16,18)->24,
       (20,22)->26, (24,26)->28, (30,32)->38, (34,36)->40,
       (38,40)->42, (44,46)->48 ... */
    }
    q[p[0x464C + p[0x46A0] + flag]]++;
}
```
Callers pass sel=0/1; the function steps a script-state byte through a
double-indirect table (`p[0x464C]` indexed by `p[0x46A0]+sel`), writes a
step count (16–48) into the `q = p+0x46A4` table, then bumps
`q[p[0x464C+p[0x46A0]+flag]]`.

How the match was won (idioms):
1. **`register u32 s __asm__("r2")`** — pins sel to r2, which makes the
   allocator put `p` in r3 (ROM: `adds r3,r0,#0; lsls r1,r1,#24;
   lsrs r2,r1,#24`). Pinning `p` too causes scheduler interleaving;
   pinning only `s` is clean.
2. **Volatile-split sum + b2 split** (wave8_B probe, confirmed): 
   `sum = p[0x46A0] + s; __asm__ volatile("" : "+r"(sum));`
   gives `adds r1,r0,r2` (sum in r1); `b2 = p + 0x4600; b2 += 0x4C;`
   defeats the `subs r1,#0x54` fold so 0x464C is pool-loaded into r6.
3. **pa/pb/k recompute per case and epilogue**: each case body and the
   epilogue recompute `k = *pa + s` / `k = *pa + flag` with
   `pa = p + 0x46A0`, `pb = p + 0x464C`, because the switch dispatch
   clobbers r1. This yields ROM's exact
   `ldr r6,=0x46A0; adds r0,r3,r6; ldrb; adds r1,r0,r2; ldr r2,=0x464C;
   adds r0,r3,r2; adds r0,r0,r1; ldrb; adds r1,r0,r4` shape.
   (Pinning `k` to r1 breaks this — the compiler then reuses r1 for
   later adds; leave `k` unpinned.)
4. **t-then-flag**: `int t = (s == 0); flag = t;` forces the boolean
   through r0 (`movs r0,#0; cmp; bne; movs r0,#1; adds r5,r0,#0`)
   instead of direct-to-r5. 2-byte prologue size fix; aligns all
   downstream pools.
5. **22 separate cases, NOT paired**: writing `case 0: case 2:` (fallthrough
   pairs) lets old_agbcc merge identical bodies into 11 (640B total).
   Writing 22 separate `case N:` blocks defeats the merge → 21 distinct
   bodies + shared last-pair body = 964B, matching ROM's layout
   (ROM's v=0 body uses `ldr r1`, v=2 body uses `ldr r6` — the allocator
   varies per body when not merged).
6. **Crossjumped store**: each case ends `movs r0,#N; b 0x0803f81c`;
   the last pair (44,46) falls through into the shared
   `strb r0,[r1,#0]` — compiler's tail-merge, reproduced exactly.
   Default (and out-of-range via `cmp r0,#46; bls`) skips the store.

Verification: isolated `vv_v26.bin` 964B, 0 diffs vs ROM extract;
landed `mmbcc.gba` section extract byte-identical; full build green
(`make` clean, only the pre-existing dirty sections remain).

## BLOCKED (0)

None. The wave8_B probe angle carried the full function.

## Behavior discoveries (for feeds_recomp_notes.md)

- Script_StepState is called with sel=0 (@0x0803d3a4) and sel=1
  (@0x0803d4dc), both passing a pointer in r0 (r7 at the call sites).
- State layout around `p`: `p[0x46A0]` = inner index byte,
  `p[0x464C+...]` = outer index byte, `q = p+0x46A4` = 256-byte step
  table. The `flag=(sel==0)` selects the increment slot.
- Step-count values written: 16,18,20,22,24,26,28 (v=0..26),
  38,40,42 (v=30..40), 48 (v=44,46). v=28,42 and all odd v are no-ops
  (default skips the store but still does the trailing `q[...]++`).
