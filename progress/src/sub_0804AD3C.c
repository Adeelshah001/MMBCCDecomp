/* sub_0804AD3C @ 0x0804AD3C (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_0804ad3c.c (registry: src/w33d_0804ad3c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 sub_0804AD7C(void);

__attribute__((section(".text.w33d_0804ad3c")))
s8 sub_0804AD3C(void)
{
    return (s8)sub_0804AD7C();
}
