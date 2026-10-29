/* Wave 34-C v2: 0x08024c14 — (u16)worker(base+v*144, a, b). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u16 Worker_08025B60(u8 *p, u8 a, u8 b);
__asm__(".set Worker_08025B60, 0x08025b60");

__attribute__((section(".text.w34c_08024c14")))
u16 Sub_08024C14(u8 *s, u8 a, u8 b)
{
    u32 base = *(u32 *)(s + 20);
    register u32 off __asm__("r3") = 216 << 1;
    register u8 *p __asm__("r4");
    register u8 v __asm__("r5");
    u32 idx;
    __asm__ volatile("" : "+r"(off));
    p = (u8 *)(base + off);
    v = *p;
    idx = v * 144;
    return Worker_08025B60((u8 *)(base + idx), a, b);
}
__asm__(".short 0x0000");
