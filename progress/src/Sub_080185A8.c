/* Sub_080185A8 @ 0x080185A8 (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_080185a8_MATCHED.c (registry: mmbcc/src/w37c_080185a8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);

extern void ChipSlot_IncUse(u8 *s, int idx);

extern void Vec2_AddMirrored(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void Vec2_SetMirrored(u8 *o, s32 x, s32 y);

extern void SetBit16(u8 *s, int bit);

extern int Text_SelectBlobIdx(int idx);

__attribute__((section(".text.w37c_080185a8")))
void Sub_080185A8(u8 *s)
{
    u32 out[2];
    register u32 y __asm__("r2");
    u32 z;
    int v;
    ChipSlot_Setup(s, 544, s[17]);
    ChipSlot_IncUse(s, 0);
    {
        u8 *q;
        int tmp;
        int w;
        v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
        w = v;
        __asm__ volatile("" : "+r"(w));
        if (w > 3)
            v = 3;
        q = s + 69;
        {
            int sh = v << 2;
            tmp = (s[69] & -13) | sh;
        }
        *q = tmp;
        __asm__ volatile("" : "+r"(q));
        q -= 35;
        z = 0;
        *q = 13;
    }
    *(u32 *)(s + 88) = 1088;
    *(u32 *)(s + 100) = *(u32 *)(s + 92) = *(u32 *)(s + 96) = z;
    Vec2_AddMirrored(s, -14080, 0);
    sub_0800DD08(out, s);
    {
        s32 x = out[0];
        y = *(volatile u32 *)&out[1];
        y = 0;
        Vec2_SetMirrored(s, x, y);
    }
    SetBit16(*(u8 **)(s + 44), 3);
    Text_SelectBlobIdx(138);
}
