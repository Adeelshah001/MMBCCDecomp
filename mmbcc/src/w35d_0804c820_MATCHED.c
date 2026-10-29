/* Wave 35-D v1: 0x0804C820 — sibling of W34-C 0x0804C7E8 (same pools 7, 0x08106d7c).
 * True extent 0x0804C820-0x0804C84C (44 B: 36 code + 2 pad + 2 pools).
 * Callee 0x0804C5F4 (ClearSignBit, MATCHED) via .set for standalone verify;
 * coordinator strips .set at landing (resolves from build).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void ClearSignBit_0804C5F4(u32 x);

__attribute__((section(".text.w35d_0804c820")))
void Sub_0804C820(void)
{
    u32 t;
    u16 n;
    u8 *p;
    u32 nn;
    __asm__ volatile("ldr %0, .Lpool7_0804c820" : "=r"(t));
    n = (u16)t;
    if (n == 0)
        return;
    __asm__ volatile("ldr %0, .Lpool6d7c_0804c820" : "=r"(p));
    nn = n;
    do {
        ClearSignBit_0804C5F4(*(u32 *)p);
        p += 12;
        nn--;
    } while (nn != 0);
}
__asm__(".Lpool7_0804c820: .word 7");
__asm__(".Lpool6d7c_0804c820: .word 0x08106d7c");
