/* Fwd_10BA0 @ 0x08010BA0 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_08010ba0.c (registry: src/w16b_08010ba0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08011170(u8 a);

extern u8 gUnknown_020051B0[];

void sub_08010BA0(void)
{
    u8 *base = gUnknown_020051B0;
    sub_08011170(base[2]);
}
