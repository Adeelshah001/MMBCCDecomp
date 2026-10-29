/* Wave 13 worker D: 4 leaves-up matches, all old_agbcc.
 * Coordinator-verified byte-identical (clean-room rebuild + ROM diff).
 * Evidence: docs/match_notes_wave13_D.md, docs/wave13_D_results.tsv. */

__attribute__((section(".text.w13d_08046ca0")))
void ChipSlot_InitEntry(unsigned char *p, unsigned short *q, unsigned char a, unsigned char b)
{
    unsigned char r;
    short i;

    p[4] = 0;
    if (b == 0) {
        p[5] = b;
        r = 20;
    } else {
        p[5] = 0;
        r = 25;
    }
    p[3] = r;
    p[2] = r;
    p[8] = b;
    {
        unsigned short v;
        __asm__ volatile("" : "=r" (v) : "0" (0x800A));
        *(unsigned short *)(p + 6) = v;
    }
    for (i = 0; i < a + 1; i++)
        q[i] = 0;
    q[0] = 0x8000;
}

__attribute__((section(".text.w13d_08002d20")))
void DispCntRestore_Dma3(void)
{
    volatile unsigned short v;
    unsigned short *ew;
    volatile unsigned int *dma;

    v = *(volatile unsigned short *)0x04000000;
    v &= 0xF0E8;
    ew = (unsigned short *)0x020031E0;
    *ew &= 0x0F17;
    v |= *ew;
    *(volatile unsigned short *)0x04000000 = v;

    dma = (volatile unsigned int *)0x040000D4;
    dma[0] = (unsigned int)ew + 4;
    dma[1] = 0x04000008;
    dma[2] = 0x8400000E;
    (void)dma[2];
}

__attribute__((section(".text.w13d_08002678")))
void PalDmaInit_02678(void)
{
    register unsigned int zero __asm__("r4") = 0;
    unsigned int w = zero;
    volatile unsigned int *dma = (volatile unsigned int *)0x040000D4;
    register unsigned char *q __asm__("r2");
    register unsigned int i __asm__("r3");

    dma[0] = (unsigned int)&w;
    q = (unsigned char *)0x03002420;
    dma[1] = (unsigned int)q;
    dma[2] = 0x85000100;
    (void)dma[2];
    dma[0] = (unsigned int)q;
    dma[1] = 0xA0 << 19;
    dma[2] = 0x84000100;
    (void)dma[2];

    i = 0x402;
    __asm__ volatile(
        "add r0, %1, %0\n\t"
        "mov r1, #32\n\t"
        "strb r1, [r0, #0]\n\t"
        "sub %0, #1\n\t"
        "add r0, %1, %0\n\t"
        "strb r1, [r0, #0]\n\t"
        "sub %0, #1\n\t"
        "add r0, %1, %0\n\t"
        "strb r1, [r0, #0]"
        : "+r" (i)
        : "r" (q)
        : "r0", "r1", "cc", "memory");
    *(unsigned short *)((unsigned int)q + 0x404) = zero;
    *(unsigned short *)((unsigned int)q + 0x406) = (unsigned short)i;
}

__attribute__((section(".text.w13d_080048b4")))
void DrawText_048B4(unsigned char *p, unsigned int x, unsigned int y)
{
    unsigned char *q = p;
    unsigned int w = x;
    unsigned short *dst;
    register unsigned int b1 __asm__("r5");
    register unsigned int b2 __asm__("r2");
    unsigned char c;

    dst = *(unsigned short **)0x02003250;
    if (y > 31) return;
    dst += w + y * 32;

    c = *q;
    if (c == 0) return;

    __asm__ volatile(
        "mov r2, #232\n\t"
        "lsl r2, r2, #2\n\t"
        "add %0, r2, #0\n\t"
        "mov r6, #184\n\t"
        "lsl r6, r6, #2\n\t"
        "add %1, r6, #0"
        : "=r" (b1), "=r" (b2)
        :
        : "r2", "r6", "cc");
    do {
        if (w > 31) return;
        if (c <= 0x9F) {
            unsigned char ch = *q;
            unsigned int s;
            __asm__ volatile("add %0, %1, %2" : "=r" (s) : "r" (b1), "r" (ch));
            *dst = s;
        } else {
            unsigned char ch = *q;
            unsigned int s;
            __asm__ volatile("add %0, %1, %2" : "=r" (s) : "r" (b2), "r" (ch));
            *dst = s;
        }
        q++;
        dst++;
        c = *q;
    } while (c != 0);
}
__asm__(".section .text.w13d_080048b4,\"ax\",%progbits\n.byte 0, 0\n.previous");
