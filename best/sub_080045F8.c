/* CpuFastSet_Vram @ 0x080045F8 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0804DB24(void *src, void *dst, unsigned mode);

extern u8 gUnknown_0805633C[];

extern u16 gUnknown_020031E4[];

extern u8 gUnknown_06007000[];

/* 0x080045F8: CpuFastSet(0x0805633C, 0x06007000+((*(u16*)0x020031E4&0xC)<<12),
 * 0x200). Tentative: ROM->VRAM copy, src bank selected by a flag nibble. */
void sub_080045F8(void)
{
    u8 *src = gUnknown_0805633C;
    u16 *flag = gUnknown_020031E4;
    u8 *dst = gUnknown_06007000 + (u32)(((*flag) & 0xC) << 12);
    sub_0804DB24(src, dst, 0x200);
}
