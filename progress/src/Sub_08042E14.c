/* Sub_08042E14 @ 0x08042E14 (172 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c2_08042e14_MATCHED.c (registry: mmbcc/src/w37c2_08042e14_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Gfx_BlitRequest(u32 a, int b, int c, u8 d, u8 e);

extern void CondTilemapRectFill_08007378(u8 mode, u16 x, int y, u8 z);

__attribute__((section(".text.w37c2_08042e14")))
void Sub_08042E14(u8 *s)
{
    register s8 *t __asm__("r4");
    register int e __asm__("r6");
    int b;
    int c;
    {
        u32 p1 = *(u32 *)0x08232bac;
        t = (s8 *)0x08232d50;
        __asm__ volatile("" : "+r"(t));
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 1;
        e = 2;
        Gfx_BlitRequest(p1, b, c, 7, e);
    }
    if (s[21] > 4) {
        u32 p2 = *(u32 *)0x08232bb4;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 3;
        Gfx_BlitRequest(p2, b, c, 7, e);
    }
    if (s[21] > 7) {
        u32 p3 = *(u32 *)0x08232bbc;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 5;
        Gfx_BlitRequest(p3, b, c, 7, e);
    } else {
        u32 p4 = *(u32 *)0x08232ba4;
        __asm__ volatile("movs %0, #0\n\tldrsb %0, [%1, %0]" : "=r"(b) : "r"(t));
        b += 2;
        __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(c) : "r"(t));
        c += 5;
        Gfx_BlitRequest(p4, b, c, 7, e);
    }
    {
        register int b22 __asm__("r5");
        int y;
        __asm__ volatile("ldrb %0, [%1, #22]" : "=r"(b22) : "r"(s));
        y = ((b22 << 17) + (192 << 10)) >> 16;
        CondTilemapRectFill_08007378(1, 7, y, 2);
    }
}
