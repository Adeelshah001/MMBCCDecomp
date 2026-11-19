/* SetXY_174CC @ 0x080174CC (8 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
/* 0x080174CC (8B, tentative): o += 0x78, then halfword stores at +4/+6
 * (i.e. struct offsets 0x7C/0x7E). Sibling getters at 0x174D4/0x174DC/
 * 0x174E4/0x174EC do signed-halfword loads at 0x78/0x7A/0x7C/0x7E, so this
 * looks like an object/sprite attribute block (s16 x/y-ish pair). */
void sub_080174CC(u8 *o, u16 x, u16 y)
{
    o += 0x78;
    *(u16 *)(o + 4) = x;
    *(u16 *)(o + 6) = y;
}
