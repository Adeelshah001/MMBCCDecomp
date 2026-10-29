/* Wave 15-C: ObjInit_08018E1C @ 0x08018e1c (old_agbcc). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
typedef signed short s16;
extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void Vec2_AddMirrored(u8 *s, u32 x, u32 y);
extern void SetBit16(u8 *s, u8 bit);
extern s16 Text_SelectBlobIdx(u16 idx);
void __attribute__((section(".text.w15c2_08018e1c"))) ObjInit_08018e1c(u8 *s)
{
    u32 idx;
    int mask;
    u8 *p;
    u32 sh;
    ChipSlot_Setup(s, 553, s[17]);
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
        *(u32 *)(s + 88) = 0x80 << 3;
        *(u32 *)(s + 96) = 10;
        *(u32 *)(s + 92) = z;
        *(u32 *)(s + 100) = z;
        Vec2_AddMirrored(s, 0xFFFFD200, 0xFFFFFB00);
        SetBit16(*(u8 **)(s + 44), 3);
        Text_SelectBlobIdx(0x8D);
    }
}

