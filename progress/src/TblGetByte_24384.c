/* TblGetByte_24384 @ 0x08024384 (174 B, compiled size (from this build)) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_B.c (registry: src/wave13_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 GetU8_0(u8 *s);

u8 GetByte0_265B0(void *ctx, u32 idx);

/* u8(u16). Twin of TblGetByte_241F8. Differences: callees 0x08025A0C /
 * 0x080265B0, cases 3/4 use ldrb [r0,#0], default returns 50.
 * Prologue: aa pinned r0 (in-place truncation); idx pinned r1
 * (`lsrs r1,r0,#12`). Switch signed (bgt). */
__attribute__((section(".text.w12a_08024384")))
u8 TblGetByte_24384(u16 a)
{
    register u32 aa __asm__("r0") = a;
    register u32 idx __asm__("r1");
    aa = (aa << 16) >> 16;
    if (aa == 0)
        return 50;
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
        return (u8)GetU8_0(p);
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
            return (u8)GetU8_0(p);
        }
        return (u8)GetByte0_265B0((void *)0x020070A8, m);
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
        return *(u8 *)t;
    }
    case 4: {
        register u8 *q __asm__("r0") = (u8 *)0x020070CC;
        return *q;
    }
    default:
        return 50;
    }
}
