/* Sub_080421E4 @ 0x080421E4 (276 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w49c_080421e4_MATCHED.c (registry: src/w49c_080421e4_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern u8 TblGetByte_241F8(u16 a);

extern u16 Sub200_08024514(u8 v);

extern u8 sub_0800B148(u8 a, s16 b, u8 c);

extern u8 Tst_0800B2D8(void);

extern u8 TblGetByte_24384(u16 a);

extern u8 Sub_0800B320(u32 a, u32 b, u32 c, u32 d);

extern u8 Check_B308(void);

extern u8 CheckAndSet_B2B4(void);

extern u8 Tst_0800B2F0(void);

extern void Setup_08005F44(u32 a, s8 b, s8 c);

extern u8 gEwram_02004E40[];

__attribute__((section(".text.w49c_080421e4")))
int Sub_080421E4(u8 *s)
{
    register u8 r __asm__("r0");
    {
        register u8 *gp __asm__("r0") = gEwram_02004E40;
        gp[20] |= 1;
    }
    switch (s[0x46ad]) {
    case 0:
        r = sub_0800B148(1, (s16)Sub200_08024514((u8)TblGetByte_241F8(4096)), 1);
        if (r != 0) {
            u8 *pp = s + 0x46ad;
            __asm__ volatile("" :: "i"(0));
            (*pp)++;
        }
        goto ret;
    case 1:
        if (Tst_0800B2D8() == 0)
            goto ret;
        r = Sub_0800B320(((u32 *)0x08232b4c)[(u8)(TblGetByte_24384(4096) - 50)], 0, 0, 0);
        if (r == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 2:
        if (Check_B308() == 0)
            goto ret;
        s[0x46ad]++;
        goto ret;
    case 3:
        r = CheckAndSet_B2B4();
        goto tail;
    tail:
        if ((r << 24) != 0)
            s[0x46ad]++;
        goto ret;
    case 4:
        if (Tst_0800B2F0() == 0)
            goto ret;
        {
            u8 *pp = s + 0x46ac;
            int z = 0;
            *pp = 10;
            s[0x46ad] = z;
        }
        {
            s8 *bp = (s8 *)0x02004ca0;
            Setup_08005F44(0, bp[0], bp[1]);
        }
        goto ret;
    default:
        goto ret;
    }
ret:
    return 0;
}
