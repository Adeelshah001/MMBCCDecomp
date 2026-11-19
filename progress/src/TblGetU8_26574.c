/* TblGetU8_26574 @ 0x08026574 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w14d_08026574")))
unsigned char TblGetU8_26574(void *ctx, signed short idx, unsigned int sel)
{
    register unsigned short ii __asm__("r3") = (unsigned short)idx;
    unsigned char *base;
    unsigned char *entry;
    unsigned int addr;
    unsigned char *p;
    __asm__ volatile("lsl %0, %0, #24\n\tlsr %0, %0, #24" : "+r" (sel));
    if (ii > 127)
        return 0;
    base = *(unsigned char **)((unsigned char *)ctx + 4);
    addr = (unsigned int)ii * 28 + (unsigned int)base;
    entry = (unsigned char *)addr;
    if (entry[25] == 0)
        return 0;
    if (sel <= 9) {
        p = entry + 2;
    } else {
        sel -= 10;
        if ((unsigned char)sel > 1)
            return 0;
        p = entry + 12;
    }
    return p[sel];
}
