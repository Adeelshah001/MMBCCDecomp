/* NodeInitSwitch_0800D1E0 @ 0x0800D1E0 (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26d_0800d1e0.c (registry: src/w26d_0800d1e0.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_08173530[];

extern u32 sub_0802260C(u8 idx);

extern u8 sub_08022634(u32 node);

extern void sub_0800520C(int x);

int sub_0800D1E0(u8 *p0, u8 *p1, u8 *p2, u8 *p3)
{
    u8 v2 = *p2;
    u8 v3 = *p3;
    u8 v1 = *p1;
    int ret = 1;
    u8 v16 = p0[6];
    switch (v1) {
    case 0:
        v1 = 1;
    case 1: {
        u8 *base = gUnknown_08173530;
        int off = v16 * 2;
        u32 node;
        int five = 5;
        base++;
        node = sub_0802260C(*(base + off));
        *(u32 *)(p0 + 12) = node;
        if (node == 0)
            break;
        v1 = (u8)(v1 + 1);
        
        p0[9] &= -five;
    }
    case 2:
        if (sub_08022634(*(u32 *)(p0 + 12)) == 0)
            break;
        sub_0800520C(1);
        ret = 0;
        break;
    }
    *p2 = v2;
    *p3 = v3;
    *p1 = v1;
    return ret;
}
