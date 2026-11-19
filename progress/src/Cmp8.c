/* Cmp8 @ 0x0802637C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w8s_0802637c")))
u32 Cmp8(u16 *a, u16 *b)
{
    if (a[0] != b[0]) return 1;
    if (a[1] != b[1]) return 1;
    if (a[2] != b[2]) return 1;
    if (a[3] != b[3]) return 1;
    return 0;
}
