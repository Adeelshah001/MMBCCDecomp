/* F_08026430 @ 0x08026430 (282 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w43b_08026430_MATCHED.c (registry: mmbcc/src/w43b_08026430_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


u8 sub_080263A4(u8 *src);

u8 sub_080252D0(u8 *list, u16 i);

u8 sub_0802637C(u8 *b, u8 *ent14);

u8 sub_08025290(u8 *list, u16 idx);

void sub_0802526C(u8 *list, u8 idx);

u8 sub_08026720(u8 v);

u16 sub_08026430(u8 *s, u8 *b, u8 *src)
{
    u16 i;
    u8 idx;
    s[24] = 0;
    s[25] = 0;
    if (sub_080263A4(src)) {
        s[24] = 3;
        return 0;
    }
    for (i = 0; i < *(u16 *)(s + 22); i++) {
        register u8 *ent;
        u8 *base;
        idx = sub_080252D0(s + 16, i);
        base = *(u8 **)(s + 4);
        ent = (u8 *)(idx * 28);
        ent += (u32)base;
        if (ent[24] != src[13])
            continue;
        if (sub_0802637C(b, ent + 14))
            continue;
        if (idx == 0) {
            s[24] = 1;
            s[25] = 0;
        } else {
            s[24] = 2;
            s[25] = (u8)i;
        }
        return 0;
    }
    if (*(u16 *)(s + 22) > 127) {
        s[24] = 4;
        return 0;
    }
    idx = sub_08025290(s + 8, *(u16 *)(s + 14) - 1);
    sub_0802526C(s + 16, idx);
    {
        u8 *ent = *(u8 **)(s + 4) + idx * 28;
        u16 hv;
    ent[0] = src[0];
    ent[1] = sub_08026720(src[0]);
    ent[2] = src[1];
    ent[3] = src[2];
    ent[4] = src[3];
    ent[5] = src[4];
    ent[6] = src[5];
    ent[7] = src[6];
    ent[8] = src[7];
    ent[9] = src[8];
    ent[10] = src[9];
    ent[11] = src[10];
    ent[12] = src[11];
    ent[13] = src[12];
    *(u16 *)(ent + 14) = *(u16 *)(b + 0);
    *(u16 *)(ent + 16) = *(u16 *)(b + 2);
    *(u16 *)(ent + 18) = *(u16 *)(b + 4);
    *(u16 *)(ent + 20) = *(u16 *)(b + 6);
    hv = 0x8000;
    *(u16 *)(ent + 22) = hv;
    ent[24] = src[13];
    ent[25] = 1;
    }
    return idx | 0x2000;
}
