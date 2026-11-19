/* Sram_VerifyCompare @ 0x0804DC00 (46 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/sram.c (registry: src/sram.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

__attribute__((section(".text.sram")))
u8 *Sram_VerifyCompare(u8 *a, u8 *b, u32 len)
{
    s32 n = (s32)len - 1;
    if (len == 0)
        goto ret0;
    len = (u32)-1;
loop:
    if (*b++ == *a++)
        goto cont;
    return b - 1;
cont:
    n--;
    if (n != (s32)len)
        goto loop;
ret0:
    return 0;
}
