/* Decode_23B88 @ 0x08023B88 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_B_old.c (registry: src/wave11_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08023B88 (60 B): 24-element u16 decoder loop. For each str[i]:
 * if (u16)(v-1) <= 9, decrement; else if (u16)(v-94) <= 26, subtract 84. */
void sub_08023B88(u16 *str)
{
    u8 i = 0;
    do {
        if ((u16)(str[i] - 1) <= 9) {
            str[i]--;
        } else if ((u16)(str[i] - 94) <= 26) {
            str[i] -= 84;
        }
        i++;
    } while (i <= 23);
}
