/* SetBit_08007eec @ 0x08007EEC (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08007eec_MATCHED.c (registry: mmbcc/src/w36a_08007eec_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD74(u8 *p);

void sub_08007EEC(u16 idx)
{
    u8 *p = (u8 *)0x02004e18 + idx * 8;
    u8 m = 2;
    u16 *g = (u16 *)0x08171ef4;
    p[7] |= m;
    if (idx == 0) {
        register u16 v = g[1];
        register u32 t = v << 5;
        t += 0x03002420;
        sub_0800DD74((u8 *)t);
    }
}
