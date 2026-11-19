/* FillPairs @ 0x0800C92C (56 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern u8 gUnknown_02003670[];

void sub_0800C92C(u8 dummy, u16 *dst, u16 n)
{
    u8 v = gUnknown_02003670[0];
    u16 c = 0xFFF8;
    s16 i = 0;
    if (i >= n)
        return;
    do {
        *dst++ = v;
        *dst++ = c;
        i++;
    } while (i < n);
}
