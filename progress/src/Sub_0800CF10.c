/* Sub_0800CF10 @ 0x0800CF10 (316 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w65b_0800cf10_MATCHED.c (registry: staging/w65b_cf10/variants/v2_s16.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void sub_0800244C(u8 *dst, int v);

extern void Copy8_28D0(u8 *dst, int a, int b);

__attribute__((section(".text.w65b_0800cf10")))
void Sub_0800CF10(u8 *s, u8 a, u8 b)
{
    int off = 2;
    if (b == 0) {
        register u8 *d __asm__("r2");
        off = 6;
        d = (u8 *)0x0830B624;
        __asm__("" : "+r"(d));
        sub_0800244C(d, (((*(u16 *)0x020031EA) & 12) << 12) + 64);
    }
    {
        u8 t = *((u8 *)0x08173500 + a);
        register u8 *d __asm__("r2") = (u8 *)(0x0830B340 + t * 20);
        __asm__("" : "+r"(d));
        sub_0800244C(d, (((*(u16 *)0x020031EA) & 12) << 12) + (off << 5));
        Copy8_28D0((u8 *)(0x0830B34C + t * 20), 0, 0);
    }
    if (b == 1) {
        u8 *q = (u8 *)0x02004F80;
        if (q[2] == 1)
            *(u16 *)0x03002420 = 0;
        else if (q[2] == 2)
            *(u16 *)0x03002420 = 0x7FFF;
    }
    {
        register int t __asm__("r2") = s[9];
        int bit;
        u16 *vp;
        u16 *dst;
        u32 tileoff;
        s16 row, col;
        u16 *src;
        s16 lo, hi;
        lo = (t ^ 1) & 1;
        hi = t & -2;
        s[9] = hi | lo;
        vp = (u16 *)0x020031F8;
        bit = s[9] & 1;
        *vp = ((bit | -bit) >> 31) & 0x100;
        tileoff = ((*(vp - 7)) & 0x1F00) << 3;
        dst = (u16 *)(0x06000000 + tileoff);
        if (bit)
            dst = (u16 *)(0x06000800 + tileoff);
        { register u8 *tbl __asm__("r1") = (u8 *)0x0817350C;
          __asm__("" : "+r"(tbl));
          src = *(u16 **)(tbl + a * 4); }
        row = 0;
        do {
            u16 *dd = dst + row * 32;
            col = 0;
            do {
                *dd++ = *src++ + off;
                col++;
            } while (col <= 29);
            row++;
        } while (row <= 19);
    }
}
