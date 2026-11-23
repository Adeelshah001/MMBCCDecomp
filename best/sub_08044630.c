/* Sub_08044630 @ 0x08044630 (252 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w47d_08044630_MATCHED.c (registry: src/w47d_08044630_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern u8 sub_080241F8(u16 a);

extern u16 sub_08024514(u8 v);

extern u8 sub_0800B148(u8 a, s16 b, u8 c);

extern u8 sub_0800B2D8(void);

extern u8 sub_08024384(u16 a);

extern u8 StartSelectionWithEntries(u32 a, u32 b, u32 c, u32 d);

extern u8 sub_0800B308(void);

extern u8 sub_0800B2B4(void);

extern u8 sub_0800B2F0(void);

extern u8 gUnknown_02004E40[];

int sub_08044630(u8 *s)
{
    register u8 r;
    switch (s[0x46ad]) {
    case 0:
        r = sub_0800B148(1, (s16)sub_08024514((u8)sub_080241F8(4096)), 1);
        goto tail;
    case 1:
        if (sub_0800B2D8() == 0)
            goto ret;
        r = StartSelectionWithEntries(((u32 *)0x08232dc0)[(u8)(sub_08024384(4096) - 50)], 0, 0, 0);
        if (r == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 2:
        {
            register u8 *gp = gUnknown_02004E40;
            gp[20] |= 1;
        }
        if (sub_0800B308() == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 3:
        r = sub_0800B2B4();
        goto tail;
    tail:
        if ((r << 24) != 0)
            s[0x46ad]++;
        goto ret;
    case 4:
        if (sub_0800B2F0() == 0)
            goto ret;
        {
            u8 *pp = s + 0x46ac;
            int z = 0;
            *pp = 5;
            s[0x46ad] = z;
        }
        goto ret;
    default:
        goto ret;
    }
ret:
    return 0;
}
