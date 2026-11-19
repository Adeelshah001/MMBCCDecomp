/* Sub_08035C5C @ 0x08035C5C (328 B, ELF compiled size) — matched C from the pret-style MMBCC decomp.
 * Pret source: mmbcc/src/w40b_08035c5c_MATCHED.c (registry: mmbcc/src/w40b_08035c5c_MATCHED.c).
 * Pret compiler: old_agbcc; decompdecomp judges with its pinned agbcc -mthumb-interwork -O2.
 * Section attribute kept: the app's judge reads the symbol's own section.
 * .set alias blocks from the pret file are NOT copied here; the aliases live
 * in the manifest symbols so the judge resolves them.
 */

#include "common.h"

typedef short s16;

extern void CondRectFill_080073D4(u8 a, int b, int c, int d, int e);

extern u8 MapTableVal_499AC(int i);

extern void Task_35C1C(u8 *s);

extern void GatedDispatch(int a, int b, int c, int d, int e);

extern void Gfx_BlitRequest(int a, int b, int c, int d, int e);

extern int SDiv_0804DD08(int a, int b);

__attribute__((section(".text.w40b_08035c5c")))
void Sub_08035C5C(u8 *s)
{
    u8 i;

    for (i = 0; i <= 3; i++) {
        u8 *p = s + i * 12;
        register int f1 __asm__("r3");
        __asm__ volatile("ldrb %0, [%1]" : "=r"(f1) : "r"(p + 289));
        if (f1)
            CondRectFill_080073D4((u8)(i + 27), 3, i * 2 + 30, 4, 0);
        else {
            u8 f2 = p[288];
            if (f2)
                CondRectFill_080073D4((u8)(i + 27), 0, i * 2 + 30, 4, f1);
            else
                CondRectFill_080073D4(0, 0, i * 2 + 30, 4, f2);
        }
    }
    for (i = 0; i <= 3; i++) {
        u8 *p = s + i * 12;
        u8 f = p[336];
        if (f)
            CondRectFill_080073D4((u8)(i + 22), MapTableVal_499AC(i), (s16)(i * 2 + 30), 7, 0);
        else
            CondRectFill_080073D4(0, 0, (s16)(i * 2 + 30), 7, f);
    }
    Task_35C1C(s);
    GatedDispatch(*(u16 *)(s + 36), 41, 7, 4, 0);
    Gfx_BlitRequest(*(int *)0x0822e994, 45, 7, 1, 0);
    GatedDispatch(*(u16 *)(s + 38), 46, 7, 4, 0);
    Gfx_BlitRequest(*(int *)0x0822e99c, 50, 7, 1, 0);
    GatedDispatch(SDiv_0804DD08(*(u16 *)(s + 36) * 100, *(u16 *)(s + 38) + *(u16 *)(s + 36)), 51, 7, 3, 0);
    Gfx_BlitRequest(*(int *)0x0822e9a4, 54, 7, 1, 0);
}
