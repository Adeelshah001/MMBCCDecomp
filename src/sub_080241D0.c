/* Sub_080241D0 @ 0x080241D0 (38 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_080241d0_MATCHED.c (registry: staging/wave34_C/w34c_080241d0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_080242A8(u16 a, int zero);

extern int sub_080241F8(u16 a);

u8 sub_080241D0(u32 a)
{
    u16 aa = a;
    u8 r = sub_080242A8(aa, 0);
    if (r == 0)
        r = sub_080241F8(aa);
    return r;
}
