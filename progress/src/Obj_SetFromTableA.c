/* Obj_SetFromTableA @ 0x08011E98 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_j_old.c (registry: src/wave4_j_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct W4J_TblEntry { u8 pad[0x10]; u32 val10; };

extern struct W4J_TblEntry *gTbl_08223CC0[];

/* 0x08011E98: *(u32*)(obj+12)=4; *(u32*)(obj+20)=table[obj[9]]->val10.
 * Tentative.
 * The `base` + `&base[obj[9]]` two-statement shape is required for the
 * ROM's order (pool load, ldrb, lsls, adds, then the =4 store, then the
 * double deref). old_agbcc puts the index byte in r3; main agbcc uses r1.
 * Sections .text.w4j_objsetfromtablea/b/c. */
__attribute__((section(".text.w4j_objsetfromtablea")))
void Obj_SetFromTableA(u8 *obj)
{
    struct W4J_TblEntry **base = gTbl_08223CC0;
    struct W4J_TblEntry **slot = &base[obj[9]];
    *(u32 *)(obj + 12) = 4;
    *(u32 *)(obj + 20) = (*slot)->val10;
}
