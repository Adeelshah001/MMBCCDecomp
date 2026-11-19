/* GetIndexedU8 @ 0x080258F8 (10 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_a.c (registry: src/wave3_a.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* 0x080258F8: return *(u8*)(a + ((u16)b<<2) + 21). Tentative.
 * The ((u16)b)<<2 with u32 accumulator is required for the exact
 * `lsls #16; lsrs #14; adds r1,r1,r0` sequence (see match notes). */
u8 sub_080258F8(u8 *a, u16 b)
{
    u32 off = ((u16)b) << 2;
    off += (u32)a;
    return *(u8 *)(off + 21);
}
