extern u32 D_082243D8[];
extern u16 D_081705B0;
extern u8 D_020031E4[];

extern void sub_0800D6E0(u8 *s, int a, int b);
extern void sub_0800D9EC(u8 *s, int a);
extern void sub_0801757C(u8 *s);

void sub_080174F4(u8 *s)
{
    u32 *base = D_082243D8;
    u32 *p;
    u32 *e;
    int c;
    int r0, r3;
    u16 val;
    u8 *addr;
    u8 *q;
    int sh, mask, tmp;
    
    p = base + s[9];
    *(u32 *)(s + 12) = 1;
    e = *p;
    *(u32 *)(s + 20) = e[1];
    *(u32 *)(s + 108) = 0;
    
    r0 = 2;
    r3 = s[10];
    r0 |= r3;
    r0 |= 1;
    s[10] = r0;
    
    sub_0800D6E0(s, 512, s[16]);
    sub_0800D9EC(s, 0);
    s[18] = 0;
    
    val = D_081705B0;
    val >>= 4;
    val <<= 1;
    addr = D_020031E4 + val;
    r0 = *addr;
    c = r0 & 3;
    r0 = c;
    
    if (c > 3)
        c = 3;
    
    q = s + 69;
    sh = c << 2;
    mask = -13;
    tmp = *q;
    tmp &= mask;
    tmp |= sh;
    *q = tmp;
    
    s[34] = 14;
    sub_0801757C(s);
}
