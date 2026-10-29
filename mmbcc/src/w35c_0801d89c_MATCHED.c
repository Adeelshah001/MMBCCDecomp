/* Wave 35-C v1: 0x0801d89c — gated increment + table block + Tick */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_0800D9FC(u8 *s);
__asm__(".set Worker_0800D9FC, 0x0800d9fc");
__attribute__((section(".text.w35c_0801d89c")))
void Sub_0801D89C(u8 *s)
{
    u8 v = s[119] - 3;
    if (v <= 1) {
        u8 *q = *(u8 **)(s + 40);
        if (q[12] <= 1) {
            u8 *p2 = *(u8 **)(s + 44);
            p2[0]++;
        }
        {
            register u32 *tbl __asm__("r1") = (u32 *)0x082243d8;
            register u8 idx __asm__("r3") = s[9];
            register u32 off __asm__("r0") = idx << 2;
            u32 *ent;
            __asm__ volatile("" : "+r"(tbl));
            ent = (u32 *)(off + (u32)tbl);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 8);
        }
    }
    Worker_0800D9FC(s);
}
