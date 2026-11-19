/* F_08001C88 @ 0x08001C88 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w24d_08001c88.c (registry: src/w24d_08001c88.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08001CA8(u8 *p, int i);

void sub_08001C88(void)
{
    int i = 0;
    u8 *p = (u8 *)0x02002F50;
    do {
        sub_08001CA8(p, i);
        p += 24;
        i++;
    } while (i <= 1);
}
