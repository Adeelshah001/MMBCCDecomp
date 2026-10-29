/* Wave 16 worker B: 0x0804580C (42 B).
 * Counts non-zero TblStride_24818(i) for i in 0..29.
 */
typedef unsigned char u8;
typedef unsigned short u16;


extern u8 TblStride_24818(u16 idx);
u8 TblStride_24818(u16 idx);

u8 CountNonzeroStride(void) __attribute__((section(".text.w16b_0804580c")));
u8 CountNonzeroStride(void)
{
    u8 n = 0;
    u8 i = 0;
    do {
        if (TblStride_24818(i))
            n = n + 1;
        i = i + 1;
    } while (i <= 29);
    return n;
}



__attribute__((section(".text"))) static const u16 w16b_0804580c_pad = 0;