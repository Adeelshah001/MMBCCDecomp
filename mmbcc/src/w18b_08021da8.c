/* Wave 18-B: 0x08021DA8 (40 B, 1 caller, 1 bl -> Node_PopAndInit_20ED4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18b_08021da8")))
u8 *NodeInit_08021DA8(u8 *p)
{
    u8 *r = (u8 *)Node_PopAndInit_20ED4(1, 0, 0, 3);
    if (r != 0) {
        r[16] = 3;
        r[17] = p[17];
        *(u32 *)(r + 40) = (u32)p;
    }
    return r;
}
