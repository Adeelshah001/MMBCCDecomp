/* Wave 36-D MATCHED (old_agbcc, 0 diffs over 140 B true extent 0x0801c254-0x0801c2e0; clamp copy via pinned-r0 inline-asm copy, mask via runtime neg variable, f34 via pointer reuse): 0x0801c254, 140 B, extent next-func 0x08018980. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u8 pad0[34];
    u8 f34;
    u8 pad1[9];
    u32 f44;
    u8 pad2[21];
    u8 f69;
    u8 pad3[18];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void Sub_0800D6E0(u32 a, u32 b, u32 c);
__asm__(".set Sub_0800D6E0, 0x0800d6e0");
extern void Sub_0800D9EC(u32 a, u32 b);
__asm__(".set Sub_0800D9EC, 0x0800d9ec");
extern void Sub_0800DD08(u32 *out, S *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_0800DD2C(S *s, u32 a, u32 b);
__asm__(".set Sub_0800DD2C, 0x0800dd2c");
extern void Sub_0804A378(u32 a);
__asm__(".set Sub_0804A378, 0x0804a378");

__attribute__((section(".text.w36d_0801c254")))
void Sub_0801C254(S *s)
{
    u32 out[2];
    s32 mode;
    u8 *p;
    s32 neg;
    u32 zero;
    Sub_0800D6E0((u32)s, 0x242, 0);
    Sub_0800D9EC((u32)s, 1);
    mode = 3 & *(u8 *)(0x020031e4 + ((*(u16 *)0x081705b0 >> 4) << 1));
    {
        /* No pure-C formulation emitted ROM's adds r0,r1 copy before the
         * compare (old_agbcc folds the temp away); force it with one
         * inline-asm copy into a pinned r0 temp, branch stays in C. */
        register s32 chk __asm__("r0");
        __asm__ volatile("add %0, %1, #0" : "=r"(chk) : "r"(mode));
        if (chk > 3)
            mode = 3;
    }
    p = (u8 *)s + 69;
    mode <<= 2;
    neg = -13;
    *p = (*p & neg) | mode;
    p -= 35;
    zero = 0;
    *p = 13;
    s->f88 = zero;
    s->f96 = zero;
    s->f92 = 128 << 2;
    s->f100 = 80;
    Sub_0800DD08(out, s);
    Sub_0800DD2C(s, 0xffffec00, 0xffffa600);
    Sub_0804A378(132);
}
