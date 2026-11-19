/* Sub_08023D68 @ 0x08023D68 (110 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08023d68_MATCHED.c (registry: mmbcc/src/w36b_08023d68_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_0804DE70(int x, int y);

extern int sub_0804DEE8(int x, int y);

void sub_08023D68(u8 *src, u16 *dst)
{
    u8 i;
    u8 j;
    u16 acc;
    for (i = 0; i < 24; i++) {
        acc = 0;
        for (j = 0; j <= 14; j++) {
            acc = ((u8)acc << 8) | src[j];
            if (acc > 35) {
                src[j] = sub_0804DE70(acc, 36);
                acc = (u16)sub_0804DEE8(acc, 36);
            } else {
                src[j] = 0;
            }
        }
        dst[i] = acc;
    }
}
