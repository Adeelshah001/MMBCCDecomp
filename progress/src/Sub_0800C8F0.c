/* Sub_0800C8F0 @ 0x0800C8F0 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0800c8f0_MATCHED.c (registry: mmbcc/src/w35c_0800c8f0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int S8TableLookup_0C248(u8 x);

extern void sub_0800DEF8(int a, u16 b, int c, int d, int e);

__attribute__((section(".text.w35c_0800c8f0")))
void Sub_0800C8F0(u8 *s, int a, u16 b)
{
    int t = S8TableLookup_0C248(s[20]);
    int idx = (t << 24) >> 22;
    u32 *tbl = (u32 *)0x08328678;
    u32 v = *(u32 *)((u8 *)tbl + idx);
    u32 w = v + (u32)tbl;
    int res = idx + (int)w;
    sub_0800DEF8(res, b, 1, a, 32);
}
