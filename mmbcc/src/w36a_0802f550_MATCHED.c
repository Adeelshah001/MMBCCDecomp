/* Wave 36-A MATCHED: 0x0802f550, 92 B, main agbcc, 5 variants.
   Extent basis: code 0x0802f550-0x0802f5a5 (bx r1), pad 0x0802f5a6-0x0802f5a7, pool
   0x0802f5a8 (0xfff10000) -> 0x0802f5ac.
   u8 params truncated at entry; x=(u16)(a0-a1+100) with asm truncation (gcc otherwise
   defers it as redundant); conditional pool add (a3==2 && a2!=2) via asm with trailing
   pool (gcc optimizes x+=0xfff1 to subs #15); sx=(s16)x, range/call sequence in C. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
extern u32 Sub_080400A8(void);
__asm__(".set Sub_080400A8, 0x080400a8");
extern u32 Sub_0804DEE8(u32 a, u32 b);
__asm__(".set Sub_0804DEE8, 0x0804dee8");
__attribute__((section(".text.w36a_0802f550")))
u32 Sub_0802F550(u8 a0, u8 a1, u8 a2, u8 a3)
{
    register u16 x __asm__("r0");
    u32 result = 0;
    u16 t;
    u32 u;
    s16 sx;
    x = (u16)(a0 - a1 + 100);
    __asm__ volatile("lsl %0, %0, #16\n\t"
        "lsr %0, %0, #16" : "+r"(x));
    if (a3 == 2 && a2 != 2) {
        __asm__ volatile(
            "lsl %0, %0, #16\n\t"
            "ldr r1, .L2f550_c\n\t"
            "add %0, %0, r1\n\t"
            "lsr %0, %0, #16\n\t"
            : "+r"(x) : : "r1");
    }
    sx = (s16)x;
    if (sx <= 99) {
        t = (u16)Sub_080400A8();
        u = Sub_0804DEE8(t, 99);
        if (sx < (s16)(u + 1))
            result = 1;
    }
    return result;
}
/* Explicit 00 00 pad + pool: ROM has 00 00 after bx, then pool 0xfff10000. */
__asm__(
    ".section .text.w36a_0802f550,\"ax\",%progbits\n\t"
    ".hword 0\n\t"
    ".align 2\n"
    ".L2f550_c: .word 0xfff10000\n\t");
