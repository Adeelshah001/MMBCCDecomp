/* Sub_08022F48 @ 0x08022F48 (64 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w35c_08022f48_MATCHED.c (registry: mmbcc/src/w35c_08022f48_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern int EwramLookup_26D94(void);

extern void ChipSlot_Tick(u8 *s);

__attribute__((section(".text.w35c_08022f48")))
void Sub_08022F48(u8 *s)
{
    if ((--s[18] << 24) == 0)
        goto TABLE;
    if (((EwramLookup_26D94() << 24) >> 24) <= 2)
        goto FINAL;
TABLE:
    {
        register u32 *tbl __asm__("r1") = (u32 *)0x08226ef0;
        register u8 idx __asm__("r2") = s[9];
        register u32 off __asm__("r0");
        u32 *ent;
        __asm__ volatile("" : "+r"(tbl));
        off = idx << 2;
        ent = (u32 *)(off + (u32)tbl);
        *(u32 *)(s + 12) = 2;
        *(u32 *)(s + 20) = *(u32 *)((u8 *)*ent + 8);
    }
FINAL:
    ChipSlot_Tick(s);
}
