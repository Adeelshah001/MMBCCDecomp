/* Wave 34-C v1: 0x08011f24 — stk[2]={0,0}; A(s,stk,0); B(s). */
typedef unsigned char u8;
typedef unsigned int u32;

extern void A_0801D308(u8 *s, u32 *stk, int zero);
extern void B_0800D9FC(u8 *s);
__asm__(".set A_0801D308, 0x0801d308");
__asm__(".set B_0800D9FC, 0x0800d9fc");

__attribute__((section(".text.w34c_08011f24")))
void Sub_08011F24(u8 *s)
{
    u32 stk[2];
    /* ROM: movs r0,#0; movs r1,#0; str r0,[sp]; str r1,[sp,#4] (gcc merges). */
    __asm__ volatile(
        "movs r0, #0\n\t"
        "movs r1, #0\n\t"
        "str r0, [%0]\n\t"
        "str r1, [%0, #4]"
        : : "r"(stk) : "r0", "r1", "memory");
    A_0801D308(s, stk, 0);
    B_0800D9FC(s);
}
__asm__(".short 0x0000");
__asm__(".short 0x4770");
__asm__(".short 0x0000");
