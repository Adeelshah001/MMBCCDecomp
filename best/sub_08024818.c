/* TblStride_24818 @ 0x08024818 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_D.c (registry: src/wave15_D.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_080258C0(u8 *s, u16 idx);

u8 sub_08024818(u16 idx)
{
    u8 * volatile *pp = (u8 * volatile *)0x2007090;
    u8 *p = pp[5];
    register u8 *q = p + (216 << 1);
    register u8 k = *q;
    return (u8)sub_080258C0(p + k * 144, idx);
}
