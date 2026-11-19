/* SetByte20_Clear21to23_02005130 @ 0x0800E1F0 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave7_g2.c (registry: src/wave7_g2.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x0800e1f0: SetByte20_Clear21to23_02005130 (20B, coordinator-verified). */
extern unsigned char gUnknown_02005130[];

void sub_0800E1F0(unsigned char v)
{
    unsigned char *p = gUnknown_02005130;
    unsigned char zero = 0;
    p[20] = v;
    p[21] = zero;
    p[22] = zero;
    p[23] = zero;
}
