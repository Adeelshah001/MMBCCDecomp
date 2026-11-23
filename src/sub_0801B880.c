extern u32 gUnknown_082243D8[];
extern u32 gUnknown_08226A04[];
void sub_0801D3A8(u8 *s);

void sub_0801D36C(u8 *s)
{
    u32 e;
    u32 *p;
    p = (u32 *)((u8 *)gUnknown_082243D8 + (s[9] << 2));
    *(u32 *)(s + 12) = 1;
    e = *p;
    *(u32 *)(s + 20) = *(u32 *)(e + 4);
    e = *(u32 *)((u8 *)gUnknown_08226A04 + (s[16] << 2));
    ((void (*)(u8 *))e)(s);
    sub_0801D3A8(s);
}

extern void sub_0800D770(u8 *p, u16 x, u8 y);
extern void sub_0800D9EC(u8 *p, u8 x);

void sub_0801C3FC(u8 *p)
{
    u32 b;
    sub_0800D770(p, 0x82a, 0);
    sub_0800D9EC(p, 0);
    b = 0xFD;
    b &= p[10];
    b &= 0xFE;
    p[10] = b;
}

struct S { u8 pad0[9]; u8 f9; u8 pad10[2]; u32 f12; u8 f16; u8 pad17[3]; u32 f20; u8 pad24[20]; u32 f44; };
typedef u8 (*Func)(struct S *s);
extern void sub_0800D9FC(struct S *s);
extern void sub_08017464(u32 x);

void sub_0801B91C(struct S *s)
{
    u32 e;
    u8 ret;
    ret = (*(Func *)((u8 *)0x082267f4 + (s->f16 << 2)))(s);
    sub_0800D9FC(s);
    if (ret != 0) {
        u32 *p;
        p = (u32 *)((u8 *)0x082243d8 + (s->f9 << 2));
        s->f12 = 2;
        e = *p;
        s->f20 = *(u32 *)(e + 8);
        sub_08017464(s->f44);
        s->f44 = 0;
    }
}

typedef signed int s32;
extern void sub_0800DD4C(void *o, s32 x, s32 y);
extern void *sub_0800DD08(void *d, void *s);
extern u32 sub_08017474(void *s);

u32 sub_0801B880(u8 *s)
{
    u32 buf[2];
    sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    sub_0800DD08(buf, s);
    if (s[13] == 0) {
        u8 v = sub_08017474(*(void **)(s + 44));
        if (v > 6) {
            u32 b = 0xFE;
            b &= s[10];
            s[10] = b;
            return 1;
        }
    }
    return 0;
}
