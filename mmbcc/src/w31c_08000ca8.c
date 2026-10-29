/* Wave 31-C: 0x08000CA8 Init_08000CA8 (44 B) - MATCHED 0 diffs, old_agbcc */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w31c_08000ca8")))
void Init_08000CA8(u32 param) {
    register u32 *base __asm__("r3") = (u32 *)0x030023c8;
    u32 *p1 = base - 2;
    register u32 zero __asm__("r2") = 0;
    *p1 = zero;
    *(base - 1) = param;
    *(u32 *)0x02000800 = zero;
    {
        u8 *b = (u8 *)base;
        u8 one = 1;
        int i = 2;
        do {
            *b = one;
            i--;
            b += 24;
        } while (i >= 0);
    }
}
