/* Sub_08007798 @ 0x08007798 (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_08007798_MATCHED.c (registry: src/w36bulk_08007798_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08006374(u8 *ctx, s8 a, s8 b, int c, int d, int e, u8 f, u32 g);

extern void sub_08006124(s8 a, s8 b, int c, int d, int e, u8 f);

void sub_08007798(u8 a, u8 b, u8 c, u8 d)
{
    if (d != 0) {
        u8 *tblA = (u8 *)0x08172074;
        u32 idx;
        u32 r4;
        
        idx = ((*(u32 *)0x02003670 >> 3) & 3);
        tblA += 4;
        {
            u8 *addr = (u8 *)(idx + (u32)tblA);
            u8 *tblB = (u8 *)0x08170e7c;
            u8 byte;
            
            byte = *addr;
            r4 = *(u32 *)(tblB + byte * 4);
        }
        sub_08006374((u8 *)0x0200483c, (s8)(a - 2), (s8)b, 2, 2, 53, c, r4);
    } else {
        sub_08006124((s8)(a - 2), (s8)b, 2, 2, 50, c);
    }
}
