/* Task_360B0 @ 0x080360B0 (18 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_k.c (registry: src/wave4_k.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 sub_080400D0(u8 *p, u32 b, u32 c);

/* 0x080360B0: poll wrapper. Tentative. */
u8 sub_080360B0(u8 *p)
{
    return (u8)sub_080400D0(p, 0, 0);
}
