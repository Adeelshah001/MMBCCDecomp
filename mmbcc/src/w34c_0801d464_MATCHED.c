/* Wave 34-C v1: 0x0801d464 — if (s[17]) B(s) else A(s); C(s). */
typedef unsigned char u8;

extern void A_0801D488(u8 *s);
extern void B_0801D598(u8 *s);
extern void C_0800D9FC(u8 *s);
__asm__(".set A_0801D488, 0x0801d488");
__asm__(".set B_0801D598, 0x0801d598");
__asm__(".set C_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w34c_0801d464")))
void Sub_0801D464(u8 *s)
{
    if (s[17] == 0)
        A_0801D488(s);
    else
        B_0801D598(s);
    C_0800D9FC(s);
}
