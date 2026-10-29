typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32; typedef signed char s8;
extern u32 FlagInit_08011070(u8 a, u8 b);
extern u32 IsOne_020051B0_4(void);
__attribute__((section(".text.w16c_08011b64")))
u32 F_08011B64(u8 *p)
{
    u8 v = p[5];
    if (v != 0) goto L1;
    {
        u8 *q = p + 0x24;
        if (*q != 0) {
            *q = v;
            p[4] = v;
            p[5] = v;
            p[6] = v;
            p[7] = v;
            goto Lret1;
        }
    }
    if ((u8)FlagInit_08011070(p[0x23], 2) == 0)
        goto Lret0a;
    p[5] = 1;
L1:
    if (p[5] != 1)
        goto Lclear;
    if ((s8)IsOne_020051B0_4() == 1)
        p[5]++;
Lret0a:
    return 0;
Lclear:
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
Lret1:
    return 1;
}