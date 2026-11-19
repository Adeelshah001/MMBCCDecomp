/* Sub_08024B3C @ 0x08024B3C (138 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08024b3c_MATCHED.c (registry: mmbcc/src/w36d_08024b3c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

extern u32 sub_080248C4(u32 a, u32 b);

extern u32 sub_08024918(u32 a, u32 b, u32 c);

extern u32 sub_08024A30(u32 a, u32 b, u32 c);

extern u32 sub_0802493C(u32 a, u32 b);

extern u32 sub_080249B8(u32 a, u32 b, u32 c);

u16 sub_08024B3C(u8 a0, u8 a1, u8 a2, u8 a3)
{
    u32 base = 0x02007090;
    s32 key = (a2 << 1) | a0;
    u32 rv;
    if (key == 1)
        goto case1;
    if (key > 1)
        goto gt;
    if (key == 0)
        goto case0;
    goto def;
gt:
    if (key == 2)
        goto case2;
    if (key == 3)
        goto case3;
    goto def;
case0:
    if (a1 == a3)
        rv = sub_080248C4(base, a3);
    else
        rv = sub_08024918(base, a1, a3);
    goto ret;
case1:
    rv = sub_08024A30(base, a3, a1);
    goto ret;
case2:
    rv = sub_08024A30(base, a1, a3);
    goto ret;
case3:
    if (a1 == a3)
        rv = sub_0802493C(base, a3);
    else
        rv = sub_080249B8(base, a1, a3);
    goto ret;
ret:
    return (u16)rv;
def:
    return 0;
}
