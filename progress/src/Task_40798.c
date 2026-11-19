/* Task_40798 @ 0x08040798 (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_g2.c (registry: src/wave5_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Task_40798 @0x08040798 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * 7x Gfx_BlitRequest(ptr[i], 0x2f, 1/3/5/7/9/11/13, 8, 0);
 * pointers from ROM 0x082325E4..0x0823261C. */
void Gfx_BlitRequest(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u32 gPtr082325E4[];

extern u32 gPtr082325EC[];

extern u32 gPtr082325F4[];

extern u32 gPtr082325FC[];

extern u32 gPtr08232604[];

extern u32 gPtr08232614[];

extern u32 gPtr0823261C[];

__attribute__((section(".text.w5g_40798")))
void Task_40798(void)
{
    Gfx_BlitRequest(gPtr082325E4[0], 0x2f, 1, 8, 0);
    Gfx_BlitRequest(gPtr082325EC[0], 0x2f, 3, 8, 0);
    Gfx_BlitRequest(gPtr082325F4[0], 0x2f, 5, 8, 0);
    Gfx_BlitRequest(gPtr082325FC[0], 0x2f, 7, 8, 0);
    Gfx_BlitRequest(gPtr08232604[0], 0x2f, 9, 8, 0);
    Gfx_BlitRequest(gPtr08232614[0], 0x2f, 11, 8, 0);
    Gfx_BlitRequest(gPtr0823261C[0], 0x2f, 13, 8, 0);
}
