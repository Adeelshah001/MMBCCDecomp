extern const u32 *const D_082243D8[];
typedef void (*InitCallback)(u8 *);
extern InitCallback const D_082265C4[];
extern void sub_0801A9F8(u8 *s);

void sub_0801A9AC(u8 *s)
{
    const u32 *const *table = D_082243D8;
    u8 idx = s[9];
    const u32 *const *entry = (const u32 *const *)((idx << 2) + (u32)table);
    u8 f;
    InitCallback const *callbacks;
    u8 callbackIndex;

    *(u32 *)(s + 12) = 1;
    *(u32 *)(s + 20) = (*entry)[1];
    *(u32 *)(s + 108) = 0;
    f = 2;
    f |= s[10];
    f |= 1;
    s[10] = f;
    callbacks = D_082265C4;
    callbackIndex = s[16];
    callbacks[callbackIndex](s);
    sub_0801A9F8(s);
}

void sub_08020230(u8 *a, u8 *p, u8 x)
{
    u8 *q = p;
    u8 xx = x;
    int mask;
    a += 0x23;
    mask = 15;
    mask &= *a;
    if (mask == 0)
        q[5] = xx;
    else
        q[6] = xx;
}

extern u32 *sub_08020ED4(u8, u8, u8, u8);
extern void QueueResourceTransfer(const u8 *, u32);
extern void sub_08002904(const u8 *, u32, u8);
extern const u32 D_08173760[];
extern const u16 D_0817386C[];
extern const u16 D_081738F2[];

u8 *sub_08021498(void)
{
    u8 *node = (u8 *)sub_08020ED4(0, 0, 0, 1);
    const u8 *asset;
    const u16 *config;

    if (node != 0) {
        u8 zero = 0;
        node[0x10] = zero;
        node[0x11] = zero;
    }
    asset = (const u8 *)D_08173760[0x58 / 4];
    asset += *(const u32 *)asset;
    config = D_0817386C;
    QueueResourceTransfer(asset, (config[0x2C / 2] << 5) + 0x10000);
    asset += 0xC;
    config = D_081738F2;
    sub_08002904(asset, 0, config[0x2C / 2]);
    return node;
}

void sub_080214F4(void)
{
    u8 *p = (u8 *)sub_08020ED4(0, 0, 0, 1);
    if (p != 0) {
        u8 z = 0;
        p[16] = 1;
        p[17] = z;
        p[18] = 255;
    }
}
