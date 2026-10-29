typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern u32 *Node_PopAndInit_20ED4(u8 a, u8 b, u8 c, u8 d);
__attribute__((section(".text.w17d_080228BC")))
u8 *F_080228BC(void)
{
    register u8 *r __asm__("r2") = (u8 *)Node_PopAndInit_20ED4(1, 1, 0, 5);
    if (r != 0) {
        u8 b = 0;
        u8 a = 1;
        r[16] = a;
        r[17] = b;
    }
    return r;
}

