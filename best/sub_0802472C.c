/* ConstZeroS16_2472C @ 0x0802472C (6 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave3_e_old.c (registry: src/wave3_e_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

/* 0x0802472C (6B, tentative): computes (u32)a << 24, tests it, returns 0
 * either way (s16 per caller sign-extension). */
s16 sub_0802472C(u8 a)
{
    if ((u32)a << 24)
        return 0;
    return 0;
}
