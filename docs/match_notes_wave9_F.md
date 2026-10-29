# Wave 9 Worker F (TAG=F) — Blocked Revisits — Match Notes

Worker: Wave 9 blocked-revisits (TAG=F). Date: 2026-10-21.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946` before start.
Toolchain: `mmbcc/tools/agbcc/bin/old_agbcc` (both matches); `arm-none-eabi`
binutils for as/ld/objcopy.
Harness: `staging/wave9_F/mk.sh` (hardened: custom ld script, non-empty
assertions on .o/.elf/.bin/rom.bin, file offset = addr − 0x08000000,
full section extent incl pools/pads, `cmp -l` zero diffs).
Staging: `~/workspace/mmbcc-decomp/staging/wave9_F/`.
Results: `docs/wave9_F_results.tsv`.

**Result: 2 MATCHED, 1 BLOCKED (deferred), 1 superseded, 19-duplicate audit
passed.** Session cut short by arm-none-eabi toolchain outage (vanished from
PATH/disk mid-session; the known VM quirk; had not recovered after ~10 min).
Both MATCHED claims were verified with the hardened harness BEFORE the outage.
Landing files (src/wave9_f_old.c, Makefile, ldscript.ld) are prepared but the
full build could NOT be verified green — coordinator must run `make` when the
toolchain recovers.

## MATCHED (2)

### FlagToggle_080481FC @ 0x080481fc (100B incl 00 00 pad, old_agbcc, 0 diffs)

W6-L4 3-byte near-miss cracked. ROM: flag toggler with bit-test dispatch.
`push {r4,r5,lr}; adds r4,r0,#0; movs r5,#0; ldr r6,[pc]` prologue; mid-function
pool (0x02002F50, 0x46B4, 0x02004CE0); XOR toggle block; three `(g[2]&mask)`
checks; `adds r0,r5,#0` epilogue (int return, no u8 zero-extend).

Idioms used (all new or newly combined):
- **Pinned r4/r5/r6 prologue with volatile-asm sequencing**: `register` pins
  plus `__asm__ volatile("movs %0,#0" : "=r"(ret))` before the tied-opaque
  pool load forces ROM's `movs r5,#0; ldr r6,[pc]` order (scheduler otherwise
  swaps them).
- **Tied-opaque pool loads**: `__asm__ volatile("" : "=r"(o2) : "0"(0x46B4))`
  forces `ldr r2,[pc]` for an arbitrary constant into a pinned register.
  (Generalizes the S `movs %0,#0` idiom to non-zero constants.)
- **XOR block via inline asm** (pre-UAL mnemonics): `movs %0,#1` /
  `ldrb %0,[%1]` (t3 pinned r3) / `eor %0,%1` reproduces ROM's
  `movs r0,#1; ldrb r3,[r1]; eors r0,r3` order (C emits ldrb first).
- **ands-dest inline asm**: `__asm__ volatile("and %0,%1" : "+r"(t) : "r"(gv))`
  forces `ands r0,r1` dest (compiler chose `ands r1,r0` in the final check).
- **Check 3 reuses r1**: ROM has NO `ldrh` before the final `ands` — r1 still
  holds g[2] from check 2. Captured by keeping `c1` live across the if/else.
- **int return**: ROM's `adds r0,r5,#0` (no extend) proves non-u8 return.
- **Trailing pad**: `static const u16` with the section attribute AFTER the
  function emits the `00 00` at 0x804825e (GAS would otherwise fill `c0 46`).

Staging: `staging/wave9_F/w9f_080481fc.c` (verified MATCH).
Landed: `mmbcc/src/wave9_f_old.c` (.text.w9f_0x080481fc).

### TableLookup_U16 @ 0x08011c58 (40B, old_agbcc, 0 diffs)

