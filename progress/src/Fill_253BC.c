/* Fill_253BC @ 0x080253BC (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w16b_080253bc.c (registry: src/w16b_080253bc.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern int Append_0802526C(void *s, u8 v);

extern void Fill_0802520C(void *s, u8 *ptr, u16 n);

void Fill_253BC(u8 *s)
{
    Fill_0802520C(s + 12, *(u8 **)(s + 8), 249);
    {
        u16 t = 0;
        s16 i;
        do {
            i = (s16)t;
            if (*(u8 *)(*(u8 **)(s + 4) + i))
                Append_0802526C(s + 12, (u8)t);
            t = (u16)(i + 1);
        } while ((s16)t <= 248);
    }
}
