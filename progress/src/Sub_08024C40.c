/* Sub_08024C40 @ 0x08024C40 (126 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36bulk_08024c40_MATCHED.c (registry: src/w36bulk_08024c40_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int CheckPair_258D8(u8 *p, u8 arg);

extern int Sub_08025A64(u8 *p, u8 arg);

extern int GetIndexedU8(u8 *p, u8 arg);

extern int F_08025A10(u8 *p, u8 arg);

__attribute__((section(".text.w36bulk_08024c40")))
u16 Sub_08024C40(u8 *s, u8 arg)
{
    u8 *sp = s;
    u8 arg2 = arg;
    u8 t;
    {
        u32 b = *(u32 *)(sp + 20);
        t = CheckPair_258D8((u8 *)(b + *(u8 *)(b + 432) * 144), arg);
    }
    if (t == 0)
        return 0;
    if (t == 2) {
        u8 r;
        {
            u32 b = *(u32 *)(sp + 20);
            r = GetIndexedU8((u8 *)(b + *(u8 *)(b + 432) * 144), arg2);
        }
        {
            u32 b = *(u32 *)(sp + 20);
            return F_08025A10((u8 *)(b + *(u8 *)(b + 432) * 144), r);
        }
    }
    {
        u32 b = *(u32 *)(sp + 20);
        return Sub_08025A64((u8 *)(b + *(u8 *)(b + 432) * 144), arg);
    }
}
