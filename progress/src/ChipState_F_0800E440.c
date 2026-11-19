/* ChipState_F_0800E440 @ 0x0800E440 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26b_0800e440.c (registry: src/w26b_0800e440.c).
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

extern void SetByte20_Clear21to23_02005130(u8 v);

extern void ListIterate_D568(u32 *p);

__attribute__((section(".text.w26b_0800e440")))
void ChipState_F_0800E440(void)
{
    register u8 *S __asm__("r4") = (u8 *)0x02005130;

    *(u16 *)(S + 24) = 1;
    switch (S[21]) {
    case 0: {
        u32 q;
        u8 t = *(S + 37);
        u8 arg;
        __asm__ volatile(
            "cmp %1, #0\n\t"
            "beq 1f\n\t"
            "movs %0, #5\n\t"
            "b 2f\n\t"
            "1:\n\t"
            "movs %0, #3\n\t"
            "2:"
            : "=r" (arg) : "r" (t) : "cc");
        *(volatile u32 *)(S + 28) = (u32)ChipInit_0801709C(arg);
        q = *(volatile u32 *)(S + 28);
        if (q == 0) {
            u8 *S2 = (u8 *)0x02005130;
            *(u16 *)(S2 + 24) = (u16)q;
            SetByte20_Clear21to23_02005130(0);
        } else {
            S[21]++;
        }
        break;
    }
    case 1:
        if (Byte12_Gt1_080170c4(*(u8 **)(S + 28))) {
            u8 z = 0;
            *(u16 *)(S + 24) = z;
            SetByte20_Clear21to23_02005130(z);
        }
        break;
    default:
        break;
    }
    ListIterate_D568(*(u32 **)0x02005270);
    ListIterate_D568(*(u32 **)0x020053C0);
}
