/* Sub_08011EB0 @ 0x08011EB0 (116 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36b_08011eb0_MATCHED.c (registry: mmbcc/src/w36b_08011eb0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

struct Ent { u32 pad; u32 f4; };

struct S { u8 pad0[9]; u8 f9; u8 f10; u8 pad11; u32 f12; u8 pad16[4]; u32 f20; u8 pad24[11]; u8 f35; u8 pad36[72]; u32 f108; };

extern void ChipSlot_Setup(struct S *s, int m, int z);

extern void ChipSlot_IncUse(struct S *s, int z);

extern void Sub_0801D070(int a, struct S *s, u32 *buf, int n);

extern void Sub_08011F24(struct S *s);

__attribute__((section(".text.w36b_08011eb0")))
void Sub_08011EB0(struct S *s)
{
    struct Ent **addr = ((struct Ent **)0x08223cc0) + s->f9;
    s->f12 = 1;
    s->f20 = (*addr)->f4;
    s->f108 = 0;
    s->f10 = 2 | s->f10;
    s->f10 = 1 | s->f10;
    {
        int m = (s->f35 & 15) ? 256 : 0;
        ChipSlot_Setup(s, m, 0);
    }
    ChipSlot_IncUse(s, 0);
    {
        u32 buf[2] = {0, 0};
        Sub_0801D070(0, s, buf, 12);
    }
    Sub_08011F24(s);
}
