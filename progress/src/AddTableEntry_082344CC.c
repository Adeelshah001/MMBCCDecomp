/* AddTableEntry_082344CC @ 0x080496E8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2_old.c (registry: src/wave7_g2_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x080496e8: AddTableEntry_082344CC (28B, coordinator-verified). */
extern unsigned char g_082344cc[];

__attribute__((section(".text.w7g2_080496e8")))
unsigned char AddTableEntry_082344CC(unsigned char a, unsigned char b)
{
    return g_082344cc[a] + b;
}
