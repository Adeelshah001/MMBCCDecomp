typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
void F_08002FD4(u16 x);
void TblFindClear_02C74(u8 a);
__attribute__((section(".text.w16c_0804b110")))
u32 TwoTblOps_0804B110(void)
{
    F_08002FD4(15);
    TblFindClear_02C74(29);
    return 1;
}