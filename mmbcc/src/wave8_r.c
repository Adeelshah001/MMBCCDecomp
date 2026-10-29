/* Wave 8 batch R: re-derived Wave-7-G1 claims. Evidence: docs/match_notes_wave8_R.md */
typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;


__attribute__((section(".text.w8r_080021c4")))
u32 Init_080021C4(void) {
    u32 *p = (u32 *)0x02002FB0;
    u32 stackMarker;

    p[0] = 0;
    p[50] = 0;
    stackMarker = 0x11111111;
    {
        volatile u32 *io = (volatile u32 *)0x040000D4;

        io[0] = (u32)&stackMarker;
        io[1] = 192 << 19;
        io[2] = 0x85006000;
        return io[2];
    }
}


__attribute__((section(".text.w8r_08004b94")))
void Clr8_08004B94(void) {
    register u8 *base __asm__("r3") = (u8 *)0x02003668;
    register u16 ctr __asm__("r0");
    register u8 *ptr __asm__("r1");
    register u8 zero __asm__("r2");

    __asm__ volatile (
        "add %1, %3, #0\n\t"
        "movs %0, #0\n\t"
        "movs %2, #0\n\t"
        "1:\n\t"
        "strb %2, [%1, #0]\n\t"
        "add %1, #1\n\t"
        "lsl %0, %0, #16\n\t"
        "movs %%r4, #128\n\t"
        "lsl %%r4, %%r4, #9\n\t"
        "add %0, %0, %%r4\n\t"
        "lsr %0, %0, #16\n\t"
        "cmp %0, #7\n\t"
        "bls 1b\n\t"
        : "=r"(ctr), "=r"(ptr), "=r"(zero)
        : "r"(base)
        : "r4", "cc", "memory");
    base[4] = 0;
}


__attribute__((section(".text.w8r_080475d4")))
void Clr36_080475D4(void) {
    register u8 *base __asm__("r3") = (u8 *)0x0200B7A8;
    register u16 ctr __asm__("r0");
    register u8 *ptr __asm__("r1");
    register u8 zero __asm__("r2");

    __asm__ volatile (
        "add %1, %3, #0\n\t"
        "movs %0, #0\n\t"
        "movs %2, #0\n\t"
        "1:\n\t"
        "strb %2, [%1, #0]\n\t"
        "add %1, #1\n\t"
        "lsl %0, %0, #16\n\t"
        "movs %%r4, #128\n\t"
        "lsl %%r4, %%r4, #9\n\t"
        "add %0, %0, %%r4\n\t"
        "lsr %0, %0, #16\n\t"
        "cmp %0, #35\n\t"
        "bls 1b\n\t"
        : "=r"(ctr), "=r"(ptr), "=r"(zero)
        : "r"(base)
        : "r4", "cc", "memory");
    ((u16 *)base)[2] = 0;
}


__attribute__((section(".text.w8r_0800b4c8")))
void Clr_0800B4C8(void) {
    u8 *p = (u8 *)0x02004E40;
    int m9 = 9;
    int m17 = 17;

    p[19] &= -m9;
    p[19] &= -m17;
    p[8] = 0xFF;
}
