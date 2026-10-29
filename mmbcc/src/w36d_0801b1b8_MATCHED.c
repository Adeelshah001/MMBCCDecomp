/* Wave 36-D MATCHED (old_agbcc, 0 diffs over 140 B true extent 0x0801b1b8-0x0801b244; out-pair in callee-saved r5/r6, signed guard, decrement-temp with shift-compare, double-AND via runtime first operand), 140 B, extent next-func 0x0801b244. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    u8 pad0[10];
    u8 f10;
    u8 pad1[2];
    u8 f13;
    u8 pad2[4];
    u8 f18;
    u8 pad3[16];
    u8 f35;
    u8 pad4[8];
    u32 f44;
    u8 pad5[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern void Sub_0800DD4C(u32 a, u32 b, u32 c);
__asm__(".set Sub_0800DD4C, 0x0800dd4c");
extern void Sub_0800DD08(u32 *out, S *s);
__asm__(".set Sub_0800DD08, 0x0800dd08");
extern void Sub_080178A8(u32 a, u32 b, s32 c, s32 d, u32 e);
__asm__(".set Sub_080178A8, 0x080178a8");

__attribute__((section(".text.w36d_0801b1b8")))
u32 Sub_0801B1B8(S *s)
{
    u32 out[2];
    u8 st;
    register s32 o0 __asm__("r5");
    register u32 o1 __asm__("r6");
    Sub_0800DD4C((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    Sub_0800DD08(out, s);
    o0 = out[0];
    o1 = out[1];
    st = s->f13;
    switch (st) {
    case 0: {
        u32 nib;
        if (o0 <= (220 << 6))
            goto ret0;
        nib = ((u32)s->f35 << 28) >> 28;
        Sub_080178A8(120, nib, (s16)o0, (s16)o1, s->f44);
        s->f18 = 25;
        s->f13++;
        goto ret0;
    }
    case 1: {
        u32 nf = s->f18 - 1;
        u32 a = 253;
        s->f18 = nf;
        if ((nf << 24) != 0)
            goto ret0;
        s->f10 = (s->f10 & a) & 254;
        return 1;
    }
    default:
        goto ret0;
    }
ret0:
    return 0;
}
