/* Copy4_2518C @ 0x0802518C (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave12_B_old.c (registry: src/wave12_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Copy4_2518C @ 0x0802518C (44 B): copies 4 u16s at p+off, off=0x13A4+2k. */
__attribute__((section(".text.w12b_0802518c")))
void Copy4_2518C(u8 *p, u16 *q)
{
    register u32 off __asm__("r3") = 0x13A4;
    q[0] = *(u16 *)(p + off);
    off += 2;
    q[1] = *(u16 *)(p + off);
    off += 2;
    q[2] = *(u16 *)(p + off);
    q[3] = *(u16 *)(p + 0x13AA);
    asm("" : : "r" (off));
}
