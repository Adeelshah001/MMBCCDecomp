/* Wave 34-C v2: 0x08002f58 — 0xffff ldr inside loop. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void Worker_0804D65C(u32 x, u32 y, int z);
__asm__(".set Worker_0804D65C, 0x0804d65c");

__attribute__((section(".text.w34c_08002f58")))
void Sub_08002F58(void)
{
    u32 t;
    u16 n;
    u8 *p;
    u32 nn;
    __asm__ volatile("ldr %0, .Lpool7_08002f58" : "=r"(t));
    n = (u16)t;
    if (n == 0)
        return;
    __asm__ volatile("ldr %0, .Lpool6d7c_08002f58" : "=r"(p));
    nn = n;
    do {
        u32 v = *(u32 *)p;
        u32 c;
        __asm__ volatile("ldr %0, .Lpoolffff_08002f58" : "=r"(c));
        Worker_0804D65C(v, c, 96);
        p += 12;
        nn--;
    } while (nn != 0);
}
__asm__(
    ".align 2\n"
    ".Lpool7_08002f58: .word 7\n"
    ".Lpool6d7c_08002f58: .word 0x08106d7c\n"
    ".Lpoolffff_08002f58: .word 0x0000ffff\n"
);
