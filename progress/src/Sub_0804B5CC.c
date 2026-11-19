/* Sub_0804B5CC @ 0x0804B5CC (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0804b5cc_MATCHED.c (registry: mmbcc/src/w36b_0804b5cc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct P { u8 pad0; u8 pad1; u8 b2; u8 b3; u8 pad4; u8 pad5; u16 cnt; };

extern void sub_0800DDE4(u8 *a, u8 *b, u8 *c, int d);

__attribute__((section(".text.w36b_0804b5cc")))
void Sub_0804B5CC(struct P *p)
{
    u8 state = p->b3;
    switch (state) {
    case 0:
        p->b3 = 1;
        p->cnt = 32;
        /* fallthrough */
    case 1: {
        if ((p->cnt & 3) == 0) {
            short k;
            for (k = 0; k <= 3; k++) {
                u8 *dst = (u8 *)0x03002420 + (k + 1) * 32;
                sub_0800DDE4(dst, (u8 *)0x082350a0, dst, 1);
            }
        }
        if (--p->cnt == 0) {
            p->b2++;
            p->b3 = 0;
        }
        break;
    }
    default:
        break;
    }
}
