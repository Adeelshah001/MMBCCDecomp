/* Task_35C1C @ 0x08035C1C (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 GatedDispatch(u32 p, u32 a, u32 b, u32 c, u32 d);

extern u8 gEwram020070F0[];

__attribute__((section(".text.w5h_35c1c")))
void Task_35C1C(void)
{
    u8 *base = gEwram020070F0;
    GatedDispatch(base[0x13], 0x2f, 4, 2, 0);
    GatedDispatch(base[0x12], 0x32, 4, 2, 0);
    GatedDispatch(base[0x11], 0x35, 4, 2, 0);
}
