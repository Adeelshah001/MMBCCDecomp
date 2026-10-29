/* Worker B wave19 @0x080228e0 (46 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_080228E0")))
u8 *NewNode_080228E0(u8 *a)
{
    register u8 *p __asm__("r2") = (u8 *)Node_PopAndInit_20ED4(1, 1, 0, 5);
    register u8 *aa __asm__("r4") = a;
    if (p != 0) {
        u32 dw0;
        u32 dw1;
        p[16] = 2;
        p[17] = aa[17];
        dw0 = *(u32 *)(aa + 80);
        dw1 = *(u32 *)(aa + 84);
        *(u32 *)(p + 80) = dw0;
        *(u32 *)(p + 84) = dw1;
    }
    return p;
}
