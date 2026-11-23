struct Ent { u32 pad; u32 f4; };

struct S {
    u8 pad0[9];
    u8 f9;
    u8 b0:1;
    u8 b1:1;
    u8 pad11;
    u32 f12;
    u8 pad16[4];
    u32 f20;
    u8 pad24[11];
    u8 f35;
    u8 pad36[72];
    u32 f108;
};

extern struct Ent *D_08223CC0[];
extern void sub_0800D6E0(struct S *s, int m, int z);
extern void sub_0800D9EC(struct S *s, int z);
extern void sub_0801D070(int a, struct S *s, u32 *buf, int n);
extern void sub_08011F24(struct S *s);

void sub_08011EB0(struct S *s)
{
    struct Ent **base = D_08223CC0;
    u32 f9 = s->f9;
    struct Ent **addr;
    int m2;
    u8 *p35;
    int m0f;

    f9 &= 0xFF;
    addr = base + f9;
    s->f12 = 1;
    s->f20 = (*addr)->f4;
    s->f108 = 0;
    m2 = 2;
    m2 |= ((u8 *)s)[0x0A];
    ((u8 *)s)[0x0A] = m2;
    s->b0 = 1;
    p35 = &s->f35;
    m0f = 15;
    m0f &= *p35;
    sub_0800D6E0(s, m0f ? 256 : 0, 0);
    sub_0800D9EC(s, 0);
    {
        u32 buf[2] = {0, 0};
        sub_0801D070(0, s, buf, 12);
    }
    sub_08011F24(s);
}
