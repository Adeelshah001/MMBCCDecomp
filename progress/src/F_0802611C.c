/* F_0802611C @ 0x0802611C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_0802611c.c (registry: src/w20d_0802611c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_080257BC(u8 *p, u16 x);

__attribute__((section(".text.w20d_0802611C")))
void F_0802611C(u8 *p, u16 a)
{
    u8 i;
    for (i = 0; i <= 2; i++) {
        sub_080257BC(p + i * 144, a);
    }
}
