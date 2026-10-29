/* Wave 22-B @0x0800ED20 (34 B). MATCHED with no-interwork agbcc.
 * Setup_08010308 wrapper: if the setup returns 1, store 15 into byte
 * 0x20 of 0x02005130 (SetByte20_0800E1F0) and return 1; otherwise return
 * the setup's s8 result.
 * Twin of 0x0800ECF8 (Setup_08010270 + store 14).
 * Idioms: codegen-shaped callee extern (u32,u32,s16,s8)->u32 (ABI-identical
 * to the real def in src/w21b_08010308.c); no-interwork epilogue
 * (push {lr} / pop {r1}; bx r1).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

extern u32 Sub_08010308(u32 a, u32 b, s16 c, s8 d);
extern void SetByte20_0800E1F0(u8 x);

__attribute__((section(".text.w22b_0800ED20")))
s8 Setup10308_Flag15_0800ED20(u32 a, u32 b, s16 c, s8 d)
{
    s8 r = Sub_08010308(a, b, c, d);
    if (r == 1) {
        SetByte20_0800E1F0(15);
        return 1;
    }
    return r;
}

/* Explicit 2-byte zero pad to match ROM (GAS would emit 0xc046) */
__asm__(
    ".section .text.w22b_0800ED20,\"ax\",%progbits\n\t"
    ".byte 0, 0\n\t"
    ".previous"
);
