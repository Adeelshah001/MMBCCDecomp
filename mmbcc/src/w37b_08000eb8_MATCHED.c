/* Wave 37-B MATCHED: 0x08000eb8, 28 B, old_agbcc, pure C. Extent to 0x08000ed4. tbl 0x030023c8, idx*24 byte |=8 unless ==1. No externs. */
typedef unsigned char u8;
__attribute__((section(".text.w37b_08000eb8")))
void Sub_08000EB8(int idx)
{
    u8 *q = (u8 *)0x030023c8 + idx * 24;
    if (*q != 1)
        *q |= 8;
}
