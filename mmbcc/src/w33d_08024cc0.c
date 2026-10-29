/* W33-D MATCHED: tiny wrappers batch 1. main agbcc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern void F_08002300(void);
extern void F_0800B520(void);
extern void F_08004E60(u8 a);
extern u32 F_08004AD7C(void);
extern u32 F_080249B8(u8 *p, u8 a, u8 b);

__attribute__((section(".text.w33d_08024cc0")))
u16 sub_08024CC0(u8 *p, u8 a, u8 b)
{
    return (u16)F_080249B8(p, a, b);
}

/* Unmatched callee stubs (absolute symbols). */
__asm__(
    ".thumb_func\n"
    ".globl F_08002300\n"
    ".set F_08002300, 0x08002300\n"
    ".thumb_func\n"
    ".globl F_0800B520\n"
    ".set F_0800B520, 0x0800B520\n"
    ".thumb_func\n"
    ".globl F_08004E60\n"
    ".set F_08004E60, 0x08004E60\n"
    ".thumb_func\n"
    ".globl F_08004AD7C\n"
    ".set F_08004AD7C, 0x0804AD7C\n"
);
