/* Wave 6 BLK-A batch (coordinator-verified).
   Evidence: docs/match_notes_wave6_blkA.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08017D50: sub_08017D50 (coordinator-verified). */
extern void ChipSlot_Setup(u8 *s, u32 a, u32 b);
extern void ChipSlot_IncUse(u8 *s, u32 idx);
extern void Vec2_AddMirrored(u8 *s, u32 x, u32 y);

__attribute__((section(".text.w6a_17d50")))
void sub_08017D50(u8 *s) {
    ChipSlot_Setup(s, 0x21b, 0);
    ChipSlot_IncUse(s, 0);
    {
        u16 v = *(u16 *)0x081705b0;
        u32 t = v;
        u8 *tab;
        register u32 idx __asm__("r1");
        register int c __asm__("r0");
        u32 b;
        int mask;
        u8 *p;
        u32 sh;
        u32 z;
        u32 y;
        t >>= 4;
        t <<= 1;
        tab = (u8 *)(0x020031e4 + t);
        __asm__("movs %0,#3" : "=r" (idx));
        b = *tab;
        __asm__("and %0,%1" : "+r" (idx) : "r" (b));
        __asm__("movs %0,%1" : "=r" (c) : "r" (idx));
        if (c > 3)
            __asm__("movs %0,#3" : "=r" (idx));

        p = s;
        p += 0x45;
        sh = idx << 2;
        mask = -13;
        *p = (*p & mask) | sh;
        p -= 0x23;
        z = 0;
        *p = 13;
        *(u32 *)(s + 0x58) = (0x80 << 3);
        *(u32 *)(s + 0x60) = z;
        *(u32 *)(s + 0x5c) = (0x80 << 3);
        *(u32 *)(s + 0x64) = 0x80;
        y = 0xffffd400;
        Vec2_AddMirrored(s, z, y);
    }
}
