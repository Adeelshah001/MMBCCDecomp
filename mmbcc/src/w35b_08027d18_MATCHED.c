/* Wave 35-B v5: 0x08027d18 idx barrier forces ldrb r2. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 Worker_0804DCD0(u8 *s, u32 v);
__asm__(".set Worker_0804DCD0, 0x0804dcd0");
extern void Worker_08027E8C(u8 *s);
__asm__(".set Worker_08027E8C, 0x08027e8c");
extern void Worker_08004F80(void);
__asm__(".set Worker_08004F80, 0x08004f80");

__attribute__((section(".text.w35b_08027d18")))
void Sub_08027D18(void)
{
    register u8 *s __asm__("r4") = (u8 *)0x0200b7e0;
    register u8 *tbl __asm__("r1") = (u8 *)0x0822dda0;
    register u32 idx __asm__("r2") = s[2];
    register u32 off __asm__("r0");
    u32 v;
    __asm__ volatile("" : "+r"(s));
    __asm__ volatile("" : "+r"(tbl));
    __asm__ volatile("" : "+r"(idx));
    off = idx << 2;
    off += (u32)tbl;
    v = *(u32 *)off;
    s[2] = Worker_0804DCD0(s, v);
    Worker_08027E8C(s);
    Worker_08004F80();
}
