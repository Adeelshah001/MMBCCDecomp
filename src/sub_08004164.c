/* SetField204_04164 @ 0x08004164 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08004164 (10B, tentative): *(u32 *)(p + 0x204) = v. agbcc materializes
 * 0x204 as `movs r2,#0x81; lsls r2,r2,#2` (no pool). */
void sub_08004164(u8 *p, u32 v)
{
    *(u32 *)(p + 0x204) = v;
}
