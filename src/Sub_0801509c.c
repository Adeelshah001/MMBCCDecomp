/* Sub_0801509c @ 0x0801509C (256 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w56d_0801509c_MATCHED.c (registry: src/w56d_0801509c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

typedef struct { s16 a; s16 b; } T2;

extern void sub_0800DD2C(u8 *s, int a, int b);

extern void sub_0800D9EC(u8 *s, int idx);

extern u16 sub_08011F50(u8 *s);

extern void sub_0801CD50(int a, int b, int c, s16 d, s16 e, u32 f);

extern u8 sub_08017474(u32 v);

extern void sub_08017464(u32 v);

extern void sub_08011F68(u8 *s, int v);

extern void sub_0800D9FC(u8 *s);

void Sub_0801509c(u8 *s)
{
    u8 *p = s + 124;
    u32 s44;
    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, -15360, 0);
        sub_0800D9EC(s, 11);
        goto inc;
    case 1:
        if ((u16)sub_08011F50(s) != 0) {
            sub_0800D9EC(s, 9);
            goto inc;
        }
        break;
    case 2:
        if ((u16)sub_08011F50(s) != 0) {
            int nib;
            T2 *tbl;
            T2 t;
            nib = ((unsigned)s[35] << 28) >> 28;
            tbl = (T2 *)0x08223ed8;
            
            t = tbl[p[0]];
            sub_0801CD50(1, 0, nib, t.a, t.b, *(u32 *)(s + 44));
            sub_0800D9EC(s, 10);
            goto inc;
        }
        break;
    case 3:
        if ((u16)sub_08011F50(s) == 0)
            goto tail;
    inc:
        s[14]++;
        goto tail;
    case 4:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            sub_08017464(*(u32 *)(s + 44));
            *(u32 *)(s + 44) = 0;
            sub_0800DD2C(s, -15360, 0);
            sub_0800D9EC(s, 0);
            p[4] = 0;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    goto tail;
tail:
    sub_0800D9FC(s);
}
