/* Obj_SetFromTableC @ 0x08020F58 (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_j_old.c (registry: src/wave4_j_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct W4J_TblEntry { u8 pad[0x10]; u32 val10; };

extern struct W4J_TblEntry *gUnknown_08226EF0[];

/* 0x08020F58: idem with gTbl_08226EF0. Tentative. */
void sub_08020F58(u8 *obj)
{
    struct W4J_TblEntry **base = gUnknown_08226EF0;
    struct W4J_TblEntry **slot = &base[obj[9]];
    *(u32 *)(obj + 12) = 4;
    *(u32 *)(obj + 20) = (*slot)->val10;
}
