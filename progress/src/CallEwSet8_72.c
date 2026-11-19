/* CallEwSet8_72 @ 0x0800EE8C (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void EwSet8_72(void);

/* 0x0800EE8C: EwSet8_72(). Tentative. EwSet8_72 takes void; r0 is incidental. */
__attribute__((section(".text.w4i_callewset8_72")))
void CallEwSet8_72(u8 *s)
{
    EwSet8_72();
}
