/* Task_45200 @ 0x08045200 (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
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

/* Task_45200 @0x08045200 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 156 bytes in built ROM.
 * Same 7x pattern with arg1=1; pointers from 0x08232C04..0x08232C3C. */
extern u32 gPtr08232C04[];

extern u32 gPtr08232C0C[];

extern u32 gPtr08232C14[];

extern u32 gPtr08232C1C[];

extern u32 gPtr08232C24[];

extern u32 gPtr08232C34[];

extern u32 gPtr08232C3C[];

__attribute__((section(".text.w5g_45200")))
void Task_45200(void)
{
    Gfx_BlitRequest(gPtr08232C04[0], 1, 1, 8, 0);
    Gfx_BlitRequest(gPtr08232C0C[0], 1, 3, 8, 0);
    Gfx_BlitRequest(gPtr08232C14[0], 1, 5, 8, 0);
    Gfx_BlitRequest(gPtr08232C1C[0], 1, 7, 8, 0);
    Gfx_BlitRequest(gPtr08232C24[0], 1, 9, 8, 0);
    Gfx_BlitRequest(gPtr08232C34[0], 1, 11, 8, 0);
    Gfx_BlitRequest(gPtr08232C3C[0], 1, 13, 8, 0);
}
