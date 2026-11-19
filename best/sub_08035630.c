/* Sub_08035630 @ 0x08035630 (520 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w126a_08035630_MATCHED.c (registry: src/w126a_08035630_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 gUnknown_0822EA88[];

extern u16 gUnknown_02002F50[];

void sub_08035BC8(u8 *s);

void sub_08035DA4(u8 *s);

void sub_0804A378(int x);

void sub_08035AFC(u8 *s);

void sub_08035C5C(u8 *s);

int sub_08035630(u8 *s)
{
    int key = 0;
    int ret = 0;
    u8 max = gUnknown_0822EA88[s[20]];
    /* kp is gEwram_02002F50 (extern array, .set below) */

    if ((gUnknown_02002F50[0] & 0x20) != 0) {
        if ((gUnknown_02002F50[3] & 0x20) != 0)
            key = 0x20;
    }
    if ((gUnknown_02002F50[0] & 0x10) != 0) {
        if ((gUnknown_02002F50[3] & 0x10) != 0)
            key = 0x10;
    }
    if ((gUnknown_02002F50[0] & 0x40) != 0) {
        if ((gUnknown_02002F50[2] & 0x40) != 0)
            key = 0x40;
    }
    if ((gUnknown_02002F50[0] & 0x80) != 0) {
        if ((gUnknown_02002F50[2] & 0x80) != 0)
            key = 0x80;
    }
    if ((gUnknown_02002F50[0] & 0x02) != 0) {
        if ((gUnknown_02002F50[2] & 0x02) != 0)
            key = 0x02;
    }
    if ((gUnknown_02002F50[0] & 0x08) != 0) {
        if ((gUnknown_02002F50[2] & 0x08) != 0)
            key = 0x08;
    }
    if ((gUnknown_02002F50[0] & 0x100) != 0) {
        if ((gUnknown_02002F50[2] & 0x100) != 0)
            key = 0x100;
    }

    switch (key) {
    case 64:
    case 128:
        if (max > 12) {
            if ((s8)s[0x46aa] > 12) {
                if ((s8)(s[0x46aa] -= 13) < 0)
                    s[0x46aa] = 0;
            } else {
                s[0x46aa] += 13;
                if ((s8)s[0x46aa] > max - 1)
                    s[0x46aa] = max - 1;
            }
            sub_08035BC8(s);
        }
        break;
    case 32:
        if ((s8)--s[0x46aa] < 0)
            s[0x46aa] = max - 1;
        sub_08035BC8(s);
        break;
    case 16:
        s[0x46aa]++;
        if ((s8)s[0x46aa] >= max) {
            s[0x46aa] = max - 1;
            sub_08035DA4(s);
            s[0x46ac] = 28;
            sub_0804A378(0x77);
            sub_08035AFC(s);
            sub_08035C5C(s);
        } else {
            sub_08035BC8(s);
        }
        break;
    case 2: {
        u8 *p = s + 0x46a8;
        u8 z = 0;
        *p = 3;
        s[0x46a9] = z;
        sub_0804A378(0x67);
        ret = 1;
        break;
    }
    case 8:
        s[0x46a8] = 0;
        s[0x46a9] = 0;
        sub_0804A378(0x67);
        ret = 1;
        break;
    case 256:
        sub_08035DA4(s);
        s[0x46ac] = 28;
        sub_0804A378(0x77);
        sub_08035AFC(s);
        sub_08035C5C(s);
        break;
    default:
        break;
    }
    return ret;
}
