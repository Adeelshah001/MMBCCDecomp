/* Task_SelectBlobIdx_0803AC4C @ 0x0803AC4C (252 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w30a_0803ac4c.c (registry: src/w30a_0803ac4c.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern u8 gEwram_02002F50[];

extern u8 gEwram_02004CE0[];

extern u8 gAddrZero[];

s16 Text_SelectBlobIdx(u16 idx);

__attribute__((section(".text.w30a_0803ac4c")))
u32 Task_SelectBlobIdx_0803AC4C(u8 *p) {
    u32 ret = 0;
    u16 w;
    u8 *q;
    {
        u8 *hw = gEwram_02002F50;
        w = *(u16 *)(hw + 6);
    }
    {
        u32 m = 32;
        if ((m &= w) != 0) {
            u8 *tbl;
            u8 a, b, v;
            q = p + 0x469a;
            if (*q == 0)
                goto tbl32;
            (*q)--;
            __asm__ volatile("");
            goto snd;
          tbl32:
            tbl = &gAddrZero[0x8231790];
            a = p[0x469b];
            {
                register u32 o2 __asm__("r7") = 0x4698;
                u8 *pb = p + o2;
                b = *pb;
                v = tbl[a - b];
            }
            if (v == 1)
                goto hw4;
            *q = v - 1;
            goto snd;
        }
    }
    {
        u32 m = 16;
        if ((m &= w) == 0)
            goto hw4;
        {
            u8 *tbl;
            register u32 off __asm__("r7");
            u8 *pa, *pb;
            u8 t, a, b, v;
            q = p + 0x469a;
            t = *q;
            tbl = &gAddrZero[0x8231790];
            off = 0x469b;
            pa = p + off;
            off -= 3;
            pb = p + off;
            a = *pa;
            b = *pb;
            v = tbl[a - b];
            if (t < v - 1) {
                *q = t + 1;
            } else {
                if (v == 1)
                    goto hw4;
                *q = ret;
            }
        }
    }
  snd:
    Text_SelectBlobIdx(0x66);
    ret = 3;
  hw4: {
        u16 w2;
        {
            u8 *hw = gEwram_02002F50;
            w2 = *(u16 *)(hw + 4);
        }
        {
            u32 m = 1;
            if ((m &= w2) != 0) {
                Text_SelectBlobIdx(0x67);
                ret = 1;
                goto tail;
            }
        }
        {
            u32 m = 2;
            if ((m &= w2) != 0) {
                Text_SelectBlobIdx(0x68);
                ret = 2;
            }
        }
    }
  tail: {
        u16 *g = (u16 *)gEwram_02004CE0;
        g[20] = (u16)((p[0x469a] << 4) + 72);
        __asm__ volatile("" ::: "r2");
        g[21] = (u16)((p[0x4698] << 4) + 8);
    }
    return ret;
}
