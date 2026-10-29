/* Wave 42 Worker B: 0x0804b634, 444 B, state machine (s[3] = state).
   v8: goto-shared tails (set5, inc_return) + barriers on unique return
   tails to defeat old_agbcc's strb-suffix merging; case4 separate ifs
   (not ||); case5 inverted condition; e via <<3; case3 temp-w order;
   case5-else / case8 / case9 temp-constant forms.
   Externs: Sub_08002FC4(u32), NewNode_0802030C(u8*,u8,u8),
   Sub_080203E0(u32,u8*,u32) -> u8. Grid table base 0x08234f84
   (8-byte entries: +0 u32, +4 u8, +5 u8). Second table 0x08235094
   (bytes indexed by s[8]) for NewNode arg b. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void Sub_08002FC4(u32 a);
extern u8 *NewNode_0802030C(u8 *a, u8 b, u8 c);
extern u8 Sub_080203E0(u8 *a, u32 b, u32 c);
#define BARRIER __asm__ volatile("" ::: "memory")

__attribute__((section(".text.w48c_0804b634")))
void F_0804B634(u8 *s)
{
    u8 *e;
    switch (s[3]) {
    case 0:
        s[3]++;
        Sub_08002FC4(17);
    case 1: {
        u8 one = 1;
        u8 s8 = s[8];
        u8 c = (one & s8) ? 2 : 0;
        u8 *p = (u8 *)0x08235094;
        __asm__ volatile("" : "+r" (p));
        p += s8;
        if (NewNode_0802030C(s, *p, c) == 0)
            return;
    }
        s[10] |= 1;
        goto inc_return;
    case 2: {
        u8 two = 2;
        u8 v = s[10];
        __asm__ volatile("" : "+r" (v));
        if ((v & two) == 0)
            return;
    }
        s[3]++;
    case 3:
        e = (u8 *)(s[11] << 3);
        e += 0x08234f84;
        {
            u8 v4 = e[4];
            __asm__ volatile("" : "+r" (v4));
            if (v4 > s[8])
                return;
        }
        {
            u8 v5 = e[5];
            __asm__ volatile("" : "+r" (v5));
            if (v5 > s[9])
                return;
        }
        {
            u32 w = *(u32 *)e;
            u32 ix = ((u32)s[10] << 26) >> 28;
            if (Sub_080203E0(s, w, ix) == 0)
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
__asm__(
    ".set Sub_08002FC4, 0x08002fc4\n"
    ".set Sub_080203E0, 0x080203e0\n"
);
