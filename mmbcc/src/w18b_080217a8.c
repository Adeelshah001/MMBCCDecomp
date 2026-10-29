/* Wave 18-B: 0x080217A8 (40 B, 1 caller, 1 bl -> Node_PopAndInit_20ED4). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);

__attribute__((section(".text.w18b_080217a8")))
u8 *NodeInit_080217A8(u8 x)
{
    u8 *r = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 2);
    u32 z = 0;
    if (r != 0) {
        r[16] = z;
        r[17] = x;
        *(u32 *)(r + 40) = (u32)r;
    }
    return r;
}
