/* Wave21 worker C @0x08043630 (76 B: 62 code + 2 pad + 12 pool), attempt 3 (landed).
 * No pins: natural C + early-zero idiom (u8 z = 0 materialized while r0=y
 * live and r3 dead -> movs r3,#0). u32 y avoids the u8 return extend (w15-D).
 * Barrier keeps the 3 pools separate (defeats the 3-pool fold).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void sub_08005A9C(u32 a);
/* W21-A fix: wave7_b.c's .set is LOCAL (invisible here); define file-local. */
__asm__(".set sub_08005A9C, 0x08005A9C");
extern u32 CountNonzeroStride(u8 *s); /* actual: u8 (w16b_0804580c.c); u32 decl suppresses the return zero-extend (w15-D idiom); call+use identical */
extern void sub_08042E14(u8 *s);
extern void sub_08043430(u8 *s);
extern void Gfx_Blit3(u8 *s);
extern void sub_08045838(u8 *s);
__attribute__((section(".text.w21c_08043630")))
void F_08043630(u8 *s)
{
    u32 y;
    u8 *base;
    u8 *p;
    u8 *q;
    u8 z;
    sub_08005A9C(8);
    y = CountNonzeroStride(s);
    base = (u8 *)0x02004830;
    __asm__ volatile("" : "+r" (base));
    p = base + 0x26A;
    z = 0;
    *p = (u8)y;
    q = base + 0x26B;
    *q = z;
    sub_08042E14(s);
    sub_08043430(s);
    Gfx_Blit3(s);
    sub_08045838(s);
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl sub_08042E14\n.set sub_08042E14, 0x08042E14\n"
    ".globl sub_08043430\n.set sub_08043430, 0x08043430\n"
    ".globl sub_08045838\n.set sub_08045838, 0x08045838\n"
);
