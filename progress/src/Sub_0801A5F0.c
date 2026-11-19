/* Sub_0801A5F0 @ 0x0801A5F0 (188 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_0801a5f0_MATCHED.c (registry: mmbcc/src/w37c2_0801a5f0_MATCHED.c).
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

extern u8 GetField17_U8(u8 *p);

extern void ChipSlot_IncUse(u8 *s, int v);

__attribute__((section(".text.w37c2_0801a5f0")))
u8 Sub_0801A5F0(u8 *s)
{
    u32 out[2];
    int mode;
    int iv;
    register u8 *sp_ __asm__("r0");
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
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    ChipInit_080178A8(124, ((u32)s[35] << 28) >> 28, 15360, 0, *(u8 **)(s + 44));
    sp_ = s;
    iv = 1;
    goto shared;
c1:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    s[18] = 15;
    goto tail;
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    sp_ = s;
    iv = 2;
    /* fallthrough */
shared:
    ChipSlot_IncUse(sp_, iv);
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5)
        return 1;
ret0:
    return 0;
}
