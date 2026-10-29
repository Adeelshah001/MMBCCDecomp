/* Wave 20-D @0x0801029C (86 B). MATCHED with main agbcc + FIXALIGN1.
 * Setup twin of 0x0800FFF4/0x0801009C family: if (*(u8*)0x02005160 != 0) return 0;
 * else Ewram5160_Init_10508(4), then write (z, a1, a2, a0, a3) to the struct:
 * [66]=z, [69]=a1, [56]=(u16)a2, [48]=(u32)a0, [65]=a3; return 1.
 * Mid-function literal pool (pool word at +0x44).
 *
 * Idioms: pinned `register u8 *p __asm__("r4")` / `register u8 z __asm__("r5")`
 * fix the p/z swap; opaque "add %0,%0,#3" forces explicit adds r0,#3;
 * pinned `register u8 *q3 __asm__("r0")` forces `adds r0,r4,#0` (compiler
 * reuses r4 otherwise).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Ewram5160_Init_10508(u32 v);

__attribute__((section(".text.w20d_0801029C")))
u8 Setup_0801029C(u32 a0, u8 a1, u16 a2, u8 a3)
{
    register u8 *p __asm__("r4") = (u8 *)0x02005160;
    register u8 z __asm__("r5");
    u8 *q1;
    u8 *q2;
    register u8 *q3 __asm__("r0");
    z = p[0];
    if (z != 0) {
        return 0;
    }
    Ewram5160_Init_10508(4);
    q1 = p + 66;
    *q1 = z;
    /* opaque adds forces adds r0,#3 (compiler folds to indexed strb otherwise) */
    __asm__ ("add %0, %0, #3" : "+r" (q1));
    *q1 = a1;
    *(u16 *)(p + 56) = a2;
    *(u32 *)(p + 48) = a0;
    q3 = p + 65;
    *q3 = a3;
    return 1;
}
