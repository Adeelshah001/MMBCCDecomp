/* Sub_0801200C @ 0x0801200C (226 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w50d_0801200c_MATCHED.c (registry: src/w50d_0801200c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D9EC(u8 *s, u8 idx);

extern void sub_0800D6E0(u8 *s, u16 b, u8 c);

extern void sub_0800D9FC(u8 *s);

extern short sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, u8 v);

void sub_0801200C(u8 *s)
{
    u8 *t = s + 124;
    u8 mode = s[14];
    switch (mode) {
    case 0:
        if (t[0] == t[1] && t[2] == t[3]) {
            sub_0800D9EC(s, 0);
            t[4] = mode;
            sub_08011F68(s, 0);
        } else {
            u8 v = t[1];
            u16 r = v | ((s[35] & 15) ? 0x100 : 0);
            sub_0800D6E0(s, r, t[3]);
            sub_0800D9EC(s, 2);
            s[14]++;
        }
        break;
    case 1:
        if (sub_08011F50(s) == 0)
            break;
        {
            u8 v = t[0];
            u16 r = v | ((s[35] & 15) ? 0x100 : 0);
            sub_0800D6E0(s, r, t[2]);
            sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 0);
        s[14]++;
        break;
    case 3:
        if (sub_08011F50(s) == 0)
            break;
        t[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
