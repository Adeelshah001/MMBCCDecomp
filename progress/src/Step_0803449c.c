/* Step_0803449c @ 0x0803449C (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_0803449c_MATCHED.c (registry: mmbcc/src/w36a_0803449c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern s8 Fwd_EBF0(void);

extern int sub_0800EA4C(int v);

__attribute__((section(".text.w36a_0803449c")))
u32 Step_0803449c(u8 *s)
{
    u32 ret = 0;
    u8 st = s[3];
    if (st == 0)
        goto state0;
    if (st == 1)
        goto state1;
    goto ret;
state0:
    s[6] |= 128;
    if ((s8)Fwd_EBF0() == 1) {
        s[3]++;
    } else {
        sub_0800EA4C(0);
        goto ret;
    }
state1:
    if ((u8)sub_0800EA4C(0) == 1)
        goto ret;
    s[6] &= 127;
    ret = 7;
ret:
    return ret;
}
