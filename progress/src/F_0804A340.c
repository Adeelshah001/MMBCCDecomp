/* F_0804A340 @ 0x0804A340 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern int TblValidate(u16 x);

__attribute__((section(".text.w15b_0804a340")))
s16 F_0804A340(void)
{
    u16 *p = (u16 *)0x0200BD10;
    if (p[1] == 0)
        return -1;
    if (TblValidate(p[0]) == 0)
        return -1;
    return (s16)p[0];
}
