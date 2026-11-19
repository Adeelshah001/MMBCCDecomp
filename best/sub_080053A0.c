/* Sub_080053A0 @ 0x080053A0 (148 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_080053a0_MATCHED.c (registry: mmbcc/src/w36d_080053a0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08005434(u32 *p, u32 a, u32 b);

void sub_080053A0(void)
{
    register u8 *base = (u8 *)0x02003670;
    register u32 *p1 = (u32 *)(base + 1140);
    register u32 v2 = 0x06004000;
    p1[0] = 0x06001000;
    p1[1] = v2;
    sub_08005434(p1, 0, 0);
    p1[5] = 240 << 7;
    p1[6] = 160 << 7;
    p1 = (u32 *)(base + 4);
    *(u32 *)(base + 4) = (u32)(base + 1708);
    p1[1] = v2;
    sub_08005434(p1, 0, 0);
    {
        register u32 *p3 = (u32 *)(base + 572);
        u8 flag;
        u8 t;
        u32 a1;
        u32 a2;
        p3[0] = 0x06003000;
        p3[1] = 0x0600c000;
        base = base + 4526;
        flag = *base;
        t = (u8)(4 & flag);
        a1 = 112;
        if (t != 0) a1 = 120;
        a2 = 72;
        if (t != 0) a2 = 80;
        sub_08005434(p3, a1, a2);
    }
}
