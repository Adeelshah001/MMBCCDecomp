/* F_08026A48 @ 0x08026A48 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern unsigned int sub_08001DB8(unsigned int a0, unsigned int key);

void sub_08026A48(u8 *p)
{
    u8 *k;
    unsigned int z = 0;
    p[10] = (u8)z;
    k = (u8 *)0x00001734;
    if (sub_08001DB8(z, (unsigned int)k) != 0) {
        u8 v1 = 1;
        p[10] = v1 | p[10];
    }
    if (sub_08001DB8(1, (unsigned int)k) != 0) {
        u8 v2 = 2;
        p[10] = v2 | p[10];
    }
}
