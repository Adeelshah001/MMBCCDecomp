/* Wave 35-C v1: 0x0800c748 — table lookup + worker call */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int Worker_0800C248(u8 x);
extern void Worker_0800DEF8(int a, u16 b, int c, int d, int e);
__asm__(".set Worker_0800C248, 0x0800c248");
__asm__(".set Worker_0800DEF8, 0x0800def8");
__attribute__((section(".text.w35c_0800c748")))
void Sub_0800C748(u8 *s, int a, u16 b)
{
    int t = Worker_0800C248(s[20]);
    int idx = (t << 24) >> 22;
    u32 *tbl = (u32 *)0x08328678;
    u32 v = *(u32 *)((u8 *)tbl + idx);
    u32 w = v + (u32)tbl;
    int res = idx + (int)w;
    Worker_0800DEF8(res, b, 1, a, 32);
}
