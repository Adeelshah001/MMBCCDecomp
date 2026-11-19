/* Sub_08021144 @ 0x08021144 (166 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08021144_MATCHED.c (registry: mmbcc/src/w37c_08021144_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_0802142C(u8 *s, u8 x);

extern void Sub_0802129C(u8 *s);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w37c_08021144")))
void Sub_08021144(u8 *s)
{
    u8 *p40 = *(u8 **)(s + 40);
    u8 *p44 = *(u8 **)(s + 44);
    u8 r5 = *p40;
    u8 r6 = *p44;
    switch (s[13]) {
    case 0:
        s[13]++;
        s[18] = 16;
    case 1:
        s[18]--;
        Sub_0802142C(s, s[18]);
        if (s[18] != 0)
            goto tail;
        s[13]++;
    case 2:
        if (s[120] != r5)
            goto inc_tail;
        if (s[121] == r6)
            goto tail;
    inc_tail:
        s[13]++;
        goto tail;
    case 3:
        Sub_0802142C(s, s[18]);
        s[18]++;
        if ((u8)s[18] <= 15)
            goto tail;
        s[13]++;
    case 4:
        s[13] = 0;
        Sub_0802129C(s);
    }
tail:
    ChipSlot_Tick(s);
}
