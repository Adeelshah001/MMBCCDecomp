/* F_08011B64 @ 0x08011B64 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_08011b64.c (registry: src/w16c_08011b64.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 FlagInit_08011070(u8 a, u8 b);

extern u32 IsOne_020051B0_4(void);

__attribute__((section(".text.w16c_08011b64")))
u32 F_08011B64(u8 *p)
{
    u8 v = p[5];
    if (v != 0) goto L1;
    {
        u8 *q = p + 0x24;
        if (*q != 0) {
            *q = v;
            p[4] = v;
            p[5] = v;
            p[6] = v;
            p[7] = v;
            goto Lret1;
        }
    }
    if ((u8)FlagInit_08011070(p[0x23], 2) == 0)
        goto Lret0a;
    p[5] = 1;
L1:
    if (p[5] != 1)
        goto Lclear;
    if ((s8)IsOne_020051B0_4() == 1)
        p[5]++;
Lret0a:
    return 0;
Lclear:
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
Lret1:
    return 1;
}
