/* EwSet8_72 @ 0x08010364 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ew02005160 { u8 _00[68]; u8 f68; u8 _69[3]; u8 f72; };

extern struct Ew02005160 gUnknown_02005160;

/* EWRAM byte setter to 1, offset 72 of 0x02005160 (TENTATIVE name).
 * ROM 0x08010364 (10 B code). Called once from sub_0800EE8C. */
void sub_08010364(void)
{
    gUnknown_02005160.f72 = 1;
}
