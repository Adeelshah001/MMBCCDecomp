/* W57-A: 0x08010138 MATCHED (standalone 0-diff, old+main, see RESULTS.md).
 * Mechanism: explicit-shift zero-extension (u32)(x<<16)>>16 in place of
 * (u16) casts (a conversion with dest==source reg is deferred by old_agbcc
 * and only the lsl survives at the ==0 test); block-scoped r0 pins q1/t
 * hold the truncated quotient in r0, q (r1) is block 2's merged value.
 * Trailing .balign 4, 0 gives the ROM 00 00 pad (GAS default is c0 46).
 * old_agbcc -O2 -mthumb-interwork (main identical).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;

extern int Ewram5160_Init_10508(int a);
extern int SDiv_0804DD08(int a, int b);

__attribute__((section(".text.w57a_08010138")))
u8 Sub_08010138(u8 a0, u32 a1, u16 a2, u16 a3, u16 a4, u16 a5, u8 a6)
{
    register u8 *g __asm__("r5") = (u8 *)0x02005160;
    u16 q;

    if (g[0] != 0)
        return 0;
    Ewram5160_Init_10508(3);
    g[0x42] = a0;
    *(u16 *)(g + 0x38) = a2;
    *(u32 *)(g + 0x30) = a1;
    g[0x41] = a6;
    {
        u16 t = a5;
        __asm__ volatile("": "+r" (t));
        if ((s16)a5 <= 0)
            t = 1;
        a5 = t;
    }
    {
        u16 t = a3;
        __asm__ volatile("": "+r" (t));
        if ((s16)a3 < 0)
            t = 0;
        a3 = t;
    }
    {
        u16 t = a3;
        __asm__ volatile("": "+r" (t));
        if ((s16)a3 > (s16)a5)
            t = a5;
        a3 = t;
    }
    {
        u16 t = a4;
        __asm__ volatile("": "+r" (t));
        if ((s16)a4 < 0)
            t = 0;
        a4 = t;
    }
    {
        u16 t = a4;
        __asm__ volatile("": "+r" (t));
        if ((s16)a4 > (s16)a5)
            t = a5;
        a4 = t;
    }
    {
        register u32 q1 __asm__("r0") = (u32)(SDiv_0804DD08((s16)a3 * 24, (s16)a5) << 16) >> 16;
        if ((s16)a3 > 0 && q1 == 0)
            q1 = 1;
        else
            q1 = (u32)(q1 << 16) >> 16;
        g[0x3b] = q1;
    }
    {
        register u32 t __asm__("r0") = (u32)(SDiv_0804DD08((s16)a4 * 24, (s16)a5) << 16) >> 16;
        if ((s16)a4 > 0 && t == 0)
            q = 1;
        else
            q = (u16)t;
    }
    g[0x40] = q;
    __asm__ volatile("": "+r" (g));
    return 1;
}


__asm__(".balign 4, 0");

