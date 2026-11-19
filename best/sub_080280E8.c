/* Sub_080280E8 @ 0x080280E8 (108 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_080280e8_MATCHED.c (registry: mmbcc/src/w36b_080280e8_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800288C(u8 *p, int n);

extern void sub_0800E144(u8 *p);

extern void sub_08028154(int k, u16 b, u8 c);

void sub_080280E8(u8 a, u16 b, u8 c)
{
    sub_0800288C((u8 *)0x087109a0 + a * 20, 64);
    if (((s8 *)0x0200b7e0)[7] >= 0) {
        sub_0800E144((u8 *)0x0200b7e0 + 8);
    }
    if (c <= 14) {
        sub_08028154(2, b, c);
        sub_08028154(3, b, c);
        sub_08028154(4, b, c);
        sub_08028154(5, b, c);
    }
}
