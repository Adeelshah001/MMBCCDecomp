/* TblGet11 @ 0x08026710 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Rom0822740C { u8 _00[11]; u8 f11; u8 _0C[4]; };

extern struct Rom0822740C rom0822740C[];

/* ROM table byte lookup (TENTATIVE name).
 * ROM 0x08026710 (12 B code): return rom0822740C[(u8)a].f11.
 * 16-byte entries; the struct view is what reproduces the ROM's
 * interleaved scheduling (pool load between the two shifts). Callers
 * truncate the result to u8. 6 bl callers. */
__attribute__((section(".text.w3b_tblget11")))
u8 TblGet11(u8 a)
{
    return rom0822740C[a].f11;
}
