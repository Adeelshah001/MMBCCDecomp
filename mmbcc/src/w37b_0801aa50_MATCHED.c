/* Wave 37-B MATCHED: 0x0801aa50, 32 B, old_agbcc, C + .s patch (w37b_0801aa50_patch.py, same as 1b96c patch). Extent to 0x0801aa70. Twin of 1b96c. No externs. */
typedef unsigned char u8;
typedef unsigned int u32;
__attribute__((section(".text.w37b_0801aa50")))
void Sub_0801AA50(u8 *s)
{
    u32 *base;
    u32 *p;
    s[10] &= 254;
    base = (u32 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    p = base + s[9];
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*p + 16);
}
