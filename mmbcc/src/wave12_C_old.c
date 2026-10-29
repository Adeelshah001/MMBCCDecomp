/* Wave 12 worker C (bulk leaves-up layer): 5 matched functions, all old_agbcc. */
/* See docs/match_notes_wave12_C.md for idioms. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

/* 0x0800CD00: if bit 2 of gEwram_02000EC0[9] clear, clear bits 11-13 of
 * gEwram_020031E0[0] (&= 0xC7FF); else set them (|= 0x3800). */
__attribute__((section(".text.w12c_0800cd00")))
void SyncEwramFlagBits_0CD00(void)
{
    unsigned int base;
    __asm__ volatile("" : "=r" (base) : "0" (0x02000EC0));
    if ((((unsigned char *)base)[9] & 4) == 0) {
        unsigned short *q = (unsigned short *)0x020031E0;
        unsigned short t = 0xC7FF;
        unsigned short u = t & *q;
        *q = u;
    } else {
        register unsigned short *q __asm__("r0") = (unsigned short *)0x020031E0;
        unsigned short t = 0x3800;
        register unsigned short u __asm__("r1") = t;
        u |= *q;
        *q = u;
    }
}

/* 0x08002C74: search 16-byte table at 0x02003090 for (a+1); clear found entry. */
__attribute__((section(".text.w12c_08002c74")))
void TblFindClear_02C74(unsigned char a)
{
    unsigned char v = a + 1;
    int i = 0;
    unsigned int addr;
    unsigned char *p;
    __asm__ volatile("" : "=r" (addr) : "0" (0x02003090));
    __asm__ volatile("add %0, %1, #0" : "=l" (p) : "l" (addr));
    if (p[0] != v) {
        unsigned char *q = p;
        do {
            i++;
        } while (i <= 15 && *(unsigned char *)((unsigned int)i + (unsigned int)q) != v);
    }
    if (i != 16)
        *(unsigned char *)((unsigned int)i + (unsigned int)p) = 0;
}

/* 0x080499AC: read u16 at (0x020070F0 + a*12 + 0x152); map 0xFF->3, 0xFE->2,
 * 0xFD->1, else 0. */
__attribute__((section(".text.w12c_080499ac")))
int MapTableVal_499AC(unsigned char a)
{
    unsigned int base;
    unsigned char *p;
    __asm__ volatile("" : "=r" (base) : "0" (0x020070F0));
    p = (unsigned char *)base;
    {
        int r = 0;
        switch (*(unsigned short *)(p + a * 12 + 0x152)) {
        case 0xFF:
            r = 3;
            break;
        case 0xFE:
            r = 2;
            break;
        case 0xFD:
            r = 1;
            break;
        }
        return r;
    }
}
__asm__(".section .text.w12c_080499ac,\"ax\",%progbits\n.byte 0, 0\n.previous");

/* 0x0800C4B4: init object struct: conditional u16 fields, OR 0xFFFF into two
 * fields, clear byte. */
__attribute__((section(".text.w12c_0800c4b4")))
void ObjInit_C4B4(unsigned char *p)
{
    unsigned int addr;
    __asm__ volatile("" : "=r" (addr) : "0" (0x02003670));
    addr += 0x11AE;
    if (((*(unsigned char *)addr) & 4) == 0) {
        unsigned short v = 0xFFF8;
        *(unsigned short *)(p + 22) = v;
        *(unsigned short *)(p + 24) = v;
    } else {
        unsigned short v = 0;
        *(unsigned short *)(p + 22) = v;
        *(unsigned short *)(p + 24) = v;
    }
    {
        register unsigned short t __asm__("r1");
        register unsigned short u __asm__("r0");
        __asm__ volatile("" : "=r" (t) : "0" (0xFFFF));
        u = t;
        *(unsigned short *)(p + 20) |= u;
        *(unsigned short *)(p + 6) |= u;
    }
    p[26] = 0;
}

/* 0x0800C3A0: fill 28x32 u16 tilemap with ((b + col) | 0x1000). */
__attribute__((section(".text.w12c_0800c3a0")))
void FillTilemap_C3A0(unsigned short *base, unsigned short b)
{
    short i = 0;
    do {
        unsigned short *p = base + i * 32;
        short j;
        j = 0;
        do {
            *p++ = (b + j) | 0x1000;
            j++;
        } while (j <= 31);
        i++;
    } while (i <= 27);
}
