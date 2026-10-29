/* Wave 26-D: 0x0800d1e0 (152 B incl. pool) - draft 1 */
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

extern u8 g_08173530[];
extern u32 NodeInit_0802260C(u8 idx);
extern u8 Byte12_Gt1_08022634(u32 node);
extern void BitCtl_520C(int x);

__asm__(
    ".set g_08173530, 0x08173530\n"
);

__attribute__((section(".text.w26d_0800d1e0")))
int NodeInitSwitch_0800D1E0(u8 *p0, u8 *p1, u8 *p2, u8 *p3)
{
    u8 v2 = *p2;
    u8 v3 = *p3;
    u8 v1 = *p1;
    int ret = 1;
    u8 v16 = p0[6];
    switch (v1) {
    case 0:
        v1 = 1;
    case 1: {
        u8 *base = g_08173530;
        int off = v16 * 2;
        u32 node;
        int five = 5;
        base++;
        node = NodeInit_0802260C(*(base + off));
        *(u32 *)(p0 + 12) = node;
        if (node == 0)
            break;
        v1 = (u8)(v1 + 1);
        __asm__ volatile("" : "+r" (five));
        p0[9] &= -five;
    }
    case 2:
        if (Byte12_Gt1_08022634(*(u32 *)(p0 + 12)) == 0)
            break;
        BitCtl_520C(1);
        ret = 0;
        break;
    }
    *p2 = v2;
    *p3 = v3;
    *p1 = v1;
    return ret;
}
