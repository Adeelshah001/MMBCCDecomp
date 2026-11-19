/* ChipState_Tick_0800E3A0 @ 0x0800E3A0 (96 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w22d_0800e3a0.c (registry: mmbcc/src/w22d_0800e3a0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef struct {
    u8 pad0[13];
    u8 mode;
    u8 pad1[3];
    u8 f17;
    u8 pad2[17];
    u8 f35;
    u8 pad3[8];
    u32 f44;
    u8 pad4[40];
    u32 f88;
    u32 f92;
    u32 f96;
    u32 f100;
} S;

extern u32 *ChipInit_0801709C(u8 a);

extern u8 Byte12_Gt1_080170c4(u8 *s);

extern void SetByte20_Clear21to23_02005130(void);

extern void ListIterate_D568(u32 *p);

__attribute__((section(".text.w22d_0800E3A0")))
void ChipState_Tick_0800E3A0(void)
{
    register u8 *S __asm__("r4") = (u8 *)0x02005130;

    *(u16 *)(S + 24) = 1;
    switch (S[21]) {
    case 0: {
        u32 *p = ChipInit_0801709C(0);
        *(u32 **)(S + 28) = p;
        if (p == 0)
            break;
        S[21]++;
        break;
    }
    case 1:
        if (Byte12_Gt1_080170c4(*(u8 **)(S + 28))) {
            *(u16 *)(S + 24) = 0;
            SetByte20_Clear21to23_02005130();
        }
        break;
    default:
        break;
    }
    ListIterate_D568(*(u32 **)0x02005270);
    ListIterate_D568(*(u32 **)0x020053C0);
}
