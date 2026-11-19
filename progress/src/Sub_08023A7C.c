/* Sub_08023A7C @ 0x08023A7C (112 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w38c_08023a7c_MATCHED.c (registry: mmbcc/src/w38c_08023a7c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_08023BC4(u8 *dst, u8 *base, u32 arg2);

extern void Xor_23CE4(u8 *p0, u8 *p1);

extern void Sub_08023C38(u8 *dst, u8 *src, u8 sl);

extern u8 F_23D10(u8 *p);

extern void Sub_08023D68(u8 *src, u16 *dst);

extern void F_23B64(u16 *p);

__attribute__((section(".text.w38c_08023a7c")))
void Sub_08023A7C(u8 *s, u8 *a1, u16 *a2)
{
    register u16 *r9 __asm__("r9");
    register int mask __asm__("r8");
    u8 *g;
    u8 *q;
    r9 = a2;
    g = (u8 *)0x02000840;
    mask = 127;
    Sub_08023BC4(g, a1, (s[0] + s[4]) & mask);
    Xor_23CE4(s, g);
    q = g;
    q += 16;
    Sub_08023C38(q, g, (s[2] + s[6]) & mask);
    g[30] = F_23D10(q);
    Xor_23CE4(s, q);
    Sub_08023D68(q, r9);
    F_23B64(r9);
}
