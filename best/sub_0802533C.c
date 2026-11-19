/* F_0802533c @ 0x0802533C (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave14_C_old.c (registry: src/wave14_C_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


/* F_0802533c @ 0x0802533c */
void sub_080252E8(u8 *p);

void sub_0802533C(u8 *p, u8 idx)
{
    u8 *q;
    if (idx > 0xf8) return;
    if (idx > 0xc7) {
        q = p + idx;
        if ((*q & 0x7f) > 0x62) return;
        sub_080252E8(q);
    } else {
        q = p + idx;
        if ((*q & 0x7f) > 0x62) return;
        sub_080252E8(q);
    }
}
