/* TableByte_16FAC @ 0x08016FAC (34 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave10_L_old.c (registry: src/wave10_L_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern unsigned char g_082240b8[];

/* 0x08016FAC (34B): ROM table byte; 0 if null entry. */
typedef struct { u8 *p; u8 _pad[4]; } TblEntry_16FAC;

__attribute__((section(".text.w10l_08016fac")))
u8 TableByte_16FAC(u8 idx, u8 off)
{
    u8 *tbl = g_082240b8;
    u8 *p = ((TblEntry_16FAC *)tbl)[idx].p;
    if (p != 0)
        return p[off];
    return 0;
}
