/* Sub_08048084 @ 0x08048084 (374 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39a_08048084_MATCHED.c (registry: mmbcc/src/w39a_08048084_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void MemsetAligned_4E008(u8 *dst, int val, int n);

extern void Copy4_2518C(u8 *q, u8 *buf);

extern void Gfx_BlitRequest(u8 *buf, int a, int b, int c, int d);

extern int F_080251d8(u8 *q);

extern void CondRectFill_080070F0(u8 v, int a, int b, int c);

extern void GatedDispatch(u8 v, int a, int b, int c, int d);

__attribute__((section(".text.w39a_08048084")))
void Sub_08048084(u8 *s)
{
    u8 buf[8];
    u8 *q;
    u8 v;

    MemsetAligned_4E008(buf, 0, 8);
    if (s[10] & 1) {
        q = s + 6832;
        Copy4_2518C(q, buf);
        Gfx_BlitRequest(buf, 4, 4, 4, 0);
        v = F_080251d8(q);
        CondRectFill_080070F0(v, 10, 4, 0);
        GatedDispatch(s[5959], 5, 7, 2, 0);
        GatedDispatch(s[5958], 8, 7, 2, 0);
        GatedDispatch(s[5957], 11, 7, 2, 0);
    } else {
        GatedDispatch(0, 5, 7, 2, 0);
        GatedDispatch(0, 8, 7, 2, 0);
        GatedDispatch(0, 11, 7, 2, 0);
    }
    if (s[10] & 2) {
        q = s + 12772;
        Copy4_2518C(q, buf);
        Gfx_BlitRequest(buf, 18, 4, 4, 0);
        v = F_080251d8(q);
        CondRectFill_080070F0(v, 24, 4, 0);
        GatedDispatch(s[11899], 19, 7, 2, 0);
        GatedDispatch(s[11898], 22, 7, 2, 0);
        GatedDispatch(s[11897], 25, 7, 2, 0);
    } else {
        GatedDispatch(0, 19, 7, 2, 0);
        GatedDispatch(0, 22, 7, 2, 0);
        GatedDispatch(0, 25, 7, 2, 0);
    }
}
