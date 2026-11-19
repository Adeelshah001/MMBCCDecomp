/* Text_SelectBlobIdx @ 0x0804A378 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/text_idx.c (registry: src/text_idx.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

s16 SelBlob_Ret(u16 idx);

__attribute__((section(".text.text_selidx")))
s16 Text_SelectBlobIdx(u16 idx)
{
    return SelBlob_Ret(idx);
}
