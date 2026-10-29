/* Wave 36-A MATCHED: 0x0801054c, 88 B, main agbcc, 7 variants.
   Extent basis: code 0x0801054c-0x08010594 (bx), pad 0x08010596-0x08010597, pools
   0x08010598 (0x02003670) / 0x0801059c (0x000011ae) / 0x080105a0 (0x02005168) -> 0x080105a4.
   Two-pool base sum via base1 pinned r0 + off pinned r1 with barrier; mask pinned r1,
   mode pinned r2; s+58 address via stmt-expr asm (copy + add + ldrb) pinned to r0 so
   gcc does not fold it to an in-place add. No trailing pad: extent ends with pools. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_08008030(u32 a, u32 b, u32 c, u32 d, u32 e);
__asm__(".set Sub_08008030, 0x08008030");
extern void Sub_080105A4(u32 a, u32 b);
__asm__(".set Sub_080105A4, 0x080105a4");
__attribute__((section(".text.w36a_0801054c")))
void Sub_0801054C(u8 *s_in)
{
    register u8 *s __asm__("r3");
    register u32 base1 __asm__("r0");
    register u32 off __asm__("r1");
    register u32 mask __asm__("r1");
    register u32 mode __asm__("r2");
    u8 *base;
    u8 *r4;
    u32 stackarg;
    s = s_in;
    base1 = 0x02003670;
    off = 0x000011ae;
    __asm__ volatile("" : "+r"(off));
    base = (u8 *)(base1 + off);
    mask = 4;
    mask &= *base;
    mode = 14;
    if (mask != 0)
        mode = 15;
    stackarg = ({ register u32 _a __asm__("r0"); __asm__("add %0, %1, #0\n\tadd %0, %0, #58\n\tldrb %0, [%0]" : "=r"(_a) : "r"(s)); _a; });
    Sub_08008030(0, mode, 0, 0, stackarg);
    r4 = (u8 *)0x02005168;
    Sub_080105A4((u32)r4, 0);
    r4 += 20;
    Sub_080105A4((u32)r4, 1);
}
