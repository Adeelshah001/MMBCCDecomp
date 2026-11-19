/* TableU32_0820B6A4 @ 0x08011CC4 (16 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_d.c (registry: src/wave3_d.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 gUnknown_0820B6A4[];

/* 0x08011CC4: lsls r0,#16 / lsrs r0,#14 zero-extends the u16 arg and scales
 * by 4; u32 table at 0x0820B6A4. */
u32 sub_08011CC4(u16 i)
{
    return gUnknown_0820B6A4[i];
}
