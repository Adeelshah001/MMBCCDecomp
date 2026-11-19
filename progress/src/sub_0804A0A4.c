/* sub_0804A0A4 @ 0x0804A0A4 (332 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w65d_0804a0a4_MATCHED.c (registry: staging/w65d_fresh/w65d_0804a0a4_RECOMMENDED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 *U_082344EC;

extern u32 *T_081720B0;

extern u32 *V1_08234B7C[];

extern u32 *V2_08234BFC[];

extern u16 gEwram_02004CE0[];

void Gfx_BlitRequest(u32 a, u16 b, u16 c, u8 d, u8 e);

void CondRectFill_080062B4(u8 x, s8 y, u8 w, u8 h, u16 a, u16 b, u32 c);

void ShiftPairCfg_4A1F0(u8 *p);

__attribute__((section(".text.w65d_0804a0a4")))
void sub_0804A0A4(u8 *s)
{
    u8 i;
    u8 j;


    for (i = 0, j = s[0x46A8]; j < s[0x46A8] + 3; i++, j++) {
        Gfx_BlitRequest((u32)U_082344EC, 2, 2 * i + 3, 24, 2);
        if (j < s[0x46AA]) {
            u8 b = *(u8 *)(j + (u32)s + 0x46B8);
            u32 m = *(u32 *)(s + 28) & (1 << b);
            u8 *q = s + j;
            if (m != 0)
                CondRectFill_080062B4(2, (s8)(2 * i + 3), 2, 2, 110, 3, *T_081720B0);
            else
                CondRectFill_080062B4(2, (s8)(2 * i + 3), 2, 2, 110, 3, T_081720B0[2]);
            Gfx_BlitRequest((u32)*V1_08234B7C[q[0x46B8]], 4, 2 * i + 3, 8, 2);
            Gfx_BlitRequest((u32)*V2_08234BFC[q[0x46B8]], 12, 2 * i + 3, 14, 2);
        }
    }
    gEwram_02004CE0[20] = 20;
    gEwram_02004CE0[21] = (s[0x46A9] << 4) + 24;
    ShiftPairCfg_4A1F0(s);
}
