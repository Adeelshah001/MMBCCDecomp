/* Sub_0801A484 @ 0x0801A484 (226 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_0801a484_MATCHED.c (registry: mmcc/src/w38a_0801a484_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Vec2_AddMirrored(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern u32 *ChipInit_080178A8(int a, int b, int c, int d, int e);

extern u8 GetField17_U8(int v);

__attribute__((section(".text.w38a_0801a484")))
int Sub_0801A484(u8 *s)
{
    int out[2];
    register int o0 __asm__("r1");
    register int o1 __asm__("r2");
    int mode;
    Vec2_AddMirrored(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    o0 = out[0];
    __asm__ volatile("" : "+r"(o0));
    o1 = out[1];
    __asm__ volatile("" : "+r"(o1));
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto ret0;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    if (o1 <= -1280)
        goto ret0;
    ChipInit_080178A8(93, (int)(((u32)s[35] << 28) >> 28), 220 << 6, -3840, *(u32 *)(s + 44));
    *(u32 *)(s + 88) = mode;
    *(u32 *)(s + 92) = mode;
    ChipSlot_IncUse(s, 1);
    goto inc;
c1:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    ChipSlot_IncUse(s, 2);
    s[18] = 30;
    goto inc;
c2:
    if (s[18] & 4)
        s[10] &= 254;
    else
        s[10] |= 1;
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    goto inc;
inc:
    s[13]++;
    goto ret0;
c3:
    if ((u8)GetField17_U8(*(u32 *)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