W7-F/W8-B mask/copy fusion blocker cracked (F's last remaining single-idiom
blocker; the other 6 were cracked in Wave 8). ROM:
```
lsls r0,r0,#24; lsrs r0,r0,#24; adds r3,r0,#0
lsls r1,r1,#24; lsrs r0,r1,#24
cmp r3,#5; bhi ret0; cmp r0,#15; bhi ret0
ldr r2,[pc]; lsls r0,r0,#1; lsls r1,r3,#5; adds r0,r0,r1; adds r0,r0,r2
ldrh r0,[r0]; b end; ret0: movs r0,#0; end: bx lr
```

Idioms used:
- **Let the compiler emit its natural u8→u32 shifts** (`u32 am = (u32)a0` gives
  `lsl r0,r0,#24; lsr r0,r0,#24`); the fusion problem was the COPY, not the
  mask. Pin the copy target: `register u32 ac __asm__("r3"); ac = am;`
  gives `adds r3,r0,#0`. (My redundant inline-asm shifts doubled the shifts —
  removed.)
- **Hardcoded-r1 b-mask asm**: `__asm__ volatile("lsl r1,r1,#24\n\tlsr %0,r1,#24"
  : "=r"(bm) : : "r1")` with bm pinned r0 gives ROM's `lsls r1,r1,#24;
  lsrs r0,r1,#24` (shift from r1 to r0 in one instruction — C cannot express
  the cross-register shift).
- **Goto-chain for dual bhi**: `if (ac>5) goto ret0; if (bm>15) goto ret0;`
  (the `||` form made the compiler invert the second to `bls`).
- **Pinned r2 pool** via tied-opaque: `__asm__ volatile("" : "=r"(tbl) :
  "0"((u16*)0x08173EEC))`.
- **Order + temps**: `bm <<= 1;` before `t = ac<<5` (t pinned r1) gives
  `lsl r0,r0,#1; lsl r1,r3,#5`; `addr = idx + (u32)tbl` temp gives
  `adds r0,r0,r2` (not `adds r2,r2,r0`) and `ldrh r0,[r0]`.

Staging: `staging/wave9_F/w9f_08011c58.c` (verified MATCH).
Landed: `mmbcc/src/wave9_f_old.c` (.text.w9f_0x08011c58).

## BLOCKED / DEFERRED

### Task_3AFFC @ 0x0803affc — retry deferred (toolchain outage)

Per brief, retried "now that more callees have landed". Audit of callee status:
- MATCHED: EntryMgr_Teardown/Setup (wave2), Text_SelectBlobIdx (wave2),
  Sub200@0x08024514 (wave7_g2).
- BLOCKED: sub_0800BEE0 (0x0800bee0).
- NO REGISTRY ROW (unattempted): sub_080241F8, sub_0800B148, sub_08024384,
  sub_0800B368, sub_0800B308.

**None of the 51 Wave-8 matches are Task_3AFFC callees.** Worker A's
"callees-first" recommendation is therefore still unfulfilled: 5 of the 7
unmatched callees have never been attempted, and sub_0800BEE0 remains BLOCKED
(bitfield regalloc). The retry could not be attempted in this session (toolchain
outage before any 3AFFC work began).

Precisely what's missing for a future retry:
1. Match (or at least RE) the 5 unattempted callees so their signatures and
   call-site register behavior are known: 0x080241F8, 0x0800B148, 0x08024384,
   0x0800B368, 0x0800B308.
2. Crack sub_0800BEE0 (W8-L blocker: bitfield at 0x0200404f, needs r4/r5/r6).
3. Then re-attack with real callee declarations. Note the fundamental blocker
   (old_agbcc cross-case if-check merging + tail over-merging across 16 cases,
   best 661/864 diffs) is a control-flow/codegen issue that callee signatures
   may only partially influence (per-call-site register allocation, not the
   merging itself). A genuinely new angle is still needed: candidates are
   per-case opaque asm barriers to defeat cross-case merging, or proving the
   original used a macro with per-site differences.

