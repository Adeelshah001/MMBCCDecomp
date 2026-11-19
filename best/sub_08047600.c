/* CopyHdr_Dispatch @ 0x08047600 (40 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave4_i_old.c (registry: src/wave4_i_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_0200B7A8[];

extern u32 gUnknown_08233AFC[];

/* 0x08047600: *(u16*)s=*(u16*)(p+4); return (s8)tbl[p[0]](p);
 * p=(u8*)0x0200B7A8. Tentative. */
s8 sub_08047600(u8 *s)
{
    u8 *dst = s;
    u8 *p = gUnknown_0200B7A8;
    *(u16 *)dst = *(u16 *)(p + 4);
    {
        u32 *tbl = gUnknown_08233AFC;
        u32 idx = p[0];
        return (s8)((u32 (*)(u8 *))tbl[idx])(p);
    }
}
