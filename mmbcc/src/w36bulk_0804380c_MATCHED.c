/* Wave 36-B MATCHED: 0x0804380c, 132 B, old_agbcc, 0 diffs. Variants: 3. Idioms: zero var set at start (r6), byte pinned to r2, 4044c twin with bit-split arg. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
typedef signed char s8;
extern int Sub_08024818(int x);
extern void Sub_08007C04(u8 t, int x);
extern void Sub_08007CF4(int a, s8 b, s8 c);
extern int Sub_080246A8(u8 t);
extern void Sub_08006A54(int a, int b, int c, int d, int e);
extern int Sub_080246C4(u8 t);
__attribute__((section(".text.w36bulk_0804380c")))
void Sub_0804380C(u8 *s)
{
    int zero = 0;
    register u8 b __asm__("r2") = s[0x46a8];
    u8 t = (u8)Sub_08024818((b >> 5) + (b & 31));
    Sub_08007C04(t, 1);
    {
        u8 *tbl = (u8 *)0x08232d84;
        Sub_08007CF4(1, (s8)(tbl[0] + 1), (s8)(tbl[1] + 3));
    }
    {
        s8 *st = (s8 *)0x08232d84;
        Sub_08006A54(Sub_080246A8(t), st[0] + 1, st[1] + 1, 8, zero);
    }
    {
        s8 *st = (s8 *)0x08232d84;
        Sub_08006A54(Sub_080246C4(t), st[0] + 1, st[1] + 10, 8, zero);
    }
}

__asm__(".set Sub_080246A8, 0x080246a8");
__asm__(".set Sub_080246C4, 0x080246c4");
__asm__(".set Sub_08024818, 0x08024818");
__asm__(".set Sub_08006A54, 0x08006a54");
__asm__(".set Sub_08007C04, 0x08007c04");
__asm__(".set Sub_08007CF4, 0x08007cf4");
