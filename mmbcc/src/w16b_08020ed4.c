/* Wave 16 worker B: 0x08020ED4 (132 B incl pools).
 * Pops a node from one of two lists (flag a selects sub_08004424 vs
 * sub_08004454 on *(u32*)0x020066F0), then initializes node fields:
 * bits at +35 from b/c, d at +9, ROM-table pointer indexed by d at +20.
 * Idioms: pinned regs (s=r4,b=r5,c=r6,d=r7); split-adds for p=s+35;
 * widened int temps for &-113 / &-16 (movs+negs, no u8 fold to 0xF0).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


extern u32 *sub_08004424(u32 list);
extern u32 *sub_08004454(u32 list);
extern u32 g_020066F0;
extern u32 PtrTbl_08226EF0[];
u32 *sub_08004424(u32 list);
u32 *sub_08004454(u32 list);

u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d) __attribute__((section(".text.w16b_08020ed4")));
u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d)
{
    register u32 *s __asm__("r4");
    u8 *p;
    u32 *tbl;
    int v;
    int w;
    u8 x, t;

    if (a == 0)
        s = sub_08004424(g_020066F0);
    else
        s = sub_08004454(g_020066F0);
    if (s != 0) {
        p = (u8 *)s;
        p += 35;
        x = (b & 7) << 4;
        v = -113;
        v &= *p;
        v |= x;
        t = c & 15;
        w = -16;
        v &= w;
        v |= t;
        *p = v;
        if (c == 0)
            v &= 0x7F;
        else
            v |= 0x80;
        *p = v;
        tbl = PtrTbl_08226EF0;
        ((u8 *)s)[9] = d;
        ((u32 *)s)[5] = *(u32 *)tbl[d];
    }
    return s;
}

__asm__(
    ".set g_020066F0, 0x020066F0\n"
    ".set PtrTbl_08226EF0, 0x08226EF0\n"
);