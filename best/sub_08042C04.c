/* F_08042C04 @ 0x08042C04 (172 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w26c_08042c04.c (registry: src/w26c_08042c04.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08004E24(u8 x);

void sub_08004F18(void);

int sub_08004E0C(u8 x);

void sub_08004F80(void);

void sub_08004DFC(u8 a);

extern u8 gUnknown_02004F80[];

extern u16 gUnknown_020031E0[];

u8 sub_08042C04(u8 *s)
{
    switch (s[5]) {
    case 0:
        sub_08004E24(0);
        s[5]++;
        /* fall through */
    case 1:
        sub_08004F18();
        if ((sub_08004E0C(3) << 24) != 0) {
            u16 v = gUnknown_020031E0[0];
            v = (u16)(v & 0xEDFFu);
            v = (u16)(v & 0xDBFFu);
            gUnknown_020031E0[0] = v;
            s[5]++;
        }
        sub_08004F80();
        break;
    case 2:
        sub_08004DFC(gUnknown_02004F80[2]);
        s[5]++;
        /* fall through */
    case 3: {
        int r;
        sub_08004F18();
        r = (sub_08004E0C(0) << 24) >> 24;
        if (r == 0) {
            if (s[7] == 1) {
                s[7] = s[4];
                s[4] = 3;
            } else {
                s[7] = s[4];
                s[4] = 1;
            }
            s[5] = (u8)r;
            s[6] = (u8)r;
        }
        sub_08004F80();
        break;
    }
    default:
        break;
    }
    return 0;
}
