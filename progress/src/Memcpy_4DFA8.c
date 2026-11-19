/* Memcpy_4DFA8 @ 0x0804DFA8 (94 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_c_noiw.c (registry: src/wave9_c_noiw.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0804DFA8: optimized memcpy (94 B).
 * Word path (len > 15, both 4-aligned): 4x ldmia/stmia unrolled loop,
 * then single-word tail. Byte tail uses the len-1 vs -1 idiom. */
__attribute__((section(".text.w9c_memcpy_4dfa8")))
void *Memcpy_4DFA8(void *dst, const void *src, u32 len)
{
    const u8 *s;
    u8 *d;

    d = (u8 *)dst;
    s = (const u8 *)src;

    if (len > 15 && ((((u32)s) | ((u32)d)) & 3) == 0) {
        u32 *dw = (u32 *)dst;
        register const u32 *sw __asm__("r3") = (const u32 *)s;
        do {
            *dw++ = *sw++;
            *dw++ = *sw++;
            *dw++ = *sw++;
            *dw++ = *sw++;
            len -= 16;
        } while (len > 15);
        while (len > 3) {
            *dw++ = *sw++;
            len -= 4;
        }
        d = (u8 *)dw;
        s = (const u8 *)sw;
    }
    {
        u32 n = len - 1;
        if (n != (u32)-1) {
            do {
                *d++ = *s++;
            } while (--n != (u32)-1);
        }
    }
    return dst;
}
