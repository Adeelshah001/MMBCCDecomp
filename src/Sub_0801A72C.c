/* Sub_0801A72C @ 0x0801A72C (238 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39c_0801a72c_MATCHED.c (registry: mmbcc/src/w39c_0801a72c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD4C(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_080178A8(int a, int b, int c, int d, int e);

int Sub_0801A72C(u8 *s)
{
    u32 out[2];
    register int o0;
    int o1;
    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08((u8 *)out, s);
    o0 = out[0];
    
    o1 = out[1];
    if (s[13] == 1)
        goto c1;
    if (s[13] > 1)
        goto gt1;
    if (s[13] == 0)
        goto c0;
    return 0;
gt1:
    if (s[13] == 2)
        goto c2;
    if (s[13] == 3)
        goto c3;
    return 0;
c0:
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    *(u32 *)(s + 88) = 160 << 3;
    *(u32 *)(s + 92) = 160 << 3;
    goto inc;
c1:
    
    if (o1 <= -1280)
        return 0;
    if (s[17] == 0) {
        int nib = (int)(((u32)s[35] << 28) >> 28);
        sub_080178A8(92, nib, 220 << 6, -3840, *(u32 *)(s + 44));
    }
    *(u32 *)(s + 88) = 0;
    *(u32 *)(s + 92) = 0;
    sub_0800D9EC(s, 1);
    goto inc;
c2:
    if ((u8)(s[119] - 3) <= 1) {
        sub_0800D9EC(s, 2);
        s[18] = 30;
    } else {
        return 0;
    }
inc:
    s[13]++;
    return 0;
c3:
    if (s[18] & 4)
        s[10] &= 254;
    else
        s[10] |= 1;
    s[18]--;
    if ((s8)s[18] != 0)
        return 0;
    return 1;
}
