/* Worker D wave18 @0x0801f154 (44 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w18d_0801F154")))
u8 *NewNode_0801F154(u8 *a, u8 *b)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 1, 0, 17);
    if (p != 0) {
        u8 z = 0;
        p[16] = 3;
        p[17] = z;
        *(u8 **)(p + 40) = a;
        *(u8 **)(p + 44) = b;
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
