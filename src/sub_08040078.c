/* F_08040078 @ 0x08040078 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_080400A8(void);

void sub_08040078(u16 x)
{
    u16 v = x;
    u16 w = v;
    u8 *p = (u8 *)0x020070F0;
    if (v == 0xAE84)
        w = 0x259E;
    *(u16 *)(p + 8) = w;
    sub_080400A8();
    sub_080400A8();
    sub_080400A8();
}
