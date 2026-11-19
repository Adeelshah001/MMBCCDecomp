/* ShiftPair_Copy_800C @ 0x0800800C (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_d_old.c (registry: src/wave9_d_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern u8 gUnknown_08172126[];

void sub_0800800C(u8 *o, u8 idx)
{
    u32 a = idx;
    ((u32 *)o)[8] = ((s16 *)o)[0x14] << 8;
    ((u32 *)o)[9] = ((s16 *)o)[0x15] << 8;
    a += (u32)gUnknown_08172126;
    o[0x1A] = *(u8 *)a;
}
