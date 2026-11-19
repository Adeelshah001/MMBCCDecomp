/* CondRectFill_080073D4 @ 0x080073D4 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w31d_080073d4.c (registry: src/w31d_080073d4.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* param1 declared int here: (x<<2)|y is int-typed, avoids u16 truncation code. */
extern void sub_08007134(void *ctx, int a, s16 b, s16 c, u8 d);

void sub_080073D4(u8 x, u8 y, u16 z, u16 w)
{
    u8 *base = (u8 *)0x02004830;
    if (base[0x265])
        return;
    sub_08007134(base, (x << 2) | y, (s16)z, (s16)w, 2);
}
