/* Wave 8 batch B: blocked-revisit cracks (old_agbcc).
 * Evidence: docs/match_notes_wave8_B.md, docs/wave8_B_results.tsv. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 gEwram_02004E40[];

__attribute__((section(".text.w8b_0800b2d8")))
int Tst_0800B2D8(void)
{
    u8 v = gEwram_02004E40[4];
    if ((v & 143) == 128)
        return 1;
    return 0;
}

__attribute__((section(".text.w8b_0800b2f0")))
int Tst_0800B2F0(void)
{
    u8 v = gEwram_02004E40[4];
    if ((v & 143) == 0)
        return 1;
    return 0;
}

__asm__(
    ".set gEwram_02004E40,0x02004E40\n\t"
);
