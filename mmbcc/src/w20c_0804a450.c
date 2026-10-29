/* Wave20 worker C @0x0804a450 (56 B), attempt 4. Pinned-constant barrier for
 * movs-before-ldrb; explicit redundant ldrh in the &= tail.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
__attribute__((section(".text.w20c_0804a450")))
void F_0804A450(void)
{
    register u16 *tbl __asm__("r1") = (u16 *)0x0200BD20;
    u8 *flag = (u8 *)0x02002EE0;
    __asm__ volatile("" : "+r" (tbl), "+r" (flag));
    {
        register u32 one __asm__("r0") = 1;
        __asm__ volatile("" : "+r" (one));
        one &= *flag;
        if (one == 0)
            return;
    }
    {
        u16 *q = (u16 *)((u8 *)tbl + 124);
        u16 v = *q;
        int i = 0;
        if (((s16 *)q)[i] == 0)
            return;
        *q = v - 1;
        if ((s16)(v - 1) != 8)
            return;
        {
            volatile u16 *pv = (volatile u16 *)(flag + 2);
            u16 v = *pv;
            u16 m = 0xFFFD;
            u16 dummy;
            m &= v;
            dummy = *pv;
            *pv = m;
        }
    }
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
