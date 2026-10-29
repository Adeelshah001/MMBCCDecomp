/* Wave 36-D MATCHED (C + .s patch w36d_0800ce7c_patch.py, old_agbcc, 0 diffs over 148 B true extent 0x0800ce7c-0x0800ce7c; pinned a=r1/b=r2, zero-before-stores, halfword double-AND split, pools + set0 moved to ROM layout, trailing 00 00 pad), 148 B, extent next-func 0x0800ce7c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 Sub_0800D12C(u8 *s, u8 *a, u8 *b, u8 *c);
__asm__(".set Sub_0800D12C, 0x0800d12c");
extern u8 Sub_0800D278(u8 *s, u8 *a, u8 *b, u8 *c);
__asm__(".set Sub_0800D278, 0x0800d278");

__attribute__((section(".text.w36d_0800ce7c")))
u32 Sub_0800CE7C(u8 *s)
{
    u32 r5 = 1;
    switch (s[1]) {
    case 0:
        if (s[6] == 0)
            s[1] = 1;
        else
            s[1] = 2;
        break;
    case 1:
        if (Sub_0800D12C(s, s + 3, s + 4, s + 5) == 0)
            s[1] = 3;
        break;
    case 2:
        if (Sub_0800D278(s, s + 3, s + 4, s + 5) == 0)
            s[1] = 3;
        break;
    case 3: {
        register u8 a __asm__("r1") = s[0];
        register u8 b __asm__("r2") = s[7];
        if (a == b) {
            r5 = 0;
        } else {
            u8 zero = 0;
            s[6] = a;
            s[0] = b;
            s[3] = zero;
            s[2] = zero;
            s[1] = zero;
            *(u16 *)0x020031e0 = (*(u16 *)0x020031e0 & 0xedff) & 0xdbff;
        }
        break;
    }
    default:
        break;
    }
    return r5;
}

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
