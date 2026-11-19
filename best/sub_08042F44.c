/* Sub_08042F44 @ 0x08042F44 (1260 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w194f_08042f44_MATCHED.c (registry: src/w194f_08042f44_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u16 gUnknown_02002F50[];

extern u8 gUnknown_02004D14[];

extern u8 gUnknown_02004CE0[];

extern void sub_0804A378(int a);

extern void sub_080248AC(int a);

extern void sub_08043630(u8 *s);

extern void sub_0800800C(u8 *a, int b);

extern void sub_08007378(int a, int b, int c, int d);

int sub_08042F44(u8 *s)
{
    int ret = 0;
    int sel = 0;
    int aa;

    if (gUnknown_02002F50[0] & 0x200)
        sel = (gUnknown_02002F50[3] & 0x200) ? 0x200 : 0;
    if (gUnknown_02002F50[0] & 0x100 && gUnknown_02002F50[3] & 0x100)
        sel = 0x100;
    if (gUnknown_02002F50[0] & 0x40 && gUnknown_02002F50[2] & 0x40)
        sel = 0x40;
    if (gUnknown_02002F50[0] & 0x80 && gUnknown_02002F50[2] & 0x80)
        sel = 0x80;
    if (gUnknown_02002F50[0] & 1 && gUnknown_02002F50[2] & 1)
        sel = 1;
    if (gUnknown_02002F50[0] & 2 && gUnknown_02002F50[2] & 2)
        sel = 2;

    aa = s[0x46aa];
    if (aa == 1)
        goto Lcase1;
    if (aa > 1)
        goto Ldef;
    if (aa == 0)
        goto Lcase0;
    goto Ltail;
Ldef:
    if (aa > 4)
        goto Ltail;
    if (s[0x46ab] == 0)
        goto Ldef0;
    if (s[0x46ab] == 1)
        goto Ldef1;
    goto Ltail;
Lcase0:

        switch (sel) {
        case 0x40:
            if ((s[0x46a9] & 0xf) != 0) {
                sub_0804A378(0x66);
                s[0x46a9]--;
                sub_080248AC(s[0x46a9] & 0xf);
                s[0x46b0] = 3;
                s[0x46b1] = 1;
                s[0x46a8] &= 0xe0;
                sub_08043630(s);
            }
            break;
        case 0x80: {
            unsigned int t = 0;
            if (s[0x15] > 7)
                t = 2;
            else if (s[0x15] > 4)
                t = 1;
            if ((s[0x46a9] & 0xf) < t) {
                sub_0804A378(0x66);
                s[0x46a9]++;
                sub_080248AC(s[0x46a9] & 0xf);
                s[0x46b0] = 3;
                s[0x46b1] = 1;
                s[0x46a8] &= 0xe0;
                sub_08043630(s);
            }
            break;
        }
        case 1:
            sub_0804A378(0x67);
            s[0x46aa] = sel;
            s[0x46ab] = aa;
            s[0x46a9] &= 0xf;
            sub_08043630(s);
            break;
        case 2:
            sub_0804A378(0x68);
            sub_080248AC(s[0x16]);
            ret = 5;
            sub_08043630(s);
            break;
        default:
            break;
        }
        { u8 *d = gUnknown_02004CE0; *(u16 *)(d + 0x28) = 0x10; *(u16 *)(d + 0x2a) = ((s[0x46a9] & 0xf) << 4) + 0x18; }
        goto Ltail;
Lcase1:
    if (s[0x46ab] == 0)
        goto Lab0;
    if (s[0x46ab] == 1)
        goto Lsel1;
    goto Ltail;
Lab0: {
            register u8 f = gUnknown_02004D14[0x2c] | 1;
            register int c = 0x18;
            *(u16 *)(gUnknown_02004D14 + 0x28) = c;
            c = 0x58;
            *(u16 *)(gUnknown_02004D14 + 0x2a) = c;
            f &= (c -= 0x77);
            f &= (c -= 2);
            gUnknown_02004D14[0x2c] = f;
            { int m = 0xfffffc3f; *(u16 *)(gUnknown_02004D14 + 0x2c) &= m; }
            sub_0800800C(gUnknown_02004D14, 0);
            s[0x46ab]++;
    }
Lsel1:

            switch (sel) {
            case 0x40:
                if ((s[0x46a9] >> 4) != 0) {
                    sub_0804A378(0x66);
                    s[0x46a9] -= 0x10;
                }
                break;
            case 0x80:
                if ((s[0x46a9] >> 4) == 0) {
                    sub_0804A378(0x66);
                    s[0x46a9] += 0x10;
                }
                break;
            case 1:
                sub_0804A378(0x67);
                if ((s[0x46a9] >> 4) == 0) {
                    { int f1 = gUnknown_02004D14[0x2c]; f1 &= ~1; gUnknown_02004D14[0x2c] = (u8)f1; }
                    ret = 2;
                } else {
                    int v = (s[0x46a9] & 0xf) + 2;
                    u8 *p = s + 0x46aa;
                    int z = 0;
                    *p = v;
                    s[0x46ab] = z;
                    { int f1 = gUnknown_02004D14[0x2c]; f1 &= ~1; gUnknown_02004D14[0x2c] = (u8)f1; }
                }
                sub_08043630(s);
                break;
            case 2:
                sub_0804A378(0x67);
                s[0x46aa] = 0;
                s[0x46ab] = 0;
                { int f1 = gUnknown_02004D14[0x2c]; f1 &= ~1; gUnknown_02004D14[0x2c] = (u8)f1; }
                sub_08043630(s);
                break;
            default:
                break;
            }
            { u8 *d = gUnknown_02004D14; *(u16 *)(d + 0x28) = 0x18; *(u16 *)(d + 0x2a) = ((s[0x46a9] >> 4) << 4) + 0x58; }
            goto Ltail;
Ldef0: {
            register u8 f = gUnknown_02004D14[0x2c] | 1;
            register int c = 0x48;
            *(u16 *)(gUnknown_02004D14 + 0x28) = c;
            c = 0x7c;
            *(u16 *)(gUnknown_02004D14 + 0x2a) = c;
            f &= (c -= 0x9b);
            f &= (c -= 2);
            gUnknown_02004D14[0x2c] = f;
            { int m = 0xfffffc3f; *(u16 *)(gUnknown_02004D14 + 0x2c) = (*(u16 *)(gUnknown_02004D14 + 0x2c) & m) | 0xc0; }
            sub_0800800C(gUnknown_02004D14, 3);
            sub_08007378(0, 7, ((s[0x16] << 17) + 0x30000) >> 16, 2);
            s[0x16] = s[0x46a9] & 0xf;
            sub_08043630(s);
            s[0x46ab]++;
    }
    /* fall through to Ldef1 */
