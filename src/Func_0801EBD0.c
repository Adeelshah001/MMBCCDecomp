/* Func_0801EBD0 @ 0x0801EBD0 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50b_0801ebd0_MATCHED.c (registry: src/w50b_0801ebd0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void Func_0801EBD0(u8 *s) {
    u32 **base = (u32 **)0x082243D8;
    register u32 idx;
    u32 *slot;
    s[10] &= 0xFE;
    
    idx = (u32)(s[9] << 2);
    idx += (u32)base;
    slot = (u32 *)idx;
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = ((u32 *)*slot)[4];
}
