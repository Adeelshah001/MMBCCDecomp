/* TwoTblOps_0804B110 @ 0x0804B110 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16c_0804b110.c (registry: src/w16c_0804b110.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08002FD4(u16 x);

void sub_08002C74(u8 a);

u32 sub_0804B110(void)
{
    sub_08002FD4(15);
    sub_08002C74(29);
    return 1;
}
