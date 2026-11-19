/* SlotClear_0801787C @ 0x0801787C (44 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w20c_0801787c.c (registry: src/w20c_0801787c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08017464(u8 *s);

void sub_0801787C(u8 *s)
{
    sub_08017464(*(u8 **)(s + 44));
    *(u32 *)(s + 44) = 0;
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
