/* Sub_080466AC @ 0x080466AC (304 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w64a_080466ac_MATCHED.c (registry: src/w64a_080466ac_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 GatedDispatch(void *p, u32 a, u32 b, u32 c, u32 d);

extern u32 F_080247C4(u8 idx);

extern u32 TblGetByte_241F8(u16 a);

extern void CondRectFill_080070F0(u32 x, u32 y, u32 z, u32 w);

extern u32 TblGetW_BB8C(u16 idx);

extern void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u32 TblGet_f0A(u8 idx);

extern void Sub_080079F0(u32 a, u32 b, u32 c);

__attribute__((section(".text.w64a_080466ac")))
void Sub_080466AC(u8 *s)
{
    u8 i = 0;
    int x = s[0x46AA];

    while ((u8)x < s[0x46AA] + 7) {
        u8 x8;
        s8 *tbl = (s8 *)0x08232e5c;
        x++;
        x8 = (u8)x;
        if (x8 > 194)
            x8 = (u8)(x8 + 5);
        __asm__ volatile("" : "+r" (tbl));
        GatedDispatch((void *)x, tbl[0], tbl[1] + 2 * i, 3, 2);
        if ((u16)F_080247C4(x8) != 0 || (u8)TblGetByte_241F8(0x1000) == x8) {
            CondRectFill_080070F0(x8, tbl[4], tbl[5] + 2 * i, 0);
            Gfx_BlitRequest(TblGetW_BB8C(x8), tbl[8], tbl[9] + 2 * i, 8, 2);
            {
                u8 t2 = (u8)TblGet_f0A(x8);
                Sub_080079F0(t2, tbl[12], tbl[13] + 2 * i);
            }
        } else {
            CondRectFill_080070F0(0, tbl[4], tbl[5] + 2 * i, 0);
            Gfx_BlitRequest(*(u32 *)0x08232e04, tbl[8], tbl[9] + 2 * i, 11, 2);
        }
        i++;
    }
    *(u16 *)(0x02004ce0 + 40) = 88;
    *(u16 *)(0x02004ce0 + 42) = (s[0x46a9] << 4) + 24;
}
