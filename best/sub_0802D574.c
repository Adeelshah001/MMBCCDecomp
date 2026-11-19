/* Lookup_02D574 @ 0x0802D574 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w32c_0802d574.c (registry: staging/wave32_C/w32c_0802d574_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

u32 sub_0802D574(u32 a0)
{
    s32 v = (u8)a0;
    register s32 v2 = v;
    register u32 r = 255;

    if (v == 2)
        goto L4;
    if (v > 2)
        goto Lgt;
    if (v == 1)
        goto L2;
    goto Lend;
Lgt:
    if (v2 == 3)
        goto L1;
    if (v2 == 4)
        goto L3;
    goto Lend;
L2:
    r = 2;
    goto Lend;
L4:
    r = 4;
    goto Lend;
L1:
    r = 1;
    goto Lend;
L3:
    r = 3;
Lend:
    return r;
}
