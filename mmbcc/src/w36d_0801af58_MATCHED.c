/* Wave 36-D MATCHED (old_agbcc + w36d_0801af58_patch.py, 0 diffs over 140 B true extent 0x0801af58-0x0801afe4; table-base load reordered by patch, trailing 00 00 pad object; out-pair loads via r2 pin + r3 inline-asm load; double-AND via runtime first operand), 140 B, extent next-func 0x0801afe4. */
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
extern u32 Sub_08017474(u32 a);
__asm__(".set Sub_08017474, 0x08017474");

__attribute__((section(".text.w36d_0801af58")))
u32 Sub_0801AF58(S *s)
{
    u32 out[2];
    u8 st;
    register u32 o0 __asm__("r2");
    register u32 o1 __asm__("r3");
    Sub_0800DD4C((u32)s, s->f88, s->f92);
    s->f88 += s->f96;
    s->f92 += s->f100;
    Sub_0800DD08(out, s);
    o0 = out[0];
    __asm__ volatile("ldr %0, [sp, #8]" : "=r"(o1));
    (void)o1;
    st = s->f13;
    switch (st) {
    case 0: {
        register u8 *tbl __asm__("r0");
        u8 b;
        u32 nib;
        tbl = (u8 *)0x08226725;
        b = tbl[s->f17];
        nib = ((u32)s->f35 << 28) >> 28;
        Sub_080178A8(b, nib, (s16)o0, 0, s->f44);
        s->f13++;
    }
        /* fall through */
    case 1: {
        u32 a = 253;
        if ((u8)Sub_08017474(s->f44) <= 5)
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

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
