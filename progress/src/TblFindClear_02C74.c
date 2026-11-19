/* TblFindClear_02C74 @ 0x08002C74 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_C_old.c (registry: src/wave12_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08002C74: search 16-byte table at 0x02003090 for (a+1); clear found entry. */
__attribute__((section(".text.w12c_08002c74")))
void TblFindClear_02C74(unsigned char a)
{
    unsigned char v = a + 1;
    int i = 0;
    unsigned int addr;
    unsigned char *p;
    __asm__ volatile("" : "=r" (addr) : "0" (0x02003090));
    __asm__ volatile("add %0, %1, #0" : "=l" (p) : "l" (addr));
    if (p[0] != v) {
        unsigned char *q = p;
        do {
            i++;
        } while (i <= 15 && *(unsigned char *)((unsigned int)i + (unsigned int)q) != v);
    }
    if (i != 16)
        *(unsigned char *)((unsigned int)i + (unsigned int)p) = 0;
}
