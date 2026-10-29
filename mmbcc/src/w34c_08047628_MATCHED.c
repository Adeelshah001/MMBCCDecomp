/* Wave 34-C v1: 0x08047628 — A(s); B(0x40,0x80); s->b0++; C(s); return 0. */
typedef unsigned char u8;

extern void A_08004E44(u8 *s);
extern void B_0800BEE0(int x, int y);
extern void C_0804764C(u8 *s);
__asm__(".set A_08004E44, 0x08004e44");
__asm__(".set B_0800BEE0, 0x0800bee0");
__asm__(".set C_0804764C, 0x0804764c");

__attribute__((section(".text.w34c_08047628")))
int Sub_08047628(u8 *s)
{
    A_08004E44(s);
    B_0800BEE0(0x40, 0x80);
    s[0]++;
    C_0804764C(s);
    return 0;
}
