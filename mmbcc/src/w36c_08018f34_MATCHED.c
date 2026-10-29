/* Wave 36-C MATCHED: 0x08018f34, 132 B, true extent per func_list next-fn. Compiler: old_agbcc.
   Twin of 0x0801cac4 family: D6E0 first call, DD2C arg via pool 0xffffec00, final call arg 159.
   Pools: D6E0 arg (0x22e/0x23e), 0x081705b0, 0x020031e4, 0xffffec00. Verification: clean-room harness, 0 diffs (old_agbcc). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D6E0(u8 *s, int a, int b);
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
extern void Sub_0800D9EC(u8 *s, int a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800DD08(u8 *sp, u8 *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_0800DD2C(u8 *s, int a, int b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0804A378(int a);
__asm__(".set Sub_0804A378, 0x0804a378");
__attribute__((section(".text.w36c_08018f34")))
void Sub_08018F34(u8 *s)
{
    u8 buf[8];
    u8 *p;
    u8 b;
    int c, t;
    u32 cc, m;
    Sub_0800D6E0(s, 558, 0);
    Sub_0800D9EC(s, 0);
    b = ((u8 *)0x020031e4)[(*(u16 *)0x081705b0 >> 4) * 2];
    c = b & 3;
    t = c;
    __asm__ volatile("" : "+r"(t));
    if (t > 3) c = 3;
    p = s + 69;
    cc = c << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *p = (*p & m) | cc;
    p -= 35;
    { u32 z = 0;
    *p = 13;
    *(u32 *)(s + 88) = z;
    *(u32 *)(s + 96) = z;
    *(u32 *)(s + 92) = z;
    *(u32 *)(s + 100) = z; }
    Sub_0800DD08(buf, s);
    Sub_0800DD2C(s, (int)0xffffec00, 0);
    Sub_0804A378(159);
}
