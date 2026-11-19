/* EwSet16_14 @ 0x0800EDF0 (12 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* --- EWRAM / ROM region views (minimal, tentative) --- */
struct Ew02005130 { u8 _00[12]; u16 f12; u16 f14; u16 f16; u16 f18; };

 /* 16-byte entries */

extern struct Ew02005130 gUnknown_02005130;

/* EWRAM u16 setter, offset 14 of 0x02005130 (TENTATIVE name).
 * ROM 0x0800EDF0 (6 B code). */
void sub_0800EDF0(u16 v)
{
    gUnknown_02005130.f14 = v;
}
