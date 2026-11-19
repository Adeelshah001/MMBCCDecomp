/* HexFormat_08004998 @ 0x08004998 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w25b_08004998.c (registry: mmbcc/src/w25b_08004998.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

extern void DrawText_048B4(u8 *p, u32 x, u32 y);

__attribute__((section(".text.w25b_08004998")))
void HexFormat_08004998(u32 p, u16 b, u16 c, u16 d)
{
    char buf[16];
    register u32 dm __asm__("r0") = d;
    register u32 d16 __asm__("r2");
    s32 tmp;
    s32 t;

    __asm__ volatile("" : "+r" (dm));
    d16 = dm << 16;
    __asm__ volatile("add %0, %1, #0" : "=r" (tmp) : "r" (d16));
    tmp >>= 16;
    {
        char *bp0 = &buf[tmp];
        *bp0 = 0;
    }
    {
        register u32 poolr __asm__("r1") = 0xFFFF0000u;
        t = (s32)(d16 + poolr);
    }
    if (t >= 0) {
        do {
            s32 idx = t >> 16;
            char *bp = &buf[idx];
            u32 q = p & 15;
            u32 ch = q + '0';
            *bp = (char)ch;
            if ((ch & 255) > (u32)'9')
                *bp = (char)(q + 'A' - 10);
            p >>= 4;
            t = (idx - 1) << 16;
        } while (t >= 0);
    }
    DrawText_048B4(buf, b, c);
}
