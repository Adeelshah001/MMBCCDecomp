/* Sub_08020F70 @ 0x08020F70 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08020f70_MATCHED.c (registry: mmbcc/src/w36d_08020f70_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 *sub_08020ED4(u32 a, u32 b, u32 c, u32 d);

extern void sub_08002300(u32 *p, u32 a);

extern void sub_08002904(u32 *p, u32 a, u32 b);

u8 *sub_08020F70(u8 a, u32 b, u32 c)
{
    register u32 bb = b;
    u32 cc = c;
    register u8 *r5;
    u32 c0, c1;
    if (a == 14) {
        c0 = 0;
        c1 = 1;
    } else {
        c0 = 0;
        c1 = 0;
    }
    r5 = sub_08020ED4(c0, c1, 0, 0);
    if (r5 != 0) {
        r5[16] = 0;
        r5[17] = a;
        *(u32 *)(r5 + 40) = bb;
        *(u32 *)(r5 + 44) = cc;
    }
    {
        u32 *base1 = (u32 *)0x08173760;
        u32 *r4 = *(u32 **)((u8 *)base1 + 88);
        u32 *base2 = (u32 *)0x08226f34;
        r4 = (u32 *)((u8 *)r4 + ((u32)*(u8 *)((u8 *)base2 + r5[17]) << 2));
        r4 = (u32 *)((u8 *)r4 + *r4);
        {
            u32 *base3 = (u32 *)0x0817386c;
            sub_08002300(r4, ((u32)*(u16 *)((u8 *)base3 + 44) << 5) + 65536);
        }
        r4 = (u32 *)((u8 *)r4 + 12);
        {
            u32 *base4 = (u32 *)0x081738f2;
            u16 hv = *(u16 *)((u8 *)base4 + 44);
            sub_08002904(r4, 0, (u8)hv);
        }
    }
    return r5;
}
