/* SelBlob_Ret @ 0x0800303C (26 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void Text_SelectBlob(u16 idx);

/* 0x0800303C: Text_SelectBlob(v); return (s16)v. Tentative.
 * Param is u16 (zero-extended on entry); return is s16 (sign-extended). */
__attribute__((section(".text.w4i_selblob_ret")))
s16 SelBlob_Ret(u16 v)
{
    Text_SelectBlob(v);
    return (s16)v;
}
