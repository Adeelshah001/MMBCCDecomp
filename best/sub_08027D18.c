extern u32 gUnknown_0822DC84[];

void sub_08027718(u8 *s)
{
    u32 *tbl = gUnknown_0822DC84;
    u32 idx = s[1];
    ((void (*)(u8 *))tbl[idx])(s);
}

extern void sub_080267B4(u8 *, u32);
extern void sub_0804A328(void);
extern u32 gUnknown_0822DD84[];

void sub_08027C84(u8 *s)
{
    sub_080267B4((u8 *)0x020070F0, gUnknown_0822DD84[*(s8 *)(s + 0x4698)]);
    sub_0804A328();
}

extern void sub_08004F18(void);
extern u8 gUnknown_0200B7E0[];

void sub_08027CFC(void)
{
    u8 *p = gUnknown_0200B7E0;
    int mask = -7;
    p[3] &= mask;
    sub_08004F18();
}

extern u8 _call_via_r1(u8 *, u32);
extern void sub_08027E8C(u8 *);
extern void sub_08004F80(void);
extern u32 gUnknown_0822DDA0[];

void sub_08027D18(void)
{
    u8 *s = (u8 *)0x0200B7E0;
    s[2] = _call_via_r1(s, gUnknown_0822DDA0[s[2]]);
    sub_08027E8C(s);
    sub_08004F80();
}
