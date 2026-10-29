/* Wave 36-C MATCHED: 0x0801ae70, 132 B, true extent 0x0801ae70-0x0801aef4 (next fn 0x0801aef4).
   Compiler: old_agbcc. Variants: 5. Key idioms: out[2] loaded before t13 test (o1 pinned r3); barrier pool-first table load;
   unsigned shift-form (u32<<28)>>28 for &0xF; two-step mask v=s[10]&253, m=254 (u32) with barrier; explicit .short 0x0000 tail pad (replaces GAS nop).
   Pools LE-verified: 0xfffffb00 (-1280), 0x08226723. Verification: clean-room harness 132/132 B, 0 diffs (old_agbcc). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
extern void Sub_0800DD4C(u8 *s, u32 a, u32 b);
__asm__(".set Sub_0800DD4C, 0x0800dd4c");
extern void Sub_0800DD08(u32 *out, u8 *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_080178A8(u8 a, u8 b, s16 c, int d, u32 e);
__asm__(".set Sub_080178A8, 0x080178a8");
__attribute__((section(".text.w36c_0801ae70")))
int Sub_0801AE70(u8 *s)
{
    u32 out[2];
    u32 o0;
    register u32 o1 __asm__("r3");
    u8 t13;
    Sub_0800DD4C(s, *(u32 *)(s + 88), *(u32 *)(s + 92));
    *(u32 *)(s + 88) += *(u32 *)(s + 96);
    *(u32 *)(s + 92) += *(u32 *)(s + 100);
    Sub_0800DD08(out, s);
    o0 = out[0];
    o1 = out[1];
    t13 = s[13];
    if (t13 == 0 && (int)o1 > (int)0xfffffb00) {
        u8 *tbl = (u8 *)0x08226723;
        u8 b, v;
        u32 m;
        __asm__ volatile("" : "+r"(tbl));
        b = tbl[s[17]];
        Sub_080178A8(b, (((u32)s[35] << 28) >> 28), (s16)o0, 0, *(u32 *)(s + 44));
        *(u32 *)(s + 88) = t13;
        *(u32 *)(s + 96) = t13;
        *(u32 *)(s + 92) = t13;
        *(u32 *)(s + 100) = t13;
        v = s[10] & 253;
        m = 254;
        __asm__ volatile("" : "+r"(m));
        s[10] = v & m;
        return 1;
    }
    return 0;
}

__asm__(".short 0x0000");
