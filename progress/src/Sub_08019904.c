/* Sub_08019904 @ 0x08019904 (312 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40b_08019904_MATCHED.c (registry: mmbcc/src/w40b_08019904_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_AddMirrored(u8 *o, int x, int y);

extern void sub_0800DD08(int *d, u8 *s);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern int Text_SelectBlobIdx(int idx);

extern void SetBit16(u8 *s, int bit);

extern void ChipInit_080178A8(int a, int b, int c, int d, u8 *e);

extern int GetField17_U8(u8 *s);

__attribute__((section(".text.w40b_08019904")))
int Sub_08019904(u8 *s)
{
    int buf[2];
    register int x __asm__("r2");
    int y;

    Vec2_AddMirrored(s, *(int *)(s + 88), *(int *)(s + 92));
    *(int *)(s + 88) += *(int *)(s + 96);
    *(int *)(s + 92) += *(int *)(s + 100);
    sub_0800DD08(buf, s);
    x = buf[0];
    y = buf[1];
    __asm__ volatile("" : : "r"(x));
    switch (s[13]) {
    case 0:
        if ((u8)(s[119] - 3) > 1)
            return 0;
        Text_SelectBlobIdx(132);
        *(int *)(s + 100) = 80;
        ChipSlot_IncUse(s, 7);
        __asm__ volatile("" ::: "memory");
        goto tail;
    case 1:
        if (y <= -1280)
            return 0;
        *(int *)(s + 92) = -768;
        ChipSlot_IncUse(s, 7);
        goto tail;
    case 2:
        if (y <= -1280)
            return 0;
        if (*(int *)(s + 92) <= 0)
            return 0;
        *(int *)(s + 92) = 0;
        *(int *)(s + 100) = 0;
        ChipSlot_IncUse(s, s[17]);
        s[18] = 20;
        goto tail;
    case 3:
        s[18]--;
        if (s[18] != 0)
            return 0;
        SetBit16(*(u8 **)(s + 44), 3);
        ChipSlot_IncUse(s, 8);
        s[18] = 15;
        goto tail;
    case 4:
        s[18]--;
        if (s[18] != 0)
            return 0;
        ChipInit_080178A8(0x59, (int)(((u32)s[35] << 28) >> 28), 0x3c00, -2560, *(u8 **)(s + 44));
        s[10] &= 0xfd;
        s[10] &= 0xfe;
        /* fall through to tail (label inside switch, before case 5) */
    tail:
        s[13]++;
        return 0;
    case 5:
        if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
            return 0;
        return 1;
    default:
        return 0;
    }
}
