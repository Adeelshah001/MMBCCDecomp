/* Sub_0801200C @ 0x0801200C (226 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_0801200c_MATCHED.c (registry: src/w50d_0801200c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_IncUse(u8 *s, u8 idx);

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);

extern void ChipSlot_Tick(u8 *s);

extern short Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w50d_0801200c")))
void Sub_0801200C(u8 *s)
{
    u8 *t = s + 124;
    u8 mode = s[14];
    switch (mode) {
    case 0:
        if (t[0] == t[1] && t[2] == t[3]) {
            ChipSlot_IncUse(s, 0);
            t[4] = mode;
            SetBytes_08011F68(s, 0);
        } else {
            u8 v = t[1];
            u16 r = v | ((s[35] & 15) ? 0x100 : 0);
            ChipSlot_Setup(s, r, t[3]);
            ChipSlot_IncUse(s, 2);
            s[14]++;
        }
        break;
    case 1:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        {
            u8 v = t[0];
            u16 r = v | ((s[35] & 15) ? 0x100 : 0);
            ChipSlot_Setup(s, r, t[2]);
            ChipSlot_IncUse(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[14]++;
        break;
    case 3:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        t[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
