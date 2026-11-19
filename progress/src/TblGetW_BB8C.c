/* TblGetW_BB8C @ 0x080246A8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 rom0822BB8C[];

__attribute__((section(".text.w8s_080246a8")))
u32 TblGetW_BB8C(u16 idx)
{
    register u32 i __asm__("r1") = idx;
    u32 *base;
    if (i > 248)
        return 0;
    base = rom0822BB8C;
    return base[i];
}
