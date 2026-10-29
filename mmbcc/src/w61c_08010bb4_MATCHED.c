/* W61-C MATCH: 0x08010bb4, TRUE extent 260 B (code through bx @0x10cb2 +
 * trailing pool @0x10cb4 = 0x020031E0; next code @0x10cb8 is a separate
 * tiny leaf). Goto-dispatch state fn (W55 28778 sibling shape):
 * dispatch on s[0]: 1 -> c1, 0 -> c0, 2 -> c2, 3 -> c3, else tail.
 * c0: if ((s8)s[14] == -1) s[0] = 2; else { s[0] = 1; s[1] = old s[0];
 *   s[15] |= 1; }
 * c1: if (Sub_28778(s+1, s[14]) == 0) s[0]++.
 * c2: s[0] = 3; Sub_4E44(); s[15] &= -2; s[13] = 1;
 *   g = 0x02004F80; if (g[2] == 0) Sub_4DFC(2); else Sub_4DFC(g[2]);
 *   Sub_16FD0(0x02004FC8, 0x020053D0, 36);
 *   *(u16*)0x020031E0 &= 0xEDFF; &= 0xDBFF; *(u16*)0x02004830 = 0;
 *   Sub_111D0(s[2]); Sub_110E0(s[2], 2);
 *   if ((s16)s[18] >= 0) Sub_BEE0((s16)s[18], 128).
 * c3: *(u16*)0x020031E0 = (144<<5) | *(u16*)0x020031E0 | (144<<6);
 *   Sub_111B4(1).
 * tail: return s[4].
 * Pools (raw LE re-derived): flag 0x02004F80; 16FD0 args 0x02004FC8 /
 * 0x020053D0; masks 0xEDFF / 0xDBFF; zero-ptr 0x02004830; trailing
 * 0x020031E0. ldrsb/ldrsh via inline asm (agbcc never emits them).
 * W61-C key vs W60-C v14 (5 diffs, all in c3's first shift): the shift
 * temp is declared int (not u16) pinned to r3, and the accumulator v is
 * pinned to r0. That makes old_agbcc emit the shift in r3 and copy it
 * to r0 (movs r3,#144; lsls r3,r3,#5; adds r0,r3,#0), exactly the ROM
 * shape; the u16-typed temp let the allocator compute the shift in r0
 * and copy it back to r3. Pure C only; no .s patch.
 * Verified: old_agbcc -O2 -mthumb-interwork, standalone linked-at-address
 * method, 260 B / 0 diffs.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef signed int s32;

extern u8 Sub_08028778(u8 *s, u8 idx);
extern void Sub_08004E44(void);
__asm__(".set Sub_08004E44, 0x08004e44");
extern void Sub_08004DFC(int a);
__asm__(".set Sub_08004DFC, 0x08004dfc");
extern void Sub_08016FD0(u32 a, u32 b, int c);
extern void Sub_080111D0(u8 a);
__asm__(".set Sub_080111D0, 0x080111d0");
extern void Sub_080110E0(u8 a, u8 b);
extern void Sub_080111B4(u32 a);
__asm__(".set Sub_080111B4, 0x080111b4");
extern void Sub_0800BEE0(u32 a, u32 b);
__asm__(".set Sub_0800BEE0, 0x0800bee0");

__attribute__((section(".text.w61c_08010bb4")))
u8 Sub_08010BB4(u8 *s)
{
    int st = s[0];
    if (st == 1)
        goto c1;
    if (st > 1)
        goto gt;
    if (st == 0)
        goto c0;
    goto tail;
gt:
    if (st == 2)
        goto c2;
    if (st == 3)
        goto c3;
    goto tail;
c0: {
    int t14;
    int k = 14;
    __asm__("ldrsb %0, [%1, %2]" : "=r" (t14) : "r" (s), "0" (k));
    if (t14 == -1) {
        s[0] = 2;
        goto tail;
    } else {
        int one = 1;
        s[0] = 1;
        s[1] = st;
        s[15] |= one;
    }
    /* FALL THROUGH into c1 (ROM: else block ends at 0xbf0 strb, c1
     * code at 0xbf2 follows with no branch between). */
}
c1:
    if (Sub_08028778(s + 1, s[14]) == 0)
        s[0]++;
    goto tail;
c2:
    s[0] = 3;
    Sub_08004E44();
    { int m = -2; s[15] &= m; }
    s[13] = 1;
    {
        u8 *gp = (u8 *)0x02004F80;
        if (gp[2] == 0)
            Sub_08004DFC(2);
        else
            Sub_08004DFC(gp[2]);
    }
    Sub_08016FD0(0x02004FC8, 0x020053D0, 36);
    {
        u16 v = *(u16 *)0x020031E0;
        v &= 0xEDFF;
        {
            int z = 0;
            v &= 0xDBFF;
            *(u16 *)0x020031E0 = v;
            *(u16 *)0x02004830 = z;
        }
    }
    Sub_080111D0(s[2]);
    Sub_080110E0(s[2], 2);
    {
        int hv;
        int k2 = 18;
        __asm__("ldrsh %0, [%1, %2]" : "=r" (hv) : "r" (s), "r" (k2));
        if (hv >= 0)
            Sub_0800BEE0(hv, 128);
    }
    goto tail;
c3:
    {
        register u16 *p __asm__("r2") = (u16 *)0x020031E0;
        register int sh __asm__("r3");
        register u16 v __asm__("r0");
        sh = 144 << 5;
        v = sh;
        v |= *p;
        v |= 144 << 6;
        *p = v;
    }
    Sub_080111B4(1);
    goto tail;
tail:
    return s[4];
}
