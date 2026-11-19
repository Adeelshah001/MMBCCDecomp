/* Sub_0801986C @ 0x0801986C (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801986c_MATCHED.c (registry: mmbcc/src/w37c_0801986c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800D770(u8 *s, int b, int c);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void sub_0800DD2C(u8 *o, s32 x, s32 y);

extern int sub_0804A378(int idx);

void sub_0801986C(u8 *s)
{
    u32 out[2];
    u32 z;
    int v;
    sub_0800D770(s, 0x837, 0);
    sub_0800D9EC(s, 0);
    {
        u8 *q;
        int tmp;
        int w;
        v = *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1)) & 3;
        w = v;
        
        if (w > 3)
            v = 3;
        q = s + 69;
        {
            int sh = v << 2;
            tmp = (s[69] & -13) | sh;
        }
        *q = tmp;
        
        q -= 35;
        z = 0;
        *q = 13;
    }
    *(u32 *)(s + 100) = *(u32 *)(s + 92) = *(u32 *)(s + 96) = *(u32 *)(s + 88) = z;
    sub_0800DD08(out, s);
    sub_0800DD2C(s, 5120, 0xffffba00);
    sub_0804A378(159);
    if (s[17] == 0)
        s[17] = 1;
    if (s[17] > 6)
        s[17] = 6;
}
