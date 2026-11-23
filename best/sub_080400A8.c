extern s8 RectOverlapsView(s8, s8, u8, u8);
extern const u8 D_082329E0[];

s8 sub_08040364(int arg0)
{
    u32 index = (u32)arg0 << 24;
    const u8 *table = D_082329E0;
    index >>= 22;
    return RectOverlapsView(
        *(const s8 *)(((u32)table + index)),
        (s8)*(const u8 *)((u32)(table + 1) + index),
        *(const u8 *)((u32)(table + 2) + index),
        *(const u8 *)((u32)(table + 3) + index)
    );
}

extern u8 _call_via_r3(u8 *a, u16 b, u8 c, u32 fn);
extern u32 D_082329B0[];

u8 sub_080400D0(u8 *s, u16 b, u8 c)
{
    u32 *tbl = D_082329B0;
    u8 idx = s[4];
    u32 fn = *(u32 *)((idx << 2) + (u32)tbl);
    return _call_via_r3(s, b, c, fn);
}

typedef struct {
    u8 unk0[8];
    u16 state;
} RandomState;
extern RandomState D_020070F0;

u16 sub_080400A8(void)
{
    RandomState *rng = &D_020070F0;
    u16 prior = rng->state;
    u32 next = (0x8D94 + prior) * 5;
    u32 low = 0xFF;
    low &= next;
    rng->state = (low << 8) | ((u16)next >> 8);
    return *(volatile u16 *)&rng->state;
}

unsigned int sub_08040060(unsigned char *s, unsigned short n)
{
    unsigned int *p = (unsigned int *)(s + 32);
    unsigned int failed;

    if (*p >= n) {
        *p -= n;
        failed = 0;
    } else {
        failed = 1;
    }
    return failed;
}
