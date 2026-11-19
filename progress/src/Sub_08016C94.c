/* Sub_08016C94 @ 0x08016C94 (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08016c94_MATCHED.c (registry: mmbcc/src/w37c_08016c94_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_IncUse(u8 *s, int idx);

extern u16 Check119_Minus3_Le1(u8 *s);

extern void SetBytes_08011F68(u8 *s, int v);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w37c_08016c94")))
void Sub_08016C94(u8 *s)
{
    u8 *q = s + 124;
    u8 mode = s[14];
    switch (mode) {
    case 0:
        ChipSlot_IncUse(s, 0);
        s[33] = 60;
        s[18] = mode;
        s[14]++;
        break;
    case 1:
        s[18]++;
        if (s[18] <= 19)
            break;
        ChipSlot_IncUse(s, 2);
        s[14]++;
        break;
    case 2:
        if (Check119_Minus3_Le1(s) == 0)
            break;
        ChipSlot_IncUse(s, 0);
        s[10] &= 0xfe;
        s[14]++;
        break;
    case 3:
        s[18]++;
        if (s[18] <= 49)
            break;
        q[4] = 0;
        SetBytes_08011F68(s, 0);
        break;
    default:
        break;
    }
    ChipSlot_Tick(s);
}
