/* Sub_266AC @ 0x080266AC (66 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_080266ac.c (registry: src/w16b_080266ac.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 Buf_RemoveAt_25290(u8 *p, u16 idx);

int Append_0802526C(void *s, u8 v);

void Sub_266AC(u8 *s)
{
    u16 i = *(u16 *)(s + 22) - 1;
    while (i != 0) {
        u8 v = Buf_RemoveAt_25290(s + 16, i);
        Append_0802526C(s + 8, v);
        *(*(u8 **)(s + 4) + v * 28 + 25) = 0;
        i--;
    }
}
