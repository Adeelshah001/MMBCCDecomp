/* Wave 34-C v1: 0x08016fd0 — Worker(r4,0,r5,140,(s16)c); *0x020053c0=r4; *0x02000838=r5. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void Worker_08004398(u32 a, int b, u32 c, int d, s16 e);
__asm__(".set Worker_08004398, 0x08004398");

__attribute__((section(".text.w34c_08016fd0")))
void Sub_08016FD0(u32 a, u32 b, int c)
{
    u32 aa = a;
    u32 bb = b;
    s16 cc = c;
    Worker_08004398(aa, 1, bb, 136, cc);
    *(u32 *)0x020053c0 = aa;
    *(u32 *)0x02000838 = bb;
}
