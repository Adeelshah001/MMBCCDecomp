/* Wave 35-B v5: 0x0804b350 direct param, int comparison for bgt. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;

extern s8 Worker_08028778(u8 *p, int x);
__asm__(".set Worker_08028778, 0x08028778");

__attribute__((section(".text.w35b_0804b350")))
int Sub_0804B350(u8 *s)
{
    s8 w = Worker_08028778(s + 1, 0);
    int t;
    if (w != 0)
        return 0;
    t = s[4];
    if (t <= 5)
    {
        *(u32 *)s = w;
        s[0] = 1;
    }
    else
    {
        *(u32 *)s = w;
        s[0] = 2;
    }
    return 0;
}
__asm__(".short 0x0000");
