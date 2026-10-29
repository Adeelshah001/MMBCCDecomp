/* W61-D v2: 0x0800cf10. Fixes vs v1: dst variables for Copy calls (ROM
 * stages dst in r2), X pointer variable (pool 0x02004F80 + [r,#2]), int-temp
 * toggle form ((t^1)&1)|(t&-2), bit variable reused for VRAM + dst select,
 * vp-7 tileoff (subs #14 derivation). */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Copy_0800244C(u8 *dst, int v);
__asm__(".set Copy_0800244C, 0x0800244c");
extern void Fill_080028D0(u8 *dst, int a, int b);
__asm__(".set Fill_080028D0, 0x080028d0");

__attribute__((section(".text.w65b_0800cf10")))
void Sub_0800CF10(u8 *s, u8 a, u8 b)
{
    int off = 2;
    if (b == 0) {
        register u8 *d __asm__("r2");
        off = 6;
        d = (u8 *)0x0830B624;
        __asm__("" : "+r"(d));
        Copy_0800244C(d, (((*(u16 *)0x020031EA) & 12) << 12) + 64);
    }
    {
        u8 t = *((u8 *)0x08173500 + a);
        register u8 *d __asm__("r2") = (u8 *)(0x0830B340 + t * 20);
        __asm__("" : "+r"(d));
        Copy_0800244C(d, (((*(u16 *)0x020031EA) & 12) << 12) + (off << 5));
        Fill_080028D0((u8 *)(0x0830B34C + t * 20), 0, 0);
    }
    if (b == 1) {
        u8 *q = (u8 *)0x02004F80;
        if (q[2] == 1)
            *(u16 *)0x03002420 = 0;
        else if (q[2] == 2)
            *(u16 *)0x03002420 = 0x7FFF;
    }
    {
        register int t __asm__("r2") = s[9];
        int bit;
        u16 *vp;
        u16 *dst;
        u32 tileoff;
        s16 row, col;
        u16 *src;
        s16 lo, hi;
        lo = (t ^ 1) & 1;
        hi = t & -2;
        s[9] = hi | lo;
        vp = (u16 *)0x020031F8;
        bit = s[9] & 1;
        *vp = ((bit | -bit) >> 31) & 0x100;
        tileoff = ((*(vp - 7)) & 0x1F00) << 3;
        dst = (u16 *)(0x06000000 + tileoff);
        if (bit)
            dst = (u16 *)(0x06000800 + tileoff);
        { register u8 *tbl __asm__("r1") = (u8 *)0x0817350C;
          __asm__("" : "+r"(tbl));
          src = *(u16 **)(tbl + a * 4); }
        row = 0;
        do {
            u16 *dd = dst + row * 32;
            col = 0;
            do {
                *dd++ = *src++ + off;
                col++;
            } while (col <= 29);
            row++;
        } while (row <= 19);
    }
}
