/* Sub_080424F4 @ 0x080424F4 (320 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w139a_080424f4_MATCHED.c (registry: src/w139a_080424f4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

extern u8 gUnknown_02004E40[];

extern s8 gUnknown_02004CA0[];

extern u32 gUnknown_08232A5C[];

extern u32 gUnknown_082325D4;

extern u32 gUnknown_082325DC;

extern int sub_080241F8(u16 a);

extern s16 sub_08024514(u8 v);

extern int sub_08024384(int a);

extern u8 sub_0800B148(u8 a, s16 b, u8 c);

extern int StartSelectionWithEntries(u32 a, u32 b, u32 c, u32 d);

extern u8 sub_0800B2D8(void);

extern u8 sub_0800B308(void);

extern u8 sub_0800B2B4(void);

extern u8 sub_0800B2F0(void);

extern void sub_08005F44(int a, s8 b, s8 c);

int sub_080424F4(u8 *s)
{
    int ret = 0;
    { u8 *gp = gUnknown_02004E40; gp[20] |= 1; }
    switch (s[0x46AD]) {
    case 0:
        if (*(u16 *)(s + 0x46A4) == 0) {
            ret = 1;
            break;
        }
        if ((u8)sub_0800B148(1, sub_08024514((u8)sub_080241F8(4096)), 5) != 0)
            s[0x46AD]++;
        break;
    case 1:
        if ((u8)sub_0800B2D8() == 0)
            break;
        {
            int v = sub_08024384(4096);
            u8 idx = (u8)(v - 50);
            int tv = gUnknown_08232A5C[idx];
            if ((u8)StartSelectionWithEntries(tv, gUnknown_082325D4, gUnknown_082325DC, 0) == 0)
                break;
        }
        s[0x46AD]++;
        break;
    case 2:
        if ((u8)sub_0800B308() == 0)
            break;
        ret = gUnknown_02004E40[8];
        if (ret == 0)
            ret = 1;
        else
            ret = 0;
        s[0x46AD]++;
        break;
    case 3:
        if ((u8)sub_0800B2B4() == 0)
            break;
        s[0x46AD]++;
        break;
    case 4:
        if ((u8)sub_0800B2F0() == 0)
            break;
        s[0x46AC] = 10;
        sub_08005F44(0, gUnknown_02004CA0[0], gUnknown_02004CA0[1]);
        break;
    default:
        break;
    }
    return ret;
}
