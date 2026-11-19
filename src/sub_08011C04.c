/* EwramInit_02005260 @ 0x08011C04 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_02005260[];

/* 0x08011C04 */
void sub_08011C04(u32 v)
{
    u32 *p = (u32 *)gUnknown_02005260;
    p[0] = v;
    p[1] = v;
    p[2] = v + 0x10;
}
