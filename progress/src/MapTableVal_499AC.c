/* MapTableVal_499AC @ 0x080499AC (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_C_old.c (registry: src/wave12_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080499AC: read u16 at (0x020070F0 + a*12 + 0x152); map 0xFF->3, 0xFE->2,
 * 0xFD->1, else 0. */
__attribute__((section(".text.w12c_080499ac")))
int MapTableVal_499AC(unsigned char a)
{
    unsigned int base;
    unsigned char *p;
    __asm__ volatile("" : "=r" (base) : "0" (0x020070F0));
    p = (unsigned char *)base;
    {
        int r = 0;
        switch (*(unsigned short *)(p + a * 12 + 0x152)) {
        case 0xFF:
            r = 3;
            break;
        case 0xFE:
            r = 2;
            break;
        case 0xFD:
            r = 1;
            break;
        }
        return r;
    }
}
