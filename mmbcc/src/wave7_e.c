/* Wave 7 batch E (coordinator-verified, main agbcc).
   Evidence: docs/match_notes_wave7_e.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 gBase082297E8[];

/* 0x08025578: FilterCopy (coordinator-verified, 122B + 2B 00 pad). */
__attribute__((section(".text.w7e_08025578")))
void FilterCopy(u8 *p, u8 a, u8 b)
{
    u8 *base;
    u16 n;
    u8 *src;
    u8 *dst;
    u8 v;
    if (a > 6) a = 0;
    if (b > 1) b = 0;
    base = gBase082297E8;
    n = *(u16*)(base + 28);
    src = *(u8**)(base + a * 4);
    dst = *(u8**)(p + 8);
    if (b == 0) {
        if (n == 0) return;
        do {
            v = *src;
            if (*(u8*)(*(u8**)(p + 4) + v))
                *dst++ = v;
            n--;
            src++;
        } while (n != 0);
        return;
    }
    src += n - 1;
    if (n == 0) return;
    do {
        v = *src;
        if (*(u8*)(*(u8**)(p + 4) + v))
            *dst++ = v;
        n--;
        src--;
    } while (n != 0);
}
__attribute__((section(".text.w7e_08025578")))
static const u16 w7e_08025578_gap = 0;
__asm__(".set gBase082297E8, 0x082297E8");
