/* NotZero_08003078 @ 0x08003078 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_08003078.c (registry: src/w15c_08003078.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 sub_0800300C(u16 x);

u32 sub_08003078(u16 x)
{
    if (sub_0800300C(x) == 0)
        return 0;
    return 1;
}
