/* SetU32_200 @ 0x08004158 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08004158: 0x200 materializes as movs r2,#0x80 / lsls r2,#2. */
void sub_08004158(u8 *s, u32 v)
{
    *(u32 *)(s + 0x200) = v;
}
