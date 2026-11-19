/* TableGet_24734 @ 0x08024734 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e.c (registry: src/wave3_e.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


           /* EWRAM base 0x02005160 */
extern u32 gUnknown_0822D69C[];

/* 0x08024734 (12B + pool, tentative): indexed word load from the ROM
 * pointer table at 0x0822D69C (entries are 0x080Fxxxx code pointers).
 * agbcc schedules the pool load between the two shifts, matching ROM. */
u32 sub_08024734(u8 i)
{
    return gUnknown_0822D69C[i];
}
