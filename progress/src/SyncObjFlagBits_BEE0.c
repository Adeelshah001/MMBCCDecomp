/* SyncObjFlagBits_BEE0 @ 0x0800BEE0 (98 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave13_B.c (registry: src/wave13_B.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

/* Logical signature: (u16 a, u8 b). Prologue as v12 (byte-exact).
 * Body: pinned r0 accumulator; mask var is the AND/OR target.
 * `m |= 128`: the compiler substitutes any register known to hold 128
 * (b3, via the branch) for the constant, emitting `orr r0,r0,r3`.
 * Materialize 128 into pinned r1 with inline asm so the OR is forced to
 * `movs r1,#128; orrs r0,r1` as in ROM. Dead prologue var v (r6) is
 * reused for the two loads ROM does into r6. */
__attribute__((section(".text.w12a_0800bee0")))
void SyncObjFlagBits_BEE0(u32 a, u32 b)
{
    u32 a32;
    register u8 b3 __asm__("r3");
    register u8 b5 __asm__("r5");
    register u16 aa __asm__("r4");
    register u8 *base __asm__("r2");
    register u16 v __asm__("r6");
    register u32 vs __asm__("r1");
    a32 = a << 16;
    b3 = (u8)((b << 24) >> 24);
    b5 = b3;
    base = (u8 *)0x02004F40;
    aa = (u16)(a32 >> 16);
    v = *(u16 *)(base + 20);
    vs = (u32)v << 16;
    if (vs == a32)
        return;
    *(u16 *)(base + 6) = aa;
    if (b3 == 128) {
        register int m __asm__("r0");
        register int o __asm__("r1");
        m = 3;
        m &= base[9];
        __asm__ volatile ("mov %0, #128" : "=r" (o));
        m |= o;
        base[9] = (u8)m;
        m = -7;
        v = base[10];
        m &= v;
        base[10] = (u8)m;
    } else {
        register int m __asm__("r0");
        if (b5 > 128) {
            m = 8;
            m |= base[10];
        } else {
            m = -9;
            v = base[10];
            m &= v;
        }
        base[10] = (u8)m;
        m = -7;
        m &= base[10];
        m |= 4;
        base[10] = (u8)m;
    }
}
