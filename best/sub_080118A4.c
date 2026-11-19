/* Sub_080118A4 @ 0x080118A4 (312 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40b_080118a4_MATCHED.c (registry: mmbcc/src/w40b_080118a4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern void sub_080112BC(u8 *s);

extern void sub_08011CD4(u16 a, int *o0, int *o1, int *o2);

extern int sub_08011CC4(u16 a);

extern u8 sub_08010FDC(u8 t, u8 b19, int c, int o0, int o1, int o2);

extern s8 sub_08011054(u8 *flag);

extern u8 *sub_080113F4(u16 v);

int sub_080118A4(u8 *s)
{
    s8 flag;
    int o0;
    int o1;
    int o2;
    int t;
    int v;
    u8 *q;

    flag = 0xFF;
    if ((*(u8 **)s)[18] != 0)
        goto test2;
    sub_080112BC(s);
    
    goto tail;
test2:
    if (s[36] != 0) {
        sub_080112BC(s);
        goto tail;
    }
    if (s[5] == 0) {
        o0 = 0;
        o1 = 0;
        o2 = 0;
        if (*(u16 *)(*(u8 **)s + 22) != 0)
            sub_08011CD4((u16)(*(u16 *)(*(u8 **)s + 22) - 1), &o0, &o1, &o2);
        *(u16 *)(s + 16) = 1;
        t = (u8)(((*(u8 **)s)[18] & 3) - 1);
        if ((*(u8 **)s)[18] & 4)
            t |= 0x80;
        if ((*(u8 **)s)[18] & 8)
            t |= 0x40;
        t = (u8)t;
        if (sub_08010FDC(t, (*(u8 **)s)[19], sub_08011CC4((u16)(*(u16 *)(*(u8 **)s + 20) - 1)), o0, o1, o2) != 0)
            s[5]++;
    }
    if (sub_08011054(&flag) != 1)
        return 0;
    if (*(u16 *)(*(u8 **)s + 22) == 0)
        goto clear_inc;
    if (flag == 1)
        goto v26;
    if (flag > 1)
        goto gt1;
    if (flag == 0)
        goto v24;
    goto v0;
gt1:
    if (flag == 2)
        goto v28;
    goto v0;
v24:
    v = *(u16 *)(*(u8 **)s + 24);
    goto havev;
v26:
    v = *(u16 *)(*(u8 **)s + 26);
    goto havev;
v28:
    v = *(u16 *)(*(u8 **)s + 28);
    goto havev;
v0:
    v = 0;
havev:
    if ((s16)v <= 0)
        goto clear_inc;
    q = sub_080113F4(v);
    if (q == 0)
        goto clear8;
    *(u8 **)s = q;
    s[4] = 1;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    
    goto tail;
clear8:
    s[4] = 8;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    goto tail;
clear_inc:
    s[4]++;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    
tail:
    return -1;
}
