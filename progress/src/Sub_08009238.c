/* Sub_08009238 @ 0x08009238 (144 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37a_08009238_MATCHED.c (registry: mmbcc/src/w37a_08009238_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08002300(u32 a, u32 b);

extern void Copy_08007BEC(u32 a, u32 b);

extern void Sub_0800288C(u32 a, u32 b);

__attribute__((section(".text.w37a_08009238")))
void Sub_08009238(void)
{
    u8 *p = (u8 *)0x02003670;
    u8 *q;
    int m;
    u8 *r;
    __asm__ volatile("" : "+r"(p));
    p += 0x11ae;
    if ((*p & 248) != 16)
        return;
    q = (u8 *)0x02004830;
    __asm__ volatile("" : "+r"(q));
    q += 616;
    m = 15;
    __asm__ volatile("" : "+r"(m));
    *q = (*q & -m) | 2;
    r = (u8 *)0x0830b3a4;
    sub_08002300((u32)r, 0x67a0);
    Copy_08007BEC(0x0806b2bc, 8);
    Copy_08007BEC(0x0806b560, 7);
    r += 20;
    sub_08002300((u32)r, 0x7560);
    r = (u8 *)0x0830b64c;
    sub_08002300((u32)r, 0x81a0);
    Sub_0800288C((u32)r + 12, 96);
}
