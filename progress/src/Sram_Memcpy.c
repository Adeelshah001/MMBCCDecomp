/* Sram_Memcpy @ 0x0804DB38 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/sram.c (registry: src/sram.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed int s32;

__attribute__((section(".text.sram")))
void Sram_Memcpy(u8 *src, u8 *dst, u32 len)
{
    s32 n = (s32)len - 1;

    if (len == 0)
        return;
    do {
        *dst++ = *src++;
        n--;
    } while (n != -1);
}
