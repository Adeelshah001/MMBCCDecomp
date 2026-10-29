/* Worker D wave18 @0x0801f050 (48 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w18d_0801F050")))
u8 *NewNode_0801F050(u8 *a, u8 b, u8 c)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 1, b, 17);
    if (p != 0) {
        p[16] = 0;
        p[17] = c;
        *(u8 **)(p + 40) = a;
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
