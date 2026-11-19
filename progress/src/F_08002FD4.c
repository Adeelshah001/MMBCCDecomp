/* F_08002FD4 @ 0x08002FD4 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B_old.c (registry: src/wave15_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int TblValidate(u16 x);

extern void Fwd_0804c84c(u32 w, u32 n);

__attribute__((section(".text.w15b_08002fd4")))
void F_08002FD4(u16 x)
{
    u16 v = x;
    if (TblValidate(v)) {
        u8 *t1 = (u8 *)0x08106D7C;
        u8 *t2 = (u8 *)0x08106DD0;
        __asm__ volatile("" : "+r" (t1), "+r" (t2));
        {
            u16 h = *(u16 *)(t2 + v * 8 + 4);
            u32 w = *(u32 *)(t1 + h * 12);
            Fwd_0804c84c(w, 6);
        }
    }
}
