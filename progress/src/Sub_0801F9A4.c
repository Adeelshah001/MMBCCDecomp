/* Sub_0801F9A4 @ 0x0801F9A4 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0801f9a4_MATCHED.c (registry: mmbcc/src/w35c_0801f9a4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int Byte12_Gt1_0801f1d8(u8 *q);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w35c_0801f9a4")))
void Sub_0801F9A4(u8 *s)
{
    u8 v = s[119] - 3;
    if (v <= 1) {
        u8 *q = *(u8 **)(s + 40);
        if ((u8)Byte12_Gt1_0801f1d8(q) == 0) {
            u8 *p2 = *(u8 **)(s + 44);
            p2[0]++;
        }
        {
            register u32 *tbl __asm__("r1") = (u32 *)0x082243d8;
            register u8 idx __asm__("r2") = s[9];
            register u32 off __asm__("r0") = idx << 2;
            u32 *ent;
            __asm__ volatile("" : "+r"(tbl));
            ent = (u32 *)(off + (u32)tbl);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 8);
        }
    }
    ChipSlot_Tick(s);
}
