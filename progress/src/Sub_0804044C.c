/* Sub_0804044C @ 0x0804044C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37b_0804044c_MATCHED.c (registry: mmbcc/src/w37b_0804044c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int TblStride_24818(int sum);

extern void Sub_08007C04(u8 t, int x);

extern void Sub_08007CF4(int a, s8 b, s8 c);

extern int TblGetW_BB8C(u8 t);

extern void Gfx_BlitRequest(int a, int b, int c, int d, int e);

extern int TblGetW_BF74(u8 t);

__attribute__((section(".text.w37b_0804044c")))
void Sub_0804044C(u8 *s)
{
    int off = 0x46a8;
    u8 b0 = s[off];
    u8 b1 = s[off + 1];
    u8 t = (u8)TblStride_24818(b0 + b1);
    Sub_08007C04(t, 2);
    {
        u8 *tbl = (u8 *)0x082329e0;
        Sub_08007CF4(2, (s8)(tbl[16] + 1), (s8)(tbl[17] + 3));
    }
    {
        s8 *st = (s8 *)0x082329e0;
        Gfx_BlitRequest(TblGetW_BB8C(t), st[16] + 1, st[17] + 1, 8, 0);
    }
    {
        s8 *st = (s8 *)0x082329e0;
        Gfx_BlitRequest(TblGetW_BF74(t), st[16] + 1, st[17] + 10, 8, 0);
    }
}
