typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void sub_08004e24(u8 v);
extern int sub_08004e0c(u32 v);
extern void sub_080111b4(u32 a);
extern void Tbl_ClearEntries(u8 a);
extern u16 G_020031E0;

__attribute__((section(".text.w36a_08010d84")))
u8 Step_08010d84(u8 *s)
{
    u8 st = s[0];
    if (st == 0)
        goto state0;
    if (st == 1)
        goto state1;
    goto ret;
state0:
    s[0] = 1;
    sub_08004e24(s[13]);
    goto ret;
state1:
    if ((u8)sub_08004e0c(3) == 0)
        goto ret;
    sub_080111b4(1);
    G_020031E0 &= 0xedff;
    G_020031E0 &= 0xdbff;
    Tbl_ClearEntries(s[2]);
ret:
    return s[4];
}

__asm__(".set sub_08004e24, 0x08004e24");
__asm__(".set sub_08004e0c, 0x08004e0c");
__asm__(".set sub_080111b4, 0x080111b4");
__asm__(".set Tbl_ClearEntries, 0x08011170");
__asm__(".set G_020031E0, 0x020031e0");
