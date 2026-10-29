# Wave 26-D Match Notes (Worker D, bulk leaves-up)

## MATCHED

### 0x08016efc — ObjInit_08016EFC (120 B, old_agbcc, 0 diffs)
6-param object initializer. Sets `p[44]=s`, calls `IncU8_12(s)`, reads an s16
pair from table `0x08223ED8` indexed by `p[124]`, calls unmatched
`sub_080174CC(s, v1, v2)` (.set at 0x080174cc), then `p[16]=a; p[17]=b;
SetBytes_08011F68(p,4); p[128]=1; *(u16*)(p+132)=e; p[131]=f`.

Idioms:
- **Natural ldrsh from C works.** The brief's "agbcc NEVER emits ldrsh" claim is
  wrong for the `s16 v = tbl[i]` pattern — both agbcc variants emit
  `ldrsh rX,[rY,rZ]` from plain C (verified by minimal test). The w25d inline-asm
  was unnecessary here.
- **Split pool-load statement.** `s16 *base = g_08223ed8; s16 *tbl = base +
  (sl[0]*2);` forces the `ldr r1,[pc]` (pool) BEFORE the `ldrb/lsls`, matching
  ROM's order. A single expression lets gcc schedule the ldrb first.
- old_agbcc nailed the prologue/param allocation (s→r9, e→sl, f→r7); main agbcc
  permuted them.
- Staged: `staging/wave26_D/w26d_08016efc.c`.

### 0x0800d1e0 — NodeInitSwitch_0800D1E0 (152 B, old_agbcc, 0 diffs)
4-pointer switch state machine. Loads `*p2→r9, *p3→sl, *p1→r4(v1)`, `ret=1`,
`v16=p0[6]`. Switch on v1: case 0 sets v1=1 and falls into case 1; case 1 does a
table lookup (`0x08173530+1+v16*2`), `NodeInit_0802260C`, stores node at
`p0+12`, bumps v1, clears bit 2 of `p0[9]`, falls into case 2; case 2 checks
`Byte12_Gt1(*(p0+12))`, calls `BitCtl_520C(1)`, sets ret=0. Epilogue restores
`*p2, *p3, *p1`, returns ret.

Idioms:
- **Opaque `+r` barrier forces runtime negs.** `p0[9] &= ~4` folds to
  `movs r0,#251`; ROM has `movs r0,#5; negs r0,r0`. Fix:
  `int five = 5; __asm__ volatile("" : "+r"(five)); p0[9] &= -five;`
- **`base++` defeats pool+1 folding.** `*(g_08173530+1+v16*2)` folds the +1 into
  the pool word (0x08173531); ROM keeps pool=0x08173530 and does `adds r0,#1`.
  Using `u8 *base=g_...; int off=v16*2; base++; ...*(base+off)` reproduces it.
- old_agbcc reproduced the branch-tree switch (`beq/bgt/beq`); main agbcc did
  not (wrong size, 148 vs 152).
- Staged: `staging/wave26_D/w26d_0800d1e0.c`.

## BLOCKED (attempted)

### 0x080224e4 / 0x08021b3c — BlendCopy (206 B, ~40 diffs best)
Identical twins (only the `bl Memcpy16` encoding differs). 15-bit color
blender: `dst = 0x03002620 + (idx<<5)`; if blend==0 → `Memcpy16(srcA,dst,32)`;
elif blend>14 → `Memcpy16(srcB,dst,32)`; else 16-iteration loop blending
`srcB` toward `srcA` per channel: `c = b + (u8)(((a-b)*blend)>>4)`, packed as
`c0 | (c1<<5) | (c2<<10)` via the `<<24>>19` / `<<24>>14` shift trick (the
unmasked shifts are intentional — ROM does NOT mask c1/c2 after add).

Progress: branch structure matched (`bls` to complex via goto), loop body ~95%
matched (mask, shifts, `negs` for -1 loop decrement, `strh`+pointer bumps).
**Wall: register allocation rotation.** gcc insists on
srcA→r9, srcB→r8, mask→ip; ROM has srcA→r8, srcB→ip, mask→r9. Tried: explicit
gotos, u32 register pins (broke prologue), cross-jump hypothesis (gcc didn't
merge), -O1/-Os, reordering. The `s0>>24 | s1>>19 | s2>>14` formulation and
increments-before-store both verified correct in isolation.

Staged attempts: `staging/wave26_D/w26d_080224e4.c` (draft 5).

### 0x08010e00 — NodeAlloc (122 B, ~100 diffs best)
Bitflag-gated node allocator: checks `pool[4]==1` (pool=0x020051B0),
`if ((pool[3]>>a)&1) return 0`, sets bit, `p = pool+24+a*12`,
`NewNode_0801DFC4(a,(s8)c,(s8)d)`, stores c/d/e, returns 1.

Progress: old_agbcc got the 2-reg push and `ldr r4,[sp,#28]` right; **forced
the dead param-b extension** with `__asm__ volatile("" : "+r"(b))` (b is
extended but never used — the asm materializes it).
**Wall:** a→r0 vs ROM a→r6; c→r7/d→r6 vs ROM c→r8/d→r7. Tried explicit u8
copies, `int aa=a`, u32 pins (broke everything). The extra live variable
forces sl usage and a 3-reg second push.

### 0x0800909c — TblFill (164 B, 143 diffs)
6-param nested table fill using FlagA_8654/GetPtr_08008610. True extent 164 B
(layer tsv said 158 — pool at 0x800913c was cut off). Did not get close;
deferred.

### 0x0801d598 — StateTick (192 B, 185 diffs)
State-machine tick with ldrsh tables and `sub_0800D9EC` call. Too many live
variables for clean allocation; deferred.

### 0x080291ec — TblBuild (196 B)
Dual-loop table builder with Scramble_400A8 and ldrsh. First draft codegen
diverged significantly; deferred.

### 0x0800571c — SysInit (224 B)
Large EWRAM init (8 pools). Pool placement diverges; deferred.

## BLOCKED (not attempted — time)
0x08002a1c, 0x080046b0, 0x0803ac4c, 0x080096bc, 0x08006fe8, 0x08024a30,
0x08034f2c, 0x08007840, 0x080176ac, 0x08025ec8, 0x08009c7c, 0x080099fc,
0x080471d8, 0x08008bc8, 0x08046df8 (callee 0x08006a54 = Gfx_BlitRequest MATCHED;
no rect-fill block).

## Tooling notes
- `staging/wave26_D/verify.sh` — hardened harness (custom .ld keeping section
  name, unquoted `-j`, non-empty asserts, file-offset dd, truncation to SIZE).
  Fixed two harness bugs during the wave: .ld renamed output section (matched
  nothing), and bin>SIZE padding (now truncated before cmp).
- Minimal test disproved "agbcc never emits ldrsh" for `s16 tbl[i]` — both
  compilers emit it. (The w25d claim may have been about ldrsb or a different
  pattern; ldrsb was not re-tested.)
- Registry check: all 24 addresses free in match_status.tsv before starting.
- Leave-alone list respected; rect-fill family untouched.
- Staging dir `staging/wave26_D/` left intact with .c drafts and disasm dumps.
