/* Wave 9 batch E: leaves-up bulk batch 2 (old_agbcc).
 * 5 functions matched byte-identical. See docs/match_notes_wave9_E.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u8 gEwram020070F0[];
extern u8 gEwram02005260[];
extern u8 gEwram_02004E40[];

__attribute__((section(".text.w9e_80400a8")))
u16 Scramble_400A8(void)
{
    register u8 *p __asm__("r2") = gEwram020070F0;
    register u16 h __asm__("r1") = *(u16 *)(p + 8);
    register u32 c __asm__("r3") = 0x8D94;
    register u32 v __asm__("r0") = (u32)h + c;
    register u32 t __asm__("r1") = (v << 2) + v;
    register u32 lo __asm__("r0");
    __asm__ volatile("movs %0, #255" : "=r" (lo));
    lo &= t;
    lo <<= 8;
    t <<= 16;
    __asm__ volatile("" : "+r" (t));
    t >>= 24;
    lo |= t;
    *(u16 *)(p + 8) = (u16)lo;
    return *(u16 *)(p + 8);
}

__attribute__((section(".text.w9e_803fd68")))
u32 Classify_3FD68(u16 x)
{
    u16 xr = x;
    int sxr = xr;
    if (xr == 37)
        goto L1;
    if (sxr > 37)
        goto Lgt;
    if (xr == 18)
        goto L4;
    goto Ldef;
Lgt:
    if (xr == 67)
        goto L5;
    if (xr == 0x2004)
        goto L4;
    goto Ldef;
L1:
    return 1;
L4:
    return 4;
L5:
    return 5;
Ldef:
    return xr >> 12;
}

__attribute__((section(".text.w9e_8025654")))
u8 TblGet_25654(u8 *base, u8 idx)
{
    u8 *p;
    u8 x = idx;
    if (x > 9)
        goto L1;
    p = base + 2;
    goto L2;
L1:
    if (x > 11)
        return 0;
    x = x - 10;
    p = base + 12;
L2:
    p += x;
    return *p;
}

__attribute__((section(".text.w9e_8011dd0")))
void TblSet_11DD0(u16 x, u8 y)
{
    u32 xr = x;
    u32 hdr;
    u8 *base;
    if (xr > 7)
        return;
    if (xr == 0)
        return;
    hdr = (u32)gEwram02005260;
    __asm__ volatile("" : "+r" (hdr));
    base = *(u8 **)(hdr + 8);
    base[xr] = y;
}

__attribute__((section(".text.w9e_800b308")))
u32 Check_B308(void)
{
    u8 v = gEwram_02004E40[4];
    if ((v & 15) == 0)
        return 1;
    return 0;
}
