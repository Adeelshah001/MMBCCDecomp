/* F_0800E068 @ 0x0800E068 (220 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w42c_0800e068_MATCHED.c (registry: mmbcc/src/w42c_0800e068_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

void Init_08004244(void *s, void *pp);

void sub_08004258(u8 *p, u8 idx);

void CpuSet(void *src, void *dst, u32 count);

__attribute__((section(".text.w42c_0800e068")))
void F_0800E068(u8 *s, u8 a, u16 b)
{
    u32 *tbl1 = (u32 *)0x086f0934;
    u32 *tbl2 = (u32 *)0x086f190c;
    u8 *q;
    u8 *p;
    u8 p1;
    u16 ucnt;
    s16 cnt;
    u32 f16;
    *(u32 *)(s + 0) = tbl1[a] + (u32)&tbl1[a];
    q = (u8 *)tbl2[a];
    *(u32 *)(s + 4) = (u32)q;
    *(u32 *)(s + 16) = b * 32;
    Init_08004244(s + 8, q);
    sub_08004258(s + 8, 0);
    p = *(u8 **)(s + 0);
    p1 = p[1];
    ucnt = p[2] - p1 + 1;
    cnt = ucnt;
    f16 = *(u32 *)(s + 16);
    if ((f16 & 0x1ff) == 0) {
        u32 *tbl = *(u32 **)(s + 8);
        u32 *entp = &tbl[s[12]];
        int off;
        u8 byte;
        u8 *src;
        u8 *dst;
        __asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]" : "=r" (off) : "r" (s));
        byte = *(u8 *)(*entp + off * 2);
        {
            int off2 = byte * cnt * 2 + 4;
            src = p + off2;
        }
        dst = (u8 *)(p1 * 2 + f16 + 0x03002420);
        CpuSet(src, dst, cnt & 0x1fffff);
    } else {
        u32 *tbl = *(u32 **)(s + 8);
        u32 *entp = &tbl[s[12]];
        int off;
        u8 byte;
        u8 *src;
        u8 *dst;
        __asm__ volatile("movs %0, #13\n\tldrsb %0, [%1, %0]" : "=r" (off) : "r" (s));
        byte = *(u8 *)(*entp + off * 2);
        {
            int off2 = byte * cnt * 2 + 4;
            src = p + off2;
        }
        dst = (u8 *)(((p1 * 2 + f16) & 0x3ff) + 0x03002420);
        CpuSet(src, dst, cnt & 0x1fffff);
    }
}
