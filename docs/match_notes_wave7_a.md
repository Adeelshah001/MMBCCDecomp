# Wave 7 worker A (TAG=A) — Task_3AFFC @ 0x0803AFFC — BLOCKED

Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` (read in
place, never copied). Toolchain: `mmbcc/tools/agbcc/bin/old_agbcc` (also
tried main agbcc, -O1, -Os). Build rule per brief. Verification via
`/tmp/wave7_a/build.sh` (hardened: non-empty assertions, file offset =
addr - 0x08000000, full section extent). Scratch: `/tmp/wave7_a/`
(`t3affc_v*.c`, `probe*.c`).

Result: **BLOCKED** — tail-crossjump unproducible. Best attempt 661/864
diffs, 62 bytes short of ROM's 926.

## Function structure (fully decoded)

16-case switch on `p[0x469d]` (u8 mode). Prologue: `push {r4,r5,lr}`,
`r4=p`, `r5=ret=0`, `bl EntryMgr_Teardown`, `gEwram_02004E40[0x14]|=1`
(with r0 pinning for g base), `cmp mode,#15; bls JT; b epi`.
JT base loaded from pool word at 0x803B030 (=0x0803B034); 16 entries at
0x803B034..0x803B073; code resumes 0x803B074. (Note: JT base is NOT at
0x803B030 — the word there is a POINTER to the JT at 0x803B034.)

Three fallthrough pairs: mode0→1, mode6→7, mode10→11 (case without break).

Tails (crossjump targets):
- **TailA** @ 0x803B38C (`strb r0,[r1]`, 2 bytes): 12 sites. 8 do
  `ldr rX,[pc]; adds r1,r4,rX; ldrb r0,[r1]; adds r0,#1; b TailA`
  (rX=r0 at 4 sites: modes 1,7,12,15; rX=r2 at 3 sites: modes 2,4,8;
  plus mode11). 4 do `movs r0,#imm; b TailA` (modes 3a/3b/5/9/10).
- **TailC** @ 0x803B33C (`strb r0,[r1]` + `p[0x469d]=0; ret=1; b epi`):
  2 sites (mode3 via `b`, mode13 via fallthrough).
- **TailD** @ 0x803B386 (`ldr r2,[pc]; adds r1,r4,r2; movs r0,#6` then
  falls into TailA): 1 site (mode14 via `b`).
- **Epilogue** @ 0x803B38E: `bl EntryMgr_Setup; adds r0,r5,#0;
  pop {r4,r5}; pop {r1}; bx r1`.

Mode behaviors (all verified by disassembly):
- 0: `sub_0800BEE0(0x40,0x80); p[0x469d]++` (inline) → fallthrough
- 1: `w=sub_08024514((u8)sub_080241F8(0x1000)); if((s8)sub_0800B148(1,(s16)w,4)!=0) p[0x469d]++` (via TailA)
- 2: `b=sub_08024384(0x1000)-50; fn=((u32*)0x08232128)[b]; if((s8)sub_0800B368(fn,*0x08231918,*0x08231920,0)!=0) p[0x469d]++`
- 3: `if((s8)sub_0800B308()==0) break; g8=g[8]; if(g8==0) p[0x469d]=4; elif(g8==1) p[0x469d]=8; else {Text_SelectBlobIdx(0x68); p[0x469c]=9; p[0x469d]=0; ret=1;}` (via TailA/TailC)
- 4: like mode2 with table 0x08232140, args (fn,0,0,0)
- 5: `if((s8)sub_0800B308()!=0) p[0x469d]=8`
- 6: `sub_0800BEE0(0x40,0x80); p[0x469d]++` → fallthrough
- 7: `sub_0800BEE0(0x40,0); p[0x469d]++` (inline); then like mode1
- 8: `if((s8)sub_0800B368(0x08231928,*0x08231930,*0x08231938,0)!=0) p[0x469d]++`
- 9: `if((s8)sub_0800B308()!=0) {g8=g[8]; if(g8==0) p[0x469d]=12; elif(g8==1){p[0x469c]=1;p[0x469d]=0;ret=1;} else{p[0x469c]=2;p[0x469d]=0;}} else {if((*(u16*)0x02002F54&2)==0) break; Text_SelectBlobIdx(0x68); p[0x469d]=2;}`
- 10: `sub_0800BEE0(0x40,0); p[0x469d]++` → fallthrough
- 11: like mode1 (but `beq epi` not `bne;b`)
- 12: `if((s8)sub_0800B368(0x08231940,*0x08231948,*0x08231950,0)!=0) p[0x469d]++`
- 13: `if((s8)sub_0800B308()==0) break; g8=g[8]; if(g8==0){p[0x469c]=6;p[0x469d]=0;ret=1;} elif(g8==1){p[0x469c]=7;p[0x469d]=0;ret=1;} else{Text_SelectBlobIdx(0x68); p[0x469d]=6;}` (via TailC/TailD)
- 14: `Text_SelectBlobIdx(0x68); p[0x469d]=6` (via TailD→TailA)
- 15: `if((s8)sub_0800B308()!=0) p[0x469d]++`

Callees: EntryMgr_Teardown/Setup, Text_SelectBlobIdx (MATCHED, real names).
Unmatched (`.set` + `.thumb_func`): sub_0800BEE0, sub_080241F8,
sub_08024514, sub_0800B148, sub_08024384, sub_0800B368, sub_0800B308.
Data: gEwram_02004E40, gEwram_02002F50 (established); ROM tables
0x08232128/0x08231918/0x08231920/0x08232140/0x08231928/0x08231930/
0x08231938/0x08231940/0x08231948/0x08231950/0x0823190C (absolute).

## What works

