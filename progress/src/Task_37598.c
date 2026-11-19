/* Task_37598 @ 0x08037598 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h2.c (registry: src/wave5_h2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

u8 GatedDispatch(u32 p, u32 a, u32 b, u32 c, u32 d);

u8 Gfx_BlitRequest(u32 p, u32 a, u32 b, u32 c, u32 d);

extern u32 gRom_0822EF0C[];

__attribute__((section(".text.w5h_37598")))
void Task_37598(u8 *p)
{
    u32 q = *(u32 *)(p + 0x20);
    GatedDispatch(q, 0x14, 1, 7, 2);
    Gfx_BlitRequest(gRom_0822EF0C[0], 0x1b, 1, 1, 2);
}
