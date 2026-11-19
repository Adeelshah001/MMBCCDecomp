/* Sub_08011F88 @ 0x08011F88 (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08011f88_MATCHED.c (registry: mmbcc/src/w36c_08011f88_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void Vec2_SetMirrored(u8 *s, u32 a, int b);

extern void ChipSlot_Setup(u8 *s, int a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void Text_SelectBlobIdx(int a);

extern void ChipSlot_Tick(u8 *s);

extern s16 Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, int a);

__attribute__((section(".text.w36c_08011f88")))
void Sub_08011F88(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 0) {
        s[14] = 1;
        Vec2_SetMirrored(s, (int)0xffffc400, 0);
        {
            int t = p[1];
            int u;
            if ((15 & s[35]) != 0)
                u = 256 | t;
            else
                u = t;
            ChipSlot_Setup(s, u, p[3]);
        }
        ChipSlot_IncUse(s, 1);
        Text_SelectBlobIdx(169);
        s[33] = 30;
    }
    ChipSlot_Tick(s);
    if (Check119_Minus3_Le1(s) != 0) {
        ChipSlot_IncUse(s, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
    }
}
