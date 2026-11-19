/* F_080248AC @ 0x080248AC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ew02007090 { u8 _00[18]; u16 f18; u8 *f20; };

extern struct Ew02007090 ew02007090;

extern void SetByte432_08026108(u8 *s, u8 v);

__attribute__((section(".text.w15b_080248ac")))
void F_080248AC(u8 v)
{
    SetByte432_08026108(ew02007090.f20, v);
}
