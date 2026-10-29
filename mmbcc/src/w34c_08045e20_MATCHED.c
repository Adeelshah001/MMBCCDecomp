/* Wave 34-C v1: 0x08045e20 — sequential 4-call chain on s. */
typedef unsigned char u8;

extern void A_0804380C(u8 *s);
extern void B_08043918(u8 *s);
extern void C_08044298(u8 *s);
extern void D_08045C54(u8 *s);
__asm__(".set A_0804380C, 0x0804380c");
__asm__(".set B_08043918, 0x08043918");
__asm__(".set C_08044298, 0x08044298");
__asm__(".set D_08045C54, 0x08045c54");

__attribute__((section(".text.w34c_08045e20")))
void Sub_08045E20(u8 *s)
{
    A_0804380C(s);
    B_08043918(s);
    C_08044298(s);
    D_08045C54(s);
}
