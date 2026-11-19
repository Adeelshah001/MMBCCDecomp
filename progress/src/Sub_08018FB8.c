/* Sub_08018FB8 @ 0x08018FB8 (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08018fb8_MATCHED.c (registry: mmcc/src/w38a_08018fb8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void SetBit16(u8 *s, int bit);

extern u32 *ChipInit_080178A8(int a, int b, int c, int d, u8 *e);

extern u8 GetField17_U8(u8 *p);

extern void MaxAssign_17(u8 *s, int v);

__attribute__((section(".text.w38a_08018fb8")))
int Sub_08018FB8(u8 *s)
{
    u32 out[2];
    int mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    return 0;
gt1:
    if (mode == 2)
        goto c2;
    return 0;
c0:
    if ((u8)(s[119] - 3) > 1)
        return 0;
    {
        register u8 *base __asm__("r0");
        base = (u8 *)0x082265bc;
        __asm__ volatile("" : "+r"(base));
        ChipSlot_IncUse(s, *(base + s[17]));
    }
    s[18] = 45;
    goto tail_inc;
c1:
    if (--s[18] != 0)
        return 0;
    SetBit16(*(u8 **)(s + 44), 3);
    {
        register u8 *base __asm__("r0");
        base = (u8 *)0x082265be;
        __asm__ volatile("" : "+r"(base));
        ChipInit_080178A8(*(base + s[17]), ((u32)s[35] << 28) >> 28, 15360, -1280, *(u8 **)(s + 44));
    }
    {
        /* ROM keeps two separate ANDs (&253 then &254); plain
         * C folds to a single &252, so pin the intermediate
         * with a barrier. */
        int t = 253 & s[10];
        int m = 254;
        __asm__ volatile("" : "+r"(t));
        s[10] = t & m;
    }
    goto tail_inc;
tail_inc:
    s[13]++;
    return 0;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        return 0;
    MaxAssign_17(*(u8 **)(s + 44), 7);
    return 1;
}
