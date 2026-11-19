/* SlotCopy_0801E14C @ 0x0801E14C (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_0801e14c.c (registry: src/w20c_0801e14c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 sub_08010F88(u8 x);

void sub_0801E14C(u8 *s)
{
    sub_08010F88(s[16]);
    {
        register u32 base = 0x082243D8;
        register u32 idx;
        u32 off;
        u32 *p;
        
        idx = s[9];
        off = idx << 2;
        {
            u32 addr = off + base;
            *(u32 *)(s + 12) = 4;
            p = *(u32 **)addr;
        }
        *(u32 *)(s + 20) = p[4];
    }
}
