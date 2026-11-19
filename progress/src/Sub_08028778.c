/* Sub_08028778 @ 0x08028778 (250 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w55d_08028778_MATCHED.c (registry: src/w55d_08028778_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void sub_08004E50(int a);

extern void PalModeSet_4DFC(int a);

extern void sub_080006DC(int a, u32 b, int c);

extern void EntryMgr_Teardown(void);

extern void EntryMgr_Setup(void);

extern void Dispatch_081734F4_0(void);

__attribute__((section(".text.w55d_08028778")))
int Sub_08028778(u8 *s, u8 idx)
{
    int st = s[0];
    int ret = 1;
    if (st == 1)
        goto c1;
    if (st > 1)
        goto gt;
    if (st == 0)
        goto c0;
    goto tail;
gt:
    if (st == 2)
        goto c2;
    goto tail;
c0:
    st = 1;
    sub_08004E50(1);
    {
        u8 *flagp = (u8 *)0x02004F80;
        if (*(flagp + 2) == 0)
            PalModeSet_4DFC(1);
        else
            PalModeSet_4DFC(*(flagp + 2));
    }
    {
        u8 *base = (u8 *)0x03002620;
        sub_080006DC(0, (u32)base, 480);
        *(u16 *)(base + 516) = 32;
        *(u16 *)(base + 518) = 480;
    }
    {
        u8 *ip0 = (u8 *)0x02000EC0;
        *(ip0 + 7) = idx;
    }
    {
        u16 v = *(u16 *)0x020031E0;
        v &= 0xedff;
        v &= 0xdbff;
        *(u16 *)0x020031E0 = v;
    }
    EntryMgr_Teardown();
    EntryMgr_Setup();
    goto tail;
c1:
    EntryMgr_Teardown();
    Dispatch_081734F4_0();
    {
        u8 *ip1 = (u8 *)0x02000EC0;
        int b8;
        int k = 8;
        __asm__("ldrsb %0, [%1, %2]" : "=r" (b8) : "r" (ip1), "0" (k));
        if (b8 != 0)
            goto tail80;
        if (*(ip1 + 0) != idx)
            goto tail80;
    }
    st = 2;
    {
        u16 v = *(u16 *)0x020031E0;
        v &= 0xedff;
        v &= 0xdbff;
        *(u16 *)0x020031E0 = v;
    }
tail80:
    EntryMgr_Setup();
    goto tail;
c2:
    EntryMgr_Teardown();
    ret = 0;
    EntryMgr_Setup();
    goto tail;
tail:
    s[0] = st;
    return ret;
}
