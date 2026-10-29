/* Wave 18-B: 0x080225E4 (38 B, 1 caller, 1 bl -> Node_PopAndInit_20ED4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18b_080225e4")))
u8 *NodeInit_080225E4(u8 x)
{
    u8 *r = (u8 *)Node_PopAndInit_20ED4(0, 2, 0, 4);
    if (r != 0) {
        r[16] = 0;
        r[17] = x;
    }
    return r;
}
