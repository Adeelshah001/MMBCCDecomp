/* Dispatch_081734F4_0 @ 0x0800CD38 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02000EC0[];

extern u32 gUnknown_081734F4[];

/* 0x0800CD38: s[8]=(u8)tbl[s[0]](s). Tentative. */
void sub_0800CD38(void)
{
    u8 *s = gUnknown_02000EC0;
    u32 *tbl = gUnknown_081734F4;
    u32 idx = s[0];
    s[8] = ((u8 (*)(u8 *))tbl[idx])(s);
}
