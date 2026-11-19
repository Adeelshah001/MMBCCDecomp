/* Sub_0801EC44 @ 0x0801EC44 (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801ec44_MATCHED.c (registry: mmbcc/src/w37c_0801ec44_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D6E0(u8 *s, u16 b, u8 c);

extern void sub_0800D9EC(u8 *s, int idx);

extern void sub_0801ECE8(u8 *s);

void sub_0801EC44(u8 *s)
{
    u8 *r5;
    int v;
    {
        u8 *q;
        int tmp;
        int w;
        u8 t10;
        register u8 *base1;
        u32 *tp;
        register u8 *base2;
        base1 = (u8 *)0x082243d8;
        
        tp = (u32 *)(s[9] * 4 + (u32)base1);
        *(u32 *)(s + 12) = 1;
        *(u32 *)(s + 20) = *(u32 *)(*(u32 *)tp + 4);
        *(u32 *)(s + 108) = 0;
        t10 = s[10] | 2;
        t10 = t10 | 1;
        s[10] = t10;
        base2 = (u8 *)0x08226da4;
        
        r5 = *(u8 **)(s[16] * 4 + (u32)base2);
        *(u32 *)(s + 40) = (u32)r5;
        sub_0800D6E0(s, r5[1] | 768, r5[0] >> 4);
        sub_0800D9EC(s, r5[2]);
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
    }
    {
        u8 t34 = s[17] + 14;
        s[34] = t34;
    }
    s[18] = r5[3];
    sub_0801ECE8(s);
}
