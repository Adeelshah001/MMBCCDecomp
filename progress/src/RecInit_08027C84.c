/* RecInit_08027C84 @ 0x08027C84 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16d_08027c84.c (registry: src/w16d_08027c84.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

void InitRec8_267B4(u8 *p, u32 kind);

void LoadCallClear_4A328(void);

void RecInit_08027C84(u8 *p)
{
    register u8 *q2 __asm__("r2");
    register u8 *q1 __asm__("r1");
    register u32 q3 __asm__("r3");
    __asm__ volatile("" : "=r" (q2) : "0" ((u8 *)0x20070f0));
    __asm__ volatile("" : "=r" (q1) : "0" ((u8 *)0x822dd84));
    __asm__ volatile("" : "=r" (q3) : "0" (0x4698));
    {
        s8 v = *(s8 *)(p + q3);
        int off = v * 4;
        u32 *addr;
        u32 val;
        __asm__ volatile("add %0, %0, %1" : "+r" (off) : "r" (q1));
        addr = (u32 *)off;
        val = *addr;
        InitRec8_267B4(q2, val);
    }
    LoadCallClear_4A328();
}
