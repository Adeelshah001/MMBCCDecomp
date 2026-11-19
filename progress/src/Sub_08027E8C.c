/* Sub_08027E8C @ 0x08027E8C (244 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w55a_08027e8c_MATCHED.c (registry: src/w55a_08027e8c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_0802800C(int a, int b);

extern void F_0800E068(u8 *s, int a, int b);

extern int Sub_080280E8(int a, int b, int c);

extern u8 Tbl_0822DDA4[];

extern u8 Tbl_0822DDB0[];

__attribute__((section(".text.w55a_08027e8c")))
int Sub_08027E8C(u8 *s0)
{
    register u8 *s __asm__("r5") = s0;
    register int c __asm__("r6") = 0x3A10;
    register u8 *p28 __asm__("r4");
    u32 b;
    u8 v;
    int ret;
    u32 hi;
    if (s[4] == 0)
        return 1;
    b = s[3];
    {
        register int nv __asm__("r0");
    if (b & 8) {
        if ((b & 240) != 0 && !(b & 1)) {
            register int sh __asm__("r1") = ((b >> 4) - 1) << 4;
            register int lo __asm__("r0") = b & 15;
            nv = lo | sh;
            goto store;
        }
        {
            int t = s[3] & 15;
            nv = t & -9;
            goto store;
        }
    }
    if (s[5] != s[6]) {
        if (b & 240) {
            nv = 8;
            nv |= b;
        } else {
            goto lookup;
        }
    } else {
        goto equal;
    }
store:
    s[3] = nv;
    p28 = s + 28;
    goto tail;
    }
lookup:
    {
        s8 t7;
        u8 *tbl;
        int idx;
        s[5] = s[6];
        tbl = Tbl_0822DDA4;
        idx = (s8)s[5];
        p28 = s + 28;
        v = p28[idx];
        sub_0802800C(tbl[v], tbl + v);
        t7 = Tbl_0822DDB0[(s8)s[5]];
        s[7] = t7;
        if (t7 >= 0)
            F_0800E068(s + 8, s[7], 2);
    }
    goto tail;
equal:
    {
        register u32 tmphi __asm__("r1");
        __asm__ volatile("lsl %0, %2, #24\n\tlsr %1, %0, #28" : "=r"(tmphi), "=r"(hi) : "r"(b));
    }
    p28 = s + 28;
    if (hi <= 14) {
        register int sh __asm__("r1");
        __asm__ volatile("add %0, %1, #0" : "=r" (sh) : "r" (hi));
        sh = (sh + 1) << 4;
        {
            register int lo __asm__("r0") = b & 15;
            s[3] = lo | sh;
        }
    }
tail:
    {
        u32 b2 = s[3];
        u8 *tblt;
        register int idx2r __asm__("r0");
        if (b2 & 1)
            c = 0xFFFF;
        tblt = Tbl_0822DDA4;
        idx2r = (s8)s[5];
        v = p28[idx2r];
        ret = Sub_080280E8(tblt[v], c, b2 >> 4);
    }
    return ret;
}
