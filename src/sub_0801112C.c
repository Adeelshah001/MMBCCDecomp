/* Sub_0801112C @ 0x0801112C (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0801112c_MATCHED.c (registry: mmbcc/src/w35c_0801112c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern s16 sub_08016F98(u8 a);

extern u8 sub_08016FAC(u8 a, u8 i);

extern void sub_08002C24(u8 v);

void sub_0801112C(u8 a)
{
    s16 n = sub_08016F98(a);
    s16 i;
    if (n <= 0)
        return;
    for (i = 0; i < n; i++)
        sub_08002C24((u8)sub_08016FAC(a, (u8)i));
}
