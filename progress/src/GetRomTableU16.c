/* GetRomTableU16 @ 0x080266F0 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 rom0822740C[];

/* 0x080266F0: return *(u16*)(0x0822740C + (idx<<4) + 6). Tentative.
 * 16-byte stride table in ROM; sibling accessor at 0x08026700 (batch2)
 * reads u8 at +11. */
__attribute__((section(".text.w3a_getromtableu16")))
u16 GetRomTableU16(u8 idx)
{
    u8 *base = rom0822740C;
    return *(u16 *)(base + ((u16)idx << 4) + 6);
}
