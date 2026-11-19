/* Flag17Init_0804B954 @ 0x0804B954 (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_0804b954.c (registry: src/w16c_0804b954.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08002FD4(u16 x);

u32 sub_0804B954(u8 *p)
{
    if (p[1] == 0) {
        p[1] = 1;
        sub_08002FD4(17);
    }
    return 1;
}
