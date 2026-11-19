/* ObjInit_C4B4 @ 0x0800C4B4 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_C_old.c (registry: src/wave12_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0800C4B4: init object struct: conditional u16 fields, OR 0xFFFF into two
 * fields, clear byte. */
__attribute__((section(".text.w12c_0800c4b4")))
void ObjInit_C4B4(unsigned char *p)
{
    unsigned int addr;
    __asm__ volatile("" : "=r" (addr) : "0" (0x02003670));
    addr += 0x11AE;
    if (((*(unsigned char *)addr) & 4) == 0) {
        unsigned short v = 0xFFF8;
        *(unsigned short *)(p + 22) = v;
        *(unsigned short *)(p + 24) = v;
    } else {
        unsigned short v = 0;
        *(unsigned short *)(p + 22) = v;
        *(unsigned short *)(p + 24) = v;
    }
    {
        register unsigned short t __asm__("r1");
        register unsigned short u __asm__("r0");
        __asm__ volatile("" : "=r" (t) : "0" (0xFFFF));
        u = t;
        *(unsigned short *)(p + 20) |= u;
        *(unsigned short *)(p + 6) |= u;
    }
    p[26] = 0;
}
