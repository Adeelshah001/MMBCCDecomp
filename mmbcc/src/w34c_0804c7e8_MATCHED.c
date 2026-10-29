/* Wave 34-C v2: 0x0804c7e8 — n=7 via manual literal pool (gcc won't pool small consts).
 * Pools must be in ROM order: 7 at +36, 0x02006d7c at +40. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_0804CECC(u32 x);
__asm__(".set Worker_0804CECC, 0x0804cecc");

__attribute__((section(".text.w34c_0804c7e8")))
void Sub_0804C7E8(void)
{
    u32 t;
    u16 n;
    u8 *p;
    u32 nn;
    __asm__ volatile("ldr %0, .Lpool7_0804c7e8" : "=r"(t));
    n = (u16)t;
    if (n == 0)
        return;
    __asm__ volatile("ldr %0, .Lpool6d7c_0804c7e8" : "=r"(p));
    nn = n;
    do {
        Worker_0804CECC(*(u32 *)p);
        p += 12;
        nn--;
    } while (nn != 0);
}
__asm__(".Lpool7_0804c7e8: .word 7");
__asm__(".Lpool6d7c_0804c7e8: .word 0x08106d7c");
