/* W37-C BLOCKED (parked, see RESULTS): 0x0800e144, 172 B.
 * Duplicated-branch call on
 * struct *s, returns void. P = s[0]; P1 = P[1]; P2 = P[2];
 * r3 = (s16)(P2 - P1 + 1); Q = s[16]; T = s[8]; idx = s[12];
 * byte = *(u8 *)(*(u32 *)(T + idx*4) + (s8)s[13]*2);
 * r0 = P + byte*r3*2 + 4; r2 = r3 & 0x1fffff;
 * if ((Q & 511) == 0): r1 = Q + P1*2 + 0x03002420;
 * else: r1 = ((Q + P1*2) & 1023) + 0x03002420;
 * F(r0, r1, r2) in both branches (computation duplicated, not
 * shared — ROM duplicates the whole block in each branch).
 * Extern callees + addresses: F_080042B8 0x080042b8 (check),
 * F_0804DB28 0x0804db28 (check).
 * Pools (LE): 0x1ff (511), 0x03002420, 0x1fffff, 0x3ff (1023).
 */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef signed int s32;
typedef unsigned int u32;

extern void F_080042B8(u8 *x);
__asm__(".set F_080042B8, 0x080042b8");
extern void F_0804DB28(u8 *a, u32 b, u32 c);
__asm__(".set F_0804DB28, 0x0804db28");

__attribute__((section(".text.w38c_0800e144")))
void Sub_0800E144(u8 *s)
{
    u8 *P;
    u8 P1;
    s16 r3;
    u32 Q;
    u8 *T;
    u8 idx;
    u8 byte;
    u8 *r0;
    u32 r1;
    u32 r2;
    F_080042B8(s + 8);
    P = *(u8 **)s;
    P1 = P[1];
    r3 = (s16)(P[2] - P1 + 1);
    Q = *(u32 *)(s + 16);
    if ((Q & 511) == 0) {
        int t;
        register u32 pool __asm__("r2");
        T = *(u8 **)(s + 8);
        idx = s[12];
        byte = *(u8 *)(*(u32 *)(T + idx * 4) + (s8)s[13] * 2);
        t = byte * r3 * 2;
        t += 4;
        r0 = P + t;
        r1 = P1 * 2;
        r1 += Q;
        pool = 0x03002420;
        __asm__ volatile("" : "+r"(pool));
        r1 += pool;
        r2 = r3 & 0x1fffff;
        F_0804DB28(r0, r1, r2);
    } else {
        int t;
        register u32 pool __asm__("r2");
        T = *(u8 **)(s + 8);
        idx = s[12];
        byte = *(u8 *)(*(u32 *)(T + idx * 4) + (s8)s[13] * 2);
        t = byte * r3 * 2;
        t += 4;
        r0 = P + t;
        r1 = P1 * 2;
        r1 += Q;
        r1 &= 1023;
        pool = 0x03002420;
        __asm__ volatile("" : "+r"(pool));
        r1 += pool;
        r2 = r3 & 0x1fffff;
        F_0804DB28(r0, r1, r2);
    }
}
