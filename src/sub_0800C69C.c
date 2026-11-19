/* FillWrap_0800C69C @ 0x0800C69C (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800c69c.c (registry: src/w15c_0800c69c.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_0800C3A0(u16 *base, u16 c);

void sub_0800C69C(u16 d, u16 *base, u32 c) { sub_0800C3A0(base, (u16)c); }
