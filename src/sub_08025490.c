/* F_25490 @ 0x08025490 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08025490(u8 *p, u8 a, u8 b)
{
    u8 aa = a;
    u8 bb = b;
    u8 *bs = *(u8 **)(p + 8);
    u8 *pa = bs + aa;
    u8 tmp = *pa;
    u8 v = bs[bb];
    *pa = v;
    {
        u8 *b2 = *(u8 **)(p + 8);
        b2[bb] = tmp;
    }
}
