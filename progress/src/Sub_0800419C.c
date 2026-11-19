/* Sub_0800419C @ 0x0800419C (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0800419c_MATCHED.c (registry: mmbcc/src/w36b_0800419c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Node { struct Node *next; u32 f4; };

struct P { struct Node *arr[4][32]; struct Node *a; struct Node *b; };

extern void sub_080030C4(u8 *buf, struct Node *a, struct Node *b);

extern void _call_via_r2(struct Node *node, u8 *buf, u32 f4);

__attribute__((section(".text.w36b_0800419c")))
void Sub_0800419C(struct P *p)
{
    u8 buf[24];
    struct Node *a = p->a;
    if (a != 0) {
        struct Node *b = p->b;
        int i;
        sub_080030C4(buf, a, b);
        for (i = 0; i <= 3; i++) {
            short j;
            for (j = 0; j <= 31; j++) {
                struct Node *node = p->arr[i][j];
                while (node != 0) {
                    _call_via_r2(node, buf, node->f4);
                    node = node->next;
                }
            }
        }
    }
}
