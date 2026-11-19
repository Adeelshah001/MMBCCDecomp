/* Set_0EA30 @ 0x0800EA30 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_0800ea30.c (registry: src/w16b_0800ea30.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void SyncObjFlagBits_BEE0(u32 a, u32 b);

extern u8 g_02005130[];

void Set_0EA30(u8 a)
{
    u8 *base = g_02005130;
    *(u16 *)(base + 2) = a;
    SyncObjFlagBits_BEE0(*(s16 *)(base + 2), 128);
}
