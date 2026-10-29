/* Wave 35-B v7: 0x08022e88 pin+barrier, off+=tbl in-place adds. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;

extern s8 Worker_08026D94(u8 *s);
__asm__(".set Worker_08026D94, 0x08026d94");
extern void Worker_0800D9FC(u8 *s);
__asm__(".set Worker_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w35b_08022e88")))
void Sub_08022E88(u8 *s)
{
    u8 *ss = s;
    s8 r = Worker_08026D94(ss);
    if (r != 3)
    {
        register u8 *tbl __asm__("r1") = (u8 *)0x08226ef0;
        register u32 idx __asm__("r2") = ss[9];
        register u32 off __asm__("r0") = idx << 2;
        u32 v;
        __asm__ volatile("" : "+r"(tbl));
        off += (u32)tbl;
        *(u32 *)(ss + 12) = 2;
        v = *(u32 *)off;
        v = *(u32 *)(v + 8);
        *(u32 *)(ss + 20) = v;
    }
    else
    {
        Worker_0800D9FC(ss);
    }
}
