extern void sub_0800288C(u8 *p, int n);
extern void sub_0800E144(s8 *p);
extern void sub_08028154(int k, u16 b, u8 c);

extern u8 D_087109A0[];
extern s8 D_0200B7E0[];

void sub_080280E8(u8 a, u16 b, u8 c)
{
    s8 *p;

    sub_0800288C(D_087109A0 + a * 20, 64);
    p = D_0200B7E0;
    if (p[7] >= 0) {
        sub_0800E144(p + 8);
    }
    if (c <= 14) {
        sub_08028154(2, b, c);
        sub_08028154(3, b, c);
        sub_08028154(4, b, c);
        sub_08028154(5, b, c);
    }
}
