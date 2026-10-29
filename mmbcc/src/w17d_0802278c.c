/* Worker D wave17 Part1 C1 re-derivation @0x0802278C (72B). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Wrapper_D728(u32 a, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
__attribute__((section(".text.w17d_0802278C")))
void ChipInit_0802278C(u8 *p)
{
    register u32 z __asm__("r5") = 0;
    u8 b;
    *(u32 *)(p + 0x6c) = z;
    b = 2;
    b |= p[10];
    b |= 1;
    p[10] = b;
    Wrapper_D728((u32)p, 0x2e12, 0);
    ChipSlot_IncUse(p, p[17]);
    *(u32 *)(p + 0x50) = 0xf0 << 7;
    *(u32 *)(p + 0x54) = 0xa0 << 7;
    {
        register u8 *q __asm__("r1") = p;
        int m;
        q += 0x45;
        m = -13;
        *q &= m;
    }
    p[0x22] = (u8)z;
}

