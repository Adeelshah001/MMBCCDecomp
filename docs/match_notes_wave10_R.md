# Wave 10 Worker R — Match Notes (W9 staging blockers)

All three W9 staging blockers cracked. All old_agbcc, 0 diffs, verified in
built ROM via full-extent cmp.

## Matched (3)

### FlagBit_Get_11D34 @ 0x08011D34 (52 B, old_agbcc)

Bitfield get: returns bit (x&7) of byte at `*(u8**)(gEwram02005260+4)+(x>>3)`
for 1<=x<=127, else 0. No push (uses r0-r3 only, bx lr).

ROM prologue: `lsls r2,r0,#16; lsrs r0,r2,#16; adds r3,r0,#0`.

**Blocker was**: compiler fused to `lsrs r3,r2,#16` directly.

**Fix** (from W9-F TableLookup_U16 idiom): pin xr to r0 via decl-init, pin
t to r3, then empty barrier on xr BEFORE the copy:
```c
register u32 xr __asm__("r0") = xs >> 16;
register u32 t __asm__("r3");
__asm__ volatile("" : "+r" (xr));
t = xr;   // -> adds r3,r0,#0
```
The barrier forces xr materialization in r0; the copy becomes a real insn.

Rest: `v >>= bit` is SIGNED (`int v`, `asrs r1,r0`); `(u8)v` then `& 1`.
Pool 0x02005260 via empty-barrier idiom (W9-E). Uses existing
`gEwram02005260` from wave3_d.o.

Staging: `staging/wave10_R/f_8011d34.c` (verified MATCH).
Landed: `mmbcc/src/wave10_R_old.c` (.text.w10r_8011d34).

### FlagBit_Set_11D68 @ 0x08011D68 (72 B, old_agbcc)

Bitfield set/clear: sets bit (x&7) of byte at
`*(u8**)(gEwram02005260+4)+(x>>3)` to (y&1), for 1<=x<=127.

ROM prologue: `lsls r2,r0,#16; lsrs r4,r2,#16; lsls r1,r1,#24; lsrs r5,r1,#24`.

**Blockers were** (W9-D): (1) scheduler emits v-mask before s (ROM order
s,i,v); (2) folds `off=xs>>19` into in-place `lsr r2,r2,#19` (ROM:
`lsrs r1,r2,#19` into different reg).

**Fixes**:
1. Hardcoded-r1 v-mask asm (W9-F idiom) with xr as dummy input for ordering:
   ```c
   __asm__ volatile("lsl r1,r1,#24\n\tlsr %0,r1,#24"
                    : "=r" (v) : "r" (xr) : "r1");
   ```
   The dummy `"r"(xr)` creates a true dependency, preventing the scheduler
   from moving the v-mask before the xs/xr computation. Volatile prevents
   sinking below the cmps.
2. Tied-opaque pool load + explicit asms for hdr/off/base/p:
   ```c
   __asm__ volatile("" : "=r" (hdr) : "0" ((u32)gEwram02005260));  // ldr r0
   __asm__ volatile("lsr %0,%1,#19" : "=r" (off) : "r" (xs));      // lsr r1,r2,#19
   __asm__ volatile("ldr %0,[%1,#4]" : "=r" (base) : "r" (hdr));   // ldr r3,[r0,#4]
   __asm__ volatile("add %0,%1,%2" : "=r" (p) : "r" (base), "r" (off)); // add r3,r3,r1
   ```
3. Volatile `mvn` defeats compiler fusion of `~(1<<bit)` into a later `bic`:
   ```c
   __asm__ volatile("mvn %0,%0" : "+r" (sh));
   ```
4. All mask/val regs pinned (bit=r2, one=r4, sh=r1, vv=r0) via explicit
   register variables as asm operands (bulletproof vs decl-init pin quirks).

**Pitfall found**: pinning two variables to the same register (xs and bit
both r2) with overlapping live ranges confuses the scheduler — it moved
`mov r2,#7` before xs's last use. Solution: declare pins at function scope
but initialize via volatile asm AFTER the earlier variable dies.

Staging: `staging/wave10_R/f_8011d68.c` (verified MATCH).
Landed: `mmbcc/src/wave10_R_old.c` (.text.w10r_8011d68).

### BitCtl_520C @ 0x0800520C (92 B, old_agbcc)

Bit control at `gEwram_02003670+0x11ae` (0x0200481E):
`*(p) = (*(p) & -5) | ((x&1)<<2)`. Then if x==1: `q[0]=q[1]=0` and
`*(q-16) &= 0xc7ff`; else `q[0]=q[1]=0xfff8`. (q = gEwram_020031f0).

