/* Dispatch_PostInc @ 0x0804DA00 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i.c (registry: src/wave4_i.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 gTbl_08105F70[];

/* 0x0804DA00: tbl[*b->ptr++](a, b). Tentative.
 * b is a struct with a u8* at +0x40; the explicit `off` local puts the
 * function pointer in r2 so agbcc emits bl _call_via_r2. */
typedef struct { u8 _00[0x40]; u8 *ptr; } Ctx4DA00;

__attribute__((section(".text.w4i_dispatch_postinc")))
void Dispatch_PostInc(u8 *a, Ctx4DA00 *b)
{
    u8 idx = *b->ptr++;
    u32 *tbl = gTbl_08105F70;
    u32 off = idx << 2;
    u32 fn = *(u32 *)((u32)tbl + off);
    ((void (*)(u8 *, Ctx4DA00 *))fn)(a, b);
}
