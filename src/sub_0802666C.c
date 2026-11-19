/* Sub_2666C @ 0x0802666C (62 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_0802666c.c (registry: src/w16b_0802666c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u8 sub_08025290(u8 *p, u16 idx);

int sub_0802526C(void *s, u8 v);

void sub_0802666C(u8 *s, u16 idx)
{
    u8 v;
    if (idx == 0)
        return;
    if (idx >= *(u16 *)(s + 22))
        return;
    v = sub_08025290(s + 16, idx);
    sub_0802526C(s + 8, v);
    *(*(u8 **)(s + 4) + v * 28 + 25) = 0;
}
