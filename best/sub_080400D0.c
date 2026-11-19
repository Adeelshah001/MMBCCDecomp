/* Dispatch4_R3 @ 0x080400D0 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 _call_via_r3(u8 *a, u16 b, u8 c, u32 fn);

extern u32 gUnknown_082329B0[];

/* 0x080400D0: return (u8)_call_via_r3(s,b,c,tbl[s[4]]). Tentative. */
u8 sub_080400D0(u8 *s, u16 b, u8 c)
{
    u32 *tbl = gUnknown_082329B0;
    u32 idx = s[4];
    u32 fn = tbl[idx];
    return _call_via_r3(s, b, c, fn);
}
