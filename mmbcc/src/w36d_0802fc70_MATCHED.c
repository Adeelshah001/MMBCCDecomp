/* Wave 36-D MATCHED (C + .s patch w36d_0802fc70_patch.py, old_agbcc, 0 diffs over 140 B true extent 0x0802fc70-0x0802fd08; off reorder, call-result in r2, f29 copy + re-extensions, u32 return preserving r0 via pop r1/bx r1, trailing 00 00 pad), 140 B, extent next-func 0x0802fd08. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 Sub_0803FD68(u16 a);
__asm__(".set Sub_0803FD68, 0x0803fd68");
extern u32 Sub_0802D7A0(u8 *s, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i);
__asm__(".set Sub_0802D7A0, 0x0802d7a0");

__attribute__((section(".text.w36d_0802fc70")))
u32 Sub_0802FC70(u8 *s, u8 a, u8 b)
{
    u32 r5 = 0;
    u16 v;
    u8 r2;
    u8 f29;
    if (a == 0)
        v = *(u16 *)(*(u32 *)(s + (168 << 1) + b * 4) + 8);
    else
        v = *(u16 *)(*(u32 *)(s + (182 << 1) + b * 4) + 8);
    r2 = Sub_0803FD68(v);
    f29 = s[29];
    if (f29 == 3) {
        if (r2 == 1) {
            s[29] = 0;
            goto call;
        }
    }
    if ((u8)f29 == 1) {
        if (r2 == 2) {
            s[29] = 0;
            goto call;
        }
    }
    if ((u8)f29 == 4) {
        if (r2 == 3) {
            s[29] = r2;
            r5 = 1;
        }
    }
    if (r5 == 0)
        goto end;
call:
    return Sub_0802D7A0(s, 0, 2, 0, 2, 0, 0, 0, 84, 5);
end: ;

}

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
