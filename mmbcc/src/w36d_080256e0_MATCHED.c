/* Wave 36-D v3: 0x080256e0 — integer offset (r1) then += base. */
typedef unsigned char u8;
typedef short s16;
typedef unsigned int u32;
extern void Worker_080255F4(u8 *s);
__asm__(".set Worker_080255F4, 0x080255f4");
__attribute__((section(".text.w36d_080256e0")))
void Sub_080256E0(u8 *s)
{
    s16 i;
    register u8 mask __asm__("r3");
    register u8 zero __asm__("r5");
    Worker_080255F4(s);
    i = 0;
    zero = 0;
    __asm__ volatile("movs %0, #255" : "=r"(mask));
    for (; i <= 29; i++) {
        register u32 poff __asm__("r1");
        register u8 b __asm__("r2");
        poff = i * 4;
        poff += (u32)s;
        ((u8 *)poff)[20] = zero;
        b = ((u8 *)poff)[21];
        b |= mask;
        ((u8 *)poff)[21] = b;
    }
    s[141] = 0;
    s[140] = 0;
}
