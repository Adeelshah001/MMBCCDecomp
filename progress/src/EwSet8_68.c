/* EwSet8_68 @ 0x0800EE44 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ew02005160 { u8 _00[68]; u8 f68; u8 _69[3]; u8 f72; };

extern struct Ew02005160 g_02005160;

/* EWRAM byte setter, offset 68 of 0x02005160 (TENTATIVE name).
 * ROM 0x0800EE44 (8 B code). */
__attribute__((section(".text.w3b_ewset8_68")))
void EwSet8_68(u8 v)
{
    g_02005160.f68 = v;
}
