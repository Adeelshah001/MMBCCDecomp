/* Wave 35-C v4: 0x08004dbc — fp load (barrier) before w=12 */
typedef unsigned char u8;
typedef unsigned short u16;
extern void Worker_0800244C(u8 *p, int v);
extern void Worker_080028D0(u8 *p, int a, int b);
__asm__(".set Worker_0800244C, 0x0800244c");
__asm__(".set Worker_080028D0, 0x080028d0");
__attribute__((section(".text.w35c_08004dbc")))
void Sub_08004DBC(u8 a)
{
    u8 *entry = (u8 *)0x082c0000 + a * 20;
    register u16 *fp __asm__("r2") = (u16 *)0x020031e6;
    int w;
    __asm__ volatile("" : "+r"(fp));
    w = 12;
    w &= *fp;
    Worker_0800244C(entry, (w << 12) + 32);
    Worker_080028D0((u8 *)0x082c000c + a * 20, 0, 0);
}
