/* Wave 15-C: ObjInit_0801F9EC @ 0x0801f9ec (old_agbcc). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void Wrapper_D728(u32 a, u16 b, u8 c);
extern void ChipSlot_IncUse(u8 *s, u8 idx);
extern u16 gRom_081705B0[];
extern u8 gEwram_020031E4[];
void __attribute__((section(".text.w15c2_0801f9ec"))) ObjInit_0801F9EC(u8 *s)
{
    register u8 *r5 __asm__("r5") = *(u8 **)(s + 40);
    u8 t;
    {
        register u32 z __asm__("r0") = 0;
        *(u32 *)(s + 108) = z;
    }
    t = 2;
    t |= s[10];
    s[10] = t | 1;
    Wrapper_D728((u32)s, 15639, 0);
    ChipSlot_IncUse(s, 0);
    {
        u32 idx;
        int mask;
        idx = (*(u8 *)((((gRom_081705B0[0] >> 4) << 1) + (u32)gEwram_020031E4))) & 3;
        {
            register int c __asm__("r0");
            __asm__ ("movs %0, %1" : "=r" (c) : "r" (idx));
            if (c > 3)
                idx = 3;
        }
        {
            u8 *p = s;
            u32 sh;
            p += 0x45;
            sh = idx << 2;
            mask = -13;
            *p = (*p & mask) | sh;
        }
    }
    {
        u8 *q = s + 0x22;
        u32 z = 0;
        *q = z;
        *(u32 *)(s + 80) = z;
        *(u32 *)(s + 84) = z;
        s[18] = 0x40;
        s[19] = 16;
        r5[7] = z;
    }
}

