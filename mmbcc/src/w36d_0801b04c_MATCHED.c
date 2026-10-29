/* Wave 36-D MATCHED (C + .s patch w36d_0801b04c_patch.py, old_agbcc, 0 diffs over 144 B true extent 0x0801b04c-0x0801b0dc; patch reorders table load to base-first; o1 pinned s32 r3, st pinned u32 r5, trailing 00 00 pad object), 144 B, extent next-func 0x0801b0dc. */
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
    u8 pad2[3];
    u8 f17;
    u8 pad3[17];
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
extern void Sub_0804A378(u32 a);
__asm__(".set Sub_0804A378, 0x0804a378");

__attribute__((section(".text.w36d_0801b04c")))
u32 Sub_0801B04C(S *s)
{
    u32 out[2];
    s32 o0;
    register s32 o1 __asm__("r3");
    register u32 st __asm__("r5");
    u32 a = 253;
    Sub_0800DD4C((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    Sub_0800DD08(out, s);
    o0 = out[0];
    o1 = out[1];
    st = s->f13;
    if (st != 0)
        goto ret0;
    if (o1 <= -1280)
        goto ret0;
    {
        u8 b = *(u8 *)(0x08226728 + s->f17);
        u32 nib = ((u32)s->f35 << 28) >> 28;
        Sub_080178A8(b, nib, (s16)o0, 0, s->f44);
    }
    s->f88 = st;
    s->f96 = st;
    s->f92 = st;
    s->f100 = st;
    s->f10 = (s->f10 & a) & 254;
    if (s->f17 != 0)
        Sub_0804A378(135);
    return 1;
ret0:
    return 0;
}

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
