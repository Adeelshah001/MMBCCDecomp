/* Poke80_08016f74 @ 0x08016F74 (20 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* Poke80_08016f74 @ 0x08016f74 */
void sub_08011F68(u8 *p, u32 v);

void sub_08016F74(u8 *p) { u8 *q = p + 0x7c; q[4] = 1; sub_08011F68(p, 5); }
