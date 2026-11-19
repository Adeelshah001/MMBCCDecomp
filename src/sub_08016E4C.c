/* F_08016E4C @ 0x08016E4C (54 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B.c (registry: src/wave15_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08011F68(u8 *s, u8 v);

void sub_08016E4C(u8 *p, u16 v)
{
    u8 *q = p + 124;
    *q = (u8)v;
    if ((u8)v > 38) {
        q[2] = (u8)(v - 39);
        *q = 39;
    } else {
        q[2] = 0;
    }
    q[4] = 1;
    sub_08011F68(p, 2);
}
