/* FlagSet_08026F98 @ 0x08026F98 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef int s32;

__attribute__((section(".text.w8r_08026f98")))
void FlagSet_08026F98(u8 x) {
    u16 *p = (u16 *)0x020031E0;
    u16 v;

    v = *p;
    v |= 144 << 5;
    *p = v;
    {
        register u8 *b __asm__("r2") = (u8 *)0x02003670;
        s32 t;

        __asm__ volatile("" : "+r"(b));
        t = (x | -x) >> 31;
        t &= 32;
        b += 0x11AC;
        *b = (u8)t;
    }
}
