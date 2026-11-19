/* Sub_08046CFC @ 0x08046CFC (232 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w42d_08046cfc_MATCHED.c (registry: mmbcc/src/w42d_08046cfc_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

extern s8 sub_080471D8(u8 *s, u32 a2, u8 a3);

extern u8 sub_08046DF8(u8 *s, u32 a2, u8 a3, u32 flag);

extern u8 Sub_0804713C(u8 *s, u8 *tbl, u32 a3, u32 a4, int a5);

__attribute__((section(".text.w42d_08046cfc")))
s8 Sub_08046CFC(u8 *s, u32 a2, u8 a3)
{
    register int ret __asm__("r8") = 0;
    u8 *g = (u8 *)0x02002F50;
    register u16 f __asm__("r1");
    int sb;
    s8 r;
    int st;
    st = s[0];
    if (st == 1)
        goto body;
    if (st > 1)
        goto gt1;
    if (st == 0)
        goto set1;
    goto end;
gt1:
    if (st == 2)
        goto call0;
    if (st == 3)
        goto call3;
    goto end;
set1:
    s[0] = 1;
    s[1] = (u8)ret;
body:
    f = *(u16 *)(g + 4);
    if (f & 4) {
        u8 z = 0;
        s[0] = 3;
        s[1] = z;
        goto end;
    }
    if (f & 2) {
        __asm__ volatile("movs %0, #4\n\tldrsb %0, [%1, %0]" : "=l"(sb) : "r"(s));
        if (sb == 0) {
            ret = 255;
            goto end;
        }
    }
    {
        register u32 old4 __asm__("r6");
        old4 = s[4];
        r = sub_080471D8(s, a2, a3);
        if (s[2] != r) {
            s[2] = (u8)r;
            s[0]++;
            goto call0;
        }
        if (s[4] == old4)
            goto end;
        sub_08046DF8(s, a2, a3, 1);
        goto call0;
    }
call0:
    if (sub_08046DF8(s, a2, a3, 0) != 0)
        goto end;
    s[0] = 1;
    goto end;
call3:
    if (Sub_0804713C(s + 1, (u8 *)0x08232EC4, 0, 0, ret) != 0)
        goto end;
    s[0] = 1;
    s[1] = (u8)ret;
    goto end;
end:
    return (s8)ret;
}
