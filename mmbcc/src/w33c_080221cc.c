/* Wave 33-C v8: 0x080221cc — v6 base + initialized pins.
 * - c initialized pin to r1 (b270), r3 (BlendCopy)
 * - idx: p computed, idx initialized pin to r1 = 3, then &= *p
 * - ldrsh: dummy read of c after 2nd store (keeps c live)
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void ChipSlot_Setup(u8 *s, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern void BlendCopy_080224E4(u8 a, void *p1, void *p2, u8 d);
/* ChipSlot_Setup is a real build T symbol — resolved at link. */
/* ChipSlot_IncUse is a real build T symbol — resolved at link. */
/* BlendCopy_080224E4 is a real build T symbol — resolved at link. */

__attribute__((section(".text.w33c_080221cc")))
void ChipInit_080221CC(u8 *s)
{
    register u8 *sp __asm__("r5") = s;
    *(u32 *)(sp + 108) = 0;
    {
        int x = 2;
        x |= *(u8 *)(sp + 10);
        x |= 1;
        *(u8 *)(sp + 10) = x;
    }
    {
        u16 w;
        {
            register u32 b270 __asm__("r2") = 0x082270b0;
            register u8 c __asm__("r1") = *(u8 *)(sp + 17);
            register u16 tbl __asm__("r0");
            __asm__ volatile("" : "+r"(b270));
            tbl = *(u16 *)(b270 + 2 * c);
            w = (c + 3) | tbl;
        }
        ChipSlot_Setup(sp, w, 0);
    }
    ChipSlot_IncUse(sp, 0);
    {
        u8 *p = (u8 *)(0x020031e4 + 2 * (*(u16 *)0x081705b0 >> 4));
        int idx = 3;
        int t;
        idx &= *p;
        t = idx;
        __asm__ volatile("" : "+r"(t));
        if (t > 3)
            idx = 3;
        {
            register u8 *p69 __asm__("r2") = sp + 69;
            int m = -13;
            idx <<= 2;
            __asm__ volatile("" : "+r"(m));
            *p69 = (*p69 & m) | idx;
        }
    }
    {
        u8 *p34 = sp + 34;
        u8 zero = 0;
        __asm__ volatile("" : "+r"(zero));
        *p34 = 16;
        {
            register u32 base __asm__("r1") = 0x082270bc;
            u8 c;
            u32 off;
            __asm__ volatile("" : "+r"(base));
            c = *(u8 *)(sp + 17);
            *(u32 *)(sp + 80) = ((s16 *)(base + 4 * c))[0] << 8;
            __asm__ volatile("" : "+r"(c));
            off = 4 * c;
            base += 2;
            *(u32 *)(sp + 84) = ((s16 *)(off + base))[0] << 8;
            __asm__ volatile("" : : "r"(c));
            __asm__ volatile("" : : "r"(base));
        }
        {
            u8 a;
            {
                register u32 t1 __asm__("r2") = 0x081738f2;
                register u32 t2 __asm__("r1") = 0x082270b0;
                register u8 c __asm__("r3") = *(u8 *)(sp + 17);
                __asm__ volatile("" : "+r"(t1));
                __asm__ volatile("" : "+r"(t2));
                a = *(u8 *)(t1 + 2 * (*(u16 *)(t2 + 2 * c) >> 8));
                __asm__ volatile("" : : "r"(c));
            }
            BlendCopy_080224E4(a, (void *)0x082270d4, (void *)0x082270d4, 0);
        }
        *(u8 *)(sp + 19) = zero;
    }
}
