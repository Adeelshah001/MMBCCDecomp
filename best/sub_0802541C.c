/* F_0802541C @ 0x0802541C (70 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_misc_old.c (registry: src/w17c_misc_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0802533C(u8 *p, u8 idx);

extern void sub_080253BC(u8 *s);

/* 0x0802541c (70 B): F_0802533c loop + Fill_253BC. */
void sub_0802541C(u8 *s, u8 *p, u16 n)
{
    u16 i;
    for (i = 0; i < n; i++) {
        u8 *s4;
        sub_0802533C(*(u8 **)s, p[i]);
        s4 = *(u8 **)(s + 4);
        s4[p[i]]++;
    }
    sub_080253BC(s);
}
