/* sub_080493EC @ 0x080493EC (372 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w72a_080493ec_MATCHED.c (registry: src/w72a_080493ec_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


void sub_08004F18(void);

void sub_0800BEE0(u32 a, u32 b);

void sub_08005A9C(u32 a);

void sub_08049560(u8 *s);

void sub_0800800C(u8 *a, u32 b);

void sub_0804A3FC(void);

s8 sub_0804A40C(void);

u32 sub_08024384(u32 a);

u32 sub_0800B368(u32 a, u32 b, u32 c, u32 d);

u32 sub_0800B308(void);

void sub_08004F80(void);

extern u8 gUnknown_02004CE0[];

extern u32 gUnknown_082343B8[];

u8 sub_080493EC(u8 *s)
{
    sub_08004F18();
    switch (s[18085]) {
    case 0: {
        u8 *g;
        u8 *p44;
        int t;
        sub_0800BEE0(64, 128);
        sub_08005A9C(25);
        sub_08049560(s);
        g = gUnknown_02004CE0;
        p44 = g;
        p44 += 44;
        t = 1;
        t |= *p44;
        *(u16 *)(g + 40) = 16;
        *(u16 *)(g + 42) = (s8)s[18086] * 16 + 8;
        t &= ~30;
        t &= ~32;
        *p44 = t;
        {
            u32 m = 0xFFFFFC3F;
            u32 v = *(u16 *)(g + 44);
            *(u16 *)(g + 44) = v & m;
        }
        sub_0800800C(g, 0);
        s[18087] = 5;
        s[18085]++;
        /* fallthrough into case 1's shared ending */
    }
    case 1:
        sub_0804A3FC();
        s[18085]++;
        break;
    case 2: {
        s8 v = sub_0804A40C();
        if (v == -2) {
            if ((s8)s[18087] > 0) {
                s[18085]--;
                s[18087]--;
            } else {
                s[18085]++;
            }
        } else if (v != -1) {
            s[18085]++;
        }
        break;
    }
    case 3: {
        u32 x = sub_08024384(4096) - 50;
        u32 *tbl;
        x = x << 24;
        tbl = gUnknown_082343B8;
        x = x >> 22;
        if ((u8)sub_0800B368(*(u32 *)((u8 *)tbl + x), 0, 0, 0))
            s[18085]++;
        break;
    }
    case 4:
        if ((u8)sub_0800B308()) {
            s[18084] = 0;
            s[18085] = 0;
        }
        break;
    default:
        break;
    }
    sub_08004F80();
    return 0;
}
