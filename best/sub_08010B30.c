typedef u8 (*Func)(u8 *s);
extern Func gUnknown_08173EB8[];
extern u8 sub_0804DCD0(u8 *base, Func func);
extern void sub_08004F18(void);
extern void sub_0800D568(u32 x);
extern void sub_0800D59C(u32 x);
extern void sub_0801112C(u8 x);
extern void sub_08004F80(void);

void sub_08010B30(void)
{
    u8 *base = (u8 *)0x020051B0;
    u8 one = 1;
    Func func;

    if ((one & base[0x0F]) == 0) {
        sub_08004F18();
        func = gUnknown_08173EB8[base[4]];
        base[4] = sub_0804DCD0(base, func);
        if (base[0x14] != 0) {
            base[0x14]--;
        }
        {
            u32 *other = (u32 *)0x020053C0;
            sub_0800D568(*other);
            sub_0800D59C(*other);
        }
        sub_0801112C(base[2]);
        sub_08004F80();
    } else {
        func = gUnknown_08173EB8[base[4]];
        base[4] = sub_0804DCD0(base, func);
    }
}
