typedef signed short s16;
typedef signed int s32;
extern u8 *sub_080113F4(u16 cur);

const u32 *sub_08011CAC(u16 idx)
{
    if (idx == 0)
        return 0;
    return (const u32 *)((u32)(idx * 4) + 0x08173FAC);
}

u16 sub_08011C58(u8 row, u8 col)
{
    if (row <= 5 && col <= 15) {
        u32 base = 0x08173EEC;
        return *(const u16 *)((col * 2 + row * 32) + base);
    }
    return 0;
}

u32 sub_08011D34(u16 x)
{
    register u32 xs = (u32)x << 16;
    register u32 xr = xs >> 16;
    register u32 t;
    u32 hdr;
    u32 off;
    u8 *base;
    u8 *p;
    u32 bit;
    int v;
    u8 vb;

    t = xr;
    if (t == 0)
        goto Lret0;
    if (t > 127)
        goto Lret0;
    hdr = 0x02005260;
    off = xs >> 19;
    base = *(u8 **)(hdr + 4);
    p = base + off;
    bit = t & 7;
    v = *p;
    v >>= bit;
    vb = (u8)v;
    return vb & 1;
Lret0:
    return 0;
}

typedef struct {
    u8 *f0;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
    u8 pad[28];
    u8 b35;
} Obj;

s32 sub_08011A78(Obj *p)
{
    register u8 *q = p->f0;
    register u8 *r2 = (u8 *)p + 35;
    u8 z = 0;
    u8 e;
    u8 t;
    *r2 = z;
    {
        register u8 eight = 8;
        e = eight;
        t = q[10];
        if ((e & t) != 0) {
            *r2 = 1;
        }
        if (*(s16 *)(p->f0 + 30) > 0) {
            u16 v = *(u16 *)(p->f0 + 30);
            u8 *w = sub_080113F4(v);
            if (w != 0) {
                p->f0 = w;
                p->b4++;
                goto done;
            }
        }
        p->b4 = eight;
    done:
        p->b5 = z;
        p->b6 = z;
        p->b7 = z;
        return -1;
    }
}
