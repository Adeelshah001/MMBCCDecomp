/* Sub_080173BC @ 0x080173BC (24 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40c_080173bc_MATCHED.c (registry: mmbcc/src/w40c_080173bc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_080173BC(u8 *s)
{
    register u32 base = 0x082243D8;
    register u32 idx;
    u32 off;
    u32 *e;
    
    idx = s[9];
    off = idx << 2;
    e = (u32 *)(off + base);
    *(u32 *)(s + 12) = 4;
    *(u32 *)(s + 20) = *(u32 *)(*e + 16);
}
