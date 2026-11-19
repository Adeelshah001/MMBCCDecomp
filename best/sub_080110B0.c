/* PairDiffMid_110B0 @ 0x080110B0 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_u_old.c (registry: src/wave8_u_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

typedef struct {
    s32 x;
    s32 y;
} Pair32;

void sub_080110B0(const Pair32 *a, Pair32 *b)
{
    register s32 x;
    register s32 y;
    register s32 d;
    register s32 m;

    y = a->y;
    x = a->x;
    d = x - y;
    m = (y >> 1) + (x >> 1);
    b->x = d;
    b->y = m;
}
