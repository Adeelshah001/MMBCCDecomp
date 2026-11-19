/* F_08018398 @ 0x08018398 (220 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w43c_08018398_MATCHED.c (registry: mmbcc/src/w43c_08018398_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(s32 *out, u8 *o);

extern void ChipInit_080178A8(s32 a, s32 b, s32 c, s32 d, u32 e);

extern u8 GetField17_U8(u8 *p);

__attribute__((section(".text.w43c_08018398")))
int F_08018398(u8 *s)
{
    s32 out[2];
    register s32 x __asm__("r2");
    register s32 y __asm__("r3");
    register s32 max __asm__("r5");
    Vec2_AddMirrored(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    x = out[0];
    y = *(volatile s32 *)&out[1];
    (void)y;
    switch (s[13]) {
    case 0: {
        max = 240 << 6;
        if (x <= max)
            return 0;
        ChipInit_080178A8(92, ((u32)s[35] << 28) >> 28, max, -5120, *(u32 *)(s + 44));
        *(s32 *)(s + 96) = -1536;
        goto adv;
    }
    case 1:
        if (*(s32 *)(s + 88) > 0)
            return 0;
        *(s32 *)(s + 96) = 0;
        s[18] = 12;
        goto adv;
    case 2:
        if (--s[18] != 0)
            return 0;
        *(s32 *)(s + 88) = -1536;
        goto adv;
    case 3:
        if (x >= -11520)
            return 0;
        *(s32 *)(s + 88) = 0;
    adv:
        s[13]++;
        break;
    case 4:
        if (GetField17_U8(*(u8 **)(s + 44)) > 5)
            return 1;
        return 0;
    default:
        return 0;
    }
    return 0;
}
