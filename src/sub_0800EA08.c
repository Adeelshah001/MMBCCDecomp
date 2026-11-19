/* EwramSet2_02005138 @ 0x0800EA08 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005130[];

/* 0x0800EA08 */
void sub_0800EA08(u8 a, u8 b)
{
    gUnknown_02005130[8] = a;
    gUnknown_02005130[9] = b;
}
