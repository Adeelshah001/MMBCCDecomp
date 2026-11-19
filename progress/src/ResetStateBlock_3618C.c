/* ResetStateBlock_3618C @ 0x0803618C (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16d_0803618c.c (registry: src/w16d_0803618c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void Call4E60_4E44(void);

void PalModeSet_4DFC(u8);

void SyncObjFlagBits_BEE0(u32, u32);

void ResetStateBlock_3618C(u8 a)
{
    register u8 *r5 __asm__("r5") = (u8 *)0x200BCE8;
    register u8 *q __asm__("r0");
    u8 *p = r5;
    u16 i;
    u16 zero;
    for (i = 0; i <= 7; i++)
        *p++ = 0;
    zero = 0;
    r5[0] = a;
    Call4E60_4E44();
    __asm__ volatile("" : "=r" (q) : "0" ((u8 *)0x2004F80));
    PalModeSet_4DFC(q[2]);
    SyncObjFlagBits_BEE0(0x40, 0x80);
    *(u16 *)0x2004830 = zero;
    Sub_08021780();
}
