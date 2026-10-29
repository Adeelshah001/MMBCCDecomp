/* Wave 36-C MATCHED: 0x08019f38, 128 B, true extent 0x08019f38-0x08019fb8 (next fn 0x08019fb8).
   Compiler: old_agbcc. Variants: 7. Key idioms: clamp copy via barrier on t (adds r0,r1 before ble); signed int c/t gives BLE;
   mask via opaque inline-asm movs #13 + negs (movs/negs, not folded mov #243); late z=0 variable (mov r1,#0 before strb 13);
   pointer reuse p-=35 for s[34]. Pools LE-verified: 0x081705b0 (u16), 0x020031e4 (table).
   Verification: clean-room harness 128/128 B, 0 diffs (old_agbcc). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D770(u8 *s, int a, int b);
__asm__(".set Sub_0800D770, 0x0800d770");
extern void Sub_0800D9EC(u8 *s, int a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800DD08(u8 *sp, u8 *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_0800DD2C(u8 *s, int a, int b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0804A378(int a);
__asm__(".set Sub_0804A378, 0x0804a378");
__attribute__((section(".text.w36c_08019f38")))
void Sub_08019F38(u8 *s)
{
    u8 buf[8];
    u8 *p;
    u8 b;
    int c, t;
    u32 cc, m;
    Sub_0800D770(s, 132 << 4, 0);
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
    Sub_0800DD2C(s, 160 << 4, 0);
    Sub_0804A378(132);
}
