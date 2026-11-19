/* EwSet16_128 @ 0x0804A3FC (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ew0200BD20 { u8 _00[128]; u16 f128; };

extern struct Ew0200BD20 gUnknown_0200BD20;

/* EWRAM u16 setter to 0, offset 128 of 0x0200BD20 (TENTATIVE name).
 * ROM 0x0804A3FC (10 B code). */
void sub_0804A3FC(void)
{
    gUnknown_0200BD20.f128 = 0;
}
