/* Wave 36-C MATCHED: 0x08038520, 136 B, true extent 0x08038520-0x080385a8 (next fn 0x080385a8; pools at 0x080385a0-0x080385a4 belong to this fn).
   Compiler: main agbcc (old also 0 diffs). Variants: 6. Key idioms: switch with fallthrough from case 0 to case 1 (not if/else-if);
   u16 barrier forces the full lsl/lsr cast; case-1 first store via pointer variable q = s + 18076 with z assigned after q, before the 7-store.
   Pools LE-verified: 0x469d (18077), 0x469c (18076). Verification: clean-room harness 136/136 B, 0 diffs (both compilers). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
extern int Sub_08024384(int a);
__asm__(".set Sub_08024384, 0x08024384");
extern int Sub_080112FC(int a, int b);
__asm__(".set Sub_080112FC, 0x080112fc");
extern int Sub_080114B8(void);
__asm__(".set Sub_080114B8, 0x080114b8");
extern int Sub_080114E8(void);
__asm__(".set Sub_080114E8, 0x080114e8");
__attribute__((section(".text.w36c_08038520")))
int Sub_08038520(u8 *s)
{
    int r = 0;
    u8 *p = s + 18077;
    s8 v = p[0];
    switch (v) {
    case 0: {
        int t = Sub_08024384(4096) - 50;
        u16 u = Sub_080112FC((u8)t, 8);
        __asm__ volatile("" : "+r"(u));
        if (u == 0) {
            *(s + 18076) = 7;
            p[0] = 0;
            break;
        }
        if ((s8)Sub_080114B8() != 0)
            break;
        p[0]++;
    }
    case 1:
        if ((s16)Sub_080114E8() == 1) {
            u8 *q = s + 18076;
            int z = 0;
            *q = 7;
            *(s + 18077) = z;
            r = 2;
        }
        break;
    default:
        break;
    }
    return r;
}
