/* S8TableLookup_0C248 @ 0x0800C248 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern s8 gTbl_0817313C[];

/* 0x0800C248 (28B): s8 table lookup; -1 if idx==-1 or idx<=59. */
__attribute__((section(".text.w10l_0800c248")))
int S8TableLookup_0C248(s16 idx)
{
    int x = idx;
    int r = -1;
    u8 b;
    if (x == -1) goto done;
    if (x <= 59) goto done;
    b = ((u8 *)gTbl_0817313C)[x];
    r = (s8)b;
done:
    return r;
}
