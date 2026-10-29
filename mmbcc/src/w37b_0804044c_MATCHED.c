/* Wave 37-B MATCHED: 0x0804044c, 132 B, old_agbcc, C + .s patch (w37b_0804044c_patch.py: swap two ldrb lines + adds operand order). Extent to 0x080404d0. Symdefs: Sub_08024818=0x08024818, Sub_08007C04=0x08007c04, Sub_08007CF4=0x08007cf4, Sub_080246A8=0x080246a8, Sub_08006A54=0x08006a54, Sub_080246C4=0x080246c4 (246a8/6a54/246c4/24818 MATCHED; 7c04 now MATCHED this wave; 7cf4 unmatched). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed char s8;
extern int Sub_08024818(int sum);
extern void Sub_08007C04(u8 t, int x);
extern void Sub_08007CF4(int a, s8 b, s8 c);
extern int Sub_080246A8(u8 t);
extern void Sub_08006A54(int a, int b, int c, int d, int e);
extern int Sub_080246C4(u8 t);
__asm__(".set Sub_08024818, 0x08024818");
__asm__(".set Sub_08007C04, 0x08007c04");
__asm__(".set Sub_080246A8, 0x080246a8");
__asm__(".set Sub_08006A54, 0x08006a54");
__asm__(".set Sub_080246C4, 0x080246c4");
__attribute__((section(".text.w37b_0804044c")))
void Sub_0804044C(u8 *s)
{
    int off = 0x46a8;
    u8 b0 = s[off];
    u8 b1 = s[off + 1];
    u8 t = (u8)Sub_08024818(b0 + b1);
    Sub_08007C04(t, 2);
    {
        u8 *tbl = (u8 *)0x082329e0;
        Sub_08007CF4(2, (s8)(tbl[16] + 1), (s8)(tbl[17] + 3));
    }
    {
        s8 *st = (s8 *)0x082329e0;
        Sub_08006A54(Sub_080246A8(t), st[16] + 1, st[17] + 1, 8, 0);
    }
    {
        s8 *st = (s8 *)0x082329e0;
        Sub_08006A54(Sub_080246C4(t), st[16] + 1, st[17] + 10, 8, 0);
    }
}
