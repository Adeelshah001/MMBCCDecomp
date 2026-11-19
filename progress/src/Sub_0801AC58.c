/* Sub_0801AC58 @ 0x0801AC58 (154 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801ac58_MATCHED.c (registry: mmbcc/src/w37c_0801ac58_MATCHED.c).
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

extern u8 TestBit16(u8 *p, int bit);

extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

__attribute__((section(".text.w37c_0801ac58")))
u8 Sub_0801AC58(u8 *s)
{
    u32 out[2];
    s32 x;
    s32 y;
    u8 t;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
    switch (s[13]) {
    case 0: goto c0;
    case 1: goto c1;
    default: goto ret0;
    }
c0:
    if (x <= 12800)
        goto ret0;
    if (TestBit16(*(u8 **)(s + 44), 0) != 0) {
        s[13] = 1;
        goto ret0;
    }
    ChipInit_080178A8(67, ((u32)s[35] << 28) >> 28, (s16)x, (s16)(y + 1280), *(u8 **)(s + 44));
    t = s[10] & 253;
    t = t & 254;
    s[10] = t;
    return 1;
c1:
    if (x <= 30720)
        goto ret0;
    return 1;
ret0:
    return 0;
}
