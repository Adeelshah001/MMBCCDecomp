typedef u8 (*StateFn)(u8 *);

extern u16 D_02002F50;
extern u8 D_02004E40[];
extern u8 D_02005160[];
extern const StateFn D_08173E8C[];

extern void sub_0801054C(u8 *);
extern void sub_08010750(u8 *);

void sub_0800EED4(void)
{
    u8 *s;
    register u8 *p = D_02005160;
    u8 tmp;
    u8 ret;
    if (p[0x44] == 0)
    {
        int bit;
        s = (u8 *)&D_02002F50;
        bit = 1;
        if ((bit &= *(u16 *)s) != 0)
        {
            int flag;
            s = D_02004E40;
            flag = 1;
            tmp = s[0x14];
            flag |= tmp;
            s[0x14] = flag;
        }
    }
    else
    {
        int flag;
        s = D_02004E40;
        flag = 2;
        tmp = s[0x14];
        flag |= tmp;
        s[0x14] = flag;
    }

    {
        const StateFn *tbl = D_08173E8C;
        tmp = p[0];
        ret = tbl[tmp](p);
    }
    {
        u8 *q = D_02005160;
        q[0] = ret;
        sub_0801054C(q);
        sub_08010750(q);
    }
}
