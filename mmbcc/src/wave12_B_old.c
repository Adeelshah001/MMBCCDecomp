/* Wave 12 batch B: r1/r2/r3 allocation-forcing cluster.
 *
 * Shared trick (docs/match_notes_wave12_B.md): pinned COPY registers.
 * Our compiler puts a fresh lsls/lsrs extension into the next free low
 * register; the ROM vintage reuses the argument register in-place and puts
 * the copy in the fresh register. Pinning the copy (not the primary) with
 * register T x __asm__("rN") occupies that register from the top of the
 * function, forcing the primary in-place - exactly the ROM allocation.
 *
 * B5 (30 B) and B7 (50 B) need the .align 1,0 section fix: the generated
 * .s has its compiler-emitted ".align 2, 0" rewritten to ".align 1, 0" by
 * the Makefile rule, or GAS pads the section with "mov r8, r8".
 * Evidence: docs/match_notes_wave12_B.md.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

__asm__(
".globl gEwram02005260\n.set gEwram02005260, 0x02005260\n"
);

extern u8 gEwram02005260[];

/* TblByte_11DB0 @ 0x08011DB0 (32 B): table byte from *(u8**)(gEwram02005260+8);
 * returns base[c], 0 if idx > 7 or idx == 0. */
__attribute__((section(".text.w12b_08011db0")))
u8 TblByte_11DB0(u16 idx)
{
    u16 a = idx;
    register u16 c __asm__("r1") = a;
    u8 *p;
    u8 *base;
    if (a > 7) goto ret0;
    if (a != 0) goto main;
ret0:
    return 0;
main:
    p = gEwram02005260;
    p += 8;
    base = *(u8 **)p;
    return base[c];
}

/* FlagClear_4D7A0 @ 0x0804D7A0 (30 B): clears flag bytes, sets bit w. */
__attribute__((section(".text.w12b_0804d7a0")))
void FlagClear_4D7A0(u8 *s)
{
    register u8 *p __asm__("r1") = s;
    register u8 z __asm__("r2") = 0;
    register u8 w __asm__("r0");
    asm volatile("" : "+r" (z));
    p[26] = 0;
    p[22] = 0;
    if (p[24] != 0) goto else_;
    w = 12;
    goto join;
else_:
    w = 3;
join:
    p[0] |= w;
}

/* Copy4_2518C @ 0x0802518C (44 B): copies 4 u16s at p+off, off=0x13A4+2k. */
__attribute__((section(".text.w12b_0802518c")))
void Copy4_2518C(u8 *p, u16 *q)
{
    register u32 off __asm__("r3") = 0x13A4;
    q[0] = *(u16 *)(p + off);
    off += 2;
    q[1] = *(u16 *)(p + off);
    off += 2;
    q[2] = *(u16 *)(p + off);
    q[3] = *(u16 *)(p + 0x13AA);
    asm("" : : "r" (off));
}

/* TblPtr_2D8F4 @ 0x0802D8F4 (50 B): table pointer lookup via idx*4. */
__attribute__((section(".text.w12b_0802d8f4")))
u32 TblPtr_2D8F4(u8 *s)
{
    register u8 *p __asm__("r2") = s;
    register u32 t __asm__("r3");
    register u32 idx4 __asm__("r1");
    u32 idx;
    u32 ret;
    if ((p[24] & 2) == 0) {
        t = 393;
        idx = p[t];
        idx4 = idx * 4;
        t -= 29;
    } else {
        idx = p[392];
        idx4 = idx * 4;
        t = 168 * 2;
    }
    ret = *(u32 *)(p + t + idx4);
    asm("" : : "r" (p), "r" (t));
    return ret;
}
