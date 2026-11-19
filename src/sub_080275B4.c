/* Sub_080275B4 @ 0x080275B4 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_080275b4_MATCHED.c (registry: mmbcc/src/w35c_080275b4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DEA4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);

extern void sub_0800DD74(u32 a, u32 b);

void sub_080275B4(void)
{
    u32 base = 0x020038ac;
    u32 arg0 = 0x0871e4e4;
    u32 a1 = *(u32 *)(base + 4);
    u32 tbl = 0x0871c8a4;
    sub_0800DEA4(arg0, a1, 1, 1,
        *(u32 *)tbl + tbl, *(u32 *)base, 32);
    sub_0800DD74(0x03002440, 0x03002440);
}
