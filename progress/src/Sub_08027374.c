/* Sub_08027374 @ 0x08027374 (140 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w36d_08027374_MATCHED.c (registry: mmbcc/src/w36d_08027374_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern void Sub_0802756C(void);

extern u8 Cmp_08004E0C(u32 a);

extern u32 BuildList_08021D10(void);

extern u8 Byte19_Bits3F_Set(u32 a);

extern void Text_SelectBlobU16(u32 a);

__attribute__((section(".text.w36d_08027374")))
void Sub_08027374(u8 *s)
{
    switch (s[3]) {
    case 0:
        s[3] = 1;
        Sub_0802756C();
        *(u16 *)0x020031e0 |= 4608;
        /* fall through */
    case 1:
        if (Cmp_08004E0C(0) == 0)
            break;
        s[3]++;
        /* fall through */
    case 2: {
        u32 v = BuildList_08021D10();
        if (v == 0)
            break;
        *(u32 *)(s + 0x4698) = v;
        s[3]++;
        /* fall through */
    }
    case 3:
        if (Byte19_Bits3F_Set(*(u32 *)(s + 0x4698)) == 0)
            break;
        {
            u32 f2new = s[2] + 1;
            u32 zero = 0;
            s[2] = f2new;
            s[3] = zero;
        }
        Text_SelectBlobU16(5);
        break;
    default:
        break;
    }
}
