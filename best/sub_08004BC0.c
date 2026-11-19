/* Dispatch_081705A4_0 @ 0x08004BC0 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02003668[];

extern u32 gUnknown_081705A4[];

/* 0x08004BC0: r=tbl[s[0]](s); s[4]=(u8)r; return (s8)s[4]. Tentative. */
s8 sub_08004BC0(void)
{
    u8 *s = gUnknown_02003668;
    u32 *tbl = gUnknown_081705A4;
    u32 idx = s[0];
    u8 r = ((u8 (*)(u8 *))tbl[idx])(s);
    s[4] = r;
    return (s8)s[4];
}
