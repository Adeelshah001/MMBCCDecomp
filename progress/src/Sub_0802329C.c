/* Sub_0802329C @ 0x0802329C (104 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_0802329c_MATCHED.c (registry: mmbcc/src/w36b_0802329c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Q { u8 b0; s8 b1; u16 h2; s8 b4; s8 b5; u8 b6; u8 b7; };

extern void Sub_08009EDC(u8 a, u16 b);

extern void sub_080099FC(u8 a, u16 b, u8 c);

__attribute__((section(".text.w36b_0802329c")))
void Sub_0802329C(u8 *p)
{
    struct Q *q = *(struct Q **)(p + 40);
    u8 flag = q->b7 & 4;
    if (flag == 0) {
        s8 v = q->b1;
        if (v == 0) {
            p[13] = 1;
            p[15] = flag;
            p[14] = flag;
            *(u32 *)(p + 88) = q->h2;
            *(int *)(p + 96) = q->b4;
            *(int *)(p + 100) = q->b5;
            Sub_08009EDC(q->b0, q->h2);
        } else if (v == 1) {
            p[13] = 2;
            p[15] = flag;
            p[14] = flag;
            *(u32 *)(p + 88) = q->h2;
            *(int *)(p + 96) = q->b4;
            *(int *)(p + 100) = q->b5;
            sub_080099FC(q->b0, q->h2, q->b6);
        }
    }
}
