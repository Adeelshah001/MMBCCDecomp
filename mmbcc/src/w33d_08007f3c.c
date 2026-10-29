/* W33-D MATCHED: tiny wrappers batch 2. main agbcc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;

extern void F_08007F54(u16 a, s8 b, s8 c, u32 d);
extern void F_0800BF6C(s16 a, u32 b);
extern u32 sub_0800B3EC(void);

__attribute__((section(".text.w33d_08007f3c")))
void sub_08007F3C(u16 a, s8 b, s8 c)
{
    F_08007F54(a, b, c, 0);
}

/* Unmatched callee stubs (absolute symbols). */
__asm__(
    ".thumb_func\n"
    ".globl F_08007F54\n"
    ".set F_08007F54, 0x08007F54\n"
    ".thumb_func\n"
    ".globl F_0800BF6C\n"
    ".set F_0800BF6C, 0x0800BF6C\n"
);
