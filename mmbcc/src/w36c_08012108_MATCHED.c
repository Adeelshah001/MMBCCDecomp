/* Wave 36-C MATCHED: 0x08012108, 136 B, true extent 0x08012108-0x08012190 (next fn 0x08012190; the 0xffffc400 pool at 0x0801218c belongs to this fn).
   Compiler: main agbcc (old also 0 diffs). Variants: 1. Pool LE-verified: 0xffffc400 (-15360), shared by both DD2C calls.
   Verification: clean-room harness 136/136 B, 0 diffs (both compilers). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_080174A4(u32 a, int b);
__asm__(".set Sub_080174A4, 0x080174a4");
extern void Sub_0800DD2C(u8 *s, u32 a, int b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0800D9EC(u8 *s, int a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_08017478(u32 a, int b);
__asm__(".set Sub_08017478, 0x08017478");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
extern void Sub_08017464(u32 a);
__asm__(".set Sub_08017464, 0x08017464");
extern void Sub_08011F68(u8 *s, int a);
__asm__(".set Sub_08011F68, 0x08011f68");
__attribute__((section(".text.w36c_08012108")))
void Sub_08012108(u8 *s)
{
    u8 *p = s + 124;
    if (s[14] == 0) {
        s[14] = 1;
        Sub_080174A4(*(u32 *)(s + 44), 3);
        Sub_0800DD2C(s, (int)0xffffc400, 0);
        Sub_0800D9EC(s, 0);
        s[18] = 15;
    }
    if (s[14] == 1 && s[18] == 8)
        Sub_08017478(*(u32 *)(s + 44), 1);
    Sub_0800D9FC(s);
    s[18]--;
    if (s[18] == 0) {
        Sub_08017478(*(u32 *)(s + 44), 7);
        Sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        Sub_0800DD2C(s, (int)0xffffc400, 0);
        p[4] = 0;
        Sub_08011F68(s, 0);
    }
}
