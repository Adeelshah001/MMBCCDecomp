/* Sub_08018FB8 @ 0x08018FB8 (216 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38a_08018fb8_MATCHED.c (registry: mmcc/src/w38a_08018fb8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800DD4C(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_080174A4(u8 *s, int bit);

extern u32 *sub_080178A8(int a, int b, int c, int d, u8 *e);

extern u8 sub_08017474(u8 *p);

extern void sub_08017478(u8 *s, int v);

int Sub_08018FB8(u8 *s)
{
    u32 out[2];
    int mode;
    sub_0800DD4C(s, *(s32 *)(s + 88), *(s32 *)(s + 92));
    *(s32 *)(s + 88) += *(s32 *)(s + 96);
    *(s32 *)(s + 92) += *(s32 *)(s + 100);
    sub_0800DD08(out, s);
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    return 0;
gt1:
    if (mode == 2)
        goto c2;
    return 0;
c0:
    if ((u8)(s[119] - 3) > 1)
        return 0;
    {
        register u8 *base;
        base = (u8 *)0x082265bc;
        
        sub_0800D9EC(s, *(base + s[17]));
    }
    s[18] = 45;
    goto tail_inc;
c1:
    if (--s[18] != 0)
        return 0;
    sub_080174A4(*(u8 **)(s + 44), 3);
    {
        register u8 *base;
        base = (u8 *)0x082265be;
        
        sub_080178A8(*(base + s[17]), ((u32)s[35] << 28) >> 28, 15360, -1280, *(u8 **)(s + 44));
    }
    {
        /* ROM keeps two separate ANDs (&253 then &254); plain
         * C folds to a single &252, so pin the intermediate
         * with a barrier. */
        int t = 253 & s[10];
        int m = 254;
        
        s[10] = t & m;
    }
    goto tail_inc;
tail_inc:
    s[13]++;
    return 0;
c2:
    if ((u8)sub_08017474(*(u8 **)(s + 44)) <= 5)
        return 0;
    sub_08017478(*(u8 **)(s + 44), 7);
    return 1;
}
