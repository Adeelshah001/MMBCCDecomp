/* sub_08012D28 @ 0x08012D28 (340 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w70a_08012d28_MATCHED.c (registry: src/w70a_08012d28_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed int s32;

void sub_0800DD2C(u8 *o, s32 x, s32 y);

void sub_0800D9EC(u8 *s, u8 idx);

u16 sub_08011F50(u8 *s);

u16 sub_0804A378(u16 idx);

void sub_080174A4(u8 *s, u8 bit);

void sub_080178A8(u8 a, u8 b, u16 c, s32 d, u8 *e);

void sub_08017478(u8 *s, u8 v);

void sub_08017464(u8 *s);

void sub_08011F68(u8 *s, u8 v);

void sub_0800D9FC(u8 *s);

void sub_08012D28(u8 *s)
{
    u8 *q = s;
    q += 124;

    switch (s[14]) {
    case 0:
        sub_0800DD2C(s, 0xFFFFC400, 0);
        sub_0800D9EC(s, 2);
        sub_0804A378(152);
        s[14]++;
        break;
    case 1:
        if (sub_08011F50(s) != 0) {
            sub_0800DD2C(s, 0xFFFFFA00, 0);
            sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 2:
        if (sub_08011F50(s) != 0) {
            sub_0800D9EC(s, 9);
            s[14]++;
        }
        break;
    case 3:
        if (sub_08011F50(s) != 0) {
            u8 nib;
            sub_080174A4(*(u8 **)(s + 44), 3);
            nib = (u32)((s + 35)[0] << 28) >> 28;
            sub_080178A8(138, nib, 0x3C00, 0xFFFFEC00, *(u8 **)(s + 44));
            sub_0800D9EC(s, 10);
            s[14]++;
            sub_0804A378(123);
        }
        break;
    case 4:
        if (sub_08011F50(s) != 0) {
            sub_08017478(*(u8 **)(s + 44), 8);
            sub_0800D9EC(s, 2);
            s[14]++;
        }
        break;
    case 5:
        if (sub_08011F50(s) != 0) {
            sub_0800DD2C(s, 0xFFFFC400, 0);
            sub_0800D9EC(s, 1);
            s[14]++;
        }
        break;
    case 6:
        if (sub_08011F50(s) != 0) {
            sub_08017464(*(u8 **)(s + 44));
            *(u32 *)(s + 44) = 0;
            sub_0800DD2C(s, 0xFFFFC400, 0);
            sub_0800D9EC(s, 0);
            q[4] = 0;
            sub_08011F68(s, 0);
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
