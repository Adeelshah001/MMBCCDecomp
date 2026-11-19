/* NewNode_0801DFC4 @ 0x0801DFC4 (98 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20b_0801dfc4.c (registry: src/w20b_0801dfc4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

extern void F_0801E87C(s16 a, s16 b, u32 *out);

__attribute__((section(".text.w20b_0801DFC4")))
u8 *NewNode_0801DFC4(int a, int b, int c, int d)
{
    u8 ta = (u8)a;
    register u8 ra __asm__("r8") = ta;
    u8 rb = (u8)b;
    u16 rc = (u16)c;
    u16 rd = (u16)d;
    register u8 *n __asm__("r6");
    s16 sc, sd;
    u32 out[2];

    n = (u8 *)Node_PopAndInit(0, 0, 0, 13);
    if (n != 0)
    {
        u32 z;
        sc = (s16)rc;
        sd = (s16)rd;
        F_0801E87C(sc, sd, out);
        z = 0;
        n[16] = ra;
        n[17] = rb;
        *(u32 *)(n + 96) = (u32)sc;
        *(u32 *)(n + 100) = (u32)sd;
        *(u32 *)(n + 80) = out[0];
        *(u32 *)(n + 84) = out[1];
        *(u32 *)(n + 40) = z;
    }
    return n;
}
