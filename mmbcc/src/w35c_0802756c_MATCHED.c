/* Wave 35-C v1: 0x0802756c — two Workers + 7-arg call */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_0800244C(u8 *p, int v);
extern void Worker_0800288C(u8 *p, int v);
extern void Worker_080062B4(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g);
__asm__(".set Worker_0800244C, 0x0800244c");
__asm__(".set Worker_0800288C, 0x0800288c");
__asm__(".set Worker_080062B4, 0x080062b4");
__attribute__((section(".text.w35c_0802756c")))
void Sub_0802756C(void)
{
    u8 *tbl = (u8 *)0x0830b638;
    Worker_0800244C(tbl, 0x4dc0);
    tbl += 12;
    Worker_0800288C(tbl, (176 << 1));
    Worker_080062B4(0, 0, 30, 20, 110, 11, 0x080f2228);
}
