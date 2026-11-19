/* Lists_0800E204 @ 0x0800E204 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0800e204: Lists_0800E204 (coordinator-verified). */
void ListIterate_D568(u8 *s);

extern u8 *gMem_02005270;

extern u8 *g_020053C0;

__attribute__((section(".text.w6l4_0800e204")))
void Lists_0800E204(void)
{
    ListIterate_D568(gMem_02005270);
    ListIterate_D568(g_020053C0);
}