**Extent correction**: true extent is **92 B** (0x520c-0x5268), not 84 B.
The wave9/wave10 layers miscounted — the trailing pools at 0x5260/0x5264
(0x020031f0, 0x0000c7ff) belong to this function (referenced by ldr at
0x5248/0x5252). Next function starts at 0x5268.

**Blocker was** (W9-E): "complex 6-pool placement; first part matches but
branch pools land in wrong spots."

**Key finding**: agbcc NATURALLY emits mid-function pools! After the
unconditional `b.n` (0x5236), the compiler places the literal pool
(0x5238-0x5247) before the branch-target code (0x5248). This is standard
gcc behavior, not a quirk. The W9-E worker's issue was elsewhere.

**Fixes**:
1. Copy fusion: ROM does `movs r1,#1; adds r2,r0,#0; ands r2,r1` (not
   `movs r2,#1; ands r2,r0`). Fixed via pinned one (r1) + pinned t2 (r2)
   + empty barrier on t2 before `t2 &= one`.
2. Constant optimization: compiler turned `m=5; m=-m` into `sub r1,r1,#6`
   (reusing r1=1). Fixed via volatile asms:
   ```c
   __asm__ volatile("mov %0,#5" : "=r" (m));
   __asm__ volatile("neg %0,%0" : "+r" (m));
   ```
3. Orr dest: compiler did `orrs r2,r1` (ROM: `orrs r1,r2`). Fixed by
   accumulating in m (r1): `m &= v; m |= t; *p = (u8)m;`

Uses local `.globl`+`.set` for gEwram_02003670 and gEwram_020031f0
(wave4_f.c not in build; no existing symbol for 0x020031f0).

Staging: `staging/wave10_R/t_520c.c` (verified MATCH).
Landed: `mmbcc/src/wave10_R_old.c` (.text.w10r_800520c).

## Blocked revisits — status check

- **Get_25654 / CtrTick5_400A8** (W9-D staging): SUPERSEDED — both matched
  in W9-E (TblGet_25654, Scramble_400A8, src/wave9_e_old.c).
- **W7-F single-idiom blockers** (FlagByte_CopyOrNeg1, BitClear_StructZero,
  U16_FillLoop, MemCopy_U16x4, Bitfield_DecOrSet): ALL MATCHED in W8-U
  (src/wave8_u_old.c).
- **W8-L blockers** (sub_0804D088, sub_080030C4, sub_08042A64/459F8,
  sub_0800BEE0, sub_0804D180): complex whole-function regalloc issues,
  not single-idiom. sub_0800BEE0 (98B bitfield) examined — needs deeper
  work than a fresh-eyes pass; documented for future worker.
- **W9 blockers**: Obj_AddEntry (340B regalloc), ComputeFields (180B, Block 2),
  division routines (C-impossible, need .s), ARM_MixSamples (ARM code),
  Task_3AFFC (926B) — all large/complex, out of scope for this worker.

No additional matches from blocked revisits. The three staging blockers
were the high-value targets.

## New idioms

1. **Barrier-before-copy** (generalizes W9-F): `__asm__ volatile("" : "+r"(src));`
   before `dst = src` with pinned regs forces a real copy insn instead of
   fusion. Works for `lsr`+`add`, `lsl`+`add`, etc.
2. **Dummy input for asm ordering**: adding `"r"(var)` as an unused input to
   a volatile asm creates a true dependency, preventing the scheduler from
   moving the asm before var's computation. (Used for v-mask ordering.)
3. **Volatile mvn/neg defeat fusion**: compiler fuses `~x` into later `bic`,
   and `m=5;m=-m` into `sub`. Volatile asms force the discrete insns.
4. **Mid-function pools are natural**: gcc emits literal pools after
   unconditional branches, before branch-target code. No special handling
   needed — just match the code and the pools follow.
5. **Pin conflict pitfall**: do not pin two variables to the same register
   with overlapping live ranges. Initialize the later pin via volatile asm
   after the earlier variable dies.

## Toolchain note

`arm-none-eabi-as` vanished from /usr/bin mid-task (known VM quirk, 3rd
occurrence). Recovered via `sudo dpkg -i` from /tmp .deb (which had also
vanished, then reappeared). Cached persistent copy at
`~/workspace/binutils-arm-none-eabi_2.42-1ubuntu1+23_amd64.deb` for future
recoveries.
