/* Sub_0804CB28 @ 0x0804CB28 (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0804cb28_MATCHED.c (registry: mmbcc/src/w37c_0804cb28_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern s32 SDiv_0804DD08(s32 a, s32 b);

extern void sub_0804CD34(void);

__attribute__((section(".text.w37c_0804cb28")))
void Sub_0804CB28(u32 keys)
{
    u8 *p;
    register u32 k __asm__("r2");
    register u32 t __asm__("r2");
    u16 z;
    u16 p16;
    s32 v;
    register u32 tm __asm__("r0");
    u16 *dst;
    u8 *tbl;
    k = keys;
    __asm__ volatile("" : "+r"(k));
    p = *(u8 **)0x03007ff0;
    t = (k & 0xF0000) >> 16;
    z = 0;
    p[8] = (u8)t;
    tbl = (u8 *)0x08105e3c;
    tm = t - 1;
    __asm__ volatile("" : "+r"(tm));
    p16 = *(u16 *)(tbl + tm * 2);
    *(u32 *)(p + 16) = p16;
    p[11] = (u8)SDiv_0804DD08(1584, p16);
    v = SDiv_0804DD08(0x91d1b * p16 + 5000, 10000);
    *(u32 *)(p + 20) = v;
    *(u32 *)(p + 24) = (SDiv_0804DD08(0x1000000, v) + 1) >> 1;
    *(u16 *)0x04000102 = z;
    dst = (u16 *)0x04000100;
    *dst = (u16)-SDiv_0804DD08(0x44940, p16);
    sub_0804CD34();
    while (*(volatile u8 *)0x04000006 == 159)
        ;
    while (*(volatile u8 *)0x04000006 != 159)
        ;
    *(u16 *)0x04000102 = 128;
}
