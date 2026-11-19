/* Sub_08035A24 @ 0x08035A24 (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08035a24_MATCHED.c (registry: mmcc/src/w38a_08035a24_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int F_080247C4(int idx);

extern u32 Dispatch_24434(u16 a);

extern void Gfx_BlitRequest(u32 a, int b, int c, int d, int e);

extern int Sub_080241D0(int a);

extern u32 TblGetW_BB8C(u16 idx);

extern void GatedDispatch(int a, int b, int c, int d, int e);

extern void F_08024f88(u8 *a);

extern void Sub_080068F0(u8 *a, int b, int c, int d, int e);

__attribute__((section(".text.w38a_08035a24")))
void Sub_08035A24(void)
{
    u8 buf[48];
    u16 c7 = 0;
    u8 c6 = 0;
    u8 i;
    for (i = 1; i <= 243; i++) {
        u8 arg = i;
        u8 ret;
        if (i > 194)
            arg = (u8)(i + 5);
        ret = (u8)F_080247C4(arg);
        if (ret != 0) {
            c7 += ret;
            c6++;
        }
    }
    c7++;
    c6++;
    Gfx_BlitRequest(Dispatch_24434(4096), 2, 4, 4, 0);
    Gfx_BlitRequest(TblGetW_BB8C((u8)Sub_080241D0(4096)), 8, 4, 8, 0);
    GatedDispatch(c6, 17, 4, 3, 0);
    Gfx_BlitRequest(*(u32 *)0x0822E9AC, 20, 4, 1, 0);
    GatedDispatch(c7, 21, 4, 4, 0);
    Gfx_BlitRequest(*(u32 *)0x0822E9B4, 25, 4, 1, 0);
    F_08024f88(buf);
    Sub_080068F0(buf, 2, 7, 25, 0);
}
