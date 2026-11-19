/* TickWrapper @ 0x08011F7C (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_b.c (registry: src/wave3_b.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D9FC(u8 *s);

/* ChipSlot_Tick (0x0800D9FC, BLOCKED wave2) tail wrapper (TENTATIVE).
 * ROM 0x08011F7C (8 B): push {lr}; bl ChipSlot_Tick; pop {r0}; bx r0. */
void sub_08011F7C(u8 *s)
{
    sub_0800D9FC(s);
}
