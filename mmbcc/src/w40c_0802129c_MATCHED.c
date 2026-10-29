/* W40-C v1: 0x0802129c, TRUE extent 400 B (0x0802129c..0x0802142c).
 * Jump-table dispatch on s[17] (14 entries, 3..11 and default -> epilogue).
 *   a = *(u8 **)(s + 40) first byte; b = *(u8 **)(s + 44) first byte;
 *   base44 = ((u16 *)0x0817386c)[22] (reloaded per case block).
 *   case 12: Draw(a, base44, 9, 0, 2); Draw(b, base44, 11, 0, 2);
 *   case 13: Draw4(0, base44, 11, 0); Draw4(0, base44, 12, 0);
 *            Draw4(b, base44, 14, 0);
 *   case 0: t = min(a, 99); q = UDiv(t, 10); if (q) q++;
 *           DrawQ(q, base44, 17, 2); r = UMod(t, 10) + 1;
 *           DrawQ(r, base44, 17, 3); Draw(b, base44, 15, 2, 2);
 *   case 1: Draw(a, base44, 10, 0, 2);
 *   case 2: Draw(a, base44, 10, 0, 3);
 *           cnt = #{i in 0..248 : TblGet11((u8)i) & 2 == 0};
 *           Draw((s16)cnt, base44, 14, 0, 3);
 *   epilogue: s[120] = a; s[121] = b.
 * Callees via .set at END (GAS idiom). Draw first param is s16: case2's
 * final call sign-extends (lsls/asrs) rather than zero-extends.
 */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

u32 UDiv_0804DE70(u32 a, u32 b);
u32 UMod_0804DEE8(u32 a, u32 b);
void Sub_08009860(s16 a, u16 b, u8 c, u8 d, u8 e);
void Sub_080098C4(u8 a, u16 b, u8 c, u8 d);
void Sub_08009994(u8 a, u16 b, u8 c, u8 d);
u8 Wrap_TblGet11(u8 idx);

__attribute__((section(".text.w40c_0802129c")))
void Sub_0802129C(u8 *s)
{
    u8 *q40 = *(u8 **)(s + 40);
    u8 *q44 = *(u8 **)(s + 44);
    u8 a = q40[0];
    u8 b = q44[0];
    switch (s[17]) {
    case 12: {
        u16 *base = (u16 *)0x0817386c;
        __asm__ volatile("" : "+r" (base));
        Sub_08009860(a, base[22], 9, 0, 2);
        Sub_08009860(b, base[22], 11, 0, 2);
        break;
    }
    case 13: {
        u16 *base = (u16 *)0x0817386c;
        __asm__ volatile("" : "+r" (base));
        Sub_080098C4(0, base[22], 11, 0);
        Sub_080098C4(0, base[22], 12, 0);
        Sub_080098C4(b, base[22], 14, 0);
        break;
    }
    case 0: {
        u8 t = a;
        u8 q;
        u8 r;
        if (t > 99)
            t = 99;
        q = UDiv_0804DE70(t, 10);
        if (q != 0)
            q++;
        {
            u16 *base = (u16 *)0x0817386c;
            __asm__ volatile("" : "+r" (base));
            Sub_08009994(q, base[22], 17, 2);
            r = UMod_0804DEE8(t, 10) + 1;
            Sub_08009994(r, base[22], 17, 3);
            Sub_08009860(b, base[22], 15, 2, 2);
        }
        break;
    }
    case 1: {
        u16 *base = (u16 *)0x0817386c;
        __asm__ volatile("" : "+r" (base));
        Sub_08009860(a, base[22], 10, 0, 2);
        break;
    }
    case 2: {
        u16 cnt;
        u16 i;
        {
            u16 *base = (u16 *)0x0817386c;
            __asm__ volatile("" : "+r" (base));
            Sub_08009860(a, base[22], 10, 0, 3);
        }
        cnt = 0;
        i = 0;
        do {
            if ((Wrap_TblGet11((u8)i) & 2) == 0)
                cnt = (u16)((((u32)cnt << 16) + 0x10000) >> 16);
            i = (u16)((((u32)i << 16) + 0x10000) >> 16);
        } while ((s16)i <= 248);
        {
            u16 *base = (u16 *)0x0817386c;
            __asm__ volatile("" : "+r" (base));
            Sub_08009860((s16)cnt, base[22], 14, 0, 3);
        }
        break;
    }
    default:
        break;
    }
    s[120] = a;
    s[121] = b;
}

__asm__(".set Sub_08009860, 0x08009860");
__asm__(".set Sub_08009994, 0x08009994");
