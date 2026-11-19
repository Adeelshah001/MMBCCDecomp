/* Sub_08025E5C @ 0x08025E5C (106 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08025e5c_MATCHED.c (registry: mmbcc/src/w36b_08025e5c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GetStride4Byte20_080258C0(u8 *s, u8 b);

extern void Sub_08023A7C(u32 a1, u8 *buf, u32 a2);

__attribute__((section(".text.w36b_08025e5c")))
void Sub_08025E5C(u8 *s, u32 a1, u32 a2)
{
    u8 buf[16];
    s8 i;
    u8 *dst;
    buf[0] = s[0];
    i = 0;
    dst = buf + 1;
    for (; i <= 9; i++) {
        dst[i] = GetStride4Byte20_080258C0(s, *(s + 2 + i));
    }
    buf[11] = GetStride4Byte20_080258C0(s, s[12]);
    buf[12] = GetStride4Byte20_080258C0(s, s[13]);
    buf[13] = 1;
    Sub_08023A7C(a1, buf, a2);
}
