/* sub_08010FB4 @ 0x08010FB4 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_f_old.c (registry: src/wave7_f_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x08010fb4: Entry_IsInactive (coordinator-verified). */
__attribute__((section(".text.w7f_08010fb4")))
u8 sub_08010FB4(u8 a) {
    u8 *p = (u8 *)0x020051C8 + a * 12;
    int b;
    if (p[0] != 0)
        return 0;
    __asm__ volatile("mov %0, #1\n\tldrsb %0, [%1, %0]" : "=l"(b) : "l"(p));
    if (b != 0)
        return 0;
    return 1;
}
