/* F_0804B634 @ 0x0804B634 (444 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w48c_0804b634_MATCHED.c (registry: src/w48c_0804b634_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


extern void sub_08002FC4(u32 a);

extern u8 *sub_0802030C(u8 *a, u8 b, u8 c);

extern u8 sub_080203E0(u8 *a, u32 b, u32 c);

void F_0804B634(u8 *s)
{
    u8 *e;
    switch (s[3]) {
    case 0:
        s[3]++;
        sub_08002FC4(17);
    case 1: {
        u8 one = 1;
        u8 s8 = s[8];
        u8 c = (one & s8) ? 2 : 0;
        u8 *p = (u8 *)0x08235094;
        
        p += s8;
        if (sub_0802030C(s, *p, c) == 0)
            return;
    }
        s[10] |= 1;
        goto inc_return;
    case 2: {
        u8 two = 2;
        u8 v = s[10];
        
        if ((v & two) == 0)
            return;
    }
        s[3]++;
    case 3:
        e = (u8 *)(s[11] << 3);
        e += 0x08234f84;
        {
            u8 v4 = e[4];
            
            if (v4 > s[8])
                return;
        }
        {
            u8 v5 = e[5];
            
            if (v5 > s[9])
                return;
        }
        {
            u32 w = *(u32 *)e;
            u32 ix = ((u32)s[10] << 26) >> 28;
            if (sub_080203E0(s, w, ix) == 0)
                return;
        }
        s[3]++;
        s[11]++;
        {
            unsigned ni = ((((u32)s[10] << 26) >> 28) + 1) & 15;
            int sh = ni << 2;
            int t = (s[10] & ~60) | sh;
            s[10] = t;
            if (ni > 3)
                s[10] = t & ~60;
        }
        return;
    case 4:
        if (s[11] > s[12])
            return;
        e = (u8 *)(0x08234f84 + (s[11] << 3));
        if (e[4] > s[8])
            goto set5;
        if (e[5] > s[9])
            goto set5;
        if (s[14] > 3)
            return;
        s[3] = 3;
        return;
    set5:
        s[3] = 5;
        return;
    case 5:
        if (s[12] != s[13])
            return;
        e = (u8 *)(s[11] << 3);
        e += 0x08234f84;
        {
            int t = s[10] & ~60;
            s[10] = t;
        }
        if (e[4] <= s[8]) {
            u8 z = 0;
            u8 t = 3;
            s[3] = t;
            s[9]++;
            s[14] = z;
                return;
        }
        s[3] = 6;
        return;
    case 6:
        s[3]++;
        {
            int t = s[10] & ~1;
            s[10] = t;
        }
    case 7:
        if ((s[10] & 2) != 0)
            return;
        s[3]++;
    case 8: {
        int ns = s[8] + 1;
        u8 z = 0;
        s[8] = ns;
        s[9] = z;
        s[14] = z;
        if ((u8)ns > 9)
            goto inc_return;
        s[3] = 1;
        return;
    }
    inc_return:
        s[3]++;
        return;
    case 9: {
        u8 a = s[2] + 1;
        u8 b = 0;
        s[2] = a;
        s[3] = b;
        return;
    }
    default:
        return;
    }
}
