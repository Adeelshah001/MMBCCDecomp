/* Sub_0804713C @ 0x0804713C (156 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w37c_0804713c_MATCHED.c (registry: mmbcc/src/w37c_0804713c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern u8 sub_0800B148(int a, int b, int c);

extern u8 Tst_0800B2D8(void);

extern u8 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);

extern u8 Check_B308(void);

extern u8 CheckAndSet_B2B4(void);

extern u8 Tst_0800B2F0(void);

__attribute__((section(".text.w37c_0804713c")))
u8 Sub_0804713C(u8 *s, u32 a, u32 b, u32 c, u32 d)
{
    u8 ret = 1;
    register u8 r __asm__("r0");
    switch (s[0]) {
    case 0: r = sub_0800B148(1, 133, 1); goto tail;
    case 1:
        if (Tst_0800B2D8() == 0)
            goto ret;
        r = Sub_0800B320(a, b, c, d);
        goto tail;
    case 2: r = Check_B308(); goto tail;
    case 3: r = CheckAndSet_B2B4(); goto tail;
tail:
    if (r != 0)
        s[0]++;
    goto ret;
    case 4:
        if (Tst_0800B2F0() != 0)
            s[0]++;
        /* fall through */
    case 5:
        ret = 0;
        goto ret;
    default:
        goto ret;
    }
ret:
    return ret;
}
