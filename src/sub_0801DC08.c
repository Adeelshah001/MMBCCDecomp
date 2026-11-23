struct ChipPosition {
    int x;
    int y;
};

extern u32 D_082243D8[];
extern void sub_0800D9EC(u8 *o, int idx);
extern void sub_0800303C(int idx);
extern void sub_0800D9FC(u8 *o);

void sub_0801DC08(u8 *o)
{
    u8 *q = *(u8 **)(o + 0x28);
    u32 phase;
    u32 lookup;
    u32 idx;
    u32 z;

    z = idx >> 16;
    z >>= 16;
    phase = o[0x0D];
    if ((phase + z) == 0) {
        z = (lookup | idx) >> 16;
        z >>= 16;
        lookup = q[0x0C] + z;
        if (lookup <= 1) {
            u8 *t;
            int face;
            *(struct ChipPosition *)(o + 0x50) = *(struct ChipPosition *)(q + 0x50);
            *(int *)(o + 0x54) += *(int *)(o + 0x64);
            t = q + 0x23;
            face = 0x0F;
            face &= *t;
            if (face == 1) {
                *(int *)(o + 0x50) -= *(int *)(o + 0x60);
            } else {
                *(int *)(o + 0x50) += *(int *)(o + 0x60);
            }
        } else {
            phase++;
            o[0x0D] = phase;
            z = (lookup | phase) >> 16;
            z >>= 16;
            o += z;
        }
    }
    switch (o[0x0E]) {
    case 0:
        if ((u8)(o[0x77] - 3) <= 1) {
            o[0x0E] = 1;
            sub_0800D9EC(o, 0x0C);
            q[0x21] = 8;
            o[0x13] = 0x20;
            sub_0800303C(0x7E);
        }
        /* fallthrough */
    case 1:
        if (--o[0x13] == 0) {
            u8 *p = *(u8 **)(o + 0x2C);
            u32 *tbl;
            u32 *e;
            (*p)++;
            tbl = D_082243D8;
            idx = o[9];
            idx &= 0xFF;
            e = tbl + idx;
            *(u32 *)(o + 0x0C) = 2;
            *(u32 *)(o + 0x14) = *(u32 *)((u8 *)*e + 8);
        }
        break;
    }
    sub_0800D9FC(o);
}
