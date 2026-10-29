/* W37-C2: 0x08017a24, 32 B. Leaf (void, s) — interstitial
 * gap function between 0x08017984 (TRUE extent 160) and
 * 0x08017a44; NOT in func_list_v2.txt, NOT in TSV.
 * s[10]&=254; s[12]=4; s[20]=*(u32*)(tbl_082243d8[s[9]]+16).
 * No callees. Pool (LE): 0x082243d8.
 */
typedef unsigned char u8;
typedef unsigned int u32;

__attribute__((section(".text.w37c2_08017a24")))
void Sub_08017A24(u8 *s)
{
    u32 **tbl = (u32 **)0x082243d8;
    register u32 **addr __asm__("r1");
    s[10] &= 254;
    __asm__ volatile("" : "+r"(tbl));
    addr = (u32 **)(s[9] * 4 + (int)tbl);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)((u8 *)*addr + 16);
}
