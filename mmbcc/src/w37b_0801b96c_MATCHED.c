/* Wave 37-B MATCHED: 0x0801b96c, 32 B, old_agbcc, C + .s patch (w37b_0801b96c_patch.py: adds operand order + mov/ldr register swap). Extent to 0x0801b98c. s[10]&=~1; s[12]=4; s[20]=tbl[s[9]] word4, tbl 0x082243d8. Twin of 1cd30/1aa50/1e970 (identical ROM bytes). No externs. */
typedef unsigned char u8;
typedef unsigned int u32;
__attribute__((section(".text.w37b_0801b96c")))
void Sub_0801B96C(u8 *s)
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
