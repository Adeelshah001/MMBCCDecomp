/* F_08015ac4 @ 0x08015AC4 (560 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w41c_08015ac4_MATCHED.c (registry: mmbcc/src/w41c_08015ac4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;
typedef signed int s32;

extern void sub_0800DD2C(u8 *s, u32 x, u8 y);

extern void sub_0800D9EC(u8 *s, u8 idx);

extern s32 sub_08017474(u32 p);

extern s32 sub_08011F50(u8 *s);

extern void sub_08011F68(u8 *s, u8 v);

extern void sub_08017478(u32 p, u8 v);

extern void sub_08017464(u32 p);

extern u8 *sub_0801EE14(u8 a, s32 b, u32 c, u32 d, u32 e);

extern void sub_0804A378(s32 idx);

extern void sub_0801D070(s32 a, u8 *s, u32 *out, u16 v);

extern void sub_0800D9FC(u8 *s);

void F_08015ac4(u8 *s) {
    u8 *p = s + 124;
    u8 mode = s[14];
    if (mode > 6) goto tail;
    switch (mode) {
    case 0:
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 0);
        
        goto inc;
    case 1: {
        u8 v;
        v = (u8)sub_08017474(*(u32 *)(s + 44));
        if (v == 0) goto tail;
        v = (u8)sub_08017474(*(u32 *)(s + 44));
        if (v > 6) {
            s[14] = 3;
            goto tail;
        }
        {
            u8 *tbl = (u8 *)0x02003670;
            
            *(tbl + 0x11af) = (*(tbl + 0x11af) & 15) | 64;
        }
        s[33] = 10;
        sub_0800D9EC(s, 3);
        s[14]++;
        goto p6;
    }
    case 2: {
        u8 v;
        v = (u8)sub_08017474(*(u32 *)(s + 44));
        if (p[6] >= v) goto check119;
        v = (u8)sub_08017474(*(u32 *)(s + 44));
        if (v > 5) goto check119;
        {
            u8 *tbl = (u8 *)0x02003670;
            
            *(tbl + 0x11af) = (*(tbl + 0x11af) & 15) | 64;
        }
        s[33] = 10;
        sub_0800D9EC(s, 3);
        goto p6;
    }
    p6:
        p[6] = (u8)sub_08017474(*(u32 *)(s + 44));
        goto tail;
    check119:
        if ((s16)sub_08011F50(s) == 0) goto tail;
        else if ((u8)sub_08017474(*(u32 *)(s + 44)) > 6) {
            u32 buf[2] = {0, 0};
            sub_0801D070(0, s, buf, *(u16 *)(p + 8));
            if (p[7] == 2) {
                sub_0800D9EC(s, 7);
                s[14] = 4;
                goto tail;
            } else {
                sub_0800D9EC(s, 0);
                goto inc;
            }
        } else goto tail;
    case 3:
        if ((u8)sub_08017474(*(u32 *)(s + 44)) <= 6) goto tail;
        sub_08017478(*(u32 *)(s + 44), 8);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = 0;
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 0);
        p[4] = 0;
        sub_08011F68(s, 0);
        
        goto tail;
    case 4: {
        u8 *q = s + 33;
        u32 zero = 0;
        *q = 60;
        s[18] = 40;
        sub_0801EE14(0, -4, ((u32)s[35] << 28) >> 28, 0xffffc400, zero);
        goto inc;
    }
    case 5:
        s[18]--;
        if (s[18] != 0) goto tail;
        sub_0800D9EC(s, 2);
        sub_0804A378(127);
    inc:
        s[14]++;
        goto tail;
    case 6: {
        u32 zero;
        u8 m;
        u8 v10;
        if ((u8)sub_08017474(*(u32 *)(s + 44)) <= 6) goto tail;
        m = 254;
        v10 = s[10] & m;
        zero = 0;
        s[10] = v10;
        sub_08017478(*(u32 *)(s + 44), 8);
        sub_08017464(*(u32 *)(s + 44));
        *(u32 *)(s + 44) = zero;
        sub_0800DD2C(s, 0xffffc400, 0);
        sub_0800D9EC(s, 0);
        p[4] = zero;
        sub_08011F68(s, 0);
    }
    }
tail:
    sub_0800D9FC(s);
}
