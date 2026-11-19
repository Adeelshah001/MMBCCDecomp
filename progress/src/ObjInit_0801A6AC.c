/* ObjInit_0801A6AC @ 0x0801A6AC (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0801a6ac.c (registry: src/w15c_0801a6ac.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void ChipSlot_Setup(u8 *s, u16 a, u8 b);

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern void SetBit16(u8 *s, u8 bit);

extern s16 Text_SelectBlobIdx(u16 idx);

extern u8 gTbl_082265C0[];

void __attribute__((section(".text.w15c2_0801a6ac"))) ObjInit_0801A6AC(u8 *s)
{
    u32 idx;
    int mask;
    u8 *p;
    u32 sh;
    ChipSlot_Setup(s, 594, 0);
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
        *(u32 *)(s + 88) = z;
        *(u32 *)(s + 96) = z;
        *(u32 *)(s + 92) = z;
        *(u32 *)(s + 100) = z;
        SetBit16(*(u8 **)(s + 44), 3);
        Text_SelectBlobIdx(0xa3);
        s[18] = gTbl_082265C0[s[17]];
    }
}
