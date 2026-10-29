/* Wave 36-C MATCHED: 0x08021628, 128 B, true extent 0x08021628-0x080216a8 (next fn 0x080216a8).
   Compiler: old_agbcc. Variants: 5. Key idioms: goto block order (bhi middle, else-stub, shared call);
   per-path callarg variable + barrier forces adds r0,r4 in stub and middle-end (and the pool-align pad);
   w>>=3 in place; family clamp (barrier copy, signed ble, opaque mask movs/negs).
   Pools LE-verified: 0x0200b7e0, 0x02003670, 0x081705b0, 0x020031e4.
   Verification: clean-room harness 128/128 B, 0 diffs (old_agbcc).
   Landing note: Sub_0800D9FC .set must be stripped at landing (already defined); D9EC .set kept. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_0800D9EC(u8 *s, int a);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800D9FC(u8 *s);
__asm__(".set Sub_0800D9FC, 0x0800d9fc");
__attribute__((section(".text.w36c_08021628")))
void Sub_08021628(u8 *s)
{
    u8 *gp = (u8 *)0x0200b7e0;
    u8 b;
    int c, t, sh, arg;
    u8 *callarg;
    u32 m, w;
    u8 *p;
    if (gp[4] > 1) goto middle;
    callarg = s;
    __asm__ volatile("" : "+r"(callarg));
    arg = 0;
    goto call;
middle:
    w = *(u32 *)0x02003670;
    if ((w & 7) != 0) goto d9fc;
    w >>= 3;
    arg = (w & 1) + 1;
    callarg = s;
    __asm__ volatile("" : "+r"(callarg));
call:
    Sub_0800D9EC(callarg, arg);
    b = ((u8 *)0x020031e4)[(*(u16 *)0x081705b0 >> 4) * 2];
    c = b & 3;
    t = c;
    __asm__ volatile("" : "+r"(t));
    if (t > 3) c = 3;
    p = s + 69;
    sh = c << 2;
    __asm__ volatile("movs %0, #13" : "=r"(m));
    m = -m;
    *p = (*p & m) | sh;
    *(s + 34) = 4;
d9fc:
    Sub_0800D9FC(s);
}
