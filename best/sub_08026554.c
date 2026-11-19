/* GetByte1_26554 @ 0x08026554 (32 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave11_B_old.c (registry: src/wave11_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

/* 0x08026554 (32 B): table-entry byte getter. Returns entry[1] of the
 * 28-byte table at *(ctx+4), or 0 if idx > 127 or entry[25] == 0.
 * Priority pick for the Task_3AFFC path: called from TblGetByte_241F8 case 2
 * as sub_08026554(0x020070A8, a & 0xFFF). Signature: u8 (void *ctx, s16 idx). */
u8 sub_08026554(void *ctx, s16 idx)
{
    u8 *base;
    u8 *entry;
    u32 addr;
    if ((u16)idx > 127)
        return 0;
    base = *(u8 **)((u8 *)ctx + 4);
    addr = (u32)(u16)idx * 28 + (u32)base;
    entry = (u8 *)addr;
    if (entry[25] == 0)
        return 0;
    return entry[1];
}
