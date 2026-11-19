/* Sub_08024C14 @ 0x08024C14 (42 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w34c_08024c14_MATCHED.c (registry: staging/wave34_C/w34c_08024c14_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 sub_08025B60(u8 *p, u8 a, u8 b);

u16 sub_08024C14(u8 *s, u8 a, u8 b)
{
    u32 base = *(u32 *)(s + 20);
    register u32 off = 216 << 1;
    register u8 *p;
    register u8 v;
    u32 idx;
    
    p = (u8 *)(base + off);
    v = *p;
    idx = v * 144;
    return sub_08025B60((u8 *)(base + idx), a, b);
}
