/* Worker B wave19 @0x08017434 (36 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_08017434")))
u8 *NewNode_08017434(void)
{
    u8 *p = (u8 *)Node_PopAndInit(0, 1, 0, 1);
    if (p != 0) {
        u8 z = 0;
        p[16] = z;
        p[17] = z;
        p[18] = z;
        *(u32 *)(p + 40) = z;
    }
    return p;
}
