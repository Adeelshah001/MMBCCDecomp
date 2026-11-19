/* Sub_080272E0 @ 0x080272E0 (148 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36e_080272e0_MATCHED.c (registry: mmbcc/src/w36e_080272e0_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef struct {
    u8 pad0;
    u8 mode;
    u8 f2;
    u8 f3;
    u8 f4;
} S;

extern void Call4E60_4E44(int a);

extern void BitCtl_520C(int a);

extern void PalModeSet_4DFC(int a);

extern void Sub_080275B4(void);

extern void Sub_08021C2C(void);

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

extern void InitRec8_267B4(u32 *p, int kind);

typedef void (*Fn)(S *s);

__attribute__((section(".text.w36e_080272e0")))
void Sub_080272E0(S *s)
{
    u8 m = s->mode;
    switch (m) {
    case 0:
        s->mode = 1;
        s->f3 = m;
        s->f2 = m;
        Call4E60_4E44(1);
        BitCtl_520C(1);
        PalModeSet_4DFC(2);
        Sub_080275B4();
        {
            register u16 *pp __asm__("r1") = (u16 *)0x020031E0;
            register u16 mask __asm__("r0") = 0xEDFF;
            *pp &= mask;
        }
        Sub_08021C2C();
        s->f4 = 255;
        break;
    case 1: {
        EntryMgr_Teardown();
        {
            register Fn *tbl __asm__("r1") = (Fn *)0x0822D968;
            __asm__ volatile("" : "+r"(tbl));
            {
                register u8 idx __asm__("r2") = s->f2;
                register u32 off __asm__("r0") = idx << 2;
                Fn fn = *(Fn *)(off + (u32)tbl);
                fn(s);
            }
        }
        *(u16 *)0x020031F4 -= 4;
        EntryMgr_Setup();
        break;
    }
    case 2:
        InitRec8_267B4((u32 *)0x020070F0, 4);
        break;
    }
}
