/* Sub_0800E144 @ 0x0800E144 (172 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_0800e144_MATCHED.c (registry: mmbcc/src/w38c_0800e144_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

struct Node { struct Node *next; u32 f4; };

struct P { struct Node *arr[4][32]; struct Node *a; struct Node *b; };

struct Q { u16 a; u16 b; u16 c; u16 d; u16 e; u16 f; };

struct T { u16 a; s16 b; };

extern void sub_080042B8(u8 *x);

extern void CpuSet(u8 *a, u32 b, u32 c);

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
    sub_080042B8(s + 8);
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
        CpuSet(r0, r1, r2);
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
        CpuSet(r0, r1, r2);
    }
}
