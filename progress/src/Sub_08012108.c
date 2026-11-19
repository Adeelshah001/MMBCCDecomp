/* Sub_08012108 @ 0x08012108 (136 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08012108_MATCHED.c (registry: mmbcc/src/w36c_08012108_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void SetBit16(u32 a, int b);

extern void Vec2_SetMirrored(u8 *s, u32 a, int b);

extern void ChipSlot_IncUse(u8 *s, int a);

extern void MaxAssign_17(u32 a, int b);

extern void ChipSlot_Tick(u8 *s);

extern void DecIfNonZero_18(u32 a);

extern void SetBytes_08011F68(u8 *s, int a);

__attribute__((section(".text.w36c_08012108")))
void Sub_08012108(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 0) {
        s[14] = 1;
        SetBit16(*(u32 *)(s + 44), 3);
        Vec2_SetMirrored(s, (int)0xffffc400, 0);
        ChipSlot_IncUse(s, 0);
        s[18] = 15;
    }
    if (s[14] == 1 && s[18] == 8)
        MaxAssign_17(*(u32 *)(s + 44), 1);
    ChipSlot_Tick(s);
    s[18]--;
    if (s[18] == 0) {
        MaxAssign_17(*(u32 *)(s + 44), 7);
        DecIfNonZero_18(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Vec2_SetMirrored(s, (int)0xffffc400, 0);
        p[4] = 0;
        SetBytes_08011F68(s, 0);
    }
}
