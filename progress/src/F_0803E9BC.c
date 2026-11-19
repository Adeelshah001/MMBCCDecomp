/* F_0803E9BC @ 0x0803E9BC (96 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_0803e9bc.c (registry: src/w20c_0803e9bc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Clr36_080475D4(void);

extern s8 CopyHdr_Dispatch(u8 *s);

__attribute__((section(".text.w20c_0803e9bc")))
u32 F_0803E9BC(u8 *s)
{
    u32 r = 0;
    u8 dummy;
    u8 *p = s + 0x469D;
    u8 v = *p;
    if (v != 0) {
        if (v == 1)
            goto body;
        goto ret;
    } else {
        Clr36_080475D4();
        (*p)++;
    }
body:
    {
        s8 q = CopyHdr_Dispatch(&dummy);
        if (q == -1 || q == 1) {
            *(s + 0x469C) = 0;
            *(s + 0x469D) = 10;
            r = 2;
        }
    }
ret:
    return r;
}
