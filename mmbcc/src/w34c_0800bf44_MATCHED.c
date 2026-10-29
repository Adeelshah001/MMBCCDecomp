/* Wave 34-C v1: 0x0800bf44 — A(p); p->h20=(u16)a; B((s16)a). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;

extern void A_0800C4B4(u8 *p);
extern void B_0800C41C(s16 x);
__asm__(".set A_0800C4B4, 0x0800c4b4");
__asm__(".set B_0800C41C, 0x0800c41c");

__attribute__((section(".text.w34c_0800bf44")))
void Sub_0800BF44(u32 a)
{
    u16 aa = a;
    u8 *p = (u8 *)0x02004f40;
    A_0800C4B4(p);
    *(u16 *)(p + 20) = aa;
    B_0800C41C((s16)aa);
}
