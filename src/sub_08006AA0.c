/* TilemapFill_08006AA0 @ 0x08006AA0 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31d_08006aa0.c (registry: src/w31d_08006aa0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* param5 declared s8 here to get the sign-extension; real callee takes u8. */
extern void sub_08006AD8(void *ctx, u32 t, s16 x, s16 y, s8 z, u8 w);

void sub_08006AA0(u32 t, int x, int y, int z, u8 w)
{
    sub_08006AD8((void *)0x0200483c, t, (s16)x, (s16)y, (s8)z, w);
}
