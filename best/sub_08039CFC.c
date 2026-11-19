/* sub_08039CFC @ 0x08039CFC (416 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w83a_08039cfc_MATCHED.c (registry: mmbcc/src/w83a_08039cfc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

s8 sub_08028778(u8 *a, u32 b);

void sub_08004E44(void);

void sub_08004DFC(u8 a);

void sub_0800BEE0(u32 a, u32 b);

void sub_0804A2DC(u32 a);

void sub_08004F18(void);

void sub_08004F80(void);

u8 sub_080241F8(u32 a);

s16 sub_08024514(u8 a);

u8 sub_0800B148(u8 f, s16 t, u8 mode);

u8 sub_0800B2D8(void);

u8 sub_08024384(u32 a);

u8 sub_0800B368(u32 f, u32 a, u32 b, u32 c);

u8 sub_0800B308(void);

void sub_0804A328(void);

u8 sub_0800B2B4(void);

extern u8 gUnknown_02004F80[];

extern u8 gUnknown_02004E40[];

extern u32 gUnknown_082317FC[];

extern u32 gUnknown_08230E28[];

extern u32 gUnknown_08230E30[];

u8 sub_08039CFC(u8 *s)
{
    u8 r = 0;
    u8 z;
    u8 *p;
    switch ((s8)s[0x469D]) {
    case 0:
        if (sub_08028778(s + 0x469F, 1) == 0) {
            s[0x469F] = 0;
            s[0x469D]++;
        }
        break;
    case 1:
        sub_08004E44();
        sub_08004DFC(gUnknown_02004F80[2]);
        sub_0800BEE0(64, 128);
        sub_0804A2DC(8);
        s[0x4699] = 0;
        s[0x469D]++;
    case 2:
        sub_08004F18();
        if (sub_0800B148(1, sub_08024514((u8)sub_080241F8(128 << 5)), 4) == 0)
            goto f80;
        goto inc;
    case 3:
        sub_08004F18();
        if (sub_0800B2D8() == 0)
            goto f80;
        goto inc;
    case 4: {
        u32 f;
        u8 idx;
        sub_08004F18();
        idx = (u8)(sub_08024384(128 << 5) - 50);
        f = gUnknown_082317FC[idx];
        if (sub_0800B368(f, *gUnknown_08230E28, *gUnknown_08230E30, 0) == 0)
            goto f80;
        goto inc;
    }
    inc:
        s[0x469D]++;
        goto f80;
    case 5:
        sub_08004F18();
        gUnknown_02004E40[20] |= 1;
        if (sub_0800B308() == 0)
            goto f80;
        {
            int i = 8;
            if ((s8)gUnknown_02004E40[i] == 0)
                goto inc;
        }
        p = s + 0x469C;
        z = 0;
        *p = 4;
        s[0x469D] = z;
        sub_0804A328();
        r = 1;
    f80:
        sub_08004F80();
        break;
    case 6:
        sub_08004F18();
        if (sub_0800B2B4() == 0)
            goto f80_6;
        p = s + 0x469C;
        z = 0;
        *p = 8;
        s[0x469D] = z;
        s[4] = z;
        r = 1;
    f80_6:
        sub_08004F80();
        break;
    default:
        break;
    }
    return r;
}
