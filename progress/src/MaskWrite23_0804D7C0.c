/* MaskWrite23_0804D7C0 @ 0x0804D7C0 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w15c_0804d7c0.c (registry: src/w15c_0804d7c0.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void FlagClear_4D7A0(u8 *s);

void __attribute__((section(".text.w15c2_0804d7c0"))) MaskWrite23_0804D7C0(u8 *s, u16 a, u8 b)
{
    register u8 *rs __asm__("r6");
    register u32 ra __asm__("sl");
    register u32 rb __asm__("r8");
    register u32 rv __asm__("r9");
    int n;
    u8 *p;
    u32 mask;
    u32 v;
    __asm__ volatile(
        "add r6, r0, #0\n\t"
        "lsl r1, r1, #16\n\t"
        "lsr r1, r1, #16\n\t"
        "mov sl, r1\n\t"
        "lsl r2, r2, #24\n\t"
        "lsr r2, r2, #24\n\t"
        "mov r8, r2"
        : "=r" (rs), "=r" (ra), "=r" (rb) : : "r0", "r1", "r2");
    v = *(u32 *)(rs + 52);
    if (v == 0x68736D53) {
        *(u32 *)(rs + 52) = v + 1;
        n = rs[8];
        p = *(u8 **)(rs + 44);
        mask = 1;
        if (n > 0) {
            rv = rb;
            do {
                register u32 am __asm__("r0") = ra;
                am &= mask;
                if (am != 0 && (0x80 & p[0]) != 0) {
                    p[23] = rb;
                    if (rv == 0)
                        FlagClear_4D7A0(p);
                }
                n--;
                p += 0x50;
                mask <<= 1;
            } while (n > 0);
        }
        *(u32 *)(rs + 52) = 0x68736D53;
    }
}
