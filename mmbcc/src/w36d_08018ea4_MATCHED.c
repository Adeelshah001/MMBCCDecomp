/* Wave 36-D MATCHED (old_agbcc, 0 diffs over 144 B true extent 0x08018ea4-0x08018f34; goto-dispatch with st pinned u32 r5, out-pair r1 + dead r2 asm load, trailing 00 00 pad object), 144 B, extent next-func 0x08018f34. */
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
extern void Sub_080178A8(u32 a, u32 b, s32 c, u32 d, u32 e);
__asm__(".set Sub_080178A8, 0x080178a8");
extern void Sub_08017478(u32 a, u32 b);
__asm__(".set Sub_08017478, 0x08017478");

__attribute__((section(".text.w36d_08018ea4")))
u32 Sub_08018EA4(S *s)
{
    u32 out[2];
    register u32 st __asm__("r5");
    register s32 o0 __asm__("r1");
    register u32 o1 __asm__("r2");
    Sub_0800DD4C((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    Sub_0800DD08(out, s);
    o0 = out[0];
    __asm__ volatile("ldr %0, [sp, #8]" : "=r"(o1));
    (void)o1;
    st = s->f13;
    if (st == 0)
        goto case0;
    if (st == 1)
        goto case1;
    goto ret0;
case0: {
        u32 nib;
        if (o0 <= (200 << 6))
            goto ret0;
        nib = ((u32)s->f35 << 28) >> 28;
        Sub_080178A8(93, nib, 240 << 6, 0xffffe700, s->f44);
        s->f96 = st;
        s->f18 = 2;
        s->f13++;
        goto ret0;
    }
case1: {
        u32 nf = s->f18 - 1;
        s->f18 = nf;
        if ((nf << 24) != 0)
            goto ret0;
        Sub_08017478(s->f44, 7);
        return 1;
    }
ret0:
    return 0;
}

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
