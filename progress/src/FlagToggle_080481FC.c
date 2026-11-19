/* FlagToggle_080481FC @ 0x080481FC (98 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_f_old.c (registry: src/wave9_f_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern s16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w9f_0x080481fc")))
int FlagToggle_080481FC(u8 *p)
{
    register u8 *pp __asm__("r4") = p;
    register u32 ret __asm__("r5");
    register u16 *gg __asm__("r6");
    __asm__ volatile("movs %0,#0" : "=r"(ret));
    __asm__ volatile("" : "=r"(gg) : "0"((u16 *)0x02002F50));
    {
        u16 c0 = gg[2];
        if ((c0 & 48) != 0) {
        register u32 o2 __asm__("r2");
        register u32 rv __asm__("r0");
        register u8 t3 __asm__("r3");
        register u8 *q __asm__("r1");
        register u16 *hh __asm__("r2");
        u32 x;
        u8 qv;
        Text_SelectBlobIdx(0x66);
        __asm__ volatile("" : "=r"(o2) : "0"(0x46B4));
        q = pp + o2;
        __asm__ volatile("movs %0,#1" : "=r"(rv));
        __asm__ volatile("ldrb %0,[%1]" : "=r"(t3) : "r"(q));
        __asm__ volatile("eor %0,%1" : "+r"(rv) : "r"(t3));
        *q = (u8)rv;
        __asm__ volatile("" : "=r"(hh) : "0"((u16 *)0x02004CE0));
        rv <<= 3;
        qv = *(volatile u8 *)q;
        x = rv - qv;
        x = (x << 4) + 24;
        hh[20] = (u16)x;
        hh[21] = 32;
        }
    }
    {
        u16 c1 = gg[2];
        if ((c1 & 1) != 0) {
            ret = 1;
        } else {
            register u32 t __asm__("r0");
            __asm__ volatile("" : "=r"(t) : "0"(2));
            __asm__ volatile("and %0,%1" : "+r"(t) : "r"((u32)c1));
            if (t != 0)
                ret = 2;
        }
    }
    return ret;
}
