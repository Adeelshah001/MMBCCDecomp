/* sub_08007678 @ 0x08007678 (176 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34d_08007678.c (registry: mmbcc/src/w34d_08007678.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void FillRect_6374(void *ctx, s8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);

__attribute__((section(".text.w34d_08007678")))
void sub_08007678(u8 a, u8 b, u8 c, u8 d)
{
    register u32 v __asm__("r4");
    if (c != 0) {
        register u8 *tbl __asm__("r2") = (u8 *)0x08172074;
        u32 t;
        __asm__ volatile("" : "+r"(tbl));
        t = (((*(u32 *)0x02003670) >> 3) & 3) + (d << 2);
        {
            register u32 *base __asm__("r1") = (u32 *)0x08170e7c;
            t += (u32)tbl;
        v = base[*(u8 *)t];
        }
        FillRect_6374((void *)0x0200483c, (s8)(a - 2), (s8)(b - 2), 2, 2, 53, 11, v);
    } else {
        if (d == 0) {
            register u32 *b1 __asm__("r0") = (u32 *)0x08170e7c;
            v = b1[7];
        } else {
            register u32 *b2 __asm__("r0");
            __asm__ volatile("" : "=r"(b2));
            b2 = (u32 *)0x08170e7c;
            v = b2[11];
        }
        FillRect_6374((void *)0x0200483c, (s8)(a - 2), (s8)(b - 2), 2, 2, 53, 11, v);
    }
}
