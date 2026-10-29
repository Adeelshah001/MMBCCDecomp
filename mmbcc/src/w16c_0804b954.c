typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
void F_08002FD4(u16 x);
__attribute__((section(".text.w16c_0804b954")))
u32 Flag17Init_0804B954(u8 *p)
{
    if (p[1] == 0) {
        p[1] = 1;
        F_08002FD4(17);
    }
    return 1;
}