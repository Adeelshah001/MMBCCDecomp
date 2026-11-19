/* Sub_0801757C @ 0x0801757C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801757c_MATCHED.c (registry: mmbcc/src/w37c_0801757c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void ChipSlot_Tick(u8 *s);

extern void ChipInit_080178A8(int a, int b, s16 c, s16 d, u8 *e);

extern int Text_SelectBlobIdx(int idx);

extern u8 GetField17_U8(u8 *p);

extern void MaxAssign_17(u8 *p, int v);

extern void DecIfNonZero_18(u8 *p);

__attribute__((section(".text.w37c_0801757c")))
void Sub_0801757C(u8 *s)
{
    u32 **t;
    ChipSlot_Tick(s);
    if (s[13] == 0 && ++s[18] == 15) {
        ChipInit_080178A8(1, ((u32)s[35] << 28) >> 28, 15360, -5632, *(u8 **)(s + 44));
        Text_SelectBlobIdx(128);
        s[13] = 1;
    }
    if (GetField17_U8(*(u8 **)(s + 44)) > 5) {
        register u8 *base __asm__("r1");
        base = (u8 *)0x082243d8;
        __asm__ volatile("" : "+r"(base));
        t = (u32 **)(s[9] * 4 + (u32)base);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*t + 8);
        MaxAssign_17(*(u8 **)(s + 44), 7);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
