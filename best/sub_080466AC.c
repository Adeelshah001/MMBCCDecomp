/* Sub_080466AC @ 0x080466AC (304 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w64a_080466ac_MATCHED.c (registry: src/w64a_080466ac_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_08006DD8(void *p, u32 a, u32 b, u32 c, u32 d);

extern u32 sub_080247C4(u8 idx);

extern u32 sub_080241F8(u16 a);

extern void sub_080070F0(u32 x, u32 y, u32 z, u32 w);

extern u32 sub_080246A8(u16 idx);

extern void sub_08006A54(u32 a, u32 b, u32 c, u32 d, u32 e);

extern u32 sub_080245C4(u8 idx);

extern void sub_080079F0(u32 a, u32 b, u32 c);

void sub_080466AC(u8 *s)
{
    u8 i = 0;
    int x = s[0x46AA];

    while ((u8)x < s[0x46AA] + 7) {
        u8 x8;
        s8 *tbl = (s8 *)0x08232e5c;
        x++;
        x8 = (u8)x;
        if (x8 > 194)
            x8 = (u8)(x8 + 5);
        
        sub_08006DD8((void *)x, tbl[0], tbl[1] + 2 * i, 3, 2);
        if ((u16)sub_080247C4(x8) != 0 || (u8)sub_080241F8(0x1000) == x8) {
            sub_080070F0(x8, tbl[4], tbl[5] + 2 * i, 0);
            sub_08006A54(sub_080246A8(x8), tbl[8], tbl[9] + 2 * i, 8, 2);
            {
                u8 t2 = (u8)sub_080245C4(x8);
                sub_080079F0(t2, tbl[12], tbl[13] + 2 * i);
            }
        } else {
            sub_080070F0(0, tbl[4], tbl[5] + 2 * i, 0);
            sub_08006A54(*(u32 *)0x08232e04, tbl[8], tbl[9] + 2 * i, 11, 2);
        }
        i++;
    }
    *(u16 *)(0x02004ce0 + 40) = 88;
    *(u16 *)(0x02004ce0 + 42) = (s[0x46a9] << 4) + 24;
}
