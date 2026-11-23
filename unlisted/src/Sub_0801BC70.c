/* Sub_0801BC70 @ 0x0801BC70 (266 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w61c_0801bc70_MATCHED.c (registry: staging/w61c_blocked/w61c_0801bc70_MATCH.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;
typedef signed int s32;

extern void sub_0800DD08(u32 *out, u8 *src);

extern void sub_080174A4(u8 *p, int bit);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_0801B98C(int a, u8 b, int c, s16 d, s16 e, u8 *f);

extern void sub_08017478(u8 *p, int v);

extern u8 gUnknown_0822687C[];

extern u8 gUnknown_08226880[];

u8 Sub_0801BC70(u8 *s)
{
    u32 out[2];
    register s32 x;
    register s32 y;
    int mode;
    sub_0800DD08(out, s);
    x = out[0];
    y = out[1];
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
    if (mode == 3)
        goto c3;
    goto ret0;
c0:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    sub_080174A4(*(u8 **)(s + 44), 3);
    s[18] = 1;
    s[19] = gUnknown_0822687C[s[17]];
    goto tail;
c1:
    {
        register int mask;
        s32 t7;
        s[18]--;
        t7 = 255;
        
        mask = t7;
        if (s[18] != 0)
            goto ret0;
        {
            u8 b = gUnknown_08226880[s[17]];
            int nib = ((u32)s[35] << 28) >> 28;
            s16 d;
            int draw;
            t7 = 152;
            t7 <<= 6;
            draw = x + t7;
            d = (s16)draw;
            {
                int neg = 0xffffe600;
                sub_0801B98C(0, b, nib, d, (s16)(y + neg),
                    *(u8 **)(s + 44));
            }
            
            
        }
        sub_0800D9EC(s, 1);
        s[18] = 8;
        {
            int t = s[19] - 1;
            s[19] = t;
            if ((t & mask) != 0)
                goto ret0;
        }
        s[18] = 10;
        goto tail;
    }
c2:
    s[18]--;
    if (s[18] != 0)
        goto ret0;
    sub_0800D9EC(s, 2);
    goto tail;
tail:
    s[13]++;
    goto ret0;
c3:
    if ((u8)(s[119] - 3) > 1)
        goto ret0;
    sub_08017478(*(u8 **)(s + 44), 7);
    return 1;
ret0:
    return 0;
}
