/* F_08025070 @ 0x08025070 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ew02007090 { u8 _00[18]; u16 f18; u8 *f20; };

extern struct Ew02007090 gUnknown_02007090;

extern u16 sub_0802663C(const void *p, u16 idx);

u8 sub_08025070(u16 idx)
{
    const u8 *p = (const u8 *)&gUnknown_02007090;
    return (u8)sub_0802663C(p + 24, idx);
}
