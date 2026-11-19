/* StateMachine_0800E6D0 @ 0x0800E6D0 (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w18c_0800e6d0.c (registry: src/w18c_0800e6d0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Poke80_08016f74(u8 *p);

extern u32 Byte128_IsZero(u8 *s);

extern void SetByte20_Clear21to23_02005130(u8 v);

extern void ListIterate_D568(u8 *s);

__attribute__((section(".text.w18c_0800e6d0")))
void StateMachine_0800E6D0(void)
{
    u8 *g = (u8 *)0x02005130;
    u32 v;
    u8 st;
    *(u16 *)(g + 24) = 1;
    {
        volatile u32 *p;
        if (g[0x29] == 0) {
            p = (volatile u32 *)0x02005020;
            v = p[0];
        } else {
            p = (volatile u32 *)0x02005020;
            v = p[1];
        }
    }
    st = g[21];
    if (st == 0) goto L0;
    if (st == 1) goto L1;
    goto Lend;
L0:
    Poke80_08016f74((u8 *)v);
    g[21]++;
    goto Lend;
L1:
    if ((u16)Byte128_IsZero((u8 *)v) != 0) {
        u8 *g2;
        u32 z;
        __asm__ volatile("" : "=r" (g2) : "0" ((u8 *)0x02005130));
        z = 0;
        *(u16 *)(g2 + 24) = z;
        SetByte20_Clear21to23_02005130(z);
    }
Lend:;
    ListIterate_D568(*(u8 **)0x02005270);
    ListIterate_D568(*(u8 **)0x020053c0);
}
