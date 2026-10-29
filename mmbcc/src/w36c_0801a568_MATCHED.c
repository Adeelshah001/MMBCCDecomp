/* Wave 36-C MATCHED: 0x0801a568, 136 B, true extent 0x0801a568-0x801a5f0 (pools at end belong to this fn).
   Compiler: old_agbcc. Variants: 1 (adapted from 1a2bc v4 template). D6E0 arg 593 (0x251); DD2C(s, 15360, 0); 174A4(s[44], 3); 4A378(159). Pools: 0x251, 0x081705b0, 0x020031e4.
   Verification: clean-room harness 136/136 B, 0 diffs (old_agbcc). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D6E0(u8 *s, int a, int b);
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
extern void Sub_0800D9EC(u8 *s, int a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800DD08(u32 *out, u8 *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_0800DD2C(u8 *s, u32 a, int b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_080174A4(u32 a, int b);
__asm__(".set Sub_080174A4, 0x080174a4");
extern void Sub_0804A378(int a);
__asm__(".set Sub_0804A378, 0x0804a378");
__attribute__((section(".text.w36c_0801a568")))
void Sub_0801A568(u8 *s)
{
    u32 out[2];
    u8 *p;
    int c;
    int t;
    int t69;
    int m69;
    int z;
    Sub_0800D6E0(s, 593, 0);
    Sub_0800D9EC(s, 0);
    c = *(u8 *)(0x020031e4 + (((*(u16 *)0x081705b0 >> 4) << 1))) & 3;
    __asm__ volatile("add %0, %1, #0" : "=r"(t) : "r"(c));
    if (t > 3)
        c = 3;
    p = s + 69;
    t69 = c << 2;
    m69 = s[69] & -13;
    s[69] = m69 | t69;
    p -= 35;
    z = 0;
    p[0] = 13;
    *(u32 *)(s + 88) = z;
    *(u32 *)(s + 96) = z;
    *(u32 *)(s + 92) = z;
    *(u32 *)(s + 100) = z;
    Sub_0800DD08(out, s);
    Sub_0800DD2C(s, 15360, 0);
    Sub_080174A4(*(u32 *)(s + 44), 3);
    Sub_0804A378(159);
}
