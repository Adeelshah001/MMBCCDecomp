# Wave 11 Worker B — Matching Notes (TAG=B)

Bulk leaves-up, second half. 7/43 matched (all old_agbcc), 10 blocked with
precise diffs, 26 untouched (time-boxed; batch was 43 targets).

## New Idioms

### old_agbcc leaf epilogue
old_agbcc emits pure-leaf `bx lr` for branched leaves; main agbcc emits
`push {lr}` / `pop {rX}` + `bx rX`. All 7 matches in this batch needed
old_agbcc for this reason. If a branched leaf won't match on main agbcc,
try old_agbcc before any source-level contortions.

### s16-param HI-normalized idiom
`lsls r1,r1,#16; lsrs r2,r1,#16` (cross-register: shift in r1, result in r2)
signals an `s16`/`short` param. The per-use extension then varies: signed
uses get `asrs`, unsigned uses get `lsrs`. Same pattern seen at 0x08024022,
0x0802411E, 0x080235A8 (there the shifted value is reused signed). When you
see the cross-register lsl/lsr on entry, declare the param `s16`/`short`.

### Pure-u32 address arithmetic defeats ptr-first canonicalization
For the 26554/265B0/265D0 table family (28-byte entries, base from
`*(ctx+4)`), ROM computes `adds r1, r1, r0` — offset added to base, i.e.
offset-first. Plain C `base + (u16)idx * 28` always canonicalizes to
`adds r1, r0, r1` (base-first) in both compilers. The winning form:
```c
u32 addr = (u32)(u16)idx * 28 + (u32)base;
entry = (u8 *)addr;
```
Keeping the arithmetic in pure `u32` (cast base to u32, never form a
`u8 *` sum) yields the ROM's offset-first `adds`. The `(u16)idx` cast is
load-bearing: without it the multiply keeps a 32-bit idx and the shift
sequence changes.

### Pool-load hoisting vs block-scoped pointers (sub_08001E74)
Declaring a pool-backed pointer (`u8 *p = (u8 *)0x02002F80;`) at function
top lets old_agbcc hoist the `ldr r3, [pc, #off]` above early-exit
branches. ROM loads the pool *after* the first `bhi`. Moving the
declaration into a `{ }` block after the first `if (a > 1) return -1;`
reproduces the post-branch load. C89-friendly (declaration at block start).

### CSE beats explicit temp (sub_08023B88)
`u16 v = str[i]; ... str[i] = v - 1;` forces the compiler to keep `v` in
r0 then `add r1, r0, #0` to copy it. Writing `str[i]` directly at both use
sites lets old_agbcc CSE the two loads into a single `ldrh r1, [r3]` —
exactly ROM. When ROM shows one load feeding two uses, don't introduce a
named temp; repeat the expression and let CSE do it.

### Absolute-symbol pool forcing (reused from wave 10, confirmed here)
`__asm__(".set gVal, 0xFFFF8000"); extern char gVal[];` then `(u32)gVal`
emits `ldr rX, [pc, #off]` / `.word gVal`. Needed when a plain hex constant
gets folded (e.g. `0xFFFF8000` → `0x8000` via `movs`+`lsls`). Used for
sub_08047510's pool (blocked on regalloc, but the pool emission matched).

### negs idiom (reused, confirmed)
`int t = v; ... t &= -7;` forces `movs rX, #7; negs rX, rX; ands`
instead of the compiler folding to `mov rX, #249` / `and`. The `int t`
intermediate is load-bearing — `u8 v; v &= -7;` folds. (sub_08005FC0:
idiom worked, blocked on downstream regalloc.)

### Inverted-if for `bhi` layout (reused, confirmed)
`if (x <= K) { ... } else { work }` written as `if (x > K) return/go-else`
with the fallthrough block inline produces ROM's `bhi` to the out-of-line
work block. Used in the 26554 family (`if ((u16)idx > 127) return ...`).

## Blocked Registry (precise diffs)

- **sub_08026574** (60 B, 52/60): `u8 (void*, s16 idx, u8 sel)` fully
  decoded (entry=base+idx*28; validity byte +25; sel<=9 → entry[2+sel];
  else t=sel-10, (u8)t>1 → 0, else entry[12+t]). 8-byte prologue diff:
  ROM zero-extends idx first then sel; every build variant extends sel
  first or interleaves. Tried ~10 variants (asm barriers, -O1 which gets
  the order right but adds a push, -fno-schedule-insns unsupported).
- **sub_08047510** (40 B): `ldrsb → lsls → adds → pool-add → strh` sequence
  wants the accumulator in r0; builds put it in r1.
- **sub_08010498** (52 B, 39/52): `& -2` via negs idiom allocates r3;
  ROM has r0 (`movs r0,#2; negs r0; ands r0,r1`).
- **sub_0804A884** (40 B): 4-word copy; ROM uses r2,r3,r4 for ldmia/stmia,
  builds pick r4,r5,r6.
- **sub_0804D634** (40 B): `a[28]` ldrh wants r0; builds allocate r4.
- **sub_08023D34** (52 B, 46/52): 6-byte prologue scheduler interleaving
  (`lsl r1` / `add r4,r0,#0` / `lsr r1` order).
- **sub_0804DA34** (72 B): u32-from-4-bytes; param `s` arrives in r1
  (two-arg function); accumulator wants r4, builds give r3.
- **sub_080047EC** (80 B): indexed struct-array writer at 0x02003250
  (idx>47 guard; `*(base+8+idx*4)=a`, `*(base+200+idx)=b`,
  `*(base+248+idx)=c`, `*(u16*)(base+296+idx*2)=0xFFFF`, idx++).
  Base/idx register swap + store-offset folding vs `str [r0]` differences.
  Note: b,c are u32 params (no zero-extend in ROM), not u8.
- **sub_08002E80** (84 B): DISPCNT read-mask-or-writeback + 3×u32 copy from
  0x02003234/38/3C to 0x04000040/44/48. Volatile stack temp for the u16
  accumulator reproduces the `sub sp,#4` frame, but ROM re-materializes
  `mov rX, sp` before each use; builds hoist it once.
- **sub_08005FC0** (78 B): struct init at `0x02004CA0 + (u8)a*32`
  (`p[30]=0`, bit-twiddle on `p[31]`, 12-iteration loop zeroing
  `*(u16*)(p+4+i*2)` and re-setting `p[31]|=1`). negs idiom lands but
  downstream regalloc differs (r0/r1/r2 vs r1/r2/r3).

## Harness Change
`staging/wave11_B/mk.sh` now tolerates ≤2 bytes of section tail-pad
(`0000`/`46c0`/`c046`) via truncation after asserting the overhang is
pad-only; compares exactly SIZE bytes. (Carried over from wave 10's
harness with the pad rule made explicit.)
