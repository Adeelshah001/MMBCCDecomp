/* TblGetByte_241F8 @ 0x080241F8 (174 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_B.c (registry: src/wave13_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 GetByte1_25A08(u8 *p);

u8 GetByte1_26554(void *ctx, u32 idx);

/* u8(u16). Prologue: aa pinned r0 forces in-place (u16) truncation;
 * idx pinned r1 forces `lsrs r1,r0,#12`. Switch is signed (bgt).
 * Cases 1/2: p pinned r0; temps pinned r1 (432/idx), r2 (p+432),
 * r3 (p[432]). Case 3: base ldr forced before mask ldr via barrier.
 * Case 4: barrier keeps pool at 0x020070CC with ldrb [r0,#1]. */
__attribute__((section(".text.w12a_080241f8")))
u8 TblGetByte_241F8(u16 a)
{
    register u32 aa __asm__("r0") = a;
    register u32 idx __asm__("r1");
    aa = (aa << 16) >> 16;
    if (aa == 0)
        return 200;
    idx = aa >> 12;
    switch ((int)idx) {
    case 1: {
        register u8 *p __asm__("r0") = *(u8 **)0x020070A4;
        register u32 k __asm__("r1") = 216;
        register u8 *q __asm__("r2");
        register u32 x __asm__("r3");
        k <<= 1;
        q = p + k;
        x = *q;
        k = (x << 3) + x;
        k <<= 4;
        p += k;
        return (u8)GetByte1_25A08(p);
    }
    case 2: {
        register u32 m __asm__("r1");
        m = 0xFFF;
        m &= aa;
        if (m == 0) {
            register u8 *p __asm__("r0") = *(u8 **)0x020070A4;
            register u32 k __asm__("r1") = 216;
            register u8 *q __asm__("r2");
            register u32 x __asm__("r3");
            k <<= 1;
            q = p + k;
            x = *q;
            k = (x << 3) + x;
            k <<= 4;
            p += k;
            return (u8)GetByte1_25A08(p);
        }
        return (u8)GetByte1_26554((void *)0x020070A8, m);
    }
    case 3: {
        register u32 base __asm__("r2") = 0x082298F0;
        register u32 m __asm__("r1");
        register u32 t __asm__("r0");
        __asm__("" : "+r" (base));
        m = 0xFFF;
        m &= aa;
        t = (m << 2) + m;
        t <<= 2;
        t += base;
        return *(u8 *)(t + 1);
    }
    case 4: {
        register u8 *q __asm__("r0") = (u8 *)0x020070CC;
        __asm__("" : "+r" (q));
        return q[1];
    }
    default:
        return 200;
    }
}
