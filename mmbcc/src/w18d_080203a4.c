/* Worker D wave18 @0x080203a4 (58 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w18d_080203A4")))
u8 *NewNode_080203A4(u8 *a, u8 *b, u8 c)
{
    u8 t;
    u8 *p = (u8 *)Node_PopAndInit(1, 0, 0, 18);
    if (p != 0) {
        p[16] = 1;
        p[17] = c;
        t = a[120];
        p[120] = t;
        *(u8 **)(p + 40) = a;
        *(u8 **)(p + 44) = b;
    }
    return p;
}
__asm__(
    ".thumb\n"
    ".thumb_func\n"
);
