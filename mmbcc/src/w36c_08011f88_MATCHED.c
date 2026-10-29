/* Wave 36-C MATCHED: 0x08011f88, 132 B, true extent 0x08011f88-0x0801200c (next fn 0x0801200c).
   Compiler: old_agbcc. Variants: 3. Key idioms: if/else statement (not ternary) for the v computation — produces the unconditional branch
   that anchors the mid-function literal pool; (15 & s[35]) mask order; s16 return test (lsls #16 + cmp) for Sub_08011F50.
   Pool LE-verified: 0xffffc400 (-15360). Verification: clean-room harness 132/132 B, 0 diffs (old_agbcc). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800DD2C(u8 *s, u32 a, int b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0800D6E0(u8 *s, int a, int b);
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
extern void Sub_0800D9EC(u8 *s, int a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0804A378(int a);
__asm__(".set Sub_0804A378, 0x0804a378");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
typedef signed short s16;
extern s16 Sub_08011F50(u8 *s);
__asm__(".set Sub_08011F50, 0x08011f50");
extern void Sub_08011F68(u8 *s, int a);
__asm__(".set Sub_08011F68, 0x08011f68");
__attribute__((section(".text.w36c_08011f88")))
void Sub_08011F88(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 0) {
        s[14] = 1;
        Sub_0800DD2C(s, (int)0xffffc400, 0);
        {
            int t = p[1];
            int u;
            if ((15 & s[35]) != 0)
                u = 256 | t;
            else
                u = t;
            Sub_0800D6E0(s, u, p[3]);
        }
        Sub_0800D9EC(s, 1);
        Sub_0804A378(169);
        s[33] = 30;
    }
    Sub_0800D9FC(s);
    if (Sub_08011F50(s) != 0) {
        Sub_0800D9EC(s, 0);
        p[4] = 0;
        Sub_08011F68(s, 0);
    }
}
