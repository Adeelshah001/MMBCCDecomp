/* Worker D wave18 @0x0801cdac (44 B). MATCHED with main agbcc. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w18d_0801CDAC")))
u8 *NewNode_0801CDAC(u8 a, u8 b)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 0, a, 11);
    if (p != 0) {
        u8 z = 0;
        p[16] = b;
        p[17] = a;
        *(u32 *)(p + 40) = z;
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
