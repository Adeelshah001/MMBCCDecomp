/* F_EF8 @ 0x08000EF8 (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08000EF8(u8 *p)
{
    int i;
    u8 *a;
    u8 z;
    u8 *b;
    i = 0;
    a = p; a += 12;
    z = 0;
    b = p; b += 16;
    do {
        a[i] = z;
        *(u16 *)b = z;
        b += 2;
        i++;
    } while (i <= 3);
}
