typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w17d_0801F12C")))
u8 *F_0801F12C(u8 *p)
{
    register u8 *pp __asm__("r4") = p;
    register u8 *n __asm__("r2") = (u8 *)Node_PopAndInit(0, 1, 0, 17);
    if (n != 0) {
        u8 b = 0;
        u8 a = 2;
        n[16] = a;
        n[17] = b;
        *(u8 **)(n + 40) = pp;
    }
    return n;
}

