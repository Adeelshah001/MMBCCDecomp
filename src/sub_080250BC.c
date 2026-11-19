/* FindEntryIdx_080250BC @ 0x080250BC (74 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w19d_080250bc.c (registry: src/w19d_080250bc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08025024(void);

extern u16 sub_08025054(u16 idx);

extern u8 sub_0802663C(u8 *p, u16 v);

s8 sub_080250BC(u16 x)
{
    u8 *base = (u8 *)0x02007090;
    u16 i = 1;
    while (i < sub_08025024()) {
        if (sub_08025054(i) == x)
            return (s8)sub_0802663C(base + 24, i);
        i++;
    }
    return -1;
}
