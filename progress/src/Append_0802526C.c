/* Append_0802526C @ 0x0802526C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_r_old.c (registry: src/wave8_r_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef struct {
    u8 *p;
    u16 a;
    u16 b;
} Buf_0802526C;

__attribute__((section(".text.w8r_0802526c")))
int Append_0802526C(Buf_0802526C *s, u8 v) {
    if (s->b >= s->a)
        return 1;
    s->p[s->b] = v;
    s->b++;
    return 0;
}
