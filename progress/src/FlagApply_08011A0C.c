/* FlagApply_08011A0C @ 0x08011A0C (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_08011a0c.c (registry: src/w15c_08011a0c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void FlagBit_Set_11D68(u16 x, u8 y);

int __attribute__((section(".text.w15c2_08011a0c"))) FlagApply_08011A0C(u8 *s)
{
    s8 *p = *(s8 **)(s);
    s8 v = p[6];
    if (v > 0) {
        FlagBit_Set_11D68((u16)v, 1);
    } else if (v < 0) {
        FlagBit_Set_11D68((u16)(-p[6]), 0);
    }
    v = p[7];
    if (v > 0) {
        FlagBit_Set_11D68((u16)v, 1);
    } else if (v < 0) {
        FlagBit_Set_11D68((u16)(-p[7]), 0);
    }
    {
        register u8 t __asm__("r1");
        int zero;
        t = s[4] + 1;
        zero = 0;
        s[4] = t;
        s[5] = zero;
        s[6] = zero;
        s[7] = zero;
        return zero - 1;
    }
}
