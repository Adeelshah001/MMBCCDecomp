/* Sub_08018474 @ 0x08018474 (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08018474_MATCHED.c (registry: mmbcc/src/w37c_08018474_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern void sub_0800D6E0(u8 *s, u16 b, u8 c);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_0800DD4C(u8 *o, s32 x, s32 y);

extern void sub_0800DD08(u32 *out, u8 *src);

extern void sub_0800DD2C(u8 *o, s32 x, s32 y);

extern void sub_080174A4(u8 *s, int bit);

extern int sub_0804A378(int idx);

void sub_08018474(u8 *s)
{
    u32 out[2];
    register u32 y;
    u32 z;
    int v;
    sub_0800D6E0(s, 542, s[17]);
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
    *(u32 *)(s + 88) = 1280;
    *(u32 *)(s + 96) = 10;
    *(u32 *)(s + 100) = *(u32 *)(s + 92) = z;
    sub_0800DD4C(s, -15360, 0);
    sub_0800DD08(out, s);
    {
        s32 x = out[0];
        y = *(volatile u32 *)&out[1];
        y = 0;
        sub_0800DD2C(s, x, y);
    }
    sub_080174A4(*(u8 **)(s + 44), 3);
    sub_0804A378(141);
}
