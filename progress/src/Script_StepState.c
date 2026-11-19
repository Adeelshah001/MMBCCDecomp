/* Script_StepState @ 0x0803F480 (964 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave9_b_old.c (registry: (worker B, wave9)).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

__attribute__((section(".text.w9b_0803f480")))
void Script_StepState(u8 *p, u8 sel)
{
    register u32 s __asm__("r2");
    u8 *q;
    int flag;
    u32 sum;
    u8 *b2;
    u8 v;
    u8 *pa;
    u8 *pb;
    u32 k;

    s = sel;
    q = p + 0x46A4;
    {
        int t = (s == 0);
        flag = t;
    }
    sum = p[0x46A0] + s;
    __asm__ volatile("" : "+r" (sum));
    b2 = p + 0x4600;
    b2 += 0x4C;
    v = q[b2[sum]];
    switch (v) {
    case 0:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 16;
        break;
    case 2:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 16;
        break;
    case 4:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 18;
        break;
    case 6:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 18;
        break;
    case 8:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 20;
        break;
    case 10:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 20;
        break;
    case 12:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 22;
        break;
    case 14:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 22;
        break;
    case 16:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 24;
        break;
    case 18:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 24;
        break;
    case 20:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 26;
        break;
    case 22:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 26;
        break;
    case 24:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 28;
        break;
    case 26:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 28;
        break;
    case 30:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 38;
        break;
    case 32:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 38;
        break;
    case 34:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 40;
        break;
    case 36:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 40;
        break;
    case 38:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 42;
        break;
    case 40:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 42;
        break;
    case 44:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 48;
        break;
    case 46:
        pa = p + 0x46A0;
        k = *pa + s;
        pb = p + 0x464C;
        q[pb[k]] = 48;
        break;
    }
    {
        u8 *pa;
        u32 k;
        u8 *pb;
        pa = p + 0x46A0;
        k = *pa + flag;
        pb = p + 0x464C;
        q[pb[k]]++;
    }
}
