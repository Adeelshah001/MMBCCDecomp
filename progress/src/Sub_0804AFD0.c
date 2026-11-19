/* Sub_0804AFD0 @ 0x0804AFD0 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_0804afd0_MATCHED.c (registry: src/w36bulk_0804afd0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Call4E60_4E44(void);

extern void PalModeSet_4DFC(int mode);

extern void Sub_08016FD0(u8 *a, u8 *b, int c);

extern void Dispatch_0800dea4(u8 *a, u32 b, int c, int d, u32 e, u32 f, int g);

extern void sub_08002AFC(int a, int b);

extern void sub_0801EE68(u8 *o);

__attribute__((section(".text.w36bulk_0804afd0")))
int Sub_0804AFD0(u8 *o)
{
    u32 *base;
    u8 t;
    u8 z;
    t = o[0] + 1;
    z = 0;
    o[0] = t;
    o[4] = z;
    base = (u32 *)0x020038ac;
    Call4E60_4E44();
    PalModeSet_4DFC(2);
    Sub_08016FD0((u8 *)0x02004fc8, (u8 *)0x020053d0, 36);
    Dispatch_0800dea4((u8 *)0x0871e534, base[1], 2, 1, *(u32 *)0x0871c8b4 + 0x0871c8b4, base[0], 32);
    {
        u16 *p;
        p = (u16 *)0x020031f4;
        p[0] = 0xFFF8;
        p[1] = 0xFFF8;
    }
    sub_08002AFC(29, 32);
    sub_0801EE68(o);
    return 0;
}
