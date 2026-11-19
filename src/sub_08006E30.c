/* Sub_08006E30 @ 0x08006E30 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08006e30_MATCHED.c (registry: mmbcc/src/w35c_08006e30_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern u8 sub_08006E6C(void *p, void *a, s16 b, s16 c, s8 d, u8 e);

u8 sub_08006E30(void *a, s16 b, s16 c, s8 d, u8 e)
{
    return sub_08006E6C((void *)0x0200483c, a, b, c, d, e);
}
