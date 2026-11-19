/* F_08024EE0 @ 0x08024EE0 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_B_old.c (registry: src/wave15_B_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


struct Ew02007090 { u8 _00[20]; u8 *f20; };

extern struct Ew02007090 gUnknown_02007090;

extern u16 sub_08025790(u8 *p);

u16 sub_08024EE0(void)
{
    u8 *base = gUnknown_02007090.f20;
    u8 idx = *(base + (0xD8 << 1));
    return (u16)sub_08025790(base + idx * 144);
}
