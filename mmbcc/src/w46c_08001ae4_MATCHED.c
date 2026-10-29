/* W45-D v1: 0x08001ae4, 292 B (bx 0x08001bec, next fn 0x08001bf8).
 * Global-state machine, no struct argument (entry never uses r0).
 * Pools (raw LE ROM): G = 0x02002ee0 at 0x08001b28; dest
 * *(u16*)0x0400012a at 0x08001b2c/1b48/1b7c/1b9c/1bb4/1bdc/1bf0;
 * default value 0x0fff at 0x08001bf4. Callee TblHash_Combine
 * 0x08001754 is registry-BLOCKED (keep .set, coordinator adjudicates). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u16 TblHash_Combine(u8 v, int n);
__asm__(".set TblHash_Combine, 0x08001754");

__attribute__((section(".text.w46c_08001ae4")))
void Sub_08001AE4(void)
{
    u8 *p = (u8 *)0x02002ee0;
    volatile u8 *g;
    register int cnt __asm__("r3");
    u16 c16;
    cnt = *(u16 *)(p + 6);
    cnt++;
    *(u16 *)(p + 6) = cnt;
    c16 = (u16)cnt;
    g = p;
    if (c16 == 1)
        goto def;
    if ((*(u16 *)(g + 2) & 2) == 0)
        goto test4;
    cnt &= 1;
    if (cnt == 0)
        goto test65;
    if (g[62] == 0)
        goto test65;
    *(u16 *)0x0400012a = TblHash_Combine(g[62], 3);
    (void)g[62];
    g[62] = 0;
    return;
test65:
    if (g[65] == 0)
        goto def;
    *(u16 *)0x0400012a = *(u16 *)(g + 66);
    return;
test4:
    if ((*(volatile u16 *)(g + 2) & 4) == 0)
        goto def;
    if (g[4] > 1)
        goto def;
    if (g[4] != 0)
        goto b4eq1;
    cnt &= 1;
    if (cnt != 0)
        goto b4eq1;
    if ((g[9] & 32) == 0)
        goto b4eq1;
    *(u16 *)0x0400012a = *(u16 *)(g + 48);
    return;
b4eq1:
    if (g[4] != 1)
        goto test10;
    if ((3 & *(u16 *)(g + 6)) != 0)
        goto test10;
    if (g[11] != 31)
        goto test10;
    *(u16 *)0x0400012a = *(u16 *)(g + 48);
    return;
test10:
    if (g[10] == 0)
        goto def;
    if (g[10] == 1) {
        *(u16 *)0x0400012a = *(u16 *)(g + 44);
        goto tailinc;
    }
    if (g[10] == 2) {
        *(u16 *)0x0400012a = *(u16 *)(g + 46);
        goto tailinc;
    }
tailinc:
    {
        int t = g[10] + 1;
        (void)g[10];
        g[10] = t;
    }
    if (g[10] <= 2)
        return;
    (void)g[10];
    g[10] = 1;
    return;
def:
    *(u16 *)0x0400012a = 0x0fff;
    return;
}
