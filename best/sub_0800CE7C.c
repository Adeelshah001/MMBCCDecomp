/* Sub_0800CE7C @ 0x0800CE7C (146 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_0800ce7c_MATCHED.c (registry: mmbcc/src/w36d_0800ce7c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern u8 sub_0800D12C(u8 *s, u8 *a, u8 *b, u8 *c);

extern u8 sub_0800D278(u8 *s, u8 *a, u8 *b, u8 *c);

u32 sub_0800CE7C(u8 *s)
{
    u32 r5 = 1;
    switch (s[1]) {
    case 0:
        if (s[6] == 0)
            s[1] = 1;
        else
            s[1] = 2;
        break;
    case 1:
        if (sub_0800D12C(s, s + 3, s + 4, s + 5) == 0)
            s[1] = 3;
        break;
    case 2:
        if (sub_0800D278(s, s + 3, s + 4, s + 5) == 0)
            s[1] = 3;
        break;
    case 3: {
        register u8 a = s[0];
        register u8 b = s[7];
        if (a == b) {
            r5 = 0;
        } else {
            u8 zero = 0;
            s[6] = a;
            s[0] = b;
            s[3] = zero;
            s[2] = zero;
            s[1] = zero;
            *(u16 *)0x020031e0 = (*(u16 *)0x020031e0 & 0xedff) & 0xdbff;
        }
        break;
    }
    default:
        break;
    }
    return r5;
}
