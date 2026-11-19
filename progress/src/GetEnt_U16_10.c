/* GetEnt_U16_10 @ 0x08024F48 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u16 GetU16_10(u8 *s);

extern u8 ew02007090[];

/* 0x08024F48: return GetU16_10(b+i*144). Tentative. */
__attribute__((section(".text.w4i_getent_u16_10")))
u16 GetEnt_U16_10(void)
{
    u8 *base = ew02007090;
    u8 *b = *(u8 **)(base + 0x14);
    u8 i = b[0x1b0];
    return GetU16_10(b + i * 144);
}
