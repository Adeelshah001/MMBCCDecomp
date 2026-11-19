/* Gfx_BlitRequest @ 0x08006A54 (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/gfx.c (registry: src/gfx.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern u8 gUnknown_02004830[];

void sub_08006AD8(u32 ctx, u32 a, s16 b, s16 c, s8 d, u8 e);

void sub_08006A54(u32 a, u16 b, u16 c, u8 d, u8 e)
{
    u8 *ctx = gUnknown_02004830;

    if (*(ctx + 0x265) != 0)
        return;
    sub_08006AD8((u32)ctx, a, b, c, d, e);
}
