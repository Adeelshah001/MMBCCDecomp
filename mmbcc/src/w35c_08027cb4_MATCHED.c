/* Wave 35-C v3: 0x08027cb4 — z declared first, assigned after loop */
typedef unsigned char u8;
typedef unsigned short u16;
extern void Worker_08004E44(void);
extern void Worker_08004DFC(int v);
extern void Worker_08021498(void);
extern void Worker_080214F4(void);
extern void Worker_08027E5C(u8 *p);
__asm__(".set Worker_08004E44, 0x08004e44");
__asm__(".set Worker_08004DFC, 0x08004dfc");
__asm__(".set Worker_08021498, 0x08021498");
__asm__(".set Worker_080214F4, 0x080214f4");
__asm__(".set Worker_08027E5C, 0x08027e5c");
__attribute__((section(".text.w35c_08027cb4")))
void Sub_08027CB4(void)
{
    u8 z;
    u8 *base = (u8 *)0x0200b7e0;
    u8 *q = base;
    u16 i;
    for (i = 0; i <= 39; i++)
        *q++ = 0;
    z = 0;
    base[2] = z;
    Worker_08004E44();
    Worker_08004DFC(2);
    *(u16 *)0x02004830 = z;
    Worker_08021498();
    Worker_080214F4();
    Worker_08027E5C(base);
}
