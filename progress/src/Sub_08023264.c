/* Sub_08023264 @ 0x08023264 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_08023264_MATCHED.c (registry: mmbcc/src/w38c_08023264_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w38c_08023264")))
void Sub_08023264(u8 *s)
{
    u8 t;
    *(u32 *)(s + 108) = 0;
    t = s[10] | 2;
    s[10] = t & 254;
}
