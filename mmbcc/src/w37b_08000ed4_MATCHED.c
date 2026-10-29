/* Wave 37-B MATCHED: 0x08000ed4, 36 B, old_agbcc, pure C. Extent to 0x08000ef8. tbl 0x030023c8, idx*24 byte: if !=1 and bit3 set, clear bit3 (compound &= form). No externs. */
typedef unsigned char u8;
__attribute__((section(".text.w37b_08000ed4")))
void Sub_08000ED4(int idx)
{
    u8 *q = (u8 *)0x030023c8 + idx * 24;
    if (*q == 1)
        return;
    if ((*q & 8) == 0)
        return;
    *q &= 247;
}
