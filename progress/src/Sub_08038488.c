/* Sub_08038488 @ 0x08038488 (152 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_08038488_MATCHED.c (registry: mmbcc/src/w37c_08038488_MATCHED.c).
 * Pret compiler: agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 Dispatch4_R3(u8 *s, u32 b, u32 c);

extern void sub_08028880(u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);

extern void LoadCallClear_4A328(void);

__attribute__((section(".text.w37c_08038488")))
int Sub_08038488(u8 *s)
{
    int flag = 0;
    if (Dispatch4_R3(s, *(u16 *)(s + 0x469a), s[0x469f]) != 0) {
        u8 *g = (u8 *)0x0200b810;
        u8 save = g[7];
        s[0x46a0] = flag;
        sub_08028880(4096, *(u16 *)(s + 0x469a), s[0x469f], 8,
                     *(u8 *)(s + 0x46a1), flag);
        g[7] = save;
        LoadCallClear_4A328();
        s[0x469c] = 4;
        s[0x469d] = flag;
        flag = 1;
    }
    return flag;
}
