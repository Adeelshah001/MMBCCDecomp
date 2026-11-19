/* Sub_08023C38 @ 0x08023C38 (170 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w41a_08023c38_MATCHED.c (registry: mmbcc/src/w41a_08023c38_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

__attribute__((section(".text.w41a_08023c38")))
void Sub_08023C38(u8 *dst, u8 *src, u8 sl_in)
{
    register int sh __asm__("sl") = sl_in;
    s16 i;
    for (i = 0; i <= 13; i++) {
        u8 bit = sh & 7;
        u8 bit2 = bit;
        u8 byte = sh >> 3;
        s16 m1 = (s16)(i - byte) % 14;
        if (m1 < 0)
            m1 += 14;
        dst[i] = src[m1] >> bit;
        if (bit != 0) {
            s16 m2 = (i - byte - 1) % 14;
            if (m2 < 0)
                m2 += 14;
            dst[i] |= src[m2] << (8 - bit2);
        }
    }
}
