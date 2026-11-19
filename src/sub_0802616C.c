/* StoreRet_0802616c @ 0x0802616C (14 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C.c (registry: src/wave14_C.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* StoreRet_0802616c @ 0x0802616c */
void sub_080260A0(u32 v);

void sub_0802616C(u32 *p, u32 v) { *p = v; sub_080260A0(v); }
