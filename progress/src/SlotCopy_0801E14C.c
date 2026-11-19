/* SlotCopy_0801E14C @ 0x0801E14C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_0801e14c.c (registry: src/w20c_0801e14c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 ClearSlot_10F88(u8 x);

__attribute__((section(".text.w20c_0801e14c")))
void SlotCopy_0801E14C(u8 *s)
{
    ClearSlot_10F88(s[16]);
    {
        register u32 base __asm__("r1") = 0x082243D8;
        register u32 idx __asm__("r2");
        u32 off;
        u32 *p;
        __asm__ volatile("" : "+r" (base));
        idx = s[9];
        off = idx << 2;
        {
            u32 addr = off + base;
            *(u32 *)(s + 12) = 4;
            p = *(u32 **)addr;
        }
        *(u32 *)(s + 20) = p[4];
    }
}
