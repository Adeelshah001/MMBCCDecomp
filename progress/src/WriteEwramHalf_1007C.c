/* WriteEwramHalf_1007C @ 0x0801007C (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Unmatched callees / absolute data (defined via .set at end of file). */
extern u8 g_02005160[];

/* 0x0801007C (8B + pool, tentative): *(u16 *)(0x02005160 + 0x46) = v.
 * The base must go through a u32 local: agbcc constant-folds
 * `(u8 *)0x02005160 + 0x46` into a single pool word, but the ROM does
 * `ldr r1,[pc,#4]` (pool = 0x02005160) + `adds r1,#0x46`. */
__attribute__((section(".text.w3e_ewramh_1007c")))
void WriteEwramHalf_1007C(u16 v)
{
    u32 base = (u32)g_02005160;
    *(u16 *)(base + 0x46) = v;
}
