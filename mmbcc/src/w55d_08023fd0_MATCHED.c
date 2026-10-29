/* W55-D: 0x08023fd0, 252 B. Adapted from MATCHED 240cc (W52-B) idiom:
 * u16* a + u8 idx params; u32* base + index; block-scoped dst/ci;
 * goto entry-check + while loop (dst loaded after check);
 * F26184 recomputes base[14]; F23E34 takes base variable.
 * Trailing calls are literals (args do not iterate, unlike 240cc).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void Sub_0802541C(u32 a, u32 b, u32 c);
__asm__(".set Sub_0802541C, 0x0802541c");
extern u8 Sub_08024500(u8 a);
__asm__(".set Sub_08024500, 0x08024500");
extern void Sub_080260D4(u32 a, u8 b, u8 c);
__asm__(".set Sub_080260D4, 0x080260d4");
extern void Sub_08026184(u32 a, u32 b);
__asm__(".set Sub_08026184, 0x08026184");
extern void Sub_08023E34(u32 a);
__asm__(".set Sub_08023E34, 0x08023e34");
extern void Sub_08024B3C(int a, u8 b, int c, u8 d);
extern void Sub_08024E2C(int a, u8 b, int c, int d);

__attribute__((section(".text.w55d_08023fd0")))
void Sub_08023FD0(u16 *a, u8 idx)
{
    u32 *base = (u32 *)0x02007090;
    u32 p;
    u8 t;
    Sub_0802541C((u32)base, 0x082273C1, 7);
    p = base[5];
    t = Sub_08024500(idx);
    Sub_080260D4(p, t, *(u8 *)(0x082273FE + idx));
    {
        u16 *dst;
        s16 ci;
        ci = 0;
        if ((a[0] & 32768) != 0)
            goto cdone;
        dst = (u16 *)(base[14]);
        while (ci <= 3 && !(a[ci] & 32768)) {
            dst[ci] = a[ci];
            ci++;
        }
    cdone:;
    }
    Sub_08026184(0x020070A8, base[14]);
    Sub_08023E34((u32)base);
    Sub_08024B3C(0, 0, 0, 0);
    Sub_08024B3C(0, 1, 0, 1);
    Sub_08024B3C(0, 0, 0, 0);
    Sub_08024B3C(0, 0, 0, 0);
    Sub_08024B3C(0, 0, 0, 0);
    Sub_08024B3C(0, 0, 0, 0);
    Sub_08024B3C(0, 0, 0, 0);
    Sub_08024E2C(1, 0, 1, 0);
    Sub_08024E2C(1, 1, 1, 1);
}
