/* EwGet16_18 @ 0x08024760 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ew02007090 { u8 _00[18]; u16 f18; };

extern struct Ew02007090 ew02007090;

/* EWRAM u16 getter (TENTATIVE name).
 * ROM 0x08024760 (6 B code): return ew02007090.f18.
 * 14 bl callers in the 0x08042xxx-0x08045xxx range; one compares the
 * result against 7 (u16). */
__attribute__((section(".text.w3b_ewget16_18")))
u16 EwGet16_18(void)
{
    return ew02007090.f18;
}
