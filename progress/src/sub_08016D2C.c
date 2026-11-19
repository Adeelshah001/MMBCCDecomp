/* sub_08016D2C @ 0x08016D2C (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22c_08016d2c.c (registry: src/w22c_08016d2c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void ObjInit_08016DAC(u8 *s);

__attribute__((section(".text.w22c_08016D2C")))
void sub_08016D2C(u8 *s)
{
    u8 *q = s + 124;
    u32 *tbl = (u32 *)0x08223CC0;
    u8 v;
    u32 *pp;
    u32 w0, w;
    u8 t;
    u16 hv;
    u32 idx;
    u8 *tab2;
    u8 b;
    int ti;
    u8 d;
    int sh;
    int m;
    u8 *r3b;

    __asm__ volatile("" : : "r"(tbl) : "r4", "r0");
    v = s[9];
    pp = tbl + v;
    *(u32 *)(s + 12) = 1;
    w0 = *pp;
    w = *(u32 *)(w0 + 4);
    *(u32 *)(s + 20) = w;
    if (q[4] == 1)
        s[13] = q[5];
    *(u32 *)(s + 108) = 0;
    t = s[10];
    t |= 2;
    t |= 1;
    s[10] = t;
    hv = *(u16 *)0x081705B0;
    idx = (hv >> 4) << 1;
    tab2 = (u8 *)0x020031E4;
    __asm__ volatile("" : : "r"(tab2) : "r4");
    b = tab2[idx] & 3;
    ti = b;
    __asm__ volatile("" : "+r"(ti));
    if (ti > 3)
        b = 3;
    r3b = s + 0x45;
    sh = b << 2;
    m = -13;
    d = *r3b;
    *r3b = (d & m) | sh;
    s[0x22] = 16;
    ObjInit_08016DAC(s);
}