- Prologue, dispatch (`cmp #15; bls; lsls#2; ldr r1,[pc]; adds; ldr; mov pc`),
  JT (16 entries, pool-loaded base) — **byte-exact**.
- `(s16)` idiom: `s16 w = sub_08024514((u8)v);` gives
  `adds r1,r0,#0; lsls r1,#16; asrs r1,#16` (ROM). (The `(s16)(u8)` form
  optimizes to just `(u8)` — do NOT use.)
- Table index: `u8 b = sub_08024384(0x1000)-50; fn = ((u32*)0x08232128)[b];`
  gives `subs#50; lsls#24; lsrs#22; ldr; adds; ldr` (but ldr NOT between
  shifts — see below).
- Mode bodies structurally correct (verified by disassembly comparison).

## The blocker: tail-crossjump layout

**Goal**: 12 sites do `ldr rX,[pc]; adds r1,r4,rX; ldrb r0,[r1]; adds r0,#1;
b TailA`, TailA is single `strb r0,[r1]`. The ldrb/adds must NOT merge
(each site keeps its own copy), but the strb MUST merge (single copy).

**Why it's hard**: old_agbcc's crossjumping merges the maximal common
suffix. With 16 similar cases, it either:
(a) merges too much (ldrb/adds/strb all shared), or
(b) merges the if-checks across cases (moving them to wrong locations).

**Angles tried**:

1. **Natural C** (`u8 *q=p+0x469d; u8 t=*q+1; *q=t;`, v1): GCC merged the
   `ldrb;adds;strb` into a shared block (over-merging). 663 diffs.

2. **Off-variable** (`u32 off=0x469d; u8 *q=p+off;`, v2): In isolation
   (probe5, 4 cases), this gives the EXACT ROM pattern (separate ldrb/adds,
   shared strb). But with 16 cases, GCC merges the `if ((s8)call()!=0)`
   checks across modes (e.g., mode2's check moved to 0x803B33C, shared with
   mode15). 661 diffs, 62 bytes short.

3. **Explicit goto to shared label** (`goto tailA; ... tailA: *q=t;`,
   probe11/13/14): GCC merges the `ldrb;adds` for identical cases (worker
   F's finding confirmed). Also, `u8 t` causes unwanted `lsls#24;lsrs#24`
   truncation; `u32 v` causes cases to merge entirely.

4. **Distinct per-mode labels** (`m0_inc: ... goto tailA`, probe13): The
   strb IS shared, ldrb/adds stay separate — but identical cases (0 and 1)
   get merged by GCC (case 1 disappears). Also introduces `lsls#24;lsrs#24`
   for u8 intermediate.

5. **Register-pinned off** (`register u32 off __asm__("r3")`, v4): Worse
   (686 diffs). Pinning ignored by allocator, disrupts pooling.

6. **Compilers/flags**: main agbcc (664 diffs), -O1 (648), -Os (661) —
   old_agbcc -O2 is best (661).

7. **Branch structure control** (v3, `if(cond) goto inc; goto epi;` for
   mode2): Did not prevent the cross-case if-check merging.

**Root cause**: With 16 cases containing similar `if ((s8)call()!=0) {inc}`
patterns, old_agbcc's crossjumping/block-merging shares the if-check code
across cases, relocating it from the ROM's per-mode positions. The ROM's
layout (with per-mode `lsls#24;cmp#0;bne X;b epi` where X differs per mode)
prevents this sharing, but my C generates `b` targets that GCC considers
mergeable.

Additionally, the `lsls#24; ldr; lsrs#22` scheduling (ROM) vs
`lsls#24; lsrs#22; ldr` (mine) for the table index could not be reproduced;
the "volatile-split" from wave6 notes did not work in this context.

## Precise remaining diff (v2, best attempt)

- Size: 864 vs 926 (62 bytes short).
- 661 differing bytes.
- Prologue (0x803AFFC-0x803B026) and JT structure match.
- Mode bodies: structurally similar but addresses shifted due to size.
- Specific: mode2's `if` check relocated to 0x803B33C (shared with mode15);
  ldrb/adds over-merged at some sites; table-index ldr scheduling differs;
  `ldr r0` vs `ldr r2` register variation not reproduced (all use r0 or r2
  consistently per my output, ROM varies).

## Files

- `/tmp/wave7_a/t3affc_v1.c` — v1 (natural C, 663 diffs)
- `/tmp/wave7_a/t3affc_v2.c` — v2 (off-variable, 661 diffs, best)
- `/tmp/wave7_a/t3affc_v3.c` — v3 (goto for mode2, 661 diffs)
- `/tmp/wave7_a/t3affc_v4.c` — v4 (pinned off, 686 diffs)
- `/tmp/wave7_a/probe*.c` — 14 isolation probes (probe5 shows the tail
  pattern works with 4 cases; probe6/12 show if-check works in isolation)
- `/tmp/wave7_a/build.sh` — hardened verification harness
- `docs/wave7_a_results.tsv` — results table
- `docs/match_notes_wave7_a.md` — this file

## Recommendation

The tail-crossjump requires the EXACT original C structure to trigger
old_agbcc's crossjumping in the ROM's specific way. The 16-case interaction
is the blocker, not the tail mechanism itself (proven in probe5).

Future angles:
- Try writing modes in a different order (though JT requires 0-15).
- Try `#pragma GCC optimize` or function attributes to disable specific
  passes (if supported by agbcc 2.9).
- Match the unmatched callees first (sub_0800B368 etc.) — their signatures
  might affect the caller's register allocation.
- Consider that the original might have used a macro for the inc pattern
  with subtle per-site differences (e.g., different variable names) that
  prevent GCC's merging.
