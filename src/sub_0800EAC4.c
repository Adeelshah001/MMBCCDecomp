/* CopyBytes_0800EAC4 @ 0x0800EAC4 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0800eac4.c (registry: src/w15c_0800eac4.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005130[];

extern u8 gUnknown_02005168[];

void sub_0800E1F0(u8 x);

void sub_0800EAC4(u8 a, u8 b)
{
    gUnknown_02005130[6] = a;
    gUnknown_02005130[4] = a;
    gUnknown_02005130[7] = b;
    gUnknown_02005130[5] = b;
    gUnknown_02005168[10] = gUnknown_02005130[8];
    gUnknown_02005168[30] = gUnknown_02005130[9];
    sub_0800E1F0(1);
}
