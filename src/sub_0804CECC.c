/* Sub_0804CECC @ 0x0804CECC (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0804cecc_MATCHED.c (registry: mmbcc/src/w35c_0804cecc_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804C288(u8 *s, u32 base);

void sub_0804CECC(u8 *s)
{
    register u8 *sp = s;
    u32 v = *(u32 *)(sp + 52);
    int cnt;
    u32 base;
    if (v != 0x68736d53)
        return;
    *(u32 *)(sp + 52) = v + 1;
    *(u32 *)(sp + 4) |= 0x80000000;
    cnt = sp[8];
    base = *(u32 *)(sp + 44);
    for (; cnt > 0; cnt--, base += 80)
        sub_0804C288(sp, base);
    *(u32 *)(sp + 52) = 0x68736d53;
}
