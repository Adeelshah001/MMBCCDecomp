/* Worker B wave19 @0x0801d278 (80 B). attempt 1 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_0801D278")))
u8 *NewNode_0801D278(u8 *a, u8 *b, u8 *c)
{
    register u8 *aa __asm__("r4") = a;
    register u8 *bb __asm__("r6") = b;
    register u8 *cc __asm__("r5") = c;
    u32 w35 = a[35];
    u8 nib = (w35 << 28) >> 28;
    register u8 *p __asm__("r2") = (u8 *)Node_PopAndInit(0, 0, nib, 12);
    if (p != 0) {
        register u8 z __asm__("r1") = 0;
        u32 dw0;
        u32 dw1;
        int t;
        u16 v;
        p[16] = 4;
        p[17] = z;
        dw0 = *(u32 *)cc;
        dw1 = *(u32 *)(cc + 4);
        *(u32 *)(p + 96) = dw0;
        *(u32 *)(p + 100) = dw1;
        t = (aa[34] - 1) << 16;
        v = (u32)t >> 16;
        if (t < 0)
            v = 0;
        p[18] = v;
        *(u8 **)(p + 40) = aa;
        *(u8 **)(p + 44) = bb;
    }
    return p;
}
