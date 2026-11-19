/* CondRectFill_080062B4 @ 0x080062B4 (100 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31d_080062b4.c (registry: src/w31d_080062b4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void FillRect_6374(void *ctx, s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);

__attribute__((section(".text.w31d_080062b4")))
void CondRectFill_080062B4(u8 x, u8 y, u8 w, u8 h, u16 a, u16 b, u32 c)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    FillRect_6374(base, (s8)x, (s8)y, w, h, a, b, c);
}
