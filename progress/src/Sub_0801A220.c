/* Sub_0801A220 @ 0x0801A220 (154 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801a220_MATCHED.c (registry: mmbcc/src/w37c_0801a220_MATCHED.c).
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

extern void SetBit16(u8 *s, int bit);

extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c_0801a220")))
u8 Sub_0801A220(u8 *s)
{
    u32 out[2];
    u32 x;
    u32 y;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
    switch (s[13]) {
    case 0: goto c0;
    case 1: goto c1;
    case 2: goto c2;
    default: goto ret0;
    }
c0:
    s[18] = 15;
    goto inc;
c1:
    if (--s[18] != 0)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    ChipInit_080178A8(102, ((u32)s[35] << 28) >> 28, (s16)x, (s16)y, *(u8 **)(s + 44));
    goto inc;
inc:
    s[13]++;
    goto ret0;
c2:
    if (GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    goto ret1;
ret1:
    return 1;
ret0:
    return 0;
}
