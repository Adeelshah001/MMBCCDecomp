/* Sub_080267C0 @ 0x080267C0 (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_080267c0_MATCHED.c (registry: mmbcc/src/w35b_080267c0_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08026880(u8 *s);

extern void InitRec8_267B4(u8 *p, int x);

__attribute__((section(".text.w35b_080267c0")))
void Sub_080267C0(u8 *s)
{
    int v = s[1];
    if (v == 1) goto Lde;
    if (v > 1) goto Ld4;
    if (v == 0) goto Lda;
    __asm__ volatile("" ::: "memory");
    goto Lee;
Ld4:
    if (v == 2) goto Le6;
    __asm__ volatile("" ::: "memory");
    goto Lee;
Lda:
    s[1] = 1;
Lde:
    sub_08026880(s);
    goto Lee;
Le6:
    InitRec8_267B4((u8 *)0x020070f0, 3);
Lee:
    return;
}
