/* Wave 20-D @0x08010EC4 (110 B). MATCHED with main agbcc + FIXALIGN1.
 * Entry setup: if (((base[3]>>a)&1)==0) return 0; p=base+24+a*12;
 * if ((s8)sub_08010FB4(a)!=1) return 0; p[0]=1; p[6]=e; p[3]=b; p[4]=c; p[2]=d;
 * return 1. 5 args (e on stack), r8/r9 for call-surviving args.
 * Mid-function literal pool.
 *
 * Idioms: pinned `register u8 *base __asm__("r2")` prevents base+24 folding;
 * explicit `int a12=a*12` temp; pinned `register u8 *q __asm__("r1")` for
 * base+24 intermediate; divided-syntax "add %0,%1,%2" forces adds r4,r0,r1.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern u8 sub_08010FB4(u8 a);

__attribute__((section(".text.w20d_08010EC4")))
u8 F_08010EC4(u8 a, u8 b, u8 c, u8 d, u8 e)
{
    register u8 *base __asm__("r2") = (u8 *)0x020051b0;
    int v = base[3];
    u8 *p;
    int a12;
    v >>= a;
    if ((v & 1) == 0) {
        return 0;
    }
    a12 = a * 12;
    {
        register u8 *q __asm__("r1") = base + 24;
        /* divided-syntax forces adds r4,r0,r1 order (compiler swaps otherwise) */
        __asm__ ("add %0, %1, %2" : "=r" (p) : "r" (a12), "r" (q));
    }
    if ((s8)sub_08010FB4(a) != 1) {
        return 0;
    }
    p[0] = 1;
    p[6] = e;
    p[3] = b;
    p[4] = c;
    p[2] = d;
    return 1;
}
