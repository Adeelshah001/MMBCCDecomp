/* Sub_08016C94 @ 0x08016C94 (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08016c94_MATCHED.c (registry: mmbcc/src/w37c_08016c94_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_0800D9EC(u8 *s, int idx);

extern u16 sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, int v);

extern void sub_0800D9FC(u8 *s);

void sub_08016C94(u8 *s)
{
    u8 *q = s + 124;
    u8 mode = s[14];
    switch (mode) {
    case 0:
        sub_0800D9EC(s, 0);
        s[33] = 60;
        s[18] = mode;
        s[14]++;
        break;
    case 1:
        s[18]++;
        if (s[18] <= 19)
            break;
        sub_0800D9EC(s, 2);
        s[14]++;
        break;
    case 2:
        if (sub_08011F50(s) == 0)
            break;
        sub_0800D9EC(s, 0);
        s[10] &= 0xfe;
        s[14]++;
        break;
    case 3:
        s[18]++;
        if (s[18] <= 49)
            break;
        q[4] = 0;
        sub_08011F68(s, 0);
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
