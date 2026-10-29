/* MMBCCDecomp — Wave 10 worker R.
 * W9 staging blockers (fresh-eyes candidates).
 *
 * MATCHED (all old_agbcc, 0 diffs):
 * - FlagBit_Get_11D34 @ 0x08011D34 (52 B): bitfield get from gEwram02005260.
 * - FlagBit_Set_11D68 @ 0x08011D68 (72 B): bitfield set/clear.
 * - BitCtl_520C @ 0x0800520C (92 B): bit control at 0x0200481E + hword init.
 *
 * Evidence: docs/match_notes_wave10_R.md.
 * Verification: staging/wave10_R/ via mk.sh harness (hardened: non-empty
 * assertions, file offset = addr - 0x08000000, full extents incl pools,
 * cmp -l zero diffs).
 *
 * Key idioms:
 * - Empty barrier on pinned source before pinned copy forces
 *   `lsr r0,r2,#16; add r3,r0,#0` (defeats mask/copy fusion).
 * - Hardcoded-r1 cross-register shift asm for y-mask (W9-F idiom).
 * - Tied-opaque pool loads for exact ldr ordering.
 * - Volatile asm for mvn/neg to defeat compiler fusion (bic/sub).
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 gEwram02005260[];

__asm__(
    ".globl gEwram_02003670\n.set gEwram_02003670, 0x02003670\n"
    ".globl gEwram_020031f0\n.set gEwram_020031f0, 0x020031f0\n"
);

extern u8 gEwram_02003670[];
extern u8 gEwram_020031f0[];

/* FlagBit_Get_11D34 @ 0x08011D34 (52 B).
 * Returns bit (x&7) of byte at *(u8**)(gEwram02005260+4) + (x>>3),
 * for 1 <= x <= 127; else 0.
 * Idiom: empty barrier on xr before t=xr forces the lsr+add copy. */
__attribute__((section(".text.w10r_8011d34")))
u32 FlagBit_Get_11D34(u16 x)
{
    register u32 xs __asm__("r2") = (u32)x << 16;
    register u32 xr __asm__("r0") = xs >> 16;
    register u32 t __asm__("r3");
    u32 hdr;
    u32 off;
    u8 *base;
    u8 *p;
    u32 bit;
    int v;
    u8 vb;

    __asm__ volatile("" : "+r" (xr));
    t = xr;
    if (t == 0)
        goto Lret0;
    if (t > 127)
        goto Lret0;
    hdr = (u32)gEwram02005260;
    __asm__ volatile("" : "+r" (hdr));
    off = xs >> 19;
    base = *(u8 **)(hdr + 4);
    p = base + off;
    bit = t & 7;
    v = *p;
    v >>= bit;
    vb = (u8)v;
    return vb & 1;
Lret0:
    return 0;
}

/* FlagBit_Set_11D68 @ 0x08011D68 (72 B).
 * Sets/clears bit (x&7) of byte at *(u8**)(gEwram02005260+4) + (x>>3)
 * to (y&1), for 1 <= x <= 127.
 * Idioms: hardcoded-r1 v-mask asm (ordered via xr dummy input);
 * tied-opaque pool load + explicit lsr/ldr/add asms for hdr/off/base/p;
 * volatile mvn defeats ~ fusion into bic. */
__attribute__((section(".text.w10r_8011d68")))
void FlagBit_Set_11D68(u16 x, u8 y)
{
    register u32 xs __asm__("r2") = (u32)x << 16;
    register u16 xr __asm__("r4") = (u16)(xs >> 16);
    register u8 v __asm__("r5");
    register u32 hdr __asm__("r0");
    register u32 off __asm__("r1");
    register u8 *base __asm__("r3");
    register u8 *p __asm__("r3");
    register u32 bit __asm__("r2");
    register u32 one __asm__("r4");
    register u32 sh __asm__("r1");
    register u8 vv __asm__("r0");
    u8 mask;
    u8 val;

    __asm__ volatile("lsl r1,r1,#24\n\tlsr %0,r1,#24"
                     : "=r" (v) : "r" (xr) : "r1");
    if (xr == 0)
        goto Lend;
    if (xr > 127)
        goto Lend;
    __asm__ volatile("" : "=r" (hdr) : "0" ((u32)gEwram02005260));
    __asm__ volatile("lsr %0,%1,#19" : "=r" (off) : "r" (xs));
    __asm__ volatile("ldr %0,[%1,#4]" : "=r" (base) : "r" (hdr));
    __asm__ volatile("add %0,%1,%2" : "=r" (p) : "r" (base), "r" (off));
    __asm__ volatile("mov %0,#7" : "=r" (bit));
    __asm__ volatile("and %0,%1" : "+r" (bit) : "r" (xr));
    __asm__ volatile("mov %0,#1" : "=r" (one));
    __asm__ volatile("add %0,%1,#0" : "=r" (sh) : "r" (one));
    __asm__ volatile("lsl %0,%1" : "+r" (sh) : "r" (bit));
    __asm__ volatile("mvn %0,%0" : "+r" (sh));
    mask = (u8)sh;
    __asm__ volatile("add %0,%1,#0" : "=r" (vv) : "r" (v));
    __asm__ volatile("and %0,%1" : "+r" (vv) : "r" (one));
    __asm__ volatile("lsl %0,%1" : "+r" (vv) : "r" (bit));
    val = (u8)vv;
    mask &= *p;
    *p = (u8)(val | mask);
Lend:;
}

/* BitCtl_520C @ 0x0800520C (92 B).
 * Bit manipulation at gEwram_02003670+0x11ae, then hword init at
 * gEwram_020031f0 (0xfff8/0xfff8 if x!=1, else 0/0 and clear bit 0x3800
 * at gEwram_020031f0-16).
 * Idioms: pinned one/t2 with barrier defeats copy fusion; volatile
 * mov/neg defeats sub optimization; accumulate in m (r1) for orr dest. */
__attribute__((section(".text.w10r_800520c")))
void BitCtl_520C(u32 x)
{
    u32 base = (u32)gEwram_02003670;
    u8 *p;
    u8 v;
    register int m __asm__("r1");
    u32 t;
    __asm__ volatile("" : "+r" (base));
    p = (u8 *)(base + 0x11ae);
    {
        register u32 one __asm__("r1") = 1;
        register u32 t2 __asm__("r2") = x;
        __asm__ volatile("" : "+r" (t2));
        t2 &= one;
        t2 <<= 2;
        t = t2;
    }
    __asm__ volatile("mov %0,#5" : "=r" (m));
    __asm__ volatile("neg %0,%0" : "+r" (m));
    v = *p;
    m &= v;
    m |= t;
    *p = (u8)m;
    if (x == 1)
        goto L1;
    {
        u16 *q = (u16 *)gEwram_020031f0;
        q[0] = 0xfff8;
        q[1] = 0xfff8;
    }
    goto Lend;
L1:
    {
        u16 *q = (u16 *)gEwram_020031f0;
        q[0] = 0;
        q[1] = 0;
        {
            u16 *r = (u16 *)((u32)gEwram_020031f0 - 16);
            u16 w = *r;
            w &= 0xc7ff;
            *r = w;
        }
    }
Lend:;
}
