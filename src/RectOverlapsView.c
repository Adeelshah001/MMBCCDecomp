typedef signed int s32;
extern u8 D_02003670[];
extern const u8 D_000011AC[];

u32 RectOverlapsView(u8 a, u8 b, u8 c, u8 d)
{
    register u32 bb = b;
    register u32 dd = d;
    register u8 *base;
    register s32 b1;
    register s32 b2;
    register s32 sb;
    int off;
    s32 sa, sac;

    
    base = D_02003670;
    if (c == 0 || dd == 0)
        return 0;
    sa = (s8)a;
    sac = sa + (s32)c;
    off = (u32)D_000011AC;
    
    b1 = *(s8 *)(off + base);
    if (sac <= b1)
        return 0;
    {
        register u32 t0;
        t0 = bb << 24;
        sb = (s32)t0 >> 24;
    }
    {
        register s32 s;
        s = sb + (s32)dd;
        off++;
        b2 = *(s8 *)(off + base);
        if (s <= b2)
            return 0;
    }
    {
        register s32 t1 = b1;
        t1 += 28;
        if (sa >= t1)
            return 0;
    }
    {
        register s32 t2 = b2;
        t2 += 20;
        if (sb < t2)
            return 1;
    }
    return 0;
}
