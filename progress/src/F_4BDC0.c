/* F_4BDC0 @ 0x0804BDC0 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_A_old.c (registry: src/wave11_A_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef struct Node {
    u8 pad[44];
    struct Node *next;
    struct Node *prev;
    struct Node *x;
} Node;

__attribute__((section(".text.w11a_0804bdc0")))
void F_4BDC0(Node *p)
{
    register Node *pp __asm__("r0") = p;
    Node *nx = pp->next;
    if (nx == 0)
        return;
    {
        Node *xv = pp->x;
        Node *pv = pp->prev;
        if (pv != 0)
            pv->x = xv;
        else
            *(Node **)((u8 *)nx + 32) = xv;
        if (xv != 0)
            xv->prev = pv;
        pp->next = 0;
    }
}
