/* Sub_0803895C @ 0x0803895C (376 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39a_0803895c_MATCHED.c (registry: mmbcc/src/w39a_0803895c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void CondRectFill_080073D4(int code, int flag, int c, int d, int e);

extern void Gfx_BlitRequest(int a, int b, int c, int d, int e);

__attribute__((section(".text.w39a_0803895c")))
void Sub_0803895C(u8 *s)
{
    int *pA;

    {
        u8 f = 0;
        if (s[289])
            f = 3;
        CondRectFill_080073D4(27, f, 2, 1, 0);
    }
    pA = (int *)0x08230174;
    Gfx_BlitRequest(*pA, 4, 1, 2, 2);
    Gfx_BlitRequest(*(int *)0x0823012c, 5, 1, 13, 2);
    if (s[20] > 1) {
        CondRectFill_080073D4(28, s[301] ? 3 : 0, 2, 3, 0);
        Gfx_BlitRequest(*pA, 4, 3, 1, 2);
        Gfx_BlitRequest(*(int *)0x08230134, 5, 3, 12, 2);
    } else {
        Gfx_BlitRequest(*pA, 2, 3, 15, 2);
    }
    {
        u8 f = s[313] ? 3 : 0;
        if (s[20] > 5) {
            CondRectFill_080073D4(29, f, 2, 5, 0);
            Gfx_BlitRequest(*(int *)0x08230174, 4, 5, 1, 2);
            Gfx_BlitRequest(*(int *)0x0823013c, 5, 5, 12, 2);
        } else {
            Gfx_BlitRequest(*(int *)0x08230174, 2, 5, 15, 2);
        }
    }
    {
        u8 f = s[325] ? 3 : 0;
        if (s[20] > 8) {
            CondRectFill_080073D4(30, f, 2, 7, 0);
            Gfx_BlitRequest(*(int *)0x08230174, 4, 7, 1, 2);
            Gfx_BlitRequest(*(int *)0x08230144, 5, 7, 12, 2);
        } else {
            Gfx_BlitRequest(*(int *)0x08230174, 2, 7, 15, 2);
        }
    }
}
