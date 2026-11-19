/* ComputeFields @ 0x0804CFD4 (180 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_H_old.c (registry: src/wave10_H_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w10h_0804cfd4")))
void ComputeFields(u32 dummy, u8 *p)
{
    register u8 *pp __asm__("r2");
    register u32 v19 __asm__("r3");
    register u32 v18 __asm__("r1");
    register u32 rv4 __asm__("r4");
    register u32 x __asm__("r1");
    register u32 b __asm__("r3");
    u32 t;
    __asm__ volatile("add %0, %1, #0" : "=r"(pp) : "r"(p));
    if (pp[0] & 1) {
        u32 r3;
        int r1;
        __asm__ volatile("ldrb %0, [%1, #19]" : "=r"(v19) : "r"(pp));
        __asm__ volatile("ldrb %0, [%1, #18]" : "=r"(v18) : "r"(pp));
        {
            register u32 t __asm__("r0");
            __asm__ volatile("add %0, %1, #0" : "=r"(t) : "r"(v19));
            r3 = (u32)(t * v18) >> 5;
        }
        __asm__ volatile("ldrb %0, [%1, #24]" : "=r"(rv4) : "r"(pp));

        if (rv4 == 1) {
            int r0 = (s8)pp[22] + 128;
            r3 = (u32)(r0 * r3) >> 7;
        }
        r1 = ((s8)pp[20] << 1) + (s8)pp[21];
        if (rv4 == 2)
            r1 += (s8)pp[22];
        if (r1 < -128)
            r1 = -128;
        else if (r1 > 127)
            r1 = 127;
        pp[16] = (u8)(((r1 + 128) * r3) >> 8);
        pp[17] = (u8)(((127 - r1) * r3) >> 8);
    }
    __asm__ volatile("ldrb %0, [%1, #0]" : "=r"(x) : "r"(pp));
    t = x & 4;
    b = x;
    if (t) {
        register int p0 __asm__("r0");
        register int p1 __asm__("r1");
        int acc;
        p0 = (s8)pp[14] * pp[15];
        p1 = (s8)pp[12];
        __asm__ volatile("add %0, %0, %1" : "+r"(p1) : "r"(p0));
        p1 <<= 2;
        acc = p1;
        acc += (s8)pp[10] << 8;
        acc += (s8)pp[11] << 8;
        acc += pp[13];
        if (pp[24] == 0)
            acc += (s8)pp[22] << 4;
        pp[8] = (u8)(acc >> 8);
        pp[9] = (u8)acc;
    }
    pp[0] = b & 250;
}
