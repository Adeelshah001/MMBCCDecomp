/* Tbl_ClearEntries @ 0x08011170 (68 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave15_D.c (registry: src/wave15_D.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


 typedef signed short s16;

extern u32 sub_08016F98(u8 a);

extern u8 sub_08016FAC(u8 a, u8 b);

extern void sub_08002C74(u8 v);

void sub_08011170(u8 a)
{
    s16 n = (s16)sub_08016F98(a);
    u16 i;
    if (n <= 0)
        return;
    for (i = 0; (s16)i < n; ) {
        u32 t;
        sub_08002C74(sub_08016FAC(a, (u8)i));
        t = (u32)i << 16;
        t += 0x80 << 9;
        i = (u16)(t >> 16);
    }
}
