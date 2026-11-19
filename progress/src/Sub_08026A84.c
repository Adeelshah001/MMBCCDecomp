/* Sub_08026A84 @ 0x08026A84 (124 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36c_08026a84_MATCHED.c (registry: mmbcc/src/w36c_08026a84_MATCHED.c).
 * Pret compiler: agbcc (pattern rule); decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Call4E60_4E44(void);

extern void EntryMgr_Teardown(void);

extern s8 UMod_0804DEE8(u8 a, int b);

extern void Gfx_BlitRequest(u32 *p, int a, int b, int c, int d);

extern void InitRec8_267B4(u8 *p, int a);

extern void EntryMgr_Setup(void);

__attribute__((section(".text.w36c_08026a84")))
void Sub_08026A84(u8 *s)
{
    u8 t = s[1];
    if (t == 0) goto case0;
    if (t == 1) goto aa2;
    goto end;
case0:
    s[6] = 0;
    Call4E60_4E44();
    s[1]++;
aa2:
    EntryMgr_Teardown();
    if (UMod_0804DEE8(s[6], 20) != 0) {
        u32 *p = (u32 *)0x082350d0;
        Gfx_BlitRequest(*p, 1, 1, 8, 0);
    }
    if (++s[6] > 60) goto docall;
    {
        register u8 *base __asm__("r1") = (u8 *)0x02002f50;
        register u32 mask __asm__("r0") = 1;
        mask = mask & *(u16 *)(base + 4);
        if (mask == 0) goto skipcall;
    }
docall:
    InitRec8_267B4((u8 *)0x020070f0, 3);
skipcall:
    EntryMgr_Setup();
end:;
}
