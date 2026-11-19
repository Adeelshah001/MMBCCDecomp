/* Sub_08016988 @ 0x08016988 (780 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w149c_08016988_MATCHED.c (registry: src/w149c_08016988_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_080174A4(u32 a, int b);

extern void sub_0800DD2C(u8 *a, u32 b, int c);

extern void sub_0800D9EC(u8 *a, int b);

extern u8 sub_08017474(u32 a);

extern void sub_08017478(u32 a, int b);

extern void sub_08017464(u32 a);

extern u16 sub_08011F50(u8 *a);

extern void sub_08011F68(u8 *a, int b);

extern void sub_0801EE14(int a, int b, int c, u32 d, int e);

extern void sub_0800D9FC(u8 *a);

extern void sub_0804A378(int a);

extern u8 gUnknown_02003670[];

void Sub_08016988(u8 *s)
{
    u8 *q = s + 0x7c;

    switch (s[0xe]) {
    case 0:
        if (q[7] == 0)
            sub_080174A4(*(u32 *)(s + 0x2c), 0);
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 0);
        s[0x12] = 0;
        if (q[7] == 0)
            s[0xe]++;
        else
            s[0xe] = 5;
        break;
    case 1:
        s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
        s[0x25] = 0;
        { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
        if (s[0x12] == 0xf) {
            int z = 0;
            s[0x13] = z;
            s[0xe]++;
        } else {
            s[0x12]++;
        }
        break;
    case 2:
        if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) > 6)
            s[0xe]++;
        else
            s[0x13]++;
        break;
    case 3:
        s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
        s[0x25] = 0;
        { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
        if (s[0x12] == 0)
            s[0xe]++;
        else
            s[0x12]--;
        break;
    case 5:
        if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) != 0) {
            { int t = s[0x24] | 1; { int m = ~0x1e; s[0x24] = t & m; } }
            s[0x25] = 0;
            { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
            if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) > 6) {
                s[0xe] = 5;
            } else {
                u8 *g = gUnknown_02003670;
                g += 0x11af;
                *g = (*g & 0xf) | 0x40;
                s[0x21] = 6;
                sub_0800D9EC(s, 3);
                s[0xe]++;
            }
        } else {
            s[0x24] |= 1; { int sh = (s[0x12] & 0xf) << 1; int m = ~0x1e; s[0x24] = (s[0x24] & m) | sh; }
            s[0x25] = 0;
            { u16 v = 0x4210; *(u16 *)(s + 0x26) = v; }
            if (s[0x12] <= 0xe)
                s[0x12]++;
        }
        break;

    case 6:
        if ((u16)sub_08011F50(s) == 0)
            break;
        if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) > 1) {
            if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) <= 5) {
                s[0x21] = 6;
                sub_0800D9EC(s, 3);
                break;
            }
        }
        if (q[7] != 2) {
            s[0xe]++;
        } else {
            sub_0800D9EC(s, 7);
            s[0xe] = 9;
        }
        break;
    case 7:
        if ((u16)sub_08011F50(s) != 0) {
            sub_0800D9EC(s, 0);
            s[0xe]++;
        }
        break;
    case 8:
        if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) <= 6)
            break;
    case 4:
        sub_08017478(*(u32 *)(s + 0x2c), 8);
        sub_08017464(*(u32 *)(s + 0x2c));
        *(u32 *)(s + 0x2c) = 0;
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 0);
        q[4] = 0;
        sub_08011F68(s, 0);
        break;
    case 9: {
        u8 *p = s + 0x21;
        int z = 0;
        *p = 0x3c;
        s[0x12] = 0x28;
        sub_0801EE14(0, ~3, (int)(((unsigned)(s[0x23] << 28)) >> 28), 0xffffc400, z);
        s[0xe]++;
        break;
    }
    case 10:
        s[0x12]--;
        if (s[0x12] == 0) {
            sub_0800D9EC(s, 2);
            sub_0804A378(0x7f);
            s[0xe]++;
        }
        break;
    case 11:
        if ((u8)sub_08017474(*(u32 *)(s + 0x2c)) > 6) {
            int t = s[0xa] & 0xfe;
            { int z = 0;
            s[0xa] = t;
            sub_08017478(*(u32 *)(s + 0x2c), 8);
            sub_08017464(*(u32 *)(s + 0x2c));
            *(u32 *)(s + 0x2c) = z;
            sub_0800DD2C(s, 0xffffc400, 0);
            sub_0800D9EC(s, 0);
            q[4] = z;
            sub_08011F68(s, 0);
            }
        }
        break;
    default:
        break;
    }
    sub_0800D9FC(s);
}
