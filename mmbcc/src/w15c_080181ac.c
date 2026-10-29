/* Wave 15-C: ObjInit_080181AC @ 0x080181ac (old_agbcc). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef signed short s16;
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void Vec2_AddMirrored(u8 *s, u32 x, u32 y);
extern void SetBit16(u8 *s, u8 bit);
extern s16 Text_SelectBlobIdx(u16 idx);
void __attribute__((section(".text.w15c2_080181ac"))) ObjInit_080181AC(u8 *s)
{
    u32 idx;
    int mask;
    u8 *p;
    u32 sh;
    ChipSlot_Setup(s, 543, ((u32)s[17] << 25) >> 24);
    ChipSlot_IncUse(s, 0);
    {
        u16 *p1 = (u16 *)0x081705B0;
        u8 *p2 = (u8 *)0x020031E4;
        idx = (*(u8 *)((((*p1 >> 4) << 1) + (u32)p2))) & 3;
    }
    {
        register int c __asm__("r0");
        __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
        if (c > 3)
            idx = 3;
    }
    p = s;
    p += 0x45;
    sh = idx << 2;
    mask = -13;
    *p = (*p & mask) | sh;
    p -= 0x23;
    {
        u32 z = 0;
        *p = 13;
        *(u32 *)(s + 88) = 0x80 << 2;
        *(u32 *)(s + 96) = z;
        *(u32 *)(s + 92) = (u32)-(int)0x80;
        *(u32 *)(s + 100) = 8;
        Vec2_AddMirrored(s, 0xFFFFD300, 0);
        SetBit16(*(u8 **)(s + 44), 3);
        Text_SelectBlobIdx(0x9F);
    }
}

