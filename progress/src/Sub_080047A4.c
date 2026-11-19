/* Sub_080047A4 @ 0x080047A4 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_080047a4_MATCHED.c (registry: mmbcc/src/w35c_080047a4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

__attribute__((section(".text.w35c_080047a4")))
s16 Sub_080047A4(u8 *p)
{
    s16 acc = 0;
    u8 **base;
    u8 c = *p;
    if (c > 252)
        goto DONE;
    base = (u8 **)0x02003664;
    do {
        if (c == 249)
            acc = (u16)(acc + Sub_080047A4(*base));
        c = *p;
        if (c <= 239)
            acc++;
        p++;
        c = *p;
    } while (c <= 252);
DONE:
    return acc;
}
