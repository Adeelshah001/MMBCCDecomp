/* Sub_08001AE4 @ 0x08001AE4 (276 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w46c_08001ae4_MATCHED.c (registry: src/w46c_08001ae4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08001754(u8 v, int n);

void sub_08001AE4(void)
{
    u8 *p = (u8 *)0x02002ee0;
    volatile u8 *g;
    register int cnt;
    u16 c16;
    cnt = *(u16 *)(p + 6);
    cnt++;
    *(u16 *)(p + 6) = cnt;
    c16 = (u16)cnt;
    g = p;
    if (c16 == 1)
        goto def;
    if ((*(u16 *)(g + 2) & 2) == 0)
        goto test4;
    cnt &= 1;
    if (cnt == 0)
        goto test65;
    if (g[62] == 0)
        goto test65;
    *(u16 *)0x0400012a = sub_08001754(g[62], 3);
    (void)g[62];
    g[62] = 0;
    return;
test65:
    if (g[65] == 0)
        goto def;
    *(u16 *)0x0400012a = *(u16 *)(g + 66);
    return;
test4:
    if ((*(volatile u16 *)(g + 2) & 4) == 0)
        goto def;
    if (g[4] > 1)
        goto def;
    if (g[4] != 0)
        goto b4eq1;
    cnt &= 1;
    if (cnt != 0)
        goto b4eq1;
    if ((g[9] & 32) == 0)
        goto b4eq1;
    *(u16 *)0x0400012a = *(u16 *)(g + 48);
    return;
b4eq1:
    if (g[4] != 1)
        goto test10;
    if ((3 & *(u16 *)(g + 6)) != 0)
        goto test10;
    if (g[11] != 31)
        goto test10;
    *(u16 *)0x0400012a = *(u16 *)(g + 48);
    return;
test10:
    if (g[10] == 0)
        goto def;
    if (g[10] == 1) {
        *(u16 *)0x0400012a = *(u16 *)(g + 44);
        goto tailinc;
    }
    if (g[10] == 2) {
        *(u16 *)0x0400012a = *(u16 *)(g + 46);
        goto tailinc;
    }
tailinc:
    {
        int t = g[10] + 1;
        (void)g[10];
        g[10] = t;
    }
    if (g[10] <= 2)
        return;
    (void)g[10];
    g[10] = 1;
    return;
def:
    *(u16 *)0x0400012a = 0x0fff;
    return;
}
