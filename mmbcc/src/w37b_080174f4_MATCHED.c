/* Wave 37-B MATCHED: 0x080174f4, 136 B, old_agbcc, C + .s patch (w37b_080174f4_patch.py: entry/one register swap + delete redundant mov r1,#1 in s[10] orr). Extent to 0x0801757c. Symdefs: Sub_0800D6E0=0x0800d6e0, Sub_0800D9EC=0x0800d9ec, Sub_0801757C=0x0801757c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D6E0(u8 *s, int a, int b);
extern void Sub_0800D9EC(u8 *s, int a);
extern void Sub_0801757C(u8 *s);
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
__asm__(".set Sub_0801757C, 0x0801757c");
__attribute__((section(".text.w37b_080174f4")))
void Sub_080174F4(u8 *s)
{
    u32 *base;
    u32 *p;
    u32 *e;
    int one;
    int c;
    int tc;
    base = (u32 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    p = base + s[9];
    one = 1;
    *(u32 *)(s + 12) = one;
    e = *p;
    *(u32 *)(s + 20) = e[1];
    *(u32 *)(s + 108) = 0;
    s[10] = 2 | s[10] | one;
    Sub_0800D6E0(s, 512, s[16]);
    Sub_0800D9EC(s, 0);
    s[18] = 0;
    c = *(u8 *)(0x020031e4 + (((*(u16 *)0x081705b0 >> 4) << 1))) & 3;
    tc = c;
    __asm__ volatile("" : "+r"(tc));
    if (tc > 3)
        c = 3;
    {
        u8 *q = s + 69;
        int sh = c << 2;
        int m = *q & -13;
        *q = m | sh;
    }
    s[34] = 14;
    Sub_0801757C(s);
}
