/* EwGet8_A8 @ 0x080247A8 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ew02007090 { u8 _00[18]; u16 f18; };

extern struct Ew02007090 gUnknown_02007090;

u8 sub_080247A8(u8 idx)
{
    register u32 i = idx;
    u8 *ew = (u8 *)&gUnknown_02007090;
    if (i > 248)
        return 0;
    return *(u8 *)(*(u32 *)(ew + 4) + i);
}
