/* Wave 37-B MATCHED: 0x08007f24, 24 B, old_agbcc, pure C. Extent 0x08007f24-0x08007f3c (next fn 0x08007f3c). Entry[7]|=4, tbl 0x02004e18, idx u16*8. No patch. No externs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
__attribute__((section(".text.w37b_08007f24")))
void Sub_08007F24(u16 idx)
{
    u32 off = idx * 8;
    u8 *q = (u8 *)0x02004e18 + off;
    u8 m = 4;
    q[7] |= m;
}