Ldef1:

            if (sel & 1) {
                sub_08007378(1, 7, ((s[0x16] << 17) + 0x30000) >> 16, 2);
                sub_0804A378(0x67);
                { int f1 = gUnknown_02004D14[0x2c]; f1 &= ~1; gUnknown_02004D14[0x2c] = (u8)f1; }
                { u8 *p = s + 0x46aa; register int z = 0; *p = z; s[0x46ab] = z; }
                sub_08043630(s);
            }
            goto Ltail;
Ltail:
    if (sel == 0x100)
        goto Ltail100;
    if (sel != 0x200)
        goto LtailEnd;
    {
        s8 *p;
        if ((s[0x46a8] & 0x1f) == 0)
            goto LtailEnd;
        sub_0804A378(0x66);
        p = (s8 *)(s + 0x46b1);
        s[0x46b1] = (*p <= 1) ? 1 : 2;
        s[0x46a8]--;
        if ((s[0x46a8] & 0x1f) == 0) {
            p = (s8 *)(s + 0x46b0);
            s[0x46b0] = (*p > 1) ? 3 : 0;
        }
        sub_08043630(s);
        goto LtailEnd;
    }
Ltail100:
    {
        s8 *p;
        if ((s[0x46a8] & 0x1f) > 0x16)
            goto LtailEnd;
        sub_0804A378(0x66);
        p = (s8 *)(s + 0x46b0);
        s[0x46b0] = (*p <= 1) ? 1 : 2;
        s[0x46a8]++;
        if ((s[0x46a8] & 0x1f) == 0x17) {
            p = (s8 *)(s + 0x46b1);
            s[0x46b1] = (*p > 1) ? 3 : 0;
        }
        sub_08043630(s);
    }
LtailEnd:
    return ret;
}
