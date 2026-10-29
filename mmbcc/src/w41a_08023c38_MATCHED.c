/* Wave 41 coordinator landing: coordinator-verified 0-diff (standalone
 * rebuild + independent ROM-extract cmp). See staging/w41coord_verify/COORD_LOG.md.
 */
typedef unsigned char u8;
typedef short s16;
__attribute__((section(".text.w41a_08023c38")))
void Sub_08023C38(u8 *dst, u8 *src, u8 sl_in)
{
    register int sh __asm__("sl") = sl_in;
    s16 i;
    for (i = 0; i <= 13; i++) {
        u8 bit = sh & 7;
        u8 bit2 = bit;
        u8 byte = sh >> 3;
        s16 m1 = (s16)(i - byte) % 14;
        if (m1 < 0)
            m1 += 14;
        dst[i] = src[m1] >> bit;
        if (bit != 0) {
            s16 m2 = (i - byte - 1) % 14;
            if (m2 < 0)
                m2 += 14;
            dst[i] |= src[m2] << (8 - bit2);
        }
    }
}
__asm__(".set __modsi3, 0x0804dda0");
__asm__(".hword 0");
