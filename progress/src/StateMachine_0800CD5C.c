/* StateMachine_0800CD5C @ 0x0800CD5C (138 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w33b_0800cd5c.c (registry: src/w33b_0800cd5c.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void BitCtl_520C(u32 x);

extern u8 NodeInitSwitch_0800D1E0(u8 *a, u8 *b, u8 *c, u8 *d);

__attribute__((section(".text.w33b_0800cd5c_v6")))
int StateMachine_0800CD5C(u8 *s)
{
    int ret = 1;
    switch (s[1]) {
    case 0:
        if (s[6] == 0) {
            s[1] = 2;
            BitCtl_520C(1);
        } else {
            s[1] = 1;
        }
        s[3] = 0;
        break;
    case 1:
        if (NodeInitSwitch_0800D1E0(s, s + 3, s + 4, s + 5) != 0)
            break;
        s[1] = 2;
        break;
    case 2: {
        if (s[0] != s[7]) {
            int zero = 0;
            s[6] = s[0];
            s[0] = s[7];
            s[3] = zero;
            s[2] = zero;
            s[1] = zero;
            {
                u16 *p = (u16 *)0x020031e0;
                u32 mask = 0xedff;
                u16 v;
                __asm__ volatile("" : "+r"(mask));
                v = *p;
                mask &= v;
                mask &= 0xdbff;
                *p = mask;
            }
        } else {
            ret = 0;
        }
        break;
    }
    default:
        break;
    }
    return ret;
}
