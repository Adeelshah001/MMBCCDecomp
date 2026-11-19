/* Sub_08019BDC @ 0x08019BDC (182 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_08019bdc_MATCHED.c (registry: mmbcc/src/w37c2_08019bdc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;
typedef signed int s32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

extern void Text_SelectBlobIdx(int v);

extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_08019bdc")))
u8 Sub_08019BDC(u8 *s)
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
    goto ret0;
gt1:
    if (mode == 2)
        goto c2;
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    s[18] = 15;
    s[13]++;
    /* fallthrough */
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    ChipInit_080178A8(1, ((u32)s[35] << 28) >> 28, 15360, 0xffffea00, *(u8 **)(s + 44));
    Text_SelectBlobIdx(128);
    s[13]++;
    goto ret0;
c2:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    s[13] = 3;
    goto ret0;
c3:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
