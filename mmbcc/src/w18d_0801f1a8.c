/* Worker D wave18 @0x0801f1a8 (46 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w18d_0801F1A8")))
u8 *NewNode_0801F1A8(u8 *a, u8 *b, u8 c)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 1, 0, 17);
    if (p != 0) {
        p[16] = 4;
        p[17] = c;
        *(u8 **)(p + 40) = a;
        *(u8 **)(p + 44) = b;
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
