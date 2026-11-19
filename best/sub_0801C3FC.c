/* ChipInit_0801C3FC @ 0x0801C3FC (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0801c3fc.c (registry: src/w15c_0801c3fc.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D770(u8 *p, u16 x, u8 y);

extern void sub_0800D9EC(u8 *p, u8 x);

void sub_0801C3FC(u8 *p)
{
    u8 b;
    sub_0800D770(p, 0x82a, 0);
    sub_0800D9EC(p, 0);
    b = p[10];
    b &= 253;
    b &= 254;
    p[10] = b;
}
