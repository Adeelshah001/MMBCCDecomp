typedef signed int s32;
typedef signed short s16;

extern u8 (* const D_0822EA6C[])(void *);

u8 sub_080350B4(u8 *s)
{
    u32 idx = s[4];
    u8 (*fn)(void *) = D_0822EA6C[idx];
    return fn(s);
}

extern s8 sub_0800EBF0(void);
extern int sub_0800EA4C(int v);

u32 sub_0803449C(u8 *s)
{
    u32 ret = 0;
    u8 st = s[3];
    if (st == 0)
        goto state0;
    if (st == 1)
        goto state1;
    goto ret;
state0:
    s[6] = 0x80 | s[6];
    if ((s8)sub_0800EBF0() == 1) {
        s[3]++;
    } else {
        sub_0800EA4C(0);
        goto ret;
    }
state1:
    if ((u8)sub_0800EA4C(0) == 1)
        goto ret;
    s[6] = 0x7F & s[6];
    ret = 7;
ret:
    return ret;
}

extern s8 (* const D_0822EB6C[])(u8 *);

void sub_08035E5C(u8 *p)
{
    s8 (* const *tbl)(u8 *) = D_0822EB6C;
    s8 *p2 = (s8 *)(p + 0x4699);
    if (tbl[*p2](p) != 0) {
        s32 x = *p2;
        if (x != 0) {
            x = 0;
            *p2 = x;
        } else {
            *p2 = *(p + 0x46B7);
        }
        p[4] = x;
        p[1] = 3;
        p[3] = x;
        p[2] = x;
    }
}

extern void sub_08004E44(void);
extern void sub_08004DFC(u8);
extern void sub_0800BEE0(s32, s32);
extern void sub_08021780(void);

extern u8 D_0200BCE8[8];
extern u8 D_02004F80[4];
extern u16 D_02004830;

void sub_0803618C(u8 arg0)
{
    u8 *ptr = D_0200BCE8;
    u16 i = 0;
    do {
        *ptr++ = 0;
        i++;
    } while (i <= 7);
    D_0200BCE8[0] = arg0;
    sub_08004E44();
    sub_08004DFC(D_02004F80[2]);
    sub_0800BEE0(0x40, 0x80);
    D_02004830 = 0;
    sub_08021780();
}
