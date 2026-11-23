typedef signed int s32;

extern u8 D_020051B0[];
extern u32 D_082243D8[];
extern u32 D_08226A60[];
extern void _call_via_r1(u8 *s, u32 e);
extern void sub_0800D9FC(u8 *s);

void sub_0801E0D0(u8 *s)
{
    u8 *gp = D_020051B0;
    u32 idx;
    if ((((int)gp[3] >> s[16]) & 1) == 0) {
        u32 z = idx >> 16;
        u32 *tbl = D_082243D8;
        u32 *e;

        idx = (z >> 16) + s[9];
        e = tbl + idx;
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*e + 8);
    } else {
        u32 *tbl = D_08226A60;
        u32 *e;
        s8 t;
        u8 res;
        u8 *dst;

        idx = s[13];
        idx &= 0xFF;
        e = tbl + idx;
        _call_via_r1(s, *e);
        t = (s8)(((s32)(*(u32 *)(s + 84) << 13) >> 24) + 6);
        if (t > 31) t = 31;
        if (t < 0) t = 0;
        res = 31 - t;
        dst = s + 34;
        *dst = res;
        sub_0800D9FC(s);
    }
}
