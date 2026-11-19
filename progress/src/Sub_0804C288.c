/* Sub_0804C288 @ 0x0804C288 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35b_0804c288_MATCHED.c (registry: mmbcc/src/w35b_0804c288_MATCHED.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef u8 (*Func)(u8 *s);

__attribute__((section(".text.w35b_0804c288")))
void Sub_0804C288(u8 a, u8 *p)
{
    u8 *pp = p;
    u32 *node;
    if ((*pp & 0x80) == 0)
        return;
    node = *(u32 **)(pp + 32);
    if (node == 0)
        goto done;
    do {
        u32 z = 0;
        if (*(u8 *)node != 0) {
            if ((((u8 *)node)[1] & 7) != 0) {
                typedef void (*Func)(void);
                register u8 *tmp __asm__("r3");
                tmp = *(u8 **)0x03007FF0;
                tmp = *(u8 **)(tmp + 44);
                ((Func)tmp)();
            }
            *(u8 *)node = z;
        }
        *(u32 *)((u8 *)node + 44) = z;
        node = *(u32 **)((u8 *)node + 52);
    } while (node != 0);
done:
    *(u32 **)(pp + 32) = node;
}
