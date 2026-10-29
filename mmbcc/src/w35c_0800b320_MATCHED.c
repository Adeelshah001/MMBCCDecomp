/* Wave 35-C v3: 0x0800b320 — second AND via fresh variable g */
typedef unsigned char u8;
typedef unsigned int u32;
extern void Worker_0800B520(u32 *b, u32 c, u32 d);
extern void Worker_0800B4E4(void);
extern void Worker_0800B4C8(void);
__asm__(".set Worker_0800B520, 0x0800b520");
__asm__(".set Worker_0800B4E4, 0x0800b4e4");
__asm__(".set Worker_0800B4C8, 0x0800b4c8");
__attribute__((section(".text.w35c_0800b320")))
int Sub_0800B320(u32 *a, u32 *b, u32 c, u32 d)
{
    u8 *base = (u8 *)0x02004e40;
    u8 flag = base[4];
    register u8 g __asm__("r0");
    if ((flag & 15) != 0)
        return 0;
    g = 128 & flag;
    if (g == 0) {
        base[5] = 1;
        return 0;
    }
    *(u32 *)(base + 32) = (u32)a;
    Worker_0800B520(b, c, d);
    base[5] = 3;
    Worker_0800B4E4();
    Worker_0800B4C8();
    return 1;
}
