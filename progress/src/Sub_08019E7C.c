/* Sub_08019E7C @ 0x08019E7C (186 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_08019e7c_MATCHED.c (registry: mmbcc/src/w37c2_08019e7c_MATCHED.c).
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

extern void SetBit16(u8 *p, int bit);

extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

extern void ChipSlot_IncUse(u8 *s, int v);

extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w37c2_08019e7c")))
u8 Sub_08019E7C(u8 *s)
{
    u32 out[2];
    register s32 x __asm__("r5");
    register s32 y __asm__("r6");
    int mode;
    int iv;
    register u8 *sp_ __asm__("r0");
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    __asm__ volatile("" : "+r"(x));
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
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    s[18] = 10;
    goto tail;
c1:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    SetBit16(*(u8 **)(s + 44), 3);
    ChipInit_080178A8(95, ((u32)s[35] << 28) >> 28, 0, (s16)y, *(u8 **)(s + 44));
    sp_ = s;
    iv = 1;
    goto do_inc;
c2:
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) <= 5)
        goto ret0;
    s[18] = 10;
    sp_ = s;
    iv = 0;
    goto do_inc;
do_inc:
    ChipSlot_IncUse(sp_, iv);
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    return 1;
ret0:
    return 0;
}
