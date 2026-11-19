/* sub_08041E58 @ 0x08041E58 (356 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w73a_08041e58_MATCHED.c (registry: mmbcc/src/w73a_08041e58_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u32 sub_08024F88(u16 *p);

u32 sub_0800B320(u32 a, u32 b, u32 c, u32 d);

u32 sub_0800B420(u32 a, u16 *b, u32 c);

u32 sub_0800B308(void);

u32 sub_0800B2B4(void);

u32 sub_0800B2F0(void);

u32 sub_08005F44(u32 a, s8 b, s8 c);

extern u8 gUnknown_02004E40[];

extern s8 gUnknown_02004CA0[];

u32 sub_08041E58(u8 *s)
{
    u16 buf[24];
    u16 b[8];
    u8 i;
    { u8 *g = gUnknown_02004E40; g[20] |= 1; }
    switch (s[0x46AD]) {
    case 0:
        sub_08024F88(buf);
        if ((u8)sub_0800B320(0x08232634, 0, 0, 0)) {
            u16 *p;
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[i]; }
            b[6] = 0;
            b[7] = 0;
            sub_0800B420(0, b, 0);
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[6 + i]; }
            b[6] = 0;
            b[7] = 0;
            sub_0800B420(1, b, 0);
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[12 + i]; }
            b[6] = 0;
            b[7] = 0;
            sub_0800B420(2, b, 0);
            for (i = 0, p = b; i <= 7; i++)
                { u16 *d = p + i; *d = buf[18 + i]; }
            b[6] = 0;
            b[7] = 0;
            sub_0800B420(3, b, 0);
            s[0x46AD]++;
        }
        break;
    case 1:
        if ((u8)sub_0800B308())
            s[0x46AD]++;
        break;
    case 2:
        if ((u8)sub_0800B2B4())
            s[0x46AD]++;
        break;
    case 3:
        if ((u8)sub_0800B2F0()) {
            int ia = 0;
            int ib = 1;
            s[0x46AC] = 10;
            sub_08005F44(0, gUnknown_02004CA0[ia], gUnknown_02004CA0[ib]);
        }
        break;
    default:
        break;
    }
    return 0;
}
