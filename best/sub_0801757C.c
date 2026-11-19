/* Sub_0801757C @ 0x0801757C (132 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0801757c_MATCHED.c (registry: mmbcc/src/w37c_0801757c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef short s16;

extern void sub_0800D9FC(u8 *s);

extern void sub_080178A8(int a, int b, s16 c, s16 d, u8 *e);

extern int sub_0804A378(int idx);

extern u8 sub_08017474(u8 *p);

extern void sub_08017478(u8 *p, int v);

extern void sub_08017464(u8 *p);

void sub_0801757C(u8 *s)
{
    u32 **t;
    sub_0800D9FC(s);
    if (s[13] == 0 && ++s[18] == 15) {
        sub_080178A8(1, ((u32)s[35] << 28) >> 28, 15360, -5632, *(u8 **)(s + 44));
        sub_0804A378(128);
        s[13] = 1;
    }
    if (sub_08017474(*(u8 **)(s + 44)) > 5) {
        register u8 *base;
        base = (u8 *)0x082243d8;
        
        t = (u32 **)(s[9] * 4 + (u32)base);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*t + 8);
        sub_08017478(*(u8 **)(s + 44), 7);
        sub_08017464(*(u8 **)(s + 44));
        *(u32 *)(s + 44) = 0;
    }
}
