/* F_08007728 @ 0x08007728 (84 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24b_08007728.c (registry: src/w24b_08007728.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 *NodeInit_08022FB0(u32 x);

extern u8 g_02004830[];

__attribute__((section(".text.w24b_08007728")))
void F_08007728(u8 a, u8 b, u8 c)
{
    u32 off622 = 622;
    s8 v = (s8)g_02004830[620];

    if (v == -1 && (s8)a != v)
        NodeInit_08022FB0((s8)a);
    g_02004830[620] = a;
    g_02004830[621] = b;
    g_02004830[off622] = c;
}
