typedef unsigned char u8;
typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w19b_0801D308")))
u8 *NewNode_0801D308(u8 *a, u8 *b, u32 c)
{
    register u8 *aa __asm__("r6") = a;
    register u8 *bb __asm__("r5") = b;
    u8 cc = (u8)c;
    register u8 *p __asm__("r2");
    p = (u8 *)Node_PopAndInit(0, 1, 0, 12);
    if (p != 0) {
        u32 dw0;
        u32 dw1;
        p[16] = 7;
        p[17] = cc;
        dw0 = *(u32 *)(aa + 80);
        dw1 = *(u32 *)(aa + 84);
        *(u32 *)(p + 88) = dw0;
        *(u32 *)(p + 92) = dw1;
        __asm__ volatile("" : : : "memory");
        *(u32 *)(p + 88) += *(u32 *)bb;
        *(u32 *)(p + 92) += *(u32 *)(bb + 4);
    }
    return p;
}

