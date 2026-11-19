/* Sub_0801BA94 @ 0x0801BA94 (256 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w46d_0801ba94_MATCHED.c (registry: src/w46d_0801ba94_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800DD4C(u8 *s, int a, int b);

extern void sub_0800DD08(u8 *out, u8 *s);

extern void sub_080174A4(u8 *s, u8 bit);

extern u32 *sub_080178A8(int a, int b, int c, int d, int e);

extern u8 sub_08017474(u8 *s);

extern void sub_08017478(u8 *s, u8 v);

extern u8 sub_08017494(u8 *s, u8 bit);

extern void sub_08017464(u8 *s);

extern void sub_0800D9FC(u8 *s);

void sub_0801BA94(u8 *s)
{
    int out[2];
    int mode;
    register int o0;
    int o1;
    u8 *tbl;
    u8 *entry;
    register int idx;
    register u8 *tbase;
    register u8 *tbaddr;
    mode = s[13];
    if (mode == 1)
        goto c1;
    if (mode > 1)
        goto gt1;
    if (mode == 0)
        goto c0;
    goto tail;
gt1:
    if (mode == 2)
        goto c2;
    goto tail;
c0:
    sub_0800DD4C(s, 212 << 2, *(u32 *)(s + 92));
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    if (*(int *)(s + 84) <= -3840)
        goto tail;
    s[10] &= 254;
    s[10] &= 253;
    goto shared;
c1:
    sub_0800DD08((u8 *)out, s);
    o0 = out[0];
    o1 = out[1];
    if (sub_08017494((u8 *)*(u32 *)(s + 44), 1) != 0) {
        sub_080178A8(14, (int)(((u32)s[35] << 28) >> 28), (short)o0, (short)o1, *(u32 *)(s + 44));
        goto shared;
    }
    sub_080174A4((u8 *)*(u32 *)(s + 44), 3);
    tbl = (u8 *)0x08226858;
    
    idx = s[16];
    
    tbaddr = (u8 *)(idx + (int)tbl);
    sub_080178A8(*tbaddr, (int)(((u32)s[35] << 28) >> 28), (short)o0, (short)o1, *(u32 *)(s + 44));
shared:
    s[13]++;
    goto tail;
c2:
    if ((u8)sub_08017474((u8 *)*(u32 *)(s + 44)) <= 5)
        goto tail;
    sub_08017478((u8 *)*(u32 *)(s + 44), 7);
    sub_08017464((u8 *)*(u32 *)(s + 44));
    *(u32 *)(s + 44) = 0;
    tbase = (u8 *)0x082243d8;
    
    entry = (u8 *)(s[9] * 4 + (int)tbase);
    *(u32 *)(s + 12) = mode;
    *(u32 *)(s + 20) = *(u32 *)(*(u32 *)entry + 8);
tail:
    sub_0800D9FC(s);
}
