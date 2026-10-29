/* Wave 18-B: 0x08022F88 (38 B, 1 caller, 1 bl -> Node_PopAndInit_20ED4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18b_08022f88")))
u8 *NodeInit_08022F88(u32 x)
{
    u8 *r = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 6);
    if (r != 0) {
        r[16] = 0;
        r[17] = 0;
        *(u32 *)(r + 40) = x;
    }
    return r;
}
