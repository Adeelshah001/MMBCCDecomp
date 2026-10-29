/* Worker D wave17 Part1 C1 re-derivation @0x0800b3b0 (58B incl pool). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Ewram4E40_Init_0B4E4(void);
extern void Clr_0800B4C8(void);
__attribute__((section(".text.w17d_0800B3B0")))
u32 FlagCheckInit_0800B3B0(u8 *p)
{
    register u32 p3 __asm__("r3");
    register u8 *q __asm__("r2");
    u8 t;
    __asm__ volatile("add %0, %1, #0" : "=r" (p3) : "r" ((u32)p));
    __asm__ volatile("" : "=r" (q) : "0" ((u8 *)0x02004E40));
    t = q[4];
    if ((t & 15) != 0) return 0;
    {
        u32 r = 128;
        r &= t;
        if (r == 0) {
            q[5] = 1;
            return 0;
        }
    }
    *(u32 *)(q + 32) = p3;
    q[5] = 3;
    Ewram4E40_Init_0B4E4();
    Clr_0800B4C8();
    return 1;
}

