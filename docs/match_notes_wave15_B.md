# Wave 15 Worker B Notes (TAG=B, rows 0–90)

20 MATCHED, 6 BLOCKED. All MATCHED claims verified per hardened protocol
(non-empty asserts at every step, file offset = addr - 0x08000000, full
extents including literal pools, cmp -l zero diffs).

## MATCHED

### 0x08000624 — F_08000624 (10 B, main agbcc)
Trivial wrapper: `F_08002F40();`. 10/10 bytes match; 2-byte GAS 46c0 tail
pad needs fix_tail_align.py at landing.

### 0x08025070 — F_08025070 (28 B, main agbcc)
`u8 F(u16 idx)`: zero-extends idx to r1, loads 0x02007090, adds 24,
calls F_0802663C, truncates to u8.
Decisive: `(const u8 *)&ew02007090 + 24` — pointer arithmetic on a
SYMBOL-derived pointer defeats the +24 constant fold that plagued
numeric-literal versions, producing ROM's `ldr r0,=sym; adds r0,#24`.
28/28 bytes including pool.

### 0x08024EE0 — F_08024EE0 (40 B, old_agbcc)
Entity-array lookup: `base = ew02007090.f20` (+20 struct field),
`idx = *(base + (0xD8<<1))` (0x1B0 via wave14 idiom 8),
`return F_08025790(base + idx*144)`.
Decisive: old_agbcc's register allocation (r1/r2/r3) vs main's (r2/r1/r2).
40/40 bytes including pool.

### 0x08002FD4 — F_0802FD4 (56 B, old_agbcc)
`if (TblValidate_300C(v))`: loads both table pointers up front
(`ldr r2,=0x08106D7C; ldr r0,=0x08106DD0`), computes `h = t2[v].f04`
(8-byte entries), `w = t1[h].f00` (12-byte entries), calls F_0804C84C(w,6).
Decisive: empty `__asm__ volatile("" : "+r"(t1), "+r"(t2))` barrier forces
both pool loads before the arithmetic (defeats load sinking); old_agbcc
allocates t1→r2, t2→r0 exactly as ROM. 56/56 bytes.

### 0x0802478C — F_0802478C (22 B, main agbcc)
`u8 F(u16 idx) { return GetBoundedByte_18((void*)0x02007090, idx); }`.
22/22 bytes.

### 0x080248AC — F_080248AC (20 B, main agbcc)
`void F(u8 v) { SetByte432(ew02007090.f20, v); }`. Struct field gives
`ldr r0,=sym; ldr r0,[r0,#20]`. 20/20 bytes.

### 0x08024648 — F_08024648 (18 B, main agbcc)
`u16 F(u8 x) { return Gt199(x); }` (Gt199 returns u32, implicit
truncation emits lsl/lsr). 18/18 bytes; fix_tail_align at landing.

