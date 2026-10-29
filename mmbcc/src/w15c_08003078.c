/* Wave 15-C: NotZero_08003078 @ 0x08003078 (main). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u32 TblValidate_300C(u16 x);

u32 NotZero_08003078(u16 x) __attribute__((section(".text.w15c1_08003078")));
u32 NotZero_08003078(u16 x)
{
    if (TblValidate_300C(x) == 0)
        return 0;
    return 1;
}

