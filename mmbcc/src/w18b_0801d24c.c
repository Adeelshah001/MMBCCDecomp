/* Wave 18-B: 0x0801D24C (42 B, 1 caller, 1 bl -> Node_PopAndInit). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18b_0801d24c")))
u8 *NodeInit_0801D24C(u8 *p, u8 x)
{
    u8 *r = (u8 *)Node_PopAndInit(0, 0, 0, 12);
    if (r != 0) {
        r[16] = 3;
        r[17] = x;
        *(u32 *)(r + 40) = (u32)p;
    }
    return r;
}
