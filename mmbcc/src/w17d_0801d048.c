typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern u32 *Node_PopAndInit(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w17d_0801D048")))
u8 *F_0801D048(u8 x)
{
    register u8 xx __asm__("r4") = x;
    register u8 *n __asm__("r1") = (u8 *)Node_PopAndInit(0, 1, 0, 12);
    if (n != 0) {
        u8 z = 0;
        n[16] = xx;
        n[17] = z;
        *(u32 *)(n + 40) = z;
    }
    return n;
}

