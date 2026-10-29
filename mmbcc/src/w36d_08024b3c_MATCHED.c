/* Wave 36-D MATCHED (old_agbcc, 0 diffs over 140 B true extent 0x08024b3c-0x08024bc8; goto-dispatch with signed key, shared (u16) ret block before default, trailing 00 00 pad object), 140 B, extent next-func 0x08024bc8. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

extern u32 Sub_080248C4(u32 a, u32 b);
__asm__(".set Sub_080248C4, 0x080248c4");
extern u32 Sub_08024918(u32 a, u32 b, u32 c);
__asm__(".set Sub_08024918, 0x08024918");
extern u32 Sub_08024A30(u32 a, u32 b, u32 c);
__asm__(".set Sub_08024A30, 0x08024a30");
extern u32 Sub_0802493C(u32 a, u32 b);
__asm__(".set Sub_0802493C, 0x0802493c");
extern u32 Sub_080249B8(u32 a, u32 b, u32 c);
__asm__(".set Sub_080249B8, 0x080249b8");

__attribute__((section(".text.w36d_08024b3c")))
u16 Sub_08024B3C(u8 a0, u8 a1, u8 a2, u8 a3)
{
    u32 base = 0x02007090;
    s32 key = (a2 << 1) | a0;
    u32 rv;
    if (key == 1)
        goto case1;
    if (key > 1)
        goto gt;
    if (key == 0)
        goto case0;
    goto def;
gt:
    if (key == 2)
        goto case2;
    if (key == 3)
        goto case3;
    goto def;
case0:
    if (a1 == a3)
        rv = Sub_080248C4(base, a3);
    else
        rv = Sub_08024918(base, a1, a3);
    goto ret;
case1:
    rv = Sub_08024A30(base, a3, a1);
    goto ret;
case2:
    rv = Sub_08024A30(base, a1, a3);
    goto ret;
case3:
    if (a1 == a3)
        rv = Sub_0802493C(base, a3);
    else
        rv = Sub_080249B8(base, a1, a3);
    goto ret;
ret:
    return (u16)rv;
def:
    return 0;
}

/* Explicit 00 00 pad: GAS would otherwise emit a c0 46 nop fill here. */
__asm__(".short 0");
