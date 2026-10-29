/* Wave 35-B v6: 0x080267c0 goto layout chain, Ld4, Lda, Lde, Le6, Lee. */
typedef unsigned char u8;

extern void Worker_08026880(u8 *s);
__asm__(".set Worker_08026880, 0x08026880");
extern void Worker_080267B4(u8 *p, int x);
__asm__(".set Worker_080267B4, 0x080267b4");

__attribute__((section(".text.w35b_080267c0")))
void Sub_080267C0(u8 *s)
{
    int v = s[1];
    if (v == 1) goto Lde;
    if (v > 1) goto Ld4;
    if (v == 0) goto Lda;
    __asm__ volatile("" ::: "memory");
    goto Lee;
Ld4:
    if (v == 2) goto Le6;
    __asm__ volatile("" ::: "memory");
    goto Lee;
Lda:
    s[1] = 1;
Lde:
    Worker_08026880(s);
    goto Lee;
Le6:
    Worker_080267B4((u8 *)0x020070f0, 3);
Lee:
    return;
}
