/* Sub_08046904 @ 0x08046904 (92 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36a_08046904_MATCHED.c (registry: mmbcc/src/w36a_08046904_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef signed short s16;

extern void ChipSlot_InitEntry(u8 *a, u8 *b, u32 c, u32 d);

extern void Call4E60_4E44(void);

extern void PalModeSet_4DFC(u32 a);

extern void SyncObjFlagBits_BEE0(u32 a, u32 b);

extern void Text_SelectBlobU16(u32 a);

extern void Sub_08046960(u8 *a);

__attribute__((section(".text.w36a_08046904")))
void Sub_08046904(u8 *arg0)
{
    u8 *pool = (u8 *)0x0200b7a8;
    u8 *p = pool;
    s16 i;
    u8 *m92;
    i = 0;
    m92 = pool - 92;
    for (; (u16)i <= 15; i++) {
        *p++ = 0;
    }
    ChipSlot_InitEntry(pool + 4, m92, 4, 0);
    Call4E60_4E44();
    PalModeSet_4DFC(2);
    SyncObjFlagBits_BEE0(63, 128);
    arg0[2]++;
    Text_SelectBlobU16(3);
    Sub_08046960(arg0);
}
