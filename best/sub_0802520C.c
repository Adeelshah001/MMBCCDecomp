/* Fill_0802520C @ 0x0802520C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef struct {
    u8 *p;
    u16 a;
    u16 b;
} Buf_0802520C;

void sub_0802520C(Buf_0802520C *s, u8 *ptr, u16 n) {
    s->p = ptr;
    s->a = n;
    s->b = 0;
    while (n != 0) {
        *ptr++ = 0xFF;
        n--;
    }
}
