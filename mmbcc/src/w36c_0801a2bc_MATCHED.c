/* Wave 36-C MATCHED: 0x0801a2bc, 136 B, true extent 0x0801a2bc-0x0801a344 (next fn 0x0801a344; pools at 0x0801a330-0x0801a340 belong to this fn).
   Compiler: old_agbcc. Variants: 4. Key idioms: asm copy (add, not adds, for GAS Thumb) forces the clamp-test copy (adds r0,r1 + cmp);
   t69 = c<<2 then m69 = s[69] & -13 (int temps avoid u8 narrowing) then s[69] = m69 | t69; zero variable z loaded before the s[34] store;
   p = s+69 then p -= 35 for s[34]. Pools LE-verified: 0x245 (581), 0x081705b0, 0x020031e4, 0xffffec00, 0xfffffd00.
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
extern void Sub_0800DD2C(u8 *s, u32 a, u32 b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0804A378(int a);
__asm__(".set Sub_0804A378, 0x0804a378");
__attribute__((section(".text.w36c_0801a2bc")))
void Sub_0801A2BC(u8 *s)
{
    u32 out[2];
    u8 *p;
    int c;
    int t;
    int t69;
    int m69;
    int z;
    Sub_0800D6E0(s, 581, 0);
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
    Sub_0800DD2C(s, (int)0xffffec00, (int)0xfffffd00);
    Sub_0804A378(159);
}
