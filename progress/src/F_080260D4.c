/* F_080260D4 @ 0x080260D4 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33d_080260d4.c (registry: src/w33d_080260d4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern void SetIfGt199(u8 *s, u8 a, u8 b);

__attribute__((section(".text.w33d_080260d4")))
void F_080260D4(u8 *a0, u8 a1, u8 a2)
{
    s16 i = 0;
    do {
        SetIfGt199(a0 + (s32)i * 144, a1, a2);
        {
            s32 t = (s32)i + 1;
            __asm__ volatile("" : "+r" (t));
            i = (s16)t;
        }
    } while (i <= 2);
}
