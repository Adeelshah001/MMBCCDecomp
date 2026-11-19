/* F_0801039C @ 0x0801039C (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08010508(u8 v);

u8 sub_0801039C(u8 *p, u8 b)
{
    u8 bb;
    u8 *q;
    bb = b;
    q = (u8 *)0x02005160;
    
    if (*q != 0)
        return 0;
    sub_08010508(6);
    *(u8 **)(q + 48) = p;
    *(q + 66) = bb;
    return 1;
}
