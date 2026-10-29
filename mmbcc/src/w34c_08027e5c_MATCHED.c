/* Wave 34-C v2: 0x08027e5c — volatile for read-modify-write ORs. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_08027F80(void);
__asm__(".set Worker_08027F80, 0x08027f80");

__attribute__((section(".text.w34c_08027e5c")))
void Sub_08027E5C(u8 *s)
{
    register u8 mask __asm__("r3");
    u32 t;
    u32 u;
    __asm__ volatile("movs %0, #255" : "=r"(mask));
    s[5] |= mask;
    t = 0;
    s[6] = (u8)t;
    s[4] = (u8)t;
    t -= 7;
    t &= s[3];
    u = 15;
    t &= u;
    u -= 24;
    t &= u;
    s[3] = (u8)t;
    mask |= s[7];
    s[7] = mask;
    Worker_08027F80();
}