### ComputeFields @ 0x0804cfd4 — attempt started, toolchain cut it off

W8-XL 180B exact-size near-miss (diffs at byte 100). Started from
`staging/wave8_XL/w8xl_0804cfd4.c`: pinning p→r2 gives the correct prologue
(`push {r4,lr}; adds r2,r1,#0` verified in .s before the outage), but the
body allocation diverged and the toolchain vanished before iteration.
Unverified staging C at `staging/wave9_F/w9f_0804cfd4.c`. The XL notes'
remaining issues stand: ROM reloads p[0] twice (explicit `b = pp[0]` reload +
`adds r3,r1,#0` copy hoisted above the `&4` branch); block-1 load order
(#19 before #18) and `adds r0,r3,#0; muls r0,r1` shapes need targeted work.

### ObjInit_1D3C0 @ 0x0801d3c0 — SUPERSEDED (already landed by W9-A)

Worker A landed this during Wave 9 (src/wave9_f_old.c is NOT needed for it;
it's in src/wave9_a_old.c). A's key idiom — a SINGLE volatile asm emitting
both movs (`__asm__ volatile("movs %0, #1\n\tmovs %1, #0" : "=l"(one),
"=l"(zero))`) — defeats the scheduler's zero-first insistence that blocked
my 4-diff attempt (and B's). My attempt is superseded; not duplicated.

## W8-U DUPLICATE AUDIT — PASSES (19/19)

All 19 claimed duplicates from batch U were verified against
docs/match_status.tsv: each address is present with status MATCHED from an
earlier wave (13× wave8_r, 1× wave8_b, 4× wave7_f/wave7_e, plus the 3 "new"
U claims 0x08004424/0x08004454/0x08025578 which were already MATCHED in
Wave 7 as List_RemoveHead/List_RemoveHead2/FilterCopy). No near-miss
mislabeled; the 9 genuinely-new U matches were the ones landed
(0x08010374/0x08010f88/0x0800c8bc/0x0804a660/0x0800db40/0x0800b6f4/0x0800b2b4/
0x0804b310/0x080110b0). The duplicate claims were honest re-derivations,
not false matches — but they were correctly excluded from the count.

## New idioms discovered (for the catalog)

- **Tied-opaque constant pool load**: `__asm__ volatile("" : "=r"(pinned) :
  "0"(CONST))` forces `ldr <pinned>,[pc]` for any constant (generalizes the
  S `movs %0,#0` idiom). Used for 0x46B4, 0x02002F50, 0x02004CE0, 0x08173EEC.
- **Volatile-asm sequencing for prologue order**: a volatile asm between two
  pinned inits forces emission order (fixes scheduler swaps).
- **Cross-register shift via hardcoded asm**: when ROM does `lsrs r0,r1,#24`
  (shift from one reg to another), C cannot express it; hardcode the source
  reg in the template with the dest as `"=r"` pinned output.
- **Goto-chain to force dual bhi**: `if||` makes the compiler invert the
  second condition to `bls`; explicit gotos keep both as `bhi`.
- **Check-3 r1 reuse**: when ROM omits a reload (reuses a register across a
  branch), keep the C variable live across the if/else instead of reloading.
- **int return proven by missing extend**: `adds r0,r5,#0` with no
  `lsls/lsrs` proves the original returned int, not u8.

## Environment

`arm-none-eabi-as`/`ld`/`objcopy` vanished from PATH and disk mid-session
(~10:55 EDT, during ComputeFields iteration). `mmbcc/tools/agbcc/bin/{agbcc,
old_agbcc}` unaffected. Not recoverable via apt (not dpkg-installed). This is
the known VM quirk from Wave 8 ("recovered on its own"); it had NOT recovered
after ~10 minutes of waiting at session end. All verification in this report
was completed BEFORE the outage. The full-build regression check for the 2
landed functions could NOT be run — coordinator must verify.
