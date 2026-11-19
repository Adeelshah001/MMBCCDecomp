/* Sub_0804CBCC @ 0x0804CBCC (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0804cbcc_MATCHED.c (registry: mmbcc/src/w37c_0804cbcc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void HwSetup_0804CCB8(void);

extern void Sub_0804CB28(u32 t);

__attribute__((section(".text.w37c_0804cbcc")))
void Sub_0804CBCC(u32 keys)
{
    register u32 k __asm__("r3");
    u32 *p;
    u32 t;
    k = keys;
    p = *(u32 **)0x03007ff0;
    if (*p != 0x68736d53)
        return;
    *p += 1;
    t = k & 0xff;
    if (t != 0)
        ((u8 *)p)[5] = t & 0x7f;
    t = k & 0xf00;
    if (t != 0) {
        u8 *q;
        ((u8 *)p)[6] = t >> 8;
        t = 12;
        q = (u8 *)p;
        q += 80;
        do {
            *q = 0;
            t--;
            q += 64;
        } while (t != 0);
    }
    t = k & 0xf000;
    if (t != 0)
        ((u8 *)p)[7] = t >> 12;
    t = k & 0xb00000;
    if (t != 0) {
        register u8 *q __asm__("r2");
        register u8 b __asm__("r1");
        t = (t & 0x300000) >> 14;
        q = (u8 *)0x04000089;
        b = *q;
        __asm__ volatile("" : "+r"(b));
        *q = (b & 0x3f) | t;
    }
    t = k & 0xf0000;
    if (t != 0) {
        HwSetup_0804CCB8();
        Sub_0804CB28(t);
    }
    *p = 0x68736d53;
}
