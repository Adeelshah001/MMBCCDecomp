/* ChkFlag_080247E8 @ 0x080247E8 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20d_080247e8.c (registry: src/w20d_080247e8.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 TblGet11(u8 a);

extern u8 sub_08025524(u8 *p, u8 x);

__attribute__((section(".text.w20d_080247E8")))
u8 ChkFlag_080247E8(u8 a)
{
    register u8 *p __asm__("r5") = (u8 *)0x02007090;
    if ((TblGet11(a) & 2) != 0) {
        return 0;
    }
    return (u8)sub_08025524(p, a);
}
