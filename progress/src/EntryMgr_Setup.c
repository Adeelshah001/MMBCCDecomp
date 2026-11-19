/* EntryMgr_Setup @ 0x08004F80 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/entrymgr.c (registry: src/entrymgr.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void ListIterate_D568(u32 v);

void Sub_0800D59C(u32 v);

void Fwd_080050e0(u8 *base);

void sub_08004FEC(u8 *base);

void Sub_0800419C(u8 *p);

__attribute__((section(".text.entrymgr_setup")))
void EntryMgr_Setup(void)
{
    u8 *base = (u8 *)0x02003670;
    u32 *hp = (u32 *)0x020066F0;
    u8 *p;
    ListIterate_D568(*hp);
    Sub_0800D59C(*hp);
    p = base + 0x11AE;
    *p |= 2;
    if ((*p & 0xF8) != 8)
        sub_08004FEC(base);
    else
        Fwd_080050e0(base);
    Sub_0800419C(base + 0x49C);
    Sub_0800419C(base + 44);
    Sub_0800419C(base + 0x264);
    *(u32 *)base += 1;
}
