/* sub_08047CC0 @ 0x08047CC0 (36 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_08047cc0.c (registry: src/w20c_08047cc0.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004F18(void);

extern void sub_08004F80(void);

u32 sub_08047CC0(u8 *s)
{
    u8 v = s[0xc];
    register u32 off = 0x46B4;
    u8 *p = s + off;
    off = 0;
    *p = v;
    s[4] = 1;
    s[5] = (u8)off;
    sub_08004F18();
    sub_08004F80();
    return 0;
}
