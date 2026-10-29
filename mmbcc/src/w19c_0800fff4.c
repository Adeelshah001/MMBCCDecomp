/* Wave19 worker C @0x0800fff4 (136 B). MATCHED with old_agbcc.
 * Flag-guarded setup of two 32-byte records at 0x02004ca0 (Ewram5160 region):
 * p[29]=a|b|c (then d|e|f), p[30]=0, p[31]|=1, after Ewram5160_Init_10508(1)
 * and Zero_0801052C(). Twin: w19c_0801009c.c (Init arg 2).
 *
 * Idioms: scoped pinned `register u32 one __asm__("r2")` + empty volatile
 * asm barrier pins `movs r2,#1` above the `ldrb` (old_agbcc's scheduler
 * otherwise hoists the load into the delay slot); pinned p->r1 keeps the
 * natural r1/r0 (p/t) allocation; u32 t avoids re-extension lsls/lsrs.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Ewram5160_Init_10508(u32 v);
extern void Zero_0801052C(void);
__attribute__((section(".text.w19c_0800FFF4")))
u8 Setup_0800FFF4(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f)
{
    u8 z = *(u8 *)0x02005160;
    u32 t;
    if (z != 0)
        return 0;
    Ewram5160_Init_10508(1);
    Zero_0801052C();
    {
        register u8 *p __asm__("r1") = (u8 *)0x02004ca0;
        register u32 one __asm__("r2");
        p[29] = a | b | c;
        one = 1;
        __asm__ volatile("" : "+r" (one));
        t = p[31] | one;
        p[30] = z;
        __asm__ volatile("" : "+r" (t));
        p[31] = t | one;
        p += 32;
        p[29] = d | e | f;
        t = p[31] | one;
        p[30] = z;
        __asm__ volatile("" : "+r" (t));
        p[31] = t | one;
    }
    return 1;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
