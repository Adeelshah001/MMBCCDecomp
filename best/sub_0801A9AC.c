/* Sub_0801A9AC @ 0x0801A9AC (76 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36e_0801a9ac_MATCHED.c (registry: mmbcc/src/w36e_0801a9ac_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void _call_via_r1(u8 *s, u32 *ent);

extern void sub_0801A9F8(u8 *s);

void sub_0801A9AC(u8 *s)
{
    u8 f;
    {
        register u32 *tbl = (u32 *)0x082243d8;
        register u8 idx = s[9];
        register u32 off = idx << 2;
        u32 *ent;
        
        ent = (u32 *)(off + (u32)tbl);
        *(u32 *)(s + 12) = 1;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 4);
    }
    *(u32 *)(s + 108) = 0;
    f = 2;
    f |= s[10];
    s[10] = f | 1;
    {
        register u32 *tbl2 = (u32 *)0x082265c4;
        register u8 idx2 = s[16];
        register u32 off2 = idx2 << 2;
        u32 *ent2;
        
        ent2 = (u32 *)(off2 + (u32)tbl2);
        _call_via_r1(s, *ent2);
    }
    sub_0801A9F8(s);
}
