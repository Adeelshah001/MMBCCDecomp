/* Wave 7 batch C (2 matched, coordinator-verified, old_agbcc).
   Evidence: docs/match_notes_wave7_c.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

/* 0x08021594: ObjInit_TypeC (148B, coordinator-verified). */
/* Wave 7 TAG=C. ObjInit_TypeC @ 0x08021594 (148 B). Tentative. v3: corrected
 * addresses (ldrh from 0x081705B0, +0x020031E4); mask as int var; literal
 * base for the 0x11AE access to avoid pool CSE. */

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
extern u8 gEwram_02003670[];

__attribute__((section(".text.w7c_08021594")))
void ObjInit_TypeC(u8 *s)
{
    u8 t;
    u32 idx;
    int mask = -13;
    u8 *p;
    u32 sh;
    register int c __asm__("r0");

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    ChipSlot_Setup(s, 0xB0 << 5, 0);
    ChipSlot_IncUse(s, 0);
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
    if (c > 3)
        idx = 3;
    p = s;
    p += 0x45;
    sh = idx << 2;
    *p = (*p & mask) | sh;
    {
        u8 *p = s;
        p += 0x22;
        {
            u8 four = 4;
            *p = four;
            *(u32 *)(s + 0x50) = (gEwram_02003670[0x11AE] & four) ? 0x7800 : 0x7000;
        }
    }
    *(u32 *)(s + 0x54) = 0xA0 << 6;
    {
        u8 z;
        __asm__("movs %0, #0" : "=r"(z));
        s[0x12] = z;
    }
}

__asm__(
".globl gEwram_02003670\n"
".set gEwram_02003670, 0x02003670\n"
".thumb_func\n"
".thumb_func\n"
);

/* 0x0802184c: ObjInit_2184C (164B, coordinator-verified). */
/* Wave 7 TAG=C. ObjInit_2184C @ 0x0802184c (164 B). Tentative. v3: scoped vars. */

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];

__attribute__((section(".text.w7c_0802184c")))
void ObjInit_2184C(u8 *s)
{
    u8 t;
    u32 idx;
    int mask = -13;
    u8 *p;
    u32 sh;
    register int c __asm__("r0");

    *(u32 *)(s + 108) = 0;
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    {
        u16 *tbl = (u16 *)0x08227028;
        __asm__ volatile("" : "+r"(tbl));
        ChipSlot_Setup(s, tbl[s[17]], 0);
    }
    {
        u8 *tbl = (u8 *)0x08227020;
        __asm__ volatile("" : "+r"(tbl));
        ChipSlot_IncUse(s, tbl[s[17]]);
    }
    idx = *(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4)) & 3;
    __asm__("movs %0, %1" : "=r"(c) : "r"(idx));
    if (c > 3)
        idx = 3;
    p = s;
    p += 0x45;
    sh = idx << 2;
    *p = (*p & mask) | sh;
    {
        register u8 z __asm__("r2");
        u8 *p = s;
        s16 *q;
        p += 0x22;
        __asm__("movs %0, #0" : "=r"(z));
        *p = z;
        {
            u8 *tbl = (u8 *)0x08227036;
            q = (s16 *)(tbl + (s[17] << 2));
            *(u32 *)(s + 0x50) = q[0] << 8;
            {
                u8 idx = s[17];
                u32 off = idx << 2;
                tbl += 2;
                q = (s16 *)(tbl + off);
                *(u32 *)(s + 0x54) = q[0] << 8;
            }
        }
        s[0x12] = z;
    }
}

__asm__(
".thumb_func\n"
".thumb_func\n"
);
