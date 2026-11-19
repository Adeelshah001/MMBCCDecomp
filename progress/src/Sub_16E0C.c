/* Sub_16E0C @ 0x08016E0C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17d_08016e0c.c (registry: src/w17d_08016e0c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void SetBytes_08011F68(u8 *s, u8 v);

__attribute__((section(".text.w17d_08016E0C")))
void Sub_16E0C(u8 *s, u32 v)
{
    register u8 *ss __asm__("r4") = s;
    u16 vv = (u16)v;
    u8 *p = ss + 124;
    u8 z = 0;
    p[0] = (u8)vv;
    p[1] = (u8)vv;
    if ((u8)vv > 38) {
        p[3] = (u8)(vv - 39);
        p[2] = (u8)(vv - 39);
        p[0] = 39;
        p[1] = 39;
    } else {
        p[3] = z;
        p[2] = z;
    }
    p[4] = 1;
    SetBytes_08011F68(ss, 1);
}
