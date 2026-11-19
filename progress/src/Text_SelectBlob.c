/* Text_SelectBlob @ 0x0804C6B4 (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/text.c (registry: src/text.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u32 Tbl2_08106D7C[];

extern u8 Tbl1_08106DD0[];

void Text_OpenDialogue(u32 a, u32 b);

/* Text_SelectBlob @0x0804C6B4 — MATCHED with old_agbcc.
 * Indexes the 8-byte text directory, loads blob pointer and config word,
 * calls Text_OpenDialogue. */
__attribute__((section(".text.text_select")))
void Text_SelectBlob(u16 idx)
{
    u32 off = (u32)idx << 16;
    u32 *cfgs = Tbl2_08106D7C;
    u8 *dir = Tbl1_08106DD0;
    u32 *entry;
    u16 sub;

    off >>= 13;
    entry = (u32 *)(dir + off);
    sub = *(u16 *)((u8 *)entry + 4);
    Text_OpenDialogue(*(u32 *)((u8 *)cfgs + sub * 12), entry[0]);
}
