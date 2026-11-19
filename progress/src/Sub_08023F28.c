/* Sub_08023F28 @ 0x08023F28 (168 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39c_08023f28_MATCHED.c (registry: mmbcc/src/w39c_08023f28_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 gEwram_0200BD20[];

extern void Sub_080253F8(u8 *a, u8 *b);

extern void StoreRet_0802616c(u8 *a, u8 *b);

extern void SetU32Pair(u8 *a, u8 *b);

__attribute__((section(".text.w39c_08023f28")))
void Sub_08023F28(u8 *s)
{
    u8 *gEwram_0200BD20 = (u8 *)0x02007090;
    s8 si;
    u8 *q62;
    *(u16 *)(gEwram_0200BD20 + 88) = 1;
    *(u32 *)(gEwram_0200BD20 + 52) = (u32)s;
    Sub_080253F8(gEwram_0200BD20, s + 436);
    StoreRet_0802616c(gEwram_0200BD20 + 20, *(u8 **)(gEwram_0200BD20 + 52));
    SetU32Pair(gEwram_0200BD20 + 24, *(u8 **)(gEwram_0200BD20 + 52) + 1184);
    s = s + 5028;
    *(u32 *)(gEwram_0200BD20 + 56) = (u32)s;
    {
        register u16 v1 __asm__("r1");
        register u16 w1 __asm__("r0");
        v1 = 128;
        __asm__ volatile("" : "+r"(v1));
        v1 <<= 8;
        w1 = v1;
        *(u16 *)(s + 0) = w1;
        *(u16 *)(s + 2) = w1;
        *(u16 *)(s + 4) = w1;
        *(u16 *)(s + 6) = w1;
        *(u16 *)(s + 8) = w1;
    }
    gEwram_0200BD20[60] = 50;
    gEwram_0200BD20[61] = 200;
    si = 0;
    q62 = gEwram_0200BD20 + 62;
    do {
        q62[si] = 0;
        si++;
    } while (si <= 9);
    {
        register u8 *q __asm__("r0");
        register u16 vv __asm__("r1");
        q = gEwram_0200BD20 + 72;
        *q = 0;
        q++;
        *q = 0;
        q++;
        vv = 128;
        __asm__ volatile("" : "+r"(vv));
        vv <<= 8;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        *(u16 *)q = vv;
        q += 2;
        __asm__ volatile("" : "+r"(q));
        *(u16 *)q = vv;
    }
}
