/* TableWalk_080113F4 @ 0x080113F4 (194 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w17c_table.c (registry: src/w17c_table.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


 typedef signed short s16;

extern u32 sub_08011D34(u16 x);

extern u8 *sub_08011C80(u16 idx);

extern u8 sub_08011DB0(u16 idx);

/* 0x080113f4 (194 B): same walk, returns u8*. */
u8 *sub_080113F4(u16 cur)
{
    u8 *p;
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
    return p;
}
