/* Sub_08042B60 @ 0x08042B60 (164 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w39c_08042b60_MATCHED.c (registry: mmbcc/src/w39c_08042b60_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08004E44(void);

extern void sub_08004DFC(u8 v);

extern void sub_0800BEE0(int a, int b);

extern void sub_0800800C(u8 *p, int v);

extern void sub_08004F18(void);

extern u8 sub_08042D80(u8 *s);

extern void sub_08004F80(void);

u8 sub_08042B60(u8 *s)
{
    u8 ret = 0;
    switch (s[5]) {
    case 0: {
        register u8 *base;
        register u8 *b;
        register int bt;
        u32 mask;
        int v24;
        u8 *gp;
        sub_08004E44();
        gp = (u8 *)0x02004f80;
        sub_08004DFC(gp[2]);
        sub_0800BEE0(64, 128);
        base = (u8 *)0x02004ce0;
        b = base + 44;
        bt = *b;
        bt |= 1;
        *(u16 *)(base + 40) = 16;
        v24 = 24;
        *(u16 *)(base + 42) = v24;
        v24 -= 55;
        bt &= v24;
        v24 -= 2;
        bt &= v24;
        *b = bt;
        mask = ~0x3c0;
        *(u16 *)(base + 44) &= mask;
        sub_0800800C(base, 0);
        s[5]++;
        /* fall through */
    }
    case 1: {
        register int t2;
        int tmp;
        int z;
        sub_08004F18();
        t2 = sub_08042D80(s);
        if (t2 == 0)
            goto done;
        if (t2 != 5) {
            tmp = s[4];
            z = 0;
            s[7] = tmp;
            s[4] = t2;
            s[5] = z;
            s[6] = z;
            goto done;
        }
        s[0x46b7] = 1;
        ret = 5;
        goto done;
    }
    default:
        goto retpt;
    }
done:
    sub_08004F80();
retpt:
    return ret;
}
