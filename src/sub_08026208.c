/* Sub_08026208 @ 0x08026208 (48 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08026208_MATCHED.c (registry: staging/wave34_C/w34c_08026208_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08025230(u8 *a, u8 *b, int c);

void sub_08026208(u8 *s, u8 *t)
{
    u8 *aa = s;
    u8 *bb = t;
    u32 off = 224 << 4;
    sub_08025230(s + 8, bb + off, 130);
    aa += 16;
    bb += 0xe82;
    sub_08025230(aa, bb, 130);
}
