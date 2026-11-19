/* FlagBitClear_10498 @ 0x08010498 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_D_old.c (registry: src/wave14_D_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


unsigned int sub_08010498(unsigned char a)
{
    unsigned char *p = (unsigned char *)0x02005168;
    unsigned char v;
    if (a == 1)
        p += 20;
    v = p[16];
    if ((v & 2) != 0) {
        if ((v & 1) != 0) {
            register unsigned int t;
            t = v & -2;
            p[16] = (unsigned char)t;
        }
        return 0;
    } else {
        return 1;
    }
}
