# Wave 7 G2 Notes (TAG=G2, 78 functions, leaves-up SMALL <40B, second half)

72 MATCHED, 6 BLOCKED. Harness: `/tmp/wave7_g2/verify.sh` (custom ld script per
function; asserts non-empty .o/.elf/.bin, exact ROM extract size, `cmp -l`).
Sections `.text.w7g2_<addr>`. C in `/tmp/wave7_g2/src/w7g2_<addr>.c`. I do NOT land.

## New idioms found

- **main agbcc emits `push {lr}...pop {r1}; bx r1` for ANY function with a
  conditional branch** (even leafs). old_agbcc uses plain `bx lr`. So nearly
  all branchy small functions need old_agbcc. (Branchless ones match with main.)
- **Goto-ladder for `beq` layout**: `if (v==0) return 1; return 0;` normalizes to
  `bne`. To get ROM's `cmp; beq L1; movs r0,#0; b L2; L1: movs r0,#1`, use the
  explicit ladder: `v=...; if (v==0) goto L1; v=0; goto L2; L1: v=1; L2: return v;`.
  (For `==1` the compiler outsmarts the ladder → make the two `movs` opaque
  via `__asm__ volatile("movs %0,#0/1" : "=r"(v))`.)
- **Opaque `movs` for instruction order**: `__asm__("movs %0, #1" : "=r"(v));`
  pins a `movs` between `ldr` and `ldrb` (ROM often does ldr,movs,ldrb).
- **`if/else` vs goto for branch direction**: `if (*p >= n) goto L;` normalizes
  to `bcc`; the `if { } else { }` form kept ROM's `bcs`.
- **Signed-branch forcing**: u16 params promote to int but the compiler may
  still pick unsigned branches (`bhi`/`bls`) or fold `< K` to `<= K-1`
  (`subs #2`). Fix: `int w = v;` + a `lim` variable (`if (w < lim-1)` keeps
  `subs #1` + `blt`).
- **Pointer compare signedness**: `q >= p` on `u8*` gives `bcs`; ROM had `bge`
  → use `int` for the pointers.
- **Explicit `static const u16 pad = 0;`** in the section when ROM has `00 00`
  after the function but the linker emits `c0 46` (many 14/16/18/22B functions).
  Section must then be exactly code+pad bytes.
- **Dead param shifts allocation**: 08001d88 needed a dummy first param to get
  `ldr r1` / `movs r0,#0` order.
- **Volatile opaque asm as scheduling barrier**: `__asm__ volatile("movs %0,#0"
  : "=r"(z));` pinned `movs r2,#0` before a `strb` (08011f68).
- **Direct indexes let the compiler build its own walking pointer**:
  0804ac48 matched with plain `p[127]=0; p[126]=0; ...` (manual walking
  over-constrained the `adds r1,#1` vs `strb [r1,#1]` folding).
- **`(u)p+(u)s` for `adds r1,r1,r0` operand order** (08025994).
- **Pool placement**: mid-function pools (after `b`) fall out naturally when the
  code shape matches; trailing pools need the section sized exactly.

## Per-function notes (matched)

Trivial clear/set (main agbcc): 08000c9c, 08002e44, 08002ed4 (word/halfword
zero at absolute EWRAM); 08001d88 (dead-param; byte+halfword); 08002e70
(halfword 0 + byte 0xff); 0800e1f0 (explicit zero local for reg order).

Predicates (old_agbcc): 080363d4/08027e44 (`v=1; v&=p[off]` opaque-movs idiom);
08010088×6 identical (`IsZero_02005160`, goto-ladder); 0801109c (`==1`,
ladder+opaque movs); 08016f88 (s+=124, `s[4]==0`); 08016f98 (pool 0x082240b8,
`off=idx*8` before `base+=4`); 080170c4×5 identical (`s[12]>1`, +00 pad);
08021d84 (`mask&=s[19]` idiom, +00 pad).

Arithmetic (old_agbcc): 08011cac (returns &table[idx], not value);
08025324 (`p[idx]&0x7f`); 0803fcc4 (signed range, lim-var); 08040060
(if/else for `bcs`); 080496e8 (`table[a]+b`); 0804aa78/0804ac48/0804a494/0804ad24
(struct clears at 0x0200bd20); 08000e64 (24B task slots at 0x030023c8);
08002e50 (blend regs; pinned r2/r1 + explicit walking); 08004188
(`off=(y<<2)+(x<<7)`); 08004244 (`*(void**)s=pp`, not `*pp`); 08008610
(asymmetric: `s[11]?0x02004aa0:*0x02003674`); 08011f68 (barrier); 08024500 /
08024514 / 08024528 / 0802453c / 08026108 (clamps); 0803fe1c / 0803fe30
(ranges); 0804c5f4 (pinned r3, magic 0x68736d53); 08002a04 (int ptrs, z-first);
08007cdc (`p[7]|=4`); 0800b29c (conditional OR); 0802571c; 08046de4;
0800dcf8/0802365c (identical pointer math, manual stmt order); 080112bc;
08017494/080174a4 (bit ops); 08017464/08017478 (dec/max); 080252e8
(decls-at-top for C89); 08025994; 08026700; 0803fef8 (`(v<<16)==0x02260000`);
08008bb8 (`(x<<24)==0`); 08009640 (`g[620]=0xff`); 080252f8 (`s[0]&0x80`);
0800edfc/0800ee14 (halfword pairs, T-marked but complete).

## BLOCKED (6)

- 08033ab2, 0803da92, 0802c7a4, 0804427c: shared epilogue fragments (no
  prologue; `pop {r3-r5}; mov r8/r9/sl; pop {r4-r7}; pop {r1}; bx r1`).
  Jumped-to tails, not standalone functions.
- 0804dd9c (2B): single `mov pc,lr` padding, not a function.
- 0804be2a (22B): alternate-entry fragment of the function at 0x0804be28
  (which starts with `ldrb r3,[r2,#0]`). `push {r0}`/`pop {r0}` + r3 in/out
  contract not reproducible from C: compilers emit `adds r1,r0,#0` instead of
  push, and extra `cmp` after flag-setting shifts; global-reg-var attempt
  (`register ... __asm__("r3")`) made codegen worse. Likely hand-written asm
  or a different compiler version. Callers: `bl` from 0x0804be18 (script-table
  copy loop) and tail-`b` from 0x0804be4c (script interpreter ~0x0804BE10).
