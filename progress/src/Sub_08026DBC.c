/* Sub_08026DBC @ 0x08026DBC (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08026dbc_MATCHED.c (registry: mmbcc/src/w35c_08026dbc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Dispatch_0800dea4(void *a, u32 b, int c, int d, u32 e, u32 f, int g);

__attribute__((section(".text.w35c_08026dbc")))
void Sub_08026DBC(void)
{
    u32 *base = (u32 *)0x020038ac;
    void *a0 = (void *)0x0871e4e4;
    u32 b1 = base[1];
    u32 *tbl = (u32 *)0x0871c8a4;
    u32 t = *tbl + (u32)tbl;
    Dispatch_0800dea4(a0, b1, 1, 1, t, base[0], 32);
}
