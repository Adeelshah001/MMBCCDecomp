/* Sub_0801F9A4 @ 0x0801F9A4 (72 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_0801f9a4_MATCHED.c (registry: mmbcc/src/w35c_0801f9a4_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_0801F1D8(u8 *q);

extern void sub_0800D9FC(u8 *s);

void sub_0801F9A4(u8 *s)
{
    u8 v = s[119] - 3;
    if (v <= 1) {
        u8 *q = *(u8 **)(s + 40);
        if ((u8)sub_0801F1D8(q) == 0) {
            u8 *p2 = *(u8 **)(s + 44);
            p2[0]++;
        }
        {
            register u32 *tbl = (u32 *)0x082243d8;
            register u8 idx = s[9];
            register u32 off = idx << 2;
            u32 *ent;
            
            ent = (u32 *)(off + (u32)tbl);
            *(u32 *)(s + 12) = 2;
            *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 8);
        }
    }
    sub_0800D9FC(s);
}
