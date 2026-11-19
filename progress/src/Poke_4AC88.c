/* Poke_4AC88 @ 0x0804AC88 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_B_old.c (registry: src/wave11_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0804AC88 (36 B incl pool): byte pokes at 0x0200BD20.
 * p[127] = 0; p[126] = 0; p[160]++; p[161] = a. */
__attribute__((section(".text.w11b_0804ac88")))
void Poke_4AC88(u8 a)
{
    u8 *p = (u8 *)0x0200BD20;
    p[127] = 0;
    p[126] = 0;
    p[160]++;
    p[161] = a;
}
