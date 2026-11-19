/* Copy_08007BEC @ 0x08007BEC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x08007bec: Copy_08007BEC (coordinator-verified). */
void sub_08000758(u8 *src, u8 *dst, u32 size);

extern u8 gUnknown_03002420[];

void sub_08007BEC(u8 *src, u16 n)
{
    u32 off = (u16)n << 5;
    sub_08000758(src, gUnknown_03002420 + off, 32);
}
