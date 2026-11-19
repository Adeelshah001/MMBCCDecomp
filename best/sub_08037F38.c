/* sub_08037F38 @ 0x08037F38 (384 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w78d_08037f38_MATCHED.c (registry: src/w78d_08037f38_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

u32 sub_08038C10(u8 *s);

u32 sub_0804DE70(u32 a, u32 b);

void sub_08011DD0(u32 a, u32 b);

void sub_08011D68(u32 a, u32 b);

u32 sub_08024384(u32 a);

u32 sub_080112FC(u32 a, u32 b);

u32 sub_080114B8(u32 a);

u32 sub_080114E8(void);

void sub_08028880(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);

extern u8 gUnknown_08230450[];

int sub_08037F38(u8 *s)
{
    int ret = 0;
    switch ((s8)s[0x469D]) {
    case 0: {
        u8 v = sub_08038C10(s);
        if (v != 255) {
            u8 *p = gUnknown_08230450;
            p += s[0x4699];
            sub_08011DD0(4, (u8)(sub_0804DE70(s[0x469E], 5) + *p));
            sub_08011D68(20, 0);
            sub_08011DD0(5, v);
        } else {
            sub_08011D68(20, 1);
            sub_08011DD0(7, (u8)sub_0804DE70(s[0x469E], 5));
        }
        s[0x469D]++;
    }
    case 1: {
        u8 t = (u8)(sub_08024384(4096) - 50);
        u16 w = sub_080112FC(t, 7);
        if (w == 0) {
            s[0x469C] = 3;
            s[0x469D] = w;
            ret = 2;
            s[0x46A0] = w;
            sub_08028880(4096, *(u16 *)(s + 0x469A), s[0x469F], 8,
                          s[0x46A1], w);
            break;
        } else {
            if ((u8)sub_080114B8(w) != 0)
                break;
            s[0x469D]++;
        }
    }
    case 2:
        if ((s16)sub_080114E8() == 1) {
            u16 oC, oD, oA;
            u8 z;
            u8 *pc;
            oC = 0x469C;
            pc = s + oC;
            z = 0;
            pc[0] = 3;
            oD = 0x469D;
            s[oD] = z;
            ret = 2;
            oA = 0x46A0;
            s[oA] = z;
            sub_08028880(4096, *(u16 *)(s + oC - 2), s[oD + 2], 8,
                          s[oA + 1], z);
            break;
        }
        break;
    default:
        break;
    }
    return ret;
}
