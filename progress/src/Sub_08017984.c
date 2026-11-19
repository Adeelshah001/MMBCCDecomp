/* Sub_08017984 @ 0x08017984 (160 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_08017984_MATCHED.c (registry: mmbcc/src/w37c2_08017984_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ChipSlot_Tick(u8 *s);

extern void ChipInit_080178A8(u8 a, int b, int c, int d, u8 *e);

extern int GetField17_U8(u8 *p);

extern void MaxAssign_17(u8 *p, int v);

extern void DecIfNonZero_18(u8 *p);

__attribute__((section(".text.w37c2_08017984")))
void Sub_08017984(u8 *s)
{
    if ((u8)(s[119] - 3) <= 1)
        s[10] &= 254;
    ChipSlot_Tick(s);
    if (s[13] == 0) {
        s[18]++;
        if (s[18] == 2) {
            register u8 *tbl __asm__("r0") = (u8 *)0x08226388;
            __asm__ volatile("" : "+r"(tbl));
            ChipInit_080178A8(tbl[s[16]],
                ((u32)s[35] << 28) >> 28,
                240 << 6, (int)0xffffea00, *(u8 **)(s + 44));
            s[13] = 1;
        }
    }
    if ((u8)GetField17_U8(*(u8 **)(s + 44)) > 5) {
        register u32 **tbl __asm__("r1") = (u32 **)0x082243d8;
        register u32 **addr __asm__("r0");
        __asm__ volatile("" : "+r"(tbl));
        addr = (u32 **)(s[9] * 4 + (int)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*addr + 8);
        MaxAssign_17(*(u8 **)(s + 44), 7);
        DecIfNonZero_18(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
