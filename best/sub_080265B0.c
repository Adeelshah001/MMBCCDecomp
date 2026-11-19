/* GetByte0_265B0 @ 0x080265B0 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_B_old.c (registry: src/wave11_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* 0x080265B0 (32 B): twin of 26554. Returns entry[0], or 49 if idx > 127
 * or entry[25] == 0. Called from TblGetByte_24384 case 2.
 * Signature: u8 (void *ctx, s16 idx). */
u8 sub_080265B0(void *ctx, s16 idx)
{
    u8 *base;
    u8 *entry;
    u32 addr;
    if ((u16)idx > 127)
        return 49;
    base = *(u8 **)((u8 *)ctx + 4);
    addr = (u32)(u16)idx * 28 + (u32)base;
    entry = (u8 *)addr;
    if (entry[25] == 0)
        return 49;
    return entry[0];
}
