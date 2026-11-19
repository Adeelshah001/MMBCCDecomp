/* ObjInit_08016EFC @ 0x08016EFC (120 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26d_08016efc.c (registry: src/w26d_08016efc.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern s16 gUnknown_08223ED8[];

extern void sub_08017458(u8 *s);

extern void sub_08011F68(u8 *s, u8 v);

void sub_080174CC(u8 *s, s16 b, s16 c);

void sub_08016EFC(u8 *p, u8 a, u8 b, u8 *s, u16 e, u8 f)
{
    u8 *sl = p + 124;
    u8 aa = a;
    u8 bb = b;
    u8 ff = f;

    *(u8 **) (p + 44) = s;
    sub_08017458(s);
    {
        s16 *base = gUnknown_08223ED8;
        s16 *tbl = base + (sl[0] * 2);
        s16 v1 = tbl[0];
        s16 v2 = tbl[1];
        sub_080174CC(s, v1, v2);
    }
    p[16] = aa;
    p[17] = bb;
    sub_08011F68(p, 4);
    sl[4] = 1;
    *(u16 *) (sl + 8) = e;
    sl[7] = ff;
}
