/* Wave 37-B MATCHED: 0x08011530, 48 B, old_agbcc, C + .s patch (w37b_08011530_patch.py: swap mov order + ldr r0 pool direct). Extent to 0x08011560. Clears fields, f12=0xfffe, f36/f34=0, f4++, f5-7=0, return -1. No externs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
__attribute__((section(".text.w37b_08011530")))
int Sub_08011530(u8 *s)
{
    u8 zb = 0;
    u32 zw = 0;
    *(u16 *)(s + 16) = zw;
    *(u16 *)(s + 14) = zw;
    *(u32 *)(s + 8) = zw;
    *(u16 *)(s + 12) = (u16)0xfffe;
    s[36] = zb;
    s[34] = zb;
    s[4]++;
    s[5] = zb;
    s[6] = zb;
    s[7] = zb;
    return -1;
}
