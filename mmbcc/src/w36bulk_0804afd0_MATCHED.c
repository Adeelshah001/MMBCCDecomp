/* Wave 36-B MATCHED: 0x0804afd0, 128 B, old_agbcc, 0 diffs. Variants: 2. Idioms: temp-split for movs-between-stores order, base assigned after stores. */
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned short u16;
extern void Sub_08004E44(void);
extern void Sub_08004DFC(int mode);
extern void Sub_08016FD0(u8 *a, u8 *b, int c);
extern void Sub_0800DEA4(u8 *a, u32 b, int c, int d, u32 e, u32 f, int g);
extern void Sub_08002AFC(int a, int b);
extern void Sub_0801EE68(u8 *o);
__attribute__((section(".text.w36bulk_0804afd0")))
int Sub_0804AFD0(u8 *o)
{
    u32 *base;
    u8 t;
    u8 z;
    t = o[0] + 1;
    z = 0;
    o[0] = t;
    o[4] = z;
    base = (u32 *)0x020038ac;
    Sub_08004E44();
    Sub_08004DFC(2);
    Sub_08016FD0((u8 *)0x02004fc8, (u8 *)0x020053d0, 36);
    Sub_0800DEA4((u8 *)0x0871e534, base[1], 2, 1, *(u32 *)0x0871c8b4 + 0x0871c8b4, base[0], 32);
    {
        u16 *p;
        p = (u16 *)0x020031f4;
        p[0] = 0xFFF8;
        p[1] = 0xFFF8;
    }
    Sub_08002AFC(29, 32);
    Sub_0801EE68(o);
    return 0;
}

__asm__(".set Sub_08002AFC, 0x08002afc");
__asm__(".set Sub_08004DFC, 0x08004dfc");
__asm__(".set Sub_08004E44, 0x08004e44");
__asm__(".set Sub_0800DEA4, 0x0800dea4");
__asm__(".set Sub_08016FD0, 0x08016fd0");
__asm__(".set Sub_0801EE68, 0x0801ee68");
