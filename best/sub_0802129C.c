/* Sub_0802129C @ 0x0802129C (400 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40c_0802129c_MATCHED.c (registry: mmbcc/src/w40c_0802129c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */


typedef signed short s16;

u32 sub_0804DE70(u32 a, u32 b);

u32 sub_0804DEE8(u32 a, u32 b);

void DrawDecimalDigits(s16 a, u16 b, u8 c, u8 d, u8 e);

void sub_080098C4(u8 a, u16 b, u8 c, u8 d);

void sub_08009994(u8 a, u16 b, u8 c, u8 d);

u8 sub_0802465C(u8 idx);

void sub_0802129C(u8 *s)
{
    u8 *q40 = *(u8 **)(s + 40);
    u8 *q44 = *(u8 **)(s + 44);
    u8 a = q40[0];
    u8 b = q44[0];
    switch (s[17]) {
    case 12: {
        u16 *base = (u16 *)0x0817386c;
        
        DrawDecimalDigits(a, base[22], 9, 0, 2);
        DrawDecimalDigits(b, base[22], 11, 0, 2);
        break;
    }
    case 13: {
        u16 *base = (u16 *)0x0817386c;
        
        sub_080098C4(0, base[22], 11, 0);
        sub_080098C4(0, base[22], 12, 0);
        sub_080098C4(b, base[22], 14, 0);
        break;
    }
    case 0: {
        u8 t = a;
        u8 q;
        u8 r;
        if (t > 99)
            t = 99;
        q = sub_0804DE70(t, 10);
        if (q != 0)
            q++;
        {
            u16 *base = (u16 *)0x0817386c;
            
            sub_08009994(q, base[22], 17, 2);
            r = sub_0804DEE8(t, 10) + 1;
            sub_08009994(r, base[22], 17, 3);
            DrawDecimalDigits(b, base[22], 15, 2, 2);
        }
        break;
    }
    case 1: {
        u16 *base = (u16 *)0x0817386c;
        
        DrawDecimalDigits(a, base[22], 10, 0, 2);
        break;
    }
    case 2: {
        u16 cnt;
        u16 i;
        {
            u16 *base = (u16 *)0x0817386c;
            
            DrawDecimalDigits(a, base[22], 10, 0, 3);
        }
        cnt = 0;
        i = 0;
        do {
            if ((sub_0802465C((u8)i) & 2) == 0)
                cnt = (u16)((((u32)cnt << 16) + 0x10000) >> 16);
            i = (u16)((((u32)i << 16) + 0x10000) >> 16);
        } while ((s16)i <= 248);
        {
            u16 *base = (u16 *)0x0817386c;
            
            DrawDecimalDigits((s16)cnt, base[22], 14, 0, 3);
        }
        break;
    }
    default:
        break;
    }
    s[120] = a;
    s[121] = b;
}
