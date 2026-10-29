/* Wave 9 batch D: leaves-up bulk batch 1 (old_agbcc).
 * 7 functions matched byte-identical. See docs/match_notes_wave9_D.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern u8 rom08172126[];
extern u8 gEwram5160[];
extern u8 gEwram_02004E40[];

__asm__(
    ".globl gEwram_02004E40\n.set gEwram_02004E40, 0x02004E40\n\t"
);

__attribute__((section(".text.w9d_0800800c")))
void ShiftPair_Copy_800C(u8 *o, u8 idx)
{
    u32 a = idx;
    ((u32 *)o)[8] = ((s16 *)o)[0x14] << 8;
    ((u32 *)o)[9] = ((s16 *)o)[0x15] << 8;
    a += (u32)rom08172126;
    o[0x1A] = *(u8 *)a;
}

__asm__(
    ".set rom08172126,0x08172126\n\t"
);

__attribute__((section(".text.w9d_08010508")))
void Ewram5160_Init_10508(u8 v)
{
    u8 *p = gEwram5160;
    u8 z = 0;
    u8 *q;
    p[0] = v;
    v = 0;
    p[2] = z;
    p[1] = z;
    p[3] = z;
    *(u16 *)(p + 6) = z;
    *(u16 *)(p + 4) = z;
    q = p;
    q += 70;
    *(u16 *)q = z;
    p += 72;
    p[0] = v;
}

__asm__(
    ".set gEwram5160,0x02005160\n\t"
);

__attribute__((section(".text.w9d_080258d8")))
u8 CheckPair_258D8(u8 *p, u16 idx)
{
    u32 off = ((u32)idx << 16) >> 14;
    u8 *q;
    off += 20;
    q = p + off;
    if (q[0] == 0)
        return 0;
    if (q[1] == 255)
        return 1;
    return 2;
}

__attribute__((section(".text.w9d_08025638")))
void StoreIdx2_25638(u8 *p, u8 idx, u8 val)
{
    register u8 *q __asm__("r0") = p;
    if (idx > 9)
        goto big;
    q += 2;
    q[idx] = val;
    return;
big: {
    u8 *r = q + idx;
    r[2] = val;
}
}

__attribute__((section(".text.w9d_08025638")))
static const u16 sPad_25638 = 0;

__attribute__((section(".text.w9d_0800b4e4")))
void Ewram4E40_Init_0B4E4(void)
{
    u8 *base = gEwram_02004E40;
    register u8 *p __asm__("r4") = base;
    u16 v;
    s16 i = 0;
    p += 136;
    v = 0x8000;
    do {
        u32 off = (u32)i * 36;
        register u8 *addr __asm__("r0");
        __asm__ volatile("add %0, %1, %2" : "=r" (addr) : "r" (p), "r" (off));
        *(u16 *)addr = v;
        i++;
    } while (i <= 2);
    base[20] |= 4;
}

__asm__(
    ".set gEwram_02004E40,0x02004E40\n\t"
);

__attribute__((section(".text.w9d_08025290")))
u8 Buf_RemoveAt_25290(u8 *p, u16 idx)
{
    u8 *buf;
    u8 *dst;
    u8 *end;
    u8 removed;
    if (idx >= *(u16 *)(p + 6))
        return 255;
    buf = *(u8 **)p;
    dst = buf + idx;
    end = buf + (*(u16 *)(p + 6) - 1);
    removed = *dst;
    while (dst < end) {
        dst[0] = dst[1];
        dst++;
    }
    *dst = 255;
    *(u16 *)(p + 6) = *(u16 *)(p + 6) - 1;
    return removed;
}

__attribute__((section(".text.w9d_08025290")))
static const u16 sPad_25290 = 0;

__attribute__((section(".text.w9d_0802d440")))
u8 Check_2D440(u8 a, u8 b, u8 c)
{
    u8 r = 0;
    if (a != 2 && b == c && b != 0)
        r = 6;
    return r;
}

