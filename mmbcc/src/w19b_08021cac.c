/* Worker B wave19 @0x08021cac (100 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_08021CAC")))
u8 *NewNode_08021CAC(u8 *a, u8 *b)
{
    register u8 *aa __asm__("r4") = a;
    register u8 *bb __asm__("r5") = b;
    register u8 *p __asm__("r2");
    p = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (p != 0) {
        u8 z = 0;
        p[16] = z;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    p = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (p != 0) {
        register u8 z __asm__("r1") = 0;
        p[16] = 1;
        p[17] = z;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    p = (u8 *)Node_PopAndInit_20ED4(0, 0, 0, 3);
    if (p != 0) {
        p[16] = 1;
        p[17] = 1;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    return p;
}
