/* Check_08028970 @ 0x08028970 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08028970_MATCHED.c (registry: src/w36a_08028970_MATCHED.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int Sub_08028778(u8 *p, u8 v);

extern int F_0802FD68(u8 *p);

__attribute__((section(".text.w36a_08028970")))
u32 Check_08028970(u8 *s)
{
    u8 flags = s[6];
    s8 v;
    if (flags & 8)
        goto set0;
    if (flags & 32) {
        v = (s8)Sub_08028778(s + 1, 0);
        if (v != 0)
            return 0;
        goto done;
    }
    if (s[1] == 0)
        s[1] = 1;
    else if (s[1] != 1)
        return 0;
    if ((u8)F_0802FD68(s) == 0)
        return 0;
set0:
    v = 0;
done:
    s[0] = 1;
    s[1] = v;
    return 0;
}
