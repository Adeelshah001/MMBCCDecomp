/* Sub_080050F0 @ 0x080050F0 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_080050f0_MATCHED.c (registry: src/w36d_080050f0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_08005130(u8 *base);

extern void NullCallback(u8 *base);

__attribute__((section(".text.w36d_080050f0")))
void Sub_080050F0(void)
{
    register u8 *base __asm__("r3") = (u8 *)0x02003670;
    register u8 *p __asm__("r4") = base + 0x11ae;
    register int b __asm__("r2") = *p;
    if ((b & 2) == 0)
        return;
    {
        register int nb __asm__("r1");
        nb = ~2;
        nb &= b;
        *p = nb;
        if ((nb & 248) != 8)
            Sub_08005130(base);
        else
            NullCallback(base);
    }
}
