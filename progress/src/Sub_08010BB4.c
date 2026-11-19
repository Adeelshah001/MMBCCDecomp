/* Sub_08010BB4 @ 0x08010BB4 (260 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w61c_08010bb4_MATCHED.c (registry: staging/w61c_blocked/w61c_08010bb4_MATCH.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 Sub_08028778(u8 *s, u8 idx);

extern void Call4E60_4E44(void);

extern void PalModeSet_4DFC(int a);

extern void Sub_08016FD0(u32 a, u32 b, int c);

extern void sub_080111D0(u8 a);

extern void Sub_080110E0(u8 a, u8 b);

extern void sub_080111B4(u32 a);

extern void SyncObjFlagBits_BEE0(u32 a, u32 b);

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
    Call4E60_4E44();
    { int m = -2; s[15] &= m; }
    s[13] = 1;
    {
        u8 *gp = (u8 *)0x02004F80;
        if (gp[2] == 0)
            PalModeSet_4DFC(2);
        else
            PalModeSet_4DFC(gp[2]);
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
    sub_080111D0(s[2]);
    Sub_080110E0(s[2], 2);
    {
        int hv;
        int k2 = 18;
        __asm__("ldrsh %0, [%1, %2]" : "=r" (hv) : "r" (s), "r" (k2));
        if (hv >= 0)
            SyncObjFlagBits_BEE0(hv, 128);
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
    sub_080111B4(1);
    goto tail;
tail:
    return s[4];
}
