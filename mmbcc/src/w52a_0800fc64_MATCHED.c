/* W52-A 0x0800fc64 MATCH (236 B, 0 diffs) — switch state machine.
 * Fix vs W51-A BEST (8 diffs): the case-1 store is split into three plain-C
 * statements in ROM's own order instead of one array-index expression:
 *   u8 *p = tbl_02003670;  p += 0x11af;  sh = v << 4;  *p = (*p & 15) | sh;
 * The two-step pointer keeps ROM's two-word pool (base 0x02003670 +
 * offset 4527) instead of folding to one word, and computing the shift
 * AFTER the address adds but BEFORE the mask-load reproduces ROM's exact
 * schedule: ldr r0 / ldr r5 / adds r0 / lsls r2,#4 / movs r1,#15 /
 * ldrb r5 / ands r1,r5 / orrs r1,r2 / strb r1. No new pins: p and sh are
 * plain locals (the inherited block-scoped v65->r3 pin is unchanged and
 * safe: no calls between its def and last use). old_agbcc -O2
 * -mthumb-interwork, linked-at-address verified, 0 diffs over the true
 * extent 236 B (bx 0xfd4e, no trailing pool, next fn 0xfd50).
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed short s16;
typedef signed char s8;

extern u8 tbl_02003670[];
__asm__(".set tbl_02003670, 0x02003670");

extern u8 Sub_0800B2B4(void);
extern u8 Sub_0800B148(u8 a, s16 b, int c);
extern u8 Sub_0800B2D8(void);
extern u8 Sub_0800B320(u32 a, int b, int c, int d);
extern u8 Sub_0800B308(void);
extern u8 Sub_0800B2F0(void);
extern void Sub_08010508(int a);
__asm__(".set Sub_0800B2B4, 0x0800b2b4");
__asm__(".set Sub_0800B148, 0x0800b148");
__asm__(".set Sub_0800B2D8, 0x0800b2d8");

__asm__(".set Sub_0800B308, 0x0800b308");
__asm__(".set Sub_0800B2F0, 0x0800b2f0");
__asm__(".set Sub_08010508, 0x08010508");

__attribute__((section(".text.w52a_0800fc64")))
u8 Sub_0800FC64(u8 *s)
{
    switch (s[1]) {
    case 0:
        if (Sub_0800B2B4() == 0)
            break;
        s[1]++;
        /* fallthrough */
    case 1: {
        register u8 v65 __asm__("r3");
        if (Sub_0800B148(s[69], *(s16 *)(s + 56), 1) == 0)
            break;
        v65 = s[65];
        {
            unsigned int t = v65;
            if (t != 0) {
                int v = v65;
                if (t > 15)
                    v = 15;
                {
                    u8 *p = tbl_02003670;
                    int sh;
                    p += 0x11af;
                    sh = v << 4;
                    *p = (u8)((*p & 15) | sh);
                }
                s[3] = v65;
            } else {
                s[3] = 1;
            }
        }
        s[1]++;
        break;
    }
    case 2:
        s[3]--;
        if ((s8)s[3] > 0)
            break;
        s[1]++;
        /* fallthrough */
    case 3:
        if (Sub_0800B2D8() == 0)
            break;
        if (Sub_0800B320(*(u32 *)(s + 48), 0, 0, 0) == 0)
            break;
        s[1]++;
        break;
    case 4:
        if (Sub_0800B308() == 0)
            break;
        s[1]++;
        break;
    case 5:
        if (Sub_0800B2B4() == 0)
            break;
        s[1]++;
        break;
    case 6:
        if (Sub_0800B2F0() == 0)
            break;
        Sub_08010508(0);
        break;
    default:
        break;
    }
    return s[0];
}
