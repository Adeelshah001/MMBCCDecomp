/* sub_0800695c @ 0x0800695C (246 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w55d_0800695c_MATCHED.c (registry: src/w55d_0800695c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern u16 Tbl_080733A6[];

extern u16 Tbl_080733B2[];

extern void TilemapRectFill_6AD8(void *dst, u16 *s, s16 x, s16 y, s8 m, u8 f);

__attribute__((section(".text.w55d_0800695c")))
void sub_0800695c(void *dst, u16 *src, u16 a2, u16 a3, s8 a4, u8 a5) {
    s16 h;
    s16 row;
    s16 j;
    u16 s[4];
    if (a4 != 0)
        h = (u16)a4;
    else
        h = 32;
    s[1] = 0x8000;
    for (row = 0; row < h; row++) {
        s[0] = *src++;
        for (j = 0; j <= 4; j++) {
            if (s[0] == Tbl_080733A6[j]) {
                s[0] = Tbl_080733B2[j];
                break;
            }
        }
        {
            s16 c = (s16)a2;
            TilemapRectFill_6AD8(dst, s, c, (s16)a3, 1, a5);
            a2 = (u16)(c + 1);
        }
    }
    if (a4 != 0)
        TilemapRectFill_6AD8(dst, src, (s16)a2, (s16)a3, (s8)(a4 - row), a5);
}
