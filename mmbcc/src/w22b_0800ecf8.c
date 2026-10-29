/* Wave 22-B @0x0800ECF8 (38 B). MATCHED with no-interwork agbcc.
 * Setup_08010270 wrapper: if the setup returns 1, store 14 into byte
 * 0x20 of 0x02005130 (SetByte20_0800E1F0) and return 1; otherwise return
 * the setup's s8 result.
 * Twin of 0x0800ED20 (Setup_08010308 + store 15).
 * Idioms: codegen-shaped callee extern (u8,u32,u8,s8)->u32 (ABI-identical
 * to the real def in src/w21d_08010270.c); no-interwork epilogue
 * (push {lr} / pop {r1}; bx r1).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern u32 F_08010270(u8 a, u32 b, u8 c, s8 d);
extern void SetByte20_0800E1F0(u8 x);

__attribute__((section(".text.w22b_0800ECF8")))
s8 Setup10270_Flag14_0800ECF8(u8 a, u32 b, u8 c, s8 d)
{
    s8 r = F_08010270(a, b, c, d);
    if (r == 1) {
        SetByte20_0800E1F0(14);
        return 1;
    }
    return r;
}

/* Explicit 2-byte zero pad to match ROM (GAS would emit 0xc046) */
__asm__(
    ".section .text.w22b_0800ECF8,\"ax\",%progbits\n\t"
    ".byte 0, 0\n\t"
    ".previous"
);
