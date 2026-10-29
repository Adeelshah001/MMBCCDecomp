# Wave 7 Batch F — Match Notes (TAG=F, worker)

119 leaf functions (40–119 bytes, all n_bl=0). Result: **5 MATCHED, 6 BLOCKED, 108 UNATTEMPTED**.
Baserom SHA-1 verified `72309736f3820470c6f372d6a05ad1f16bc5a946`. All MATCHED claims
verified with hardened harness (non-empty .o/.elf/.bin/rom.bin assertions, file
offset = addr − 0x08000000, full section extent incl. pools/pads, `cmp -l` zero diffs).

Staging: `/tmp/wave7_f/` (`f_<addr>.c` work files, `f_<ADDR>_MATCHED.c` /
`f_<ADDR>_BLOCKED.c` snapshots). Sections `.text.w7f_<addr>`.

## MATCHED (5)

### Gfx_PaletteModeSet @ 0x0800d3a0 (128B incl. pad+pool, main agbcc)
EWRAM 0x02004F80 + IWRAM 0x03002820–22 control-byte writer. Complex bit-packing
with dead-code branches (`if (s>31)`, `if (r3==2)` unreachable but emitted).
Idioms used:
- Pinned registers (`register int lo __asm__("r2")`, `hi`→r1, `v`→r0) to force
  ROM's exact allocation (else compiler swaps lo/hi and folds `v` into r1).
- Inline-asm `lsl %0,%1,#24` (GAS 2.42 needs `lsl` not `lsls` in inline asm) to
  hide the shift from GVN — otherwise compiler CSEs `r4<<24` across blocks and
  spills to r7/ip.
- `u8 *q = base; q += 0x402; *q = t;` reproduces ROM's pool+`adds r2,r2,r1`.
- True extent 128B: 118 code + `00 00` pad + 8 pool (pool aligned to 4).
  Inline pool word overlaps code at 0x800d3b4 (loaded as data by earlier `ldr`).

### Entry_IsInactive @ 0x08010fb4 (40B, old_agbcc)
EWRAM 12-byte entry check: `p[0]==0 && (s8)p[1]==0`. The `(s8)p[1]!=0` is
optimized by the compiler to `ldrb` (sign-ext not observable for `!=0`), so
forced via inline asm: `mov %0,#1; ldrsb %0,[%1,%0]` (Thumb1 ldrsb has no
immediate form). Result kept in `int` to avoid redundant post-ldrsb sign-extend.

### ContextSwitch @ 0x08000300 (40B, old_agbcc)
Coroutine/fiber switch: saves r4–r11/lr, stores lr→[r0], sp→[r1], `mov sp,r2`,
restores new context, `bx lr`. Handwritten asm in original (C cannot express
`mov sp,r2`); reproduced byte-exact via file-scope `__asm__` block.

### List_RemoveHead @ 0x08004424 (48B incl. 00 00 pad, old_agbcc)
Doubly-linked list remove with pointer fixups (offsets 0/4/10/12/16/20/24).
`if (r2 != 0) { ... } return r2;` (not early-return) lets compiler merge the
null return into the tail `adds r0,r2,#0`. Trailing `00 00` gap: emit
`static const u16 pad = 0;` AFTER the function in the same section (before the
function it goes first and misaligns).

### List_RemoveHead2 @ 0x08004454 (48B, old_agbcc)
Sibling of 08004424 using offset-20 field instead of 24; same idioms.

## BLOCKED (6)

### TableLookup_U16 @ 0x08011c58 — mask/copy fusion
ROM: `lsls/lsrs r0` (full u8 mask into r0) then `adds r3,r0,#0`.
Compiler fuses to `lsrs r2,r0,#24` (mask directly into dest). Tried: u8/int
locals, `register __asm__("r3")` pin (breaks entry masking), two-step address,
inline-asm `mov` (re-masks, opaque). Closest: `adds r2,r0,#0` variant — off by
one register (r2 vs r3) plus late table load.

### FlagByte_CopyOrNeg1 @ 0x08010374 — extra mov + in-place modify
ROM v-part: `movs r2,#1; negs r2,r2; adds r0,r2,#0; strb r0,[r1]` (redundant mov);
L1: `adds r0,r2,#0; adds r0,#67` (copy, not in-place). `int v = -1` gives the
negs (u8/s8 fold to `movs #255`), but compiler omits the mov and does
`adds r2,#67` in place. Pinning p→r2 fixes the pool reg but not the copies.

### BitClear_StructZero @ 0x08010f88 — r3-zero dance
ROM: mask in r1, base[3] in r3, then `adds r1,r3,#0; movs r3,#0` (frees r3 for
the zero used by later stores), `adds r2,#24` in place. Compiler will not
produce the dance; pins cause spills (48B vs 40B).

### U16_FillLoop @ 0x0800c8bc — 32-bit i++ idiom
ROM i++: `lsls r0,r3,#16; movs r3,#128; lsls r3,#9; adds r0,r3; lsrs r3,r0,#16;
asrs r0,r0,#16` (adds 0x10000 in 32-bit domain). Compiler does
`adds r0,r3,#1` then shifts. `push {r4,r5,lr}` + `r5=r4` copy matched; only the
increment idiom blocks.

### MemCopy_U16x4 @ 0x0804a660 — value-numbering of base+const
ROM recomputes `base+132/134/136/138` fresh from r3 each time. Compiler
value-numbers `base+132` as `(base+126)+6`, reusing r2 with increments.
Tried: block separation, fresh q1–q4 vars, fresh base reload, volatile,
load-value-first ordering — compiler sees through all of them.

### Bitfield_DecOrSet @ 0x0800db40 — shift-based & 0xF + OR dest
ROM L1: `ldrb r1,[r2,#31]; lsls r0,r1,#28; lsrs r1,r0,#28` (compiler emits
`ands` for `r1 &= 0xF`); final `orrs r0,r1` vs compiler's `orrs r1,r0`.
`*(s8 *)` ldrsb works (value is decremented/stored so sign-ext is observable).

## New idioms found
- **GAS 2.42 inline-asm shifts**: use `lsl`/`lsr`/`asr`/`neg`, NOT `lsls`/`lsrs`/
  `asrs`/`negs` — the `s`-suffixed forms are rejected in inline asm.
- **Pinned-register triple** (`r2`/`r1`/`r0`) for bit-pack computations where
  the allocator swaps operands.
- **Inline-asm `lsl` to defeat GVN CSE** of `x<<24` across basic blocks.
- **Trailing `00 00` pad**: `static const u16 pad = 0;` must be declared AFTER
  the function in the same section.
- **`if (x != 0) {...} return x;`** merges null-return into tail mov (vs early
  `return 0` which emits a separate path).
- **Thumb1 `ldrsb`/`ldrh`-with-offset**: no immediate form — compiler
  materializes index in a register (`movs r0,#1; ldrsb r0,[r1,r0]`); the
  compiler will optimize `(s8)p[i] != 0` to `ldrb` unless the signed value is
  observably used (decrement/store).

## UNATTEMPTED (108)
Listed in `docs/wave7_f_results.tsv` with status UNATTEMPTED. Notable clusters
for future workers: 0x08008628/54/80 (44B, 3 branches, 2 pools each — likely
related), 0x0803fa1c/0x0803fb9c/0x0803fc8c (44–46B, 5–6 branches — dispatchers),
0x0802fbf0/0x0802fcfc (46–108B, 2 pools), EWRAM accessor runs at 0x0800cxxx and
0x08004xxx.
