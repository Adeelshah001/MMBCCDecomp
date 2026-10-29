/* Wave 15-C: MaskWrite23_0804D7C0 @ 0x0804d7c0 (old_agbcc). Coordinator-landed, 0-diff verified. */
typedef unsigned char u8; typedef unsigned short u16; typedef unsigned int u32;
extern void sub_0804D7A0(u8 *s);
void __attribute__((section(".text.w15c2_0804d7c0"))) MaskWrite23_0804D7C0(u8 *s, u16 a, u8 b)
{
    register u8 *rs __asm__("r6");
    register u32 ra __asm__("sl");
    register u32 rb __asm__("r8");
    register u32 rv __asm__("r9");
    int n;
    u8 *p;
    u32 mask;
    u32 v;
    __asm__ volatile(
        "add r6, r0, #0\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr r1, r1, #16\n\t"
        "mov sl, r1\n\t"
        "lsl r2, r2, #24\n\t"
        "lsr r2, r2, #24\n\t"
        "mov r8, r2"
        : "=r" (rs), "=r" (ra), "=r" (rb) : : "r0", "r1", "r2");
    v = *(u32 *)(rs + 52);
    if (v == 0x68736D53) {
        *(u32 *)(rs + 52) = v + 1;
        n = rs[8];
        p = *(u8 **)(rs + 44);
        mask = 1;
        if (n > 0) {
            rv = rb;
            do {
                register u32 am __asm__("r0") = ra;
                am &= mask;
                if (am != 0 && (0x80 & p[0]) != 0) {
                    p[23] = rb;
                    if (rv == 0)
                        sub_0804D7A0(p);
                }
                n--;
                p += 0x50;
                mask <<= 1;
            } while (n > 0);
        }
        *(u32 *)(rs + 52) = 0x68736D53;
    }
}

__asm__(
    ".thumb\n"
    ".thumb_func\n"
    ".globl sub_0804D7A0\n"
    ".set sub_0804D7A0, 0x0804D7A0\n"
);
