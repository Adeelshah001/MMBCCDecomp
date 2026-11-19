/* Sub_08022290 @ 0x08022290 (144 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08022290_MATCHED.c (registry: mmbcc/src/w36d_08022290_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u32 sub_080225B4(u32 a, u32 b);

extern void sub_080224E4(u32 a, u32 b, u32 c, u32 d);

extern void sub_0800D9FC(u8 *s);

void sub_08022290(u8 *s)
{
    u8 *r6 = *(u8 **)(s + 40);
    if (s[13] != 0) goto end;
    if (s[14] == 0) goto set14;
    if (s[14] == 1) goto dec18;
    goto end;
set14:
    s[14] = 1;
    s[18] = (s[17] << 3) + 60;
dec18:
    s[18]--;
    if ((u8)s[18] > 59) goto end;
    {
        u8 *base1 = (u8 *)0x081738f2;
        u8 *base2 = (u8 *)0x082270b0;
        u16 hv = *(u16 *)(base2 + (s[17] << 1));
        u8 b = *(u8 *)(base1 + ((hv >> 8) << 1));
        u32 res = sub_080225B4(((u32)s[17] + 3) | hv, 0);
        sub_080224E4(b, res, 0x082270d4, s[18] >> 2);
    }
    if (s[18] != 0) goto end;
    s[13]++;
    s[14] = 0;
    {
        register u8 bv = r6[19];
        r6[19] = (1 << s[17]) | bv;
    }
end:
    sub_0800D9FC(s);
}
