/* Wave 35-C v1: 0x08006e30 — u8 wrapper over 0x08006e6c */
typedef unsigned char u8;
typedef short s16;
typedef signed char s8;
typedef unsigned int u32;
extern u8 Worker_08006E6C(void *p, void *a, s16 b, s16 c, s8 d, u8 e);
__asm__(".set Worker_08006E6C, 0x08006e6c");
__attribute__((section(".text.w35c_08006e30")))
u8 Sub_08006E30(void *a, s16 b, s16 c, s8 d, u8 e)
{
    return Worker_08006E6C((void *)0x0200483c, a, b, c, d, e);
}
