/* 0x08024bc8: Sub_08024BC8 (76 B, old_agbcc).
 * If TblLookup_25730(ptr, v) != 0, return (u16)F_08025A10(ptr, v); else 0.
 * ptr = *(u32 *)(p+20) + (*(u8 *)(*(u32 *)(p+20) + 432) * 144), computed
 * inline twice (compiler does not CSE across the call).
 * old_agbcc required for ROM's register allocation (r1/r2/r3 in the
 * address computation); main agbcc uses r2/r1/r2.
 * Wave 20 Worker B. Evidence: docs/match_notes_wave20_B.md. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u8 TblLookup_25730(u8 *tbl, u8 idx);
extern u32 F_08025A10(u8 *s, u8 idx);
__attribute__((section(".text.w20b_08024BC8")))
u16 Sub_08024BC8(u8 *p, u8 v)
{
    if (TblLookup_25730((u8 *)(*(u32 *)(p + 20) + (*(u8 *)(*(u32 *)(p + 20) + 432) * 144)), v) == 0)
        return 0;
    return (u16)F_08025A10((u8 *)(*(u32 *)(p + 20) + (*(u8 *)(*(u32 *)(p + 20) + 432) * 144)), v);
}
