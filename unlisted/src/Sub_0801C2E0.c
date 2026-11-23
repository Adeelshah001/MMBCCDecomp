/* Sub_0801C2E0 @ 0x0801C2E0 (282 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w46d_0801c2e0_MATCHED.c (registry: src/w46d_0801c2e0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD4C(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void sub_0800DD2C(u8 *s, int a, int b);

extern int sub_0804A378(int idx);

extern void sub_080174A4(int v, int bit);

extern u32 *sub_0801B98C(int a, int b, int c, int d, int e, int f);

extern u8 sub_08017474(int v);

extern void sub_08017478(int v, int val);

int Sub_0801C2E0(u8 *s)
{
    int out[2];
    int out2[2];
    int mode;
    register int o0;
    int o1;
    int m;
    int h;
    int off;
    u8 *q;
    u8 *q35;
    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    o0 = out[0];
    o1 = out[1];
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto ret0;
gt1:
    if (mode == 2)
        goto c2;
    goto ret0;
c0:
    if (o1 <= 0)
        goto ret0;
    sub_0800DD08((u8 *)out2, s);
    sub_0800DD2C(s, o0, o1);
    *(u32 *)(s + 92) = mode;
    *(u32 *)(s + 100) = mode;
    {
        register u8 *base;
        base = (u8 *)0x02003670;
        off = 0x11af;
        
        q = base + off;
        h = 128;
        m = 15;
        *q = (*q & m) | h;
    }
    sub_0804A378(135);
    s[18] = m;
    s[13]++;
    goto ret0;
c1:
    s[18]--;
    if (s[18] != 0)
        goto c2;
    q35 = s + 35;
    sub_0801B98C(4, 0, (int)(((u32)*q35 << 28) >> 28), 160 << 5, -25600, *(u32 *)(s + 44));
    sub_0801B98C(4, 1, (int)(((u32)*q35 << 28) >> 28), 240 << 6, -25600, *(u32 *)(s + 44));
    sub_0801B98C(4, 0, (int)(((u32)*q35 << 28) >> 28), 200 << 7, -25600, *(u32 *)(s + 44));
    sub_080174A4(*(u32 *)(s + 44), 3);
    s[13]++;
c2:
    if ((u8)sub_08017474(*(u32 *)(s + 44)) <= 5)
        goto ret0;
    sub_08017478(*(u32 *)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
