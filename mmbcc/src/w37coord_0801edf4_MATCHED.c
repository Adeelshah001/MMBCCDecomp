/* Wave 37 coordinator: 0x0801edf4, 32 B, old_agbcc, C + .s patch
   (tools/fix_w37coord_0801edf4_patch.py: adds operand order + mov/ldr
   register swap — same patch as the Slot_FetchWord4 twins). Extent to
   0x0801ee14 (next fn NewNode_0801EE14, Wave 18). s[10]&=~1; s[12]=4;
   s[20]=tbl[s[9]] word4, tbl 0x082243d8. Slot_FetchWord4 twin family;
   gap found inside the 0x0801ece8 TSV 300 B window (W37-D). No externs. */
typedef unsigned char u8;
typedef unsigned int u32;
__attribute__((section(".text.w37coord_0801edf4")))
void Sub_0801EDF4(u8 *s)
{
    u32 *base;
    u32 *p;
    s[10] &= 254;
    base = (u32 *)0x082243d8;
    __asm__ volatile("" : "+r"(base));
    p = base + s[9];
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*p + 16);
}
