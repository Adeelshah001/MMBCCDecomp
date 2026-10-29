/* Worker D wave18 @0x0802030c (52 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w18d_0802030C")))
u8 *NewNode_0802030C(u8 *a, u8 b, u8 c)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 0, 0, 18);
    if (p != 0) {
        p[16] = 0;
        p[17] = c;
        p[120] = b;
        *(u8 **)(p + 40) = a;
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
