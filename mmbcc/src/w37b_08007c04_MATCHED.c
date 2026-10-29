/* Wave 37-B MATCHED: 0x08007c04, 136 B, old_agbcc, C (inline-asm ldrsb for entry[1] test) + .s patch (w37b_08007c04_patch.py: entry adds order lsl/ldr/add register swap). Extent to 0x08007c8c. Symdefs: Sub_08024670=0x08024670 (MATCHED), Sub_08005268=0x08005268, Sub_08007C8C=0x08007c8c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
extern int Sub_08024670(u16 a);
extern void Sub_08005268(u8 *a, u32 b);
extern void Sub_08007C8C(u16 a, int b);
__asm__(".set Sub_08024670, 0x08024670");
__asm__(".set Sub_08005268, 0x08005268");
__asm__(".set Sub_08007C8C, 0x08007c8c");
__attribute__((section(".text.w37b_08007c04")))
int Sub_08007C04(u16 a, u16 b)
{
    u16 bb = b;
    register s8 *e __asm__("r1");
    int z;
    u32 idx;
    int v;
    if (bb > 3)
        return -1;
    idx = bb * 8;
    e = (s8 *)0x02004e18 + idx;
    __asm__ volatile("movs %0, #1\n\tldrsb %0, [%1, %0]" : "=r"(v) : "r"(e));
    if (v == 0 && *(u16 *)(e + 2) == a)
        return 0;
    z = 0;
    e[1] = z;
    *(u16 *)(e + 2) = a;
    ((u8 *)e)[7] &= z - 3;
    if (bb == 0) {
        u32 *base = (u32 *)0x02003670;
        u16 h = *(u16 *)0x08171ef4;
        u32 r4 = base[2] + ((u32)h << 5) + 0xfa000000;
        int t = Sub_08024670(a);
        Sub_08005268((u8 *)0x0832b6c0 + (u16)t * 20, r4);
        Sub_08007C8C(a, 0);
    }
    return 0;
}
