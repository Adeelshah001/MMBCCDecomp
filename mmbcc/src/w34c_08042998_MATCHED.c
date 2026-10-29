/* Wave 34-C v1: 0x08042998 — A(s);B(s);C(s);D();E(s). D takes no args (r0=C's ret). */
typedef unsigned char u8;

extern void A_0804039C(u8 *s);
extern void B_080404D0(u8 *s);
extern void C_08040698(u8 *s);
extern void D_080406E4(void);
extern void E_0804152C(u8 *s);
__asm__(".set A_0804039C, 0x0804039c");
__asm__(".set B_080404D0, 0x080404d0");
__asm__(".set C_08040698, 0x08040698");
__asm__(".set D_080406E4, 0x080406e4");
__asm__(".set E_0804152C, 0x0804152c");

__attribute__((section(".text.w34c_08042998")))
void Sub_08042998(u8 *s)
{
    A_0804039C(s);
    B_080404D0(s);
    C_08040698(s);
    D_080406E4();
    E_0804152C(s);
}
