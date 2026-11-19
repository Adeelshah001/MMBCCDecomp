/* Text_SelectBlobU16 @ 0x08002FC4 (14 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_c.c (registry: src/wave3_c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Text_SelectBlob(u16 idx);

__attribute__((section(".text.w3c_text_blobu16")))
void Text_SelectBlobU16(u16 idx)
{
    Text_SelectBlob(idx);
}
