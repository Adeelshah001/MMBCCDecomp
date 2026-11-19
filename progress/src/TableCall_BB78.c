/* TableCall_BB78 @ 0x0800BB78 (52 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave5_h1.c (registry: src/wave5_h1.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

/* TableCall_BB78 @0x0800BB78 — MATCHED 2026-10-20 (main agbcc),
 * coordinator-verified 0 diffs over 52 bytes in built ROM.
 * Indirect call through ROM tables 0x081731A0/0x0817313C, guarded by
 * *(s16*)(s+0x14) != -1. Idiom: declaring tbl/idx as locals assigned
 * inside the if gives ROM's regalloc (s->r3, v->r2) and pool order. */
extern u8 gTbl_0817313C[];

extern u32 gTbl_081731A0[];

__attribute__((section(".text.w5h_bb78")))
void TableCall_BB78(u8 *s)
{
    s16 v = *(s16 *)(s + 0x14);
    u32 *tbl;
    s8 idx;
    if (v != -1) {
        tbl = gTbl_081731A0;
        idx = gTbl_0817313C[v];
        ((void (*)(u8 *))tbl[idx])(s);
    }
}
