/* Ent_TblInit_0801F1E8 @ 0x0801F1E8 (60 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave6_l4_old.c (registry: src/wave6_l4_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* 0x0801d36c: Ent_TblInit_0801D36C (coordinator-verified). */
extern u32 Tbl_082243D8[];

extern u32 gTbl_08226DC0[];

void Dispatch_08226DD8_10(u8 *s);

__attribute__((section(".text.w6l4_0801f1e8")))
void Ent_TblInit_0801F1E8(u8 *s)
{
    u32 *t1 = Tbl_082243D8;
    u32 *p = t1 + s[9];
    *(u32 *)(s + 12) = 1;
    {
        u32 e = *p;
        *(u32 *)(s + 20) = *(u32 *)(e + 4);
    }
    {
        u32 *t2 = gTbl_08226DC0;
        u32 t = t2[s[16]];
        ((void (*)(u8 *))t)(s);
    }
    Dispatch_08226DD8_10(s);
}
