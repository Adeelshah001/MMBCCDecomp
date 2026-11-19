/* Sub_08005130 @ 0x08005130 (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08005130_MATCHED.c (registry: mmbcc/src/w38a_08005130_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;
typedef volatile unsigned int vu32;

extern void Sub_080059A8(void);

__attribute__((section(".text.w38a_08005130")))
void Sub_08005130(u8 *s)
{
    register u8 *sp __asm__("r3") = s;
    vu32 *dmaF;
    vu32 *dmaL;
    int raw1, raw2;
    int a1, a2, b1, b2;
    u32 ptr, dst;
    u8 *p;
    if (sp[0x11ae] & 1) {
        dmaF = (vu32 *)0x040000d4;
        dmaF[0] = *(u32 *)(sp + 4);
        dmaF[1] = 0x06002000;
        dmaF[2] = 0x80000400;
        (void)dmaF[2];
        goto tail;
    }
    p = sp + 0x11ac;
    __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(raw1) : "r"(p));
    a1 = (u16)raw1;
    b1 = a1;
    __asm__ volatile("" : "+r"(b1));
    if ((s16)a1 > 32)
        b1 = 32;
    a1 = b1;
    __asm__ volatile("" : "+r"(a1));
    b1 = a1;
    __asm__ volatile("" : "+r"(a1));
    if ((s16)a1 < 0)
        b1 = 0;
    a1 = b1;
    *p = (u8)a1;
    p = sp + 0x11ad;
    __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(raw2) : "r"(p));
    a2 = (u16)raw2;
    b2 = a2;
    __asm__ volatile("" : "+r"(b2));
    if ((s16)a2 > 2)
        b2 = 2;
    a2 = b2;
    __asm__ volatile("" : "+r"(a2));
    b2 = a2;
    __asm__ volatile("" : "+r"(a2));
    if ((s16)a2 < 0)
        b2 = 0;
    a2 = b2;
    *p = (u8)a2;
    ptr = *(u32 *)(sp + 4) + (u32)((((a2 << 16) >> 10) + (s16)a1) << 1);
    dst = 0x06002000;
    {
        register u16 i __asm__("r4");
        int sgn;
        i = 0;
        dmaL = (vu32 *)0x040000d4;
        do {
            dmaL[0] = ptr;
            dmaL[1] = dst;
            dmaL[2] = 0x80000020;
            sgn = dmaL[2];
            ptr += 128;
            dst += 64;
            __asm__ volatile(
                "lsl %0, %1, #16\n\t"
                "movs %%r4, #128\n\t"
                "lsl %%r4, %%r4, #9\n\t"
                "add %0, %0, %%r4\n\t"
                "lsr %1, %0, #16\n\t"
                "asr %0, %0, #16\n\t"
                : "+r"(sgn), "+r"(i) : : "cc");
        } while (sgn <= 19);
    }
tail:
    Sub_080059A8();
}
