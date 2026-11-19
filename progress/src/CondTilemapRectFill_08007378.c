/* CondTilemapRectFill_08007378 @ 0x08007378 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31d_08007378.c (registry: src/w31d_08007378.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void TilemapRectFill_6AD8(void *ctx, u32 t, s16 x, s16 y, u8 d, u8 e);

__attribute__((section(".text.w31d_08007378")))
void CondTilemapRectFill_08007378(u8 mode, u16 x, u16 y, u8 z)
{
    u8 *base;
    register u32 t __asm__("r1");
    t = 0;
    base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    if (mode != 0) {
        u32 *tbl = (u32 *)0x08171ee0;
        int m;
        __asm__ volatile("" : "+r"(tbl));
        m = mode - 1;
        t = tbl[m];
    }
    TilemapRectFill_6AD8(base, t, (s16)x, (s16)y, 2, z);
}
