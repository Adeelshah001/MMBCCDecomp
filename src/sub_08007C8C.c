/* Apply_08007c8c @ 0x08007C8C (80 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08007c8c_MATCHED.c (registry: mmbcc/src/w36a_08007c8c_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern u32 sub_08024670(u16 idx);

extern u32 sub_0802468C(u16 idx);

extern void sub_08005274(u8 *s, u32 a, u32 b);

extern void sub_08007EEC(u16 idx);

extern u16 gUnknown_08171EF4[];

void sub_08007C8C(u16 a, u8 flag)
{
    u16 v = sub_08024670(a);
    u8 *e = (u8 *)0x0832b6c0 + v * 20;
    s16 w = sub_0802468C(a);
    sub_08005274(e, w, gUnknown_08171EF4[1]);
    if (flag != 0)
        sub_08007EEC(0);
}
