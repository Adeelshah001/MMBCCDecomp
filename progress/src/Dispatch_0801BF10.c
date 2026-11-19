/* Dispatch_0801BF10 @ 0x0801BF10 (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26c_0801bf10.c (registry: src/w26c_0801bf10.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u32 *ChipInit_080178A8(u8 a, u8 b, u16 c, u16 d, u8 *e);

void SetBit16(u8 *s, u8 bit);

u8 GetField17_U8(u8 *s);

void ChipSlot_IncUse(u8 *s, u8 idx);

void MaxAssign_17(u8 *s, u8 v);

extern u8 g_08226884[];

__attribute__((section(".text.w26c_0801bf10")))
u8 Dispatch_0801BF10(u8 *s)
{
    switch (s[13]) {
    case 0:
        if ((u8)(s[119] - 3) > 1)
            break;
        {
            u8 t = g_08226884[s[17]];
            ChipInit_080178A8(t, (u8)(((u32)s[35] << 28) >> 28), (u16)(0xF0 << 6), 0, *(u8 **)(s + 44));
            SetBit16(*(u8 **)(s + 44), 3);
            ChipSlot_IncUse(s, 1);
            s[13]++;
        }
        break;
    case 1:
        if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
            ChipSlot_IncUse(s, 2);
            s[13]++;
        }
        break;
    case 2:
        if ((u8)(s[119] - 3) > 1)
            break;
        MaxAssign_17(*(u8 **)(s + 44), 7);
        return 1;
    default:
        break;
    }
    return 0;
}
