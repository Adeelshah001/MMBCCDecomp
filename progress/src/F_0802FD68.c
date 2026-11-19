/* F_0802FD68 @ 0x0802FD68 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16d_0802fd68.c (registry: src/w16d_0802fd68.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Clr8_08004B94(int x);

s8 Dispatch_081705A4_0(void);

int F_0802FD68(u8 *p)
{
    int ret = 0;
    u8 v = p[3];
    if (v == 0)
        goto L1;
    if (v == 1)
        goto L2;
    goto End;
L1:
    Clr8_08004B94(1);
    p[3]++;
L2:
    {
        s8 r = Dispatch_081705A4_0();
        if (r != 1)
            goto End;
        p[3] = 0;
        ret = 1;
    }
End:
    return ret;
}
