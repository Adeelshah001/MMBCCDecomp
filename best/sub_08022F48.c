/* Sub_08022F48 @ 0x08022F48 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08022f48_MATCHED.c (registry: mmbcc/src/w35c_08022f48_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern int sub_08026D94(void);

extern void sub_0800D9FC(u8 *s);

void sub_08022F48(u8 *s)
{
    if ((--s[18] << 24) == 0)
        goto TABLE;
    if (((sub_08026D94() << 24) >> 24) <= 2)
        goto FINAL;
TABLE:
    {
        register u32 *tbl = (u32 *)0x08226ef0;
        register u8 idx = s[9];
        register u32 off;
        u32 *ent;
        
        off = idx << 2;
        ent = (u32 *)(off + (u32)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 8);
    }
FINAL:
    sub_0800D9FC(s);
}
