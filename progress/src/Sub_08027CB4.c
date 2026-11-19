/* Sub_08027CB4 @ 0x08027CB4 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08027cb4_MATCHED.c (registry: mmbcc/src/w35c_08027cb4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Call4E60_4E44(void);

extern void PalModeSet_4DFC(int v);

extern void sub_08021498(void);

extern void NewNode_080214F4(void);

extern void Sub_08027E5C(u8 *p);

__attribute__((section(".text.w35c_08027cb4")))
void Sub_08027CB4(void)
{
    u8 z;
    u8 *base = (u8 *)0x0200b7e0;
    u8 *q = base;
    u16 i;
    for (i = 0; i <= 39; i++)
        *q++ = 0;
    z = 0;
    base[2] = z;
    Call4E60_4E44();
    PalModeSet_4DFC(2);
    *(u16 *)0x02004830 = z;
    sub_08021498();
    NewNode_080214F4();
    Sub_08027E5C(base);
}
