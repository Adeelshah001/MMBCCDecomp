/* Shift_080008c0 @ 0x080008C0 (88 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_080008c0_MATCHED.c (registry: mmbcc/src/w36a_080008c0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08000A1C(void);

extern void HBlank_RasterSetup(void);

__attribute__((section(".text.w36a_080008c0")))
void Shift_080008c0(void)
{
    u32 *B = (u32 *)0x03000580;
    B[-6] = B[-3];
    B[-5] = B[-2];
    B[-4] = B[-1];
    B[-1] = 0;
    sub_08000A1C();
    B[0] = B[4];
    B[1] = B[5];
    B[2] = B[6];
    B[6] = 0;
    B += 7;
    B[0] = B[4];
    B[1] = B[5];
    B[2] = B[6];
    B[6] = 0;
    HBlank_RasterSetup();
}
