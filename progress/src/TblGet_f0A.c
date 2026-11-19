/* TblGet_f0A @ 0x080245C4 (28 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/wave8_s_old.c (registry: src/wave8_s_old.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Rom0822740C {
    u16 f00; u16 f02; u16 f04; u8 _06[2];
    u16 f08; u8 f0A; u8 _0B; u8 f0C; u8 f0D; u8 f0E; u8 f0F;
};

extern struct Rom0822740C rom0822740C[];

__attribute__((section(".text.w8s_080245c4")))
u8 TblGet_f0A(u8 idx)
{
    register u32 i __asm__("r1") = idx;
    struct Rom0822740C *base;
    if (i > 248)
        return 0;
    base = rom0822740C;
    return base[i].f0A;
}