### 0x0801E87C — F_0801E87C (18 B, main agbcc)
`void F(s16 a, s16 b, u32 *out) { SetDiffSum(a, b, out); }`.
r2 passes through untouched (matches SetDiffSum's 3-param signature).
18/18 bytes; fix_tail_align at landing.

### 0x080247C4 — F_080247C4 (34 B, main agbcc)
`u8 F(u8 idx)`: loads pool (0x02007090) to r0, compares idx>248,
dereferences pool, calls GetMaskedByte, or returns 0.
Decisive: `u8 **pp` + empty-asm barrier forces `ldr r0,=pool` BEFORE
the `cmp/bhi` (compiler otherwise sinks it); `*pp` dereferenced after.
34/34 bytes; mid-section pool; GAS pad truncated at landing.

### 0x0802D5A8 — F_0802D5A8 (44 B, main agbcc)
`void F(s16 delta, u16 *p, u8 idx)`: `*p += delta` (via `int d` temp to
force `asr` sign-extension; compiler's `lsr` zero-extension is valid mod
2^16 but doesn't match), then `lim = TblGet_f00(idx)`, clamp
`if ((s16)*p > (s16)lim` using explicit `s16 cur` local for ROM's
`ldrsh r0,[r4,r2]; cmp r0,r1` allocation.
Decisive: divided-syntax `__asm__("add %0, %1, %0" : "+r"(d) : "r"(pv))`
forces ROM's `adds r0,r1,r0` operand order (C always gives r0,r0,r1).
44/44 bytes.

### 0x08024848 — F_08024848 (42 B, old_agbcc)
Like 08024EE0 but calls CheckPair_258D8 and takes u16 idx param.
old_agbcc for the r1/r2/r3 allocation. 42/42 bytes.

### 0x0802476C — F_0802476C (26 B, main agbcc)
`void F(u8 a, u8 b) { FilterCopy((u8*)0x02007090, a, b); }`. 26/26 bytes.

### 0x08024918 — F_08024918 (34 B, main agbcc)
`u8 F(u8 *p, u8 b, u8 c)`: `lim = *(u16*)(p+18)`; two separate
`if (b >= lim) return 1; if (c >= lim) return 1;` (splitting the `||`
avoids the compiler's `bcc` inversion); else `F_25490(p,b,c); return 0`.
34/34 bytes; fix_tail_align at landing.

### 0x08040078 — F_08040078 (34 B, main agbcc)
`void F(u16 x)`: `w = (x == 0xAE84) ? 0x259E : x`; `*(u16*)(p+8) = w`
where p is a `u8*` VARIABLE (prevents +8 folding into pool, keeps
`strh [r0,#8]`); then 3× `Scramble_400A8()`. 34/34 code bytes.

### 0x080104CC — F_080104CC (38 B, main agbcc)
`u8 F(u8 x)`: `if (*(u8*)0x02005160) return 0; SyncObjFlagBits_BEE0(x,0);
return 1;`. 38/38 bytes; 2B tail pad truncated at landing.

### 0x0804A340 — F_0804A340 (42 B, main agbcc)
`s16 F(void)`: `p = (u16*)0x0200BD10`; `if (p[1]==0) return -1`;
`if (!TblValidate_300C(p[0])) return -1`; `return (s16)p[0]`
(`ldrsh [r4,r1]` indexed form from `(s16)p[0]`). 42/42 bytes; 2B tail
pad truncated at landing.

### 0x0802660C — F_0802660C (48 B, main agbcc)
`u16 F(u8 *p, u16 idx)`: `if (idx==0) return 0x1000` (via
`movs r0,#0x80; lsls r0,#5`); `if (idx >= *(u16*)(p+22)) return 0`;
`return GetBoundedByte_6(p+16, idx) | 0x2000` (via `movs r2,#0x80;
lsls r2,#6`). 48/48 bytes.

### 0x08016E4C — F_08016E4C (54 B, main agbcc)
`void F(u8 *p, u16 v)`: `q = p+124`; `*q = (u8)v` (direct from r1, no
temp); `if ((u8)v > 38) { q[2] = v-39; *q = 39; } else q[2] = 0`;
`q[4] = 1`; `SetBytes_08011F68(p, 2)`. 54/54 bytes; fix_tail_align.

### 0x0801039C — F_0801039C (48 B, main agbcc)
`u8 F(u8 *p, u8 b)`: `bb = b;` as STATEMENT forces early
`lsls/lsrs r5` (register allocation: b→r5, pool→r4); `q = 0x02005160`
with barrier prevents `+66` fold; `if (*q) return 0`;
`Ewram5160_Init_10508(6)`; `*(u8**)(q+48) = p`; `*(q+66) = bb`;
`return 1`. 48/48 bytes.

### 0x08026A48 — F_08026A48 (54 B, main agbcc)
`void F(u8 *p)`: `p[10] = 0`; `k = 0x1734` (pool loaded AFTER strb via
statement placement); `z = 0` shared for strb and first call's r0;
`if (Sram_VerifySlot(z,k)) { u8 v1=1; p[10] = v1|p[10]; }`
(explicit temp forces `movs r0,#1` before `ldrb`); same for bit 1.
54/54 bytes.

## BLOCKED

### 0x080242A8 (220 B) — complex switch, prologue allocation
220-byte switch on `(a>>12)` with 4 cases. Prologue needs
`lsls r0,#16; lsrs r0,#16` (aa in r0, in-place) + `lsls r1,#16`
(bsh kept) + `lsrs r3,r1,#16` (bb). Compiler puts aa in r2 whenever
a u32 bsh variable is live; without bsh, `a>>12` becomes `lsr #28`.
The TblGetU8_26574 call needs r1 = (b<<16) pass-through (no
instruction). Tried: main/old_agbcc, with/without bsh, param
assignment. Best: 147 diffs. Needs deeper work on prologue idiom.

### 0x0804990C (30 B) — register allocation
Needs `ldr r2,=0x020070F0; ldr r3,=0x082344E0` up front, then
`ldrb r0,[r2,#21]; adds r1,r0,#1; strb; lsls/lsrs r0` (re-extension of
v), `adds r0,r3; ldrb`. Barrier forces loads but allocator gives
r0/r1 not r2/r3. The `(u8)v` re-extension is optimized away (compiler
knows r0 is 0..255 from ldrb). Tried: barrier (r0/r1), no barrier
(lazy p2 load), unsigned v. Best: 30 diffs.

### 0x08001C5C (38 B) — register allocation
Loop with 4 vars (base, off, n, p). ROM uses r4/r5/r6/r7 only.
Compiler caches constants 24/4 in r8/r9. Tried: main/old/-O1,
do-while, statement form. Best: 51 diffs (-O1). Needs allocation
control.

### 0x0802538C (46 B) — loop register allocation
Zero-fill loop. ROM: `push {lr}` (no r4!), i in r0 (clobbered by base
load, restored via r1 at loop end), 0-value in r3. Compiler keeps i
in r3 and 0 in r4, using `push {r4,lr}`. The clobber/restore pattern
is key. Tried: do-while, for-loop, main/old. Best: 20 diffs.

### 0x080112CC (46 B) — loop register allocation
Loop calling Entry_IsInactive. ROM keeps i in r1 (0..6), r4 = i<<24,
with clobber/restore. Compiler keeps i<<24 in r4 directly. Tried:
u8/i, do-while. Best: 38 diffs.

### 0x0802FD68 (56 B) — branch layout
Needs `cmp #0; beq L1; cmp #1; beq L2; b End` with L1 falling through
to L2 (no `b`), and v>1 going directly to `b End` (no `movs r0,#0`,
r5=0 returned). My goto version gives `bne`+`b`; if/else gives
`bls`. Best: 18 diffs. Close — needs exact branch idiom.

## New idioms discovered
- Symbol-derived pointer arithmetic defeats constant folding
  (`(u8*)&sym + K` → `ldr; adds`, vs `(u8*)0xADDR + K` which folds).
- Empty-asm barrier on pointer variables forces early pool loads AND
  defeats sinking; old_agbcc's allocator often matches ROM after.
- `bb = b;` as a STATEMENT (not init) forces early lsl/lsr extension
  and influences register allocation (b→r5).
- Shared zero variable (`unsigned z = 0`) reuses r0 across strb and
  call setup.
- Explicit `u8 v1 = 1; p[10] = v1 | p[10];` forces `movs` before `ldrb`
  for `orrs` operand order.
- Divided-syntax `__asm__("add %0, %1, %0")` forces `adds r0,r1,r0`
  when C only gives `adds r0,r0,r1`.
- `int d = delta;` (not `s16`) forces `asr` sign-extension; compiler's
  `lsr` is valid mod 2^16 but doesn't match.
