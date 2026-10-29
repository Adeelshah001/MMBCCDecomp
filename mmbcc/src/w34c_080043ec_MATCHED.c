/* Wave 34-C v1: 0x080043ec — worker(s, (s8)s[4], *(u32*)s, (s16)s[6], (s16)s[8]).
 * agbcc never emits ldrsb/ldrsh from C: inline asm with pinned regs (w31d idiom). */
typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

extern void Worker_08004398(u8 *s, s32 b4, u32 w, s32 h6, s32 h8);
__asm__(".set Worker_08004398, 0x08004398");

__attribute__((section(".text.w34c_080043ec")))
void Sub_080043EC(u8 *s)
{
    register s32 b4 __asm__("r1");
    register u32 w __asm__("r2");
    register s32 h6 __asm__("r3");
    register s32 h8 __asm__("r4");
    __asm__ volatile("movs r1, #4\n\tldrsb %0, [%1, r1]" : "=r"(b4) : "r"(s));
    w = *(u32 *)s;
    __asm__ volatile("movs r4, #6\n\tldrsh %0, [%1, r4]" : "=r"(h6) : "r"(s) : "r4");
    __asm__ volatile("movs r5, #8\n\tldrsh %0, [%1, r5]" : "=r"(h8) : "r"(s) : "r5");
    Worker_08004398(s, b4, w, h6, h8);
}
