/* TblLookup_0804C7B4 @ 0x0804C7B4 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16d_0804c7b4.c (registry: src/w16d_0804c7b4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void ClearSignBit_0804C5F4(u32 *p);

void TblLookup_0804C7B4(u16 idx)
{
    u32 t = (u32)idx << 16;
    register u32 *tbl1 __asm__("r2");
    register u8 *tbl2 __asm__("r1");
    u8 *base;
    u16 v;
    u32 *p;
    u32 *q;
    __asm__ volatile("" : "=r" (tbl1) : "0" ((u32 *)0x8106d7c));
    __asm__ volatile("" : "=r" (tbl2) : "0" ((u8 *)0x8106dd0));
    t >>= 13;
    base = (u8 *)(t + (u32)tbl2);
    v = *(u16 *)(base + 4);
    {
        int v12 = v * 12;
        __asm__ volatile("add %0, %0, %1" : "+r" (v12) : "r" (tbl1));
        p = (u32 *)v12;
    }
    q = (u32 *)*p;
    if (*q == *(u32 *)base)
        ClearSignBit_0804C5F4(q);
}
