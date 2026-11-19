/* Sub_0804380C @ 0x0804380C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_0804380c_MATCHED.c (registry: src/w36bulk_0804380c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int TblStride_24818(int x);

extern void Sub_08007C04(u8 t, int x);

extern void Sub_08007CF4(int a, s8 b, s8 c);

extern int TblGetW_BB8C(u8 t);

extern void Gfx_BlitRequest(int a, int b, int c, int d, int e);

extern int TblGetW_BF74(u8 t);

__attribute__((section(".text.w36bulk_0804380c")))
void Sub_0804380C(u8 *s)
{
    int zero = 0;
    register u8 b __asm__("r2") = s[0x46a8];
    u8 t = (u8)TblStride_24818((b >> 5) + (b & 31));
    Sub_08007C04(t, 1);
    {
        u8 *tbl = (u8 *)0x08232d84;
        Sub_08007CF4(1, (s8)(tbl[0] + 1), (s8)(tbl[1] + 3));
    }
    {
        s8 *st = (s8 *)0x08232d84;
        Gfx_BlitRequest(TblGetW_BB8C(t), st[0] + 1, st[1] + 1, 8, zero);
    }
    {
        s8 *st = (s8 *)0x08232d84;
        Gfx_BlitRequest(TblGetW_BF74(t), st[0] + 1, st[1] + 10, 8, zero);
    }
}
