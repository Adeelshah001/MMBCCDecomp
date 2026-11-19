/* Sub_08007CF4 @ 0x08007CF4 (110 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08007cf4_MATCHED.c (registry: mmbcc/src/w36b_08007cf4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ent { u8 pad[4]; u8 f4; u8 f5; u8 pad6; u8 f7; };

struct Arr { u16 f0; u16 f2; };

extern void sub_08006578(s8 a, s8 b, int c, int d, u32 e, u32 f);

extern int F_08022fe4(struct Ent *e);

__attribute__((section(".text.w36b_08007cf4")))
void Sub_08007CF4(u16 idx, u8 a, u8 b)
{
    struct Ent *e = ((struct Ent *)0x02004e18) + idx;
    e->f4 = a;
    e->f5 = b;
    {
        register int m __asm__("r1") = -5;
        e->f7 = m & e->f7;
    }
    if (idx == 0) {
        sub_08006578(a, b, 8, 7, ((struct Arr *)0x08171ef4)->f0, ((struct Arr *)0x08171ef4)->f2);
    } else {
        if ((e->f7 & 1) == 0) {
            if (F_08022fe4(e) != 0) {
                e->f7 = 1 | e->f7;
            }
        }
    }
}
