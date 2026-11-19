/* F_08003e80 @ 0x08003E80 (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w41b_08003e80_MATCHED.c (registry: mmbcc/src/w41b_08003e80_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;
typedef signed int s32;

extern s32 SDiv_0804DD08(s32 a, s32 b);

#define LDRSH(dst, base, off) \
    __asm__("ldrsh %0, [%1, %2]" : "=r"(dst) : "r"(base), "r"(off))

__attribute__((section(".text.w41b_08003e80")))
void F_08003e80(u8 *s, u8 v) {
    register u8 *sp __asm__("r6");
    register u8 vv __asm__("r8");
    u8 *e;
    u8 x;
    int t;
    int idx;

    sp = s;
    vv = v;
    {
    register u8 *base __asm__("r4");
    register u16 *tbl __asm__("r5");
    register int ff __asm__("r3");
    u8 *q2, *q3, *q4;
    register u32 sh2 __asm__("r2");
    register u32 sh3 __asm__("r2");
    register u32 sh4 __asm__("r2");
    {
    u32 sh = ((((u32)sp[19] << 26) >> 27) << 5);
    base = (u8 *)0x03002830;
    e = (u8 *)(sh + (u32)base);
    }
    tbl = (u16 *)0x0804e05c;
    x = sp[24] ^ sp[25];
    t = (((x << 8) - x) ^ vv) + x;
    ff = 255;
    idx = t & ff;
    idx += 64;
    ((s16 *)e)[3] = tbl[idx];

    sh2 = ((((u32)sp[19] << 26) >> 27) << 5);
    q2 = (u8 *)(sh2 + (u32)base);
    x = sp[24] ^ sp[25];
    t = (((x << 8) - x) ^ vv) + x;
    idx = t & ff;
    idx += 64;
    ((s16 *)q2)[15] = tbl[idx];

    sh3 = ((((u32)sp[19] << 26) >> 27) << 5);
    q3 = (u8 *)(sh3 + (u32)base);
    x = sp[24] ^ sp[25];
    t = (((x << 8) - x) ^ vv) + x;
    ((s16 *)q3)[7] = tbl[t & ff];

    sh4 = ((((u32)sp[19] << 26) >> 27) << 5);
    q4 = (u8 *)(sh4 + (u32)base);
    x = sp[24] ^ sp[25];
    t = (((x << 8) - x) ^ vv) + x;
    ((s16 *)q4)[11] = -tbl[t & ff];
    }

    {
    register int n __asm__("r5");
    register s32 v6 __asm__("r4");
    register s32 v22 __asm__("r4");
    int off;
    s32 tmp;
    s32 v14, v30;
    register int mask __asm__("r1");
    register int b24 __asm__("r5");
    register int b25 __asm__("r5");
    n = *(u16 *)(sp + 28);
    if ((((n - 1) | n) + 1) == (n * 2)) n++;
    off = 6;
    LDRSH(tmp, e, off);
    v6 = SDiv_0804DD08(tmp << 8, n);
    ((s16 *)e)[3] = v6;
    off = 14;
    LDRSH(tmp, e, off);
    v14 = SDiv_0804DD08(tmp << 8, n);
    ((s16 *)e)[7] = v14;
    b24 = sp[24];
    mask = ((int)b24 << 31) >> 31;
    v6 ^= mask;
    v6 += b24;
    ((s16 *)e)[3] = v6;
    v14 = (mask ^ v14) + b24;
    ((s16 *)e)[7] = v14;

    n = *(u16 *)(sp + 30);
    if ((((n - 1) | n) + 1) == (n * 2)) n++;
    off = 22;
    LDRSH(tmp, e, off);
    v22 = SDiv_0804DD08(tmp << 8, n);
    ((s16 *)e)[11] = v22;
    off = 30;
    LDRSH(tmp, e, off);
    v30 = SDiv_0804DD08(tmp << 8, n);
    ((s16 *)e)[15] = v30;
    b25 = sp[25];
    mask = ((int)b25 << 31) >> 31;
    v22 ^= mask;
    v22 += b25;
    ((s16 *)e)[11] = v22;
    v30 = (mask ^ v30) + b25;
    ((s16 *)e)[15] = v30;
    }

    sp[27] = vv;
}
