/* Worker B wave19 @0x0801f180 (40 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_0801F180")))
u8 *NewNode_0801F180(u8 *a)
{
    register u8 *p __asm__("r2") = (u8 *)Node_PopAndInit(1, 1, 0, 17);
    register u8 *aa __asm__("r4") = a;
    if (p != 0) {
        register u8 z __asm__("r1") = 0;
        p[16] = 5;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
    }
    return p;
}
