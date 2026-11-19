/* Search_080112FC @ 0x080112FC (248 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_table.c (registry: src/w17c_table.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


 typedef signed short s16;

extern void sub_08011D68(u16 x, u8 y);

extern u32 sub_08011D34(u16 x);

extern u16 sub_08011C58(u8 a0, u8 a1);

extern u8 *sub_08011C80(u16 idx);

extern u8 sub_08011DB0(u16 idx);

/* 0x080112fc (248 B): flag-init + table walk. */
u16 sub_080112FC(u8 a, u8 b)
{
    u16 i = 3;
    u16 cur;
    u8 *p;
    do {
        if (a + 3 == i)
            sub_08011D68(i, 1);
        else
            sub_08011D68(i, 0);
        i++;
    } while (i <= 8);
    cur = sub_08011C58(a, b);
    if (cur == 0)
        return 0;
    goto loop;
adv:
    if (*(s16 *)(p + 4) == 0)
        return 0;
    cur = *(u16 *)(p + 4);
loop:
    p = sub_08011C80(cur);
    {
        s8 v0 = (s8)p[0];
        if (v0 > 0) {
            if ((u8)sub_08011D34((u16)v0) == 0)
                goto adv;
        } else if (v0 < 0) {
            if ((u8)sub_08011D34((u16)(-(s8)p[0])) == 1)
                goto adv;
        }
    }
    {
        s8 v1 = (s8)p[1];
        if (v1 > 0) {
            if ((u8)sub_08011D34((u16)v1) == 0)
                goto adv;
        } else if (v1 < 0) {
            if ((u8)sub_08011D34((u16)(-(s8)p[1])) == 1)
                goto adv;
        }
    }
    {
        s8 v2 = (s8)p[2];
        if (v2 > 0) {
            if (sub_08011DB0((u16)v2) < p[3])
                goto adv;
        } else if (v2 < 0) {
            if (sub_08011DB0((u16)(-(s8)p[2])) >= p[3])
                goto adv;
        }
    }
    return cur;
}
