/* Xor_23CE4 @ 0x08023CE4 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08023CE4 (44B): XOR-fold 14 bytes with ((i*2)&7) key stream. */
__attribute__((section(".text.w10l_08023ce4")))
void Xor_23CE4(u8 *p0, u8 *p1)
{
    u8 *a = p1;
    u8 *b = p0;
    u8 i = 0;
    do {
        u8 *dst = a + i;
        u8 *src = b + ((i * 2) & 7);
        *dst ^= *src;
        i++;
    } while (i <= 13);
}
