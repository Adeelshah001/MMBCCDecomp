/* Sub_0801969C @ 0x0801969C (176 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_0801969c_MATCHED.c (registry: mmbcc/src/w37c2_0801969c_MATCHED.c).
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

extern u8 TestBit16(u8 *p, int bit);

extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_0801969c")))
u8 Sub_0801969C(u8 *s)
{
    u32 out[2];
    u8 t;
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
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
    goto ret0;
c0:
    if (x <= 12800)
        goto ret0;
    ChipInit_080178A8(82, ((u32)s[35] << 28) >> 28, 15360, (s16)y, *(u8 **)(s + 44));
    if (TestBit16(*(u8 **)(s + 44), 0) != 0) {
        s[13] = 1;
        goto ret0;
    }
    t = s[10] & 253;
    t = t & 254;
    s[10] = t;
    goto c1tail;
c1:
    if (x <= 30720)
        goto ret0;
c1tail:
    s[13] = 2;
    goto ret0;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
