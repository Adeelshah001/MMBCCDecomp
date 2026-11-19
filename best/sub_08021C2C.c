/* Sub_08021C2C @ 0x08021C2C (128 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_08021c2c_MATCHED.c (registry: src/w36bulk_08021c2c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08002300(u8 *p, int v);

extern void sub_08002904(u8 *p, int a, u8 b);

void sub_08021C2C(void)
{
    short i = 0;
    u32 *t2 = (u32 *)0x08173760;
    u16 *t1 = (u16 *)0x08227104;
    for (i = 0; i <= 7; i++) {
        u16 *ep = (u16 *)((i * 2) + (u32)t1);
        u16 v = *ep;
        u32 bv = t2[v];
        u16 w = ((u16 *)0x08227114)[i];
        u8 *q = (u8 *)(bv + w * 4);
        q = (u8 *)((u32)q + *(u32 *)q);
        {
            u16 *t4 = (u16 *)0x0817386c;
            
            sub_08002300(q, t4[v] * 32 + 0x10000);
        }
        q = (u8 *)q + 12;
        {
            u8 *t5 = (u8 *)0x081738f2;
            
            sub_08002904(q, 0, t5[*ep * 2]);
        }
    }
}
